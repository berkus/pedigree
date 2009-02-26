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

#include <log.h>
#include <Debugger.h>
#include "PageFaultHandler.h"
#include <process/Scheduler.h>
#include <panic.h>

PageFaultHandler PageFaultHandler::m_Instance;

#define PAGE_FAULT_EXCEPTION  0x0E

bool PageFaultHandler::initialise()
{
  InterruptManager &IntManager = InterruptManager::instance();

  return(IntManager.registerInterruptHandler(PAGE_FAULT_EXCEPTION, this));
}

void PageFaultHandler::interrupt(size_t interruptNumber, InterruptState &state)
{
  uint32_t cr2;
  asm volatile("mov %%cr2, %%eax" : "=a" (cr2));

  static LargeStaticString e;
  e.clear();
  e.append("Page Fault Exception at 0x");
  e.append(cr2, 16, 8, '0');
  e.append(", error code 0x");
  e.append(state.m_Errorcode, 16, 8, '0');
  ERROR(static_cast<const char*>(e));

  #ifdef DEBUGGER
    Debugger::instance().start(state, e);
  #endif

  Scheduler &scheduler = Scheduler::instance();
  if(UNLIKELY(scheduler.getNumProcesses() == 0))
  {
    //  We are in the early stages of the boot process (no processes started)
    panic(e);
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