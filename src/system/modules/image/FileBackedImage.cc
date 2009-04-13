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

#include "FileBackedImage.h"
#include <processor/PhysicalMemoryManager.h>
#include "ImageTrapManager.h"
#include <process/Process.h>

FileBackedImage::FileBackedImage(File *pFile) :
  m_pFile(pFile), m_Mappings(), m_Extent(0), m_nAdjust(0)
{
  m_Extent = (pFile->getSize() / PhysicalMemoryManager::getPageSize() + 1) *
    PhysicalMemoryManager::getPageSize();
}

FileBackedImage::~FileBackedImage()
{
}

uintptr_t FileBackedImage::load()
{

  Process *pProcess = Processor::information().getCurrentThread()->getParent();

  if (m_nAdjust == 0)
  {
    if (!pProcess->getSpaceAllocator().allocate(m_Extent, m_nAdjust))
      return false;
  }
  else
  {
    if (!pProcess->getSpaceAllocator().allocateSpecific(m_nAdjust, m_Extent))
      return false;
  }

  ImageTrapManager::instance().add(this, m_nAdjust, m_Extent);

  VirtualAddressSpace &va = Processor::information().getVirtualAddressSpace();
  
  // Add all the V->P mappings we currently posess.
  for (Tree<size_t,size_t>::Iterator it = m_Mappings.begin();
       it != m_Mappings.end();
       it++)
  {
    uintptr_t v = reinterpret_cast<uintptr_t>(it.key());
    uintptr_t p = reinterpret_cast<uintptr_t>(it.value());
    // Don't make the page writable - just copy on write.
    if (!va.map(p, reinterpret_cast<void*>(m_nAdjust+v), VirtualAddressSpace::CopyOnWrite))
    {
      WARNING("IMAGE: map() failed in FileBackedImage::load()");
      return 0;
    }
  }
  return m_nAdjust;
}

size_t FileBackedImage::getExtent()
{
  return m_Extent;
}

void FileBackedImage::trap(uintptr_t address, size_t nAdjust)
{
  // Sanity check...
  if (address > m_Extent)
  {
    FATAL("IMAGE: FileBackedImage::trap called with invalid address: " << Hex << address);
    return;
  }

  VirtualAddressSpace &va = Processor::information().getVirtualAddressSpace();

  uintptr_t v = address & ~(PhysicalMemoryManager::getPageSize()-1);
  //NOTICE("v = " << v << ", nAdjust = " << nAdjust);
  // Grab a physical page.
  physical_uintptr_t p = PhysicalMemoryManager::instance().allocatePage();


  // Map it into the address space.
  if (!va.map(p, reinterpret_cast<void*>(nAdjust+v), VirtualAddressSpace::Write))
  {
    WARNING("IMAGE: map() failed in FileBackedImage::load()");
    return;
  }

  // We can't just read directly to our new page, as the Filesystem stuff
  // uses thread IPC and our new page won't be mapped in any other address
  // spaces.
  uint8_t *buffer = new uint8_t[PhysicalMemoryManager::getPageSize()];

  // Now that it's mapped, read the file in.
  if (m_pFile->read(v, PhysicalMemoryManager::getPageSize(), reinterpret_cast<uintptr_t>(buffer)) != 
      PhysicalMemoryManager::getPageSize())
  {
    WARNING("IMAGE: read() failed in FileBackedImage::load()");
  }

  memcpy(reinterpret_cast<uint8_t*>(nAdjust+v), buffer, PhysicalMemoryManager::getPageSize());
  delete [] buffer;

  // And now that the file is read and the memory written, change the mapping to
  // copy-on-write.
  va.setFlags(reinterpret_cast<void*>(nAdjust+v), VirtualAddressSpace::CopyOnWrite);
}
