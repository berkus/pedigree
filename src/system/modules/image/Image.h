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
#ifndef IMAGE_H
#define IMAGE_H

#include <processor/types.h>
#include <processor/VirtualAddressSpace.h>
#include <processor/PhysicalMemoryManager.h>

/** This class provides an "Image" - a (possibly sparse) collection of virtual->
 *  physical mappings, ready to be "pasted" into a virtual address space.
 *
 *  All the pages mapped in an Image are copy-on-write, which means they can
 *  be loaded into an address space without fear of overwriting the original
 *  content.
 *
 *  \note This is the abstract base class - the populating of an Image is done
 *        by subclasses.
 */
class Image
{
public:
  Image();

  virtual ~Image();

  /** Loads the image into the given address space.
      \param nAdjust The amount to adjust the base address of this Image by.
      \param pAS The address space to load into, or 0 for the current process'. */
  virtual uintptr_t load() =0;

  /** Returns the extent of the Image - from address zero, how far it extends. */
  virtual size_t getExtent() =0;

  /** Called by ImageTrapManager ONLY. */
  virtual void trap(uintptr_t address, size_t nAdjust) =0;

private:
  /** Not implemented - use subclass. */
  Image(const Image &);

};

#endif
