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

#include <Log.h>
#include <Elf32.h>
#include <utilities/utility.h>
#include <BootstrapInfo.h>

Elf32::Elf32(const char *name) :
  m_pHeader(0),
  m_pSymbolTable(0),
  m_pStringTable(0),
  m_pShstrtab(0),
  m_pGotTable(0),
  m_pRelTable(0),
  m_pSectionHeaders(0),
  m_nSectionHeaders(0),
  m_pBuffer(0)
{
  strncpy(m_pId, name, 127);
}

Elf32::~Elf32()
{
}

bool Elf32::load(uint8_t *pBuffer, unsigned int nBufferLength)
{
  // The main header will be at pBuffer[0].
  m_pHeader = reinterpret_cast<Elf32Header_t *>(pBuffer);
  
  // Check the ident.
  if ( (m_pHeader->ident[0] != 'E') ||
       (m_pHeader->ident[1] != 'L') ||
       (m_pHeader->ident[2] != 'F') ||
       (m_pHeader->ident[3] != 127) )
  {
    m_pHeader = 0;
    ERROR("ELF file with id '" << m_pId << "'; ident check failed!");
    return false;
  }
  
  // Load in the section headers.
  m_pSectionHeaders = reinterpret_cast<Elf32SectionHeader_t *>(&pBuffer[m_pHeader->shoff]);
  
  // Find the string tab&pBuffer[m_pStringTable->offset];le.
  m_pStringTable = &m_pSectionHeaders[m_pHeader->shstrndx];

  // FIXME TODO HACK huh?
  // m_pBootstrap->getSectionHeader(
  //    pBootstrap->getStringTable() )

  // Temporarily load the string table.
  const char *pStrtab = reinterpret_cast<const char *>(&pBuffer[m_pStringTable->offset]);
  
  // Go through each section header, trying to find .symtab.
  for (int i = 0; i < m_pHeader->shnum; i++)
  {
    const char *pStr = pStrtab + m_pSectionHeaders[i].name;
    if (!strcmp(pStr, ".symtab"))
    {
      m_pSymbolTable = &m_pSectionHeaders[i];
      break;
    }
  }
  
  if (m_pSymbolTable == 0)
    WARNING("ELF file with id '" << m_pId << "'; symbol table not found!");
  
  m_pBuffer = pBuffer;
  
  // Success.
  return true;
}

bool Elf32::load(BootstrapInfo *pBootstrap)
{
  // Firstly get the section header string table.
  m_pShstrtab = reinterpret_cast<Elf32SectionHeader_t *>( pBootstrap->getSectionHeader(
                                                          pBootstrap->getStringTable() ));
  
  m_nSectionHeaders = pBootstrap->getSectionHeaderCount();
  m_pSectionHeaders = reinterpret_cast<Elf32::Elf32SectionHeader_t*>(pBootstrap->getSectionHeader(0));
  
  // Normally we will try to use the sectionHeader->offset member to access data, so an
  // Elf section's data can be accessed without being mapped into virtual memory. However,
  // when GRUB loads us, it doesn't tell us where exactly ->offset is with respect to, so here
  // we fix offset = addr, then we work w.r.t 0x00.
  
  // Temporarily load the string table.
  const char *pStrtab = reinterpret_cast<const char *>(m_pShstrtab->addr);

  // Now search for the symbol table.
  for (int i = 0; i < pBootstrap->getSectionHeaderCount(); i++)
  {
    Elf32SectionHeader_t *pSh = reinterpret_cast<Elf32SectionHeader_t *>(pBootstrap->getSectionHeader(i));
    const char *pStr = pStrtab + pSh->name;

    if (pSh->type == SHT_SYMTAB)
    {
      m_pSymbolTable = pSh;
      m_pSymbolTable->offset = m_pSymbolTable->addr;
    }
    else if (!strcmp(pStr, ".strtab"))
    {
      m_pStringTable = pSh;
      m_pStringTable->offset = m_pStringTable->addr;
    }
  }

  return true;
}

bool Elf32::writeSections()
{
  // TODO
  return false;
}

unsigned int Elf32::getLastAddress()
{
  // TODO
  return 0;
}

const char *Elf32::lookupSymbol(uintptr_t addr, uintptr_t *startAddr)
{
  if (!m_pSymbolTable || !m_pStringTable)
    return 0; // Just return null if we haven't got a symbol table.
  
  Elf32Symbol_t *pSymbol = reinterpret_cast<Elf32Symbol_t *>(m_pSymbolTable->addr);
  
  const char *pStrtab = reinterpret_cast<const char *>(&m_pBuffer[m_pStringTable->offset]);
  
  for (size_t i = 0; i < m_pSymbolTable->size / sizeof(Elf32Symbol_t); i++)
  {
    // Make sure we're looking at an object or function.
    if (ELF32_ST_TYPE(pSymbol->info) != 0x2 /* function */ &&
        ELF32_ST_TYPE(pSymbol->info) != 0x0 /* notype (asm functions) */)
    {
      pSymbol++;
      continue;
    }
    
    // If we're checking for a symbol that is apparently zero-sized, add one so we can actually
    // count it!
    uint32_t size = pSymbol->size;
    if (size == 0)
      size = 1;
    if ( (addr >= pSymbol->value) &&
         (addr < (pSymbol->value + size)) )
    {
      const char *pStr = pStrtab + pSymbol->name;
      if (startAddr)
        *startAddr = pSymbol->value;
      return pStr;
    }
    pSymbol ++;
  }
  return 0;
  
}

uint32_t Elf32::lookupDynamicSymbolAddress(uint32_t off)
{
  // TODO
  return 0;
}

char *Elf32::lookupDynamicSymbolName(uint32_t off)
{
  // TODO
  return 0;
}

uint32_t Elf32::getGlobalOffsetTable()
{
  // TODO
  return 0;
}

uint32_t Elf32::getEntryPoint()
{
  // TODO
  return 0;
}

uint32_t Elf32::debugFrameTable()
{
  // Temporarily load the string table.
  const char *pStrtab = reinterpret_cast<const char *>(m_pShstrtab->addr);
  
  // Now search for the debug_frame table.
  for (size_t i = 0; i < m_nSectionHeaders; i++)
  {
    Elf32SectionHeader_t *pSh = &m_pSectionHeaders[i];
    const char *pStr = pStrtab + pSh->name;

    if (!strcmp(pStr, ".debug_frame"))
    {
      return pSh->addr;
    }
  }
  return 0;
}

uint32_t Elf32::debugFrameTableLength()
{
  // Temporarily load the string table.
  const char *pStrtab = reinterpret_cast<const char *>(m_pShstrtab->addr);
  
  // Now search for the debug_frame table.
  for (size_t i = 0; i < m_nSectionHeaders; i++)
  {
    Elf32SectionHeader_t *pSh = &m_pSectionHeaders[i];
    const char *pStr = pStrtab + pSh->name;

    if (!strcmp(pStr, ".debug_frame"))
    {
      return pSh->size;
    }
  }
  return 0;
}