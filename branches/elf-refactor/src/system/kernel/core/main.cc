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

// If we're being called standalone, we don't get passed any BootstrapInfo.
#include "BootstrapInfo.h"

#ifdef DEBUGGER
  #include <Debugger.h>
#endif

#include <Log.h>
#include <panic.h>
#include <utilities/StaticString.h>
#include "cppsupport.h"                   // initialiseConstructors()
#include <processor/Processor.h>          // Processor::initialise1(), Processor::initialise2()
#include <machine/Machine.h>              // Machine::initialise()
#include <KernelElf.h>                    // KernelElf::initialise()
#include <Version.h>
#include <LocalIO.h>
#include <SerialIO.h>
#include <DebuggerIO.h>
#include "BootIO.h"
#include <processor/PhysicalMemoryManager.h>
#ifdef THREADS
#include <process/initialiseMultitasking.h>
#include <process/Thread.h>
#include <processor/PhysicalMemoryManager.h>
#include <process/Scheduler.h>
#endif
#include <Archive.h>

#include <machine/Device.h>

#include <machine/openfirmware/Device.h>

#include <processor/KernelCoreSyscallManager.h>
#include <utilities/List.h>

BootIO bootIO;

/** Kernel entry point for application processors (after processor/machine has been initialised
    on the particular processor */
void apMain()
{
  NOTICE("apMain()");
  Processor::halt();
}

int foo(void *p)
{
  HugeStaticString str;
  int j=0;
  for (;;)
  {
    for(int i = 0; i < 10000000; i++) ;
    str.clear();
    str += "b";
    bootIO.write(str, BootIO::White, BootIO::Green);
    j++;
  }
  return 0;
}

int bar(void *p)
{
  HugeStaticString str;
  for (;;)
  {
    for(int i = 0; i < 10000000; i++) ;
    str.clear();
    str += "c";
    bootIO.write(str, BootIO::White, BootIO::Red);
  }
  return 0;
}

/// Kernel entry point.
extern "C" void _main(BootstrapStruct_t &bsInf)
{
  // Firstly call the constructors of all global objects.
  initialiseConstructors();

  // Initialise the processor-specific interface
  Processor::initialise1(bsInf);

  // Initialise the Kernel Elf class
  if (KernelElf::instance().initialise(bsInf) == false)
    panic("KernelElf::initialise() failed");
  
  // Initialise the machine-specific interface
  Machine &machine = Machine::instance();
  machine.initialise();
  
#if defined(DEBUGGER)
  Debugger::instance().initialise();
#endif
  
#if !defined(ARM_COMMON)
  if (bsInf.isInitrdLoaded() == false)
    panic("Initrd module not loaded!");
#endif

  // Initialise the processor-specific interface
  // Bootup of the other Application Processors and related tasks
  Processor::initialise2();

  List<void*> list;
  for(int i = 0; i < 20; i++)
  list.pushBack(0);

  KernelCoreSyscallManager::instance().initialise();

#if 0 && defined(ARM_COMMON) && defined(DEBUGGER)
   InterruptState st;
   LargeStaticString str2("I r cool");
   Debugger::instance().start(st, str2);
  return; // Go back to the YAMON prompt.
#endif

  // Initialise the boot output.
  bootIO.initialise();
#if defined(X86_COMMON) || defined(PPC_COMMON)
  Machine::instance().initialiseDeviceTree();
#endif
  
  // Spew out a starting string.
  HugeStaticString str;
  str += "Pedigree - revision ";
  str += g_pBuildRevision;
  str += "\n=======================\n";
  bootIO.write(str, BootIO::White, BootIO::Black);

  str.clear();
  str += "Built at ";
  str += g_pBuildTime;
  str += " by ";
  str += g_pBuildUser;
  str += " on ";
  str += g_pBuildMachine;
  str += "\n";
  bootIO.write(str, BootIO::LightGrey, BootIO::Black);

  str.clear();
  str += "Build flags: ";
  str += g_pBuildFlags;
  str += "\n";
  bootIO.write(str, BootIO::LightGrey, BootIO::Black);

#ifdef THREADS
  initialiseMultitasking();
  // while(1)
  // {
  //   NormalStaticString strz;
  //   Device *d = Device::root().getChild(0);
  //   OFDevice dev(d->getOFHandle());
  //   dev.getProperty("device_type", strz);
  //   Processor::breakpoint();
  // }

  // Gets me a stacks.
   // int i;
   // for (i = 0; i < 10; i++)
   // {
   //   stackBase = PhysicalMemoryManager::instance().allocatePage();
   //   VirtualAddressSpace::getKernelAddressSpace().map(stackBase, (void*)(0xB0100000+(i*0x1000)), 0);
   // }
//Thread *pThread = new Thread(Scheduler::instance().getProcess(0), &foo, (void*)0x136, 0);
//    pThread = new Thread(Scheduler::instance().getProcess(0), &bar, (void*)0x136, 0);
//Thread *pThread;
  // Fork a new process.
//   Process *pProcess = new Process(Scheduler::instance().getProcess(0));
//  Processor::switchAddressSpace(*pProcess->getAddressSpace());
  // Add a thread to it.
//   for (i = 0; i < 15; i++)
//   {
//     stackBase = PhysicalMemoryManager::instance().allocatePage();
//     Processor::information().getVirtualAddressSpace().map(stackBase, (void*)(0xB0000000+(i*0x1000)), VirtualAddressSpace::Write);
//   }

 // Create a 'function'.
//  stackBase = PhysicalMemoryManager::instance().allocatePage();
//  Processor::information().getVirtualAddressSpace().map(stackBase, (void*)(0x70000000), VirtualAddressSpace::Write);
//  uint8_t *func = reinterpret_cast<uint8_t*> (0x70000000);
//  func[0] = 0xEB;
//  func[1] = 0xFE;

//  pThread = new Thread(pProcess, reinterpret_cast<int (*)(void*)> (func), (void*)0x136, reinterpret_cast<uintptr_t*> ((0xB0000FF0 + (i-1)*0x1000)));
//  Processor::switchAddressSpace(VirtualAddressSpace::getKernelAddressSpace());
// VirtualAddressSpace::setCurrentAddressSpace(0);
  Processor::setInterrupts(true);
#endif
  // NOTE We have to do this before we call Processor::initialisationDone() otherwise the
  //      BootstrapStruct_t might already be unmapped
#if defined(X86_COMMON) || defined(PPC_COMMON)
  Archive initrd(bsInf.getInitrdAddress(), bsInf.getInitrdSize());

  size_t nFiles = initrd.getNumFiles();
  for (size_t i = 0; i < nFiles; i++)
  {
    uint32_t percentage = ((i+1)*100) / nFiles;
    str.clear();
    str += "\r                                        \rLoading modules: ";
    str.append(percentage, 10, 3, ' ');
    str += "% (";
    str += initrd.getFileName(i);
    str += ")";
    bootIO.write(str, BootIO::LightGrey, BootIO::Black);

    // Load file.
    Module *m = KernelElf::instance().loadModule(reinterpret_cast<uint8_t*> (initrd.getFile(i)),
                                     initrd.getFileSize(i));
  }

#endif
  
  // The initialisation is done here, unmap/free the .init section and on x86/64 the identity
  // mapping of 0-4MB
  // NOTE: BootstrapStruct_t unusable after this point
#ifdef X86_COMMON
  Processor::initialisationDone();
#endif
  

#ifdef DEBUGGER_RUN_AT_START
  //Processor::breakpoint();
#endif
  
  // Try and create a mapping.
#ifdef MIPS_COMMON
  physical_uintptr_t stackBase;
  stackBase = PhysicalMemoryManager::instance().allocatePage();
  NOTICE("StackBase = " << Hex << stackBase);
  bool br = VirtualAddressSpace::getKernelAddressSpace().map(stackBase, (void*)(0xC1505000), 0);
  NOTICE("b :" << br);

  uintptr_t *leh = reinterpret_cast<uintptr_t*> ((stackBase|0xa0000000) + 0x4);
  *leh = 0x1234567;

 Processor::breakpoint();

  volatile uintptr_t *a = (uintptr_t*)0xC1505004;
  uintptr_t b = *a;
  NOTICE("b : " << b);
  b++;
 Processor::breakpoint();
#endif

  for (;;)
  {
    // Kernel idle thread.
    Processor::setInterrupts(true);
    Scheduler::instance().yield();
    
//    for(int i = 0; i < 10000000; i++) ;
//    str.clear();
//    str += "a";
//    bootIO.write(str, BootIO::White, BootIO::Blue);
  }
}