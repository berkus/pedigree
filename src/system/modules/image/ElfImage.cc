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

#include <processor/types.h>
#include "ElfImage.h"
#include "ImageTrapManager.h"

ElfImage::ElfImage(uintptr_t buffer, size_t size, SymbolTable *pSymtab) :
  m_Buffer(buffer), m_BufferSize(size), m_pElf(0), m_LoadBase(0), m_pSymtab(pSymtab), m_Mappings(), m_Start(0), m_Extent(0), m_bIsValid(false)
{
  m_pElf = new Elf();
  if (!m_pElf->create(reinterpret_cast<uint8_t*>(buffer), size))
  {
    ERROR("ElfImage: Elf creation failed!");
    return;
  }
  m_pElf->allocate(reinterpret_cast<uint8_t*>(buffer), size, m_LoadBase, m_pSymtab,
                   0, &m_Start, &m_Extent, false /* Don't allocate */);

  // Ensure m_Extent is page-aligned.
  m_Extent = (m_Extent & ~(PhysicalMemoryManager::getPageSize()-1)) + 
    PhysicalMemoryManager::getPageSize();

  if (!m_pSymtab)
    m_pSymtab = m_pElf->getSymbolTable();

  m_bIsValid = true;
}

ElfImage::~ElfImage()
{
  delete m_pElf;
}

uintptr_t ElfImage::load()
{
  ImageTrapManager::instance().add(this, m_Start, m_Extent);

  /// \todo Need to grab from the memory allocator if not already...

  VirtualAddressSpace &va = Processor::information().getVirtualAddressSpace();
  
  // Add all the V->P mappings we currently posess.
  for (Tree<size_t,size_t>::Iterator it = m_Mappings.begin();
       it != m_Mappings.end();
       it++)
  {
    uintptr_t v = reinterpret_cast<uintptr_t>(it.key());
    uintptr_t p = reinterpret_cast<uintptr_t>(it.value());
    // Don't make the page writable - just copy on write.
    NOTICE("Mapping " << v << " to " << p );
    if (!va.map(p, reinterpret_cast<void*>(v), VirtualAddressSpace::CopyOnWrite))
    {
      WARNING("IMAGE: map() failed in ElfImage::load()");
      return 0;
    }
  }
  return m_Start;
}

size_t ElfImage::getExtent()
{
  return m_Extent;
}

void ElfImage::trap(uintptr_t address, size_t nAdjust)
{
  NOTICE("ElfImage::trap");
  // Sanity check...
  if (address > getExtent())
  {
    FATAL("IMAGE: ElfImage::trap called with invalid address: " << Hex << address);
    return;
  }

  address += m_Start;

  VirtualAddressSpace &va = Processor::information().getVirtualAddressSpace();

  uintptr_t v = address & ~(PhysicalMemoryManager::getPageSize()-1);

  // Grab a physical page.
  physical_uintptr_t p = PhysicalMemoryManager::instance().allocatePage();
  // Map it into the address space.
  if (!va.map(p, reinterpret_cast<void*>(v), VirtualAddressSpace::Write))
  {
    WARNING("IMAGE: map() failed in ElfImage::trap()");
    for(;;);
    return;
  }

  // Add the V->P mapping to the cache.
  m_Mappings.insert(v, p);

  // Now that it's mapped, load the ELF region.
  if (m_pElf->load(reinterpret_cast<uint8_t*>(m_Buffer), m_BufferSize, m_LoadBase, m_pSymtab, v,
                   v+PhysicalMemoryManager::getPageSize()) == false)
  {
    WARNING("IMAGE: load() failed in ElfImage::trap()");
    for(;;);
    return;
  }

  // And now that the file is read and the memory written, change the mapping to
  // copy-on-write.
  va.setFlags(reinterpret_cast<void*>(v), VirtualAddressSpace::CopyOnWrite);
}
