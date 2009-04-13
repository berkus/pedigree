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
#ifndef IMAGE_TRAP_MANAGER_H
#define IMAGE_TRAP_MANAGER_H

#include <processor/PageFaultHandler.h>
#include <vfs/File.h>
#include <utilities/Tree.h>
#include "Image.h"

class ImageTrapManager : private MemoryTrapHandler
{
public:
  static ImageTrapManager &instance() {return m_Instance;}

  virtual ~ImageTrapManager();

  //
  // MemoryTrapHandler interface.
  //
  bool trap(uintptr_t address, bool bIsWrite);

  /** Copies the image mappings from this address space to the given 
      address space. */
  void clone(VirtualAddressSpace *va);

  /** Removes all images for this address space.
      \note Does not delete or destroy any Images. */
  void removeAll();

  /** Adds a Image for the current VA space with the given adjust and
      extent.
      \note Should ONLY be called from Image::load(). */
  void add(Image *pImage, uintptr_t nAdjust, size_t nExtent);

private:
  ImageTrapManager();

  struct FBImage
  {
    FBImage(uintptr_t a, size_t e, Image *i) :
      nAdjust(a), nExtent(e), pImage(i)
    {}
    uintptr_t nAdjust;
    size_t nExtent;
    Image *pImage;
  };

  Tree<VirtualAddressSpace*, List<FBImage*>*> m_Images;

  static ImageTrapManager m_Instance;
};

#endif
