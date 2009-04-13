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
#ifndef ELF_IMAGE_H
#define ELF_IMAGE_H

#include "FileBackedImage.h"
#include <linker/Elf.h>

/** This class defines an Image that lazily populates itself with the contents
 *  of the given File, interpreted as an ELF executable. */
class ElfImage : public Image
{
public:
  /** Creates a new ElfImage. Takes the given File as input. */
  ElfImage(uintptr_t buffer, size_t size, SymbolTable *pSymtab);

  virtual ~ElfImage();

  //
  // Image interface
  //
  uintptr_t load();
  size_t getExtent();

  void trap(uintptr_t address, size_t nAdjust);

  Elf *getElf()
    {return m_pElf;}

  uintptr_t getLoadBase()
    {return m_LoadBase;}

  bool isValid()
    {return m_bIsValid;}

private:
  uintptr_t m_Buffer;
  size_t m_BufferSize;
  Elf *m_pElf;
  uintptr_t m_LoadBase;
  SymbolTable *m_pSymtab;

  /** Virtual -> physical mappings. */
  Tree<size_t, size_t> m_Mappings;

  uintptr_t m_Start;
  size_t m_Extent;

  bool m_bIsValid;
};

#endif
