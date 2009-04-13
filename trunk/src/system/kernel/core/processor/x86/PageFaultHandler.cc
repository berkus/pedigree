/*
 * Copyright (c) 2008 James Molloy, Jörg Pfähler, Matthew Iselin
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <Log.h>
#include <Debugger.h>
#include <processor/PageFaultHandler.h>
#include <process/Scheduler.h>
#include <panic.h>
#include <processor/PhysicalMemoryManager.h>

PageFaultHandler PageFaultHandler::m_Instance;

#define PAGE_FAULT_EXCEPTION  0x0E
#define PFE_PAGE_PRESENT      0x01
#define PFE_ATTEMPTED_WRITE   0x02
#define PFE_USER_MODE         0x04
#define PFE_RESERVED_BIT      0x08
#define PFE_INSTRUCTION_FETCH 0x10

bool PageFaultHandler::initialise()
{
  InterruptManager &IntManager = InterruptManager::instance();

  return(IntManager.registerInterruptHandler(PAGE_FAULT_EXCEPTION, this));
}

void PageFaultHandler::interrupt(size_t interruptNumber, InterruptState &state)
{
  uint32_t cr2, code;
  asm volatile("mov %%cr2, %%eax" : "=a" (cr2));
  code = state.m_Errorcode;

  uintptr_t page = cr2 & ~(PhysicalMemoryManager::instance().getPageSize()-1);

  // Check for copy-on-write.
  VirtualAddressSpace &va = Processor::information().getVirtualAddressSpace();
  if (va.isMapped(reinterpret_cast<void*>(page)))
  {
    physical_uintptr_t phys;
    size_t flags;
    va.getMapping(reinterpret_cast<void*>(page), phys, flags);
    if (flags & VirtualAddressSpace::CopyOnWrite)
    {
      static uint8_t buffer[/*PhysicalMemoryManager::instance().getPageSize()*/4096];
      memcpy(buffer, reinterpret_cast<uint8_t*>(page), PhysicalMemoryManager::instance().getPageSize());

      // Now that we've saved the page content, we can make a new physical page and map it.
      physical_uintptr_t p = PhysicalMemoryManager::instance().allocatePage();
      if (!p)
      {
        FATAL("PageFaultHandler: Out of memory!");
        return;
      }
      va.unmap(reinterpret_cast<void*>(page));
      if (!va.map(p, reinterpret_cast<void*>(page), VirtualAddressSpace::Write))
      {
        FATAL("PageFaultHandler: map() failed.");
        return;
      }
      memcpy(reinterpret_cast<uint8_t*>(page), buffer, PhysicalMemoryManager::instance().getPageSize());
      return;
    }
  }

  // Check our handler list.
  for (List<MemoryTrapHandler*>::Iterator it = m_Handlers.begin();
       it != m_Handlers.end();
       it++)
  {
    if ((*it)->trap(cr2, code & PFE_ATTEMPTED_WRITE))
    {
//      NOTICE("Page fault at " << Hex << cr2 << " : handled.");
      return;
    }
  }

  //  Get PFE location and error code
  static LargeStaticString sError;
  sError.clear();
  sError.append("Page Fault Exception at 0x");
  sError.append(cr2, 16, 8, '0');
  sError.append(", error code 0x");
  sError.append(code, 16, 8, '0');

  //  Extract error code information
  static LargeStaticString sCode;
  sCode.clear();
  sCode.append("Details: ");

  if(!(code & PFE_PAGE_PRESENT)) sCode.append("NOT ");
  sCode.append("PRESENT | ");

  if(code & PFE_ATTEMPTED_WRITE)
    sCode.append("WRITE | ");
  else
    sCode.append("READ | ");

  if(code & PFE_USER_MODE) sCode.append("USER "); else sCode.append("KERNEL ");
  sCode.append("MODE | ");

  if(code & PFE_RESERVED_BIT) sCode.append("RESERVED BIT SET | ");
  if(code & PFE_INSTRUCTION_FETCH) sCode.append("FETCH |");

  // Ensure the log spinlock isn't going to die on us...
//  Log::instance().m_Lock.release();

  ERROR(static_cast<const char*>(sError));
  ERROR(static_cast<const char*>(sCode));

  //static LargeStaticString eCode;
  #ifdef DEBUGGER
    Debugger::instance().start(state, sError);
  #endif

  Scheduler &scheduler = Scheduler::instance();
  if(UNLIKELY(scheduler.getNumProcesses() == 0))
  {
    //  We are in the early stages of the boot process (no processes started)
    panic(sError);
  }
  else
  {
    //  Unrecoverable PFE in a process - Kill the process and yield
    Processor::information().getCurrentThread()->getParent()->kill();

    //  kill member function also calls yield(), so shouldn't get here.
    for(;;) ;
  }

  //  Currently, no code paths return from a PFE.
}

PageFaultHandler::PageFaultHandler()
{
}
