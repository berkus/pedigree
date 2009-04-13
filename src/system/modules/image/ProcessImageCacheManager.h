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
#ifndef PROCESS_IMAGE_CACHE_MANAGER_H
#define PROCESS_IMAGE_CACHE_MANAGER_H

#include <processor/types.h>
#include <vfs/File.h>
#include <utilities/Tree.h>
#include "ProcessImage.h"

/** The ProcessImageCacheManager caches process images. */
class ProcessImageCacheManager
{
public:
  /** Gets the singleton class instance. */
  static ProcessImageCacheManager &instance()
    {return m_Instance;}

  /** Gets a ProcessImage for the given file.
      \note This function is responsible for detecting changes in the File
            since the creation of any existing ProcessImage entries. */
  ProcessImage *getImage(File *pFile);

  /** Returns a ProcessImage once it is unused. */
  void returnImage(ProcessImage *pImage);

private:
  /** Default constructor. */
  ProcessImageCacheManager();
  ~ProcessImageCacheManager();
  
  /** File*->ProcessImage* mappings - all mappings can be assumed to be valid (
      no stale File*'s should be mapped here) */
  Tree<File*, ProcessImage*> m_Cache;

  /** Static singleton instance. */
  static ProcessImageCacheManager m_Instance;
};

#endif
