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
#ifndef PROCESS_IMAGE_H
#define PROCESS_IMAGE_H

#include "Image.h"
#include "ElfImage.h"
#include <linker/Elf.h>
#include <utilities/List.h>
#include <vfs/File.h>

/** This class defines an Image that lazily populates an entire process - 
    including main ELF, and all library ELFs. */
class ProcessImage : public Image
{
public:
  /** Creates a new ProcessImage. Takes the given File as input. */
  ProcessImage(File *pFile);

  virtual ~ProcessImage();

  //
  // Image interface
  //
  uintptr_t load();
  size_t getExtent();

  void trap(uintptr_t address, size_t nAdjust);

  bool isValid()
    {return m_bIsValid;}

  Elf *getMainElf()
    {return m_pElfImage->getElf();}

private:
  ElfImage *m_pElfImage;

  List<ElfImage*> m_Libraries;
  List<FileBackedImage*> m_FBImages;

  bool m_bIsValid;
};

#endif
