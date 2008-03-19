/*
 * Copyright (c) 2008 James Molloy, James Pritchett, Jörg Pfähler, Matthew Iselin
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
#include <processor/types.h>
#include "cppsupport.h"

// Required for G++ to link static init/destructors.
void *__dso_handle;

// Defined in the linker.
uintptr_t start_ctors;
uintptr_t end_ctors;

/// Calls the constructors for all global objects.
/// Call this before using any global objects.
void initialiseConstructors()
{
  // Constructor list is defined in the linker script.
  // The .ctors section is just an array of function pointers.
  // iterate through, calling each in turn.
  uintptr_t *iterator = reinterpret_cast<uintptr_t*>(&start_ctors);
  while (iterator < reinterpret_cast<uintptr_t*>(&end_ctors))
  {
    void (*fp)(void) = reinterpret_cast<void (*)(void)>(*iterator);
    fp();
    iterator++;
  }
}

/// Required for G++ to compile code.
extern "C" void __cxa_atexit(void (*f)(void *), void *p, void *d)
{
}

/// Called by G++ if a pure virtual function is called. Bad Thing, should never happen!
extern "C" void __cxa_pure_virtual()
{
}

// HACK FIXME TODO: Very, very simple memory management
#include <utilities/utility.h>
#include <processor/VirtualAddressSpace.h>
#include <processor/PhysicalMemoryManager.h>
static void *allocate(size_t size)
{
  static void *HeapEnd = 0;
  static size_t UnusedSize = 0;

  if (UnusedSize < size)
  {
    VirtualAddressSpace &VAddressSpace = VirtualAddressSpace::getKernelAddressSpace();
    size_t pageCount = (size - UnusedSize + PhysicalMemoryManager::getPageSize() - 1) / PhysicalMemoryManager::getPageSize();
    HeapEnd = VAddressSpace.expandHeap(pageCount, VirtualAddressSpace::KernelMode | VirtualAddressSpace::Write);
    HeapEnd = adjust_pointer(HeapEnd, pageCount * PhysicalMemoryManager::getPageSize());
    UnusedSize += pageCount * PhysicalMemoryManager::getPageSize();
  }

  void *tmp = adjust_pointer(HeapEnd, -UnusedSize);
  UnusedSize -= size;
  return tmp;
}

void *operator new (size_t size) throw()
{
  return allocate(size);
}
void *operator new[] (size_t size) throw()
{
  return allocate(size);
}
void *operator new (size_t size, void* memory) throw()
{
  return memory;
}
void *operator new[] (size_t size, void* memory) throw()
{
  return memory;
}
void operator delete (void * p)
{
  // TODO
}
void operator delete[] (void * p)
{
  // TODO
}
void operator delete (void *p, void *q)
{
  // TODO
}
void operator delete[] (void *p, void *q)
{
  // TODO
}