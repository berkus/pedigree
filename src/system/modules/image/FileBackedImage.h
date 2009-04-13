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
#ifndef FILE_BACKED_IMAGE_H
#define FILE_BACKED_IMAGE_H

#include "Image.h"

#include <processor/PageFaultHandler.h>
#include <vfs/File.h>
#include <utilities/Tree.h>

/** This class defines an Image that is lazily populated by a File's contents.
 *  This type of image consists of one consecutive region of virtual memory. */
class FileBackedImage : public Image
{
public:
  /** Creates a file backed image. Takes the given File as input. */
  FileBackedImage(File *pFile);

  virtual ~FileBackedImage();

  //
  // Image interface
  //
  uintptr_t load();
  size_t getExtent();

  void trap(uintptr_t address, size_t nAdjust);

private:
  /** The main File object. */
  File *m_pFile;
  /** Virtual -> physical mappings. */
  Tree<size_t, size_t> m_Mappings;
  /** File size, rounded to nearest page. */
  size_t m_Extent;
  size_t m_nAdjust;
};

#endif
