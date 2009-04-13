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

#include "ProcessImageCacheManager.h"

ProcessImageCacheManager ProcessImageCacheManager::m_Instance;

ProcessImageCacheManager::ProcessImageCacheManager() :
  m_Cache()
{
}

ProcessImageCacheManager::~ProcessImageCacheManager()
{
}

ProcessImage *ProcessImageCacheManager::getImage(File *pFile)
{
  /// \todo Check file validity.
#if 0
  if (pFile->isTouched())
  {
    // The file has changed. Update our cache.
    ProcessImage *pI = m_Cache.lookup(pFile);
    if (pI)
    {
      pI->markForDeletion();
      m_Cache.remove(pFile);
    }
  }
#endif

  ProcessImage *pImage = m_Cache.lookup(pFile);
  if (!pImage)
  {
    pImage = new ProcessImage(pFile);
    if (!pImage->isValid())
    {
      delete pImage;
      return 0;
    }
    m_Cache.insert(pFile, pImage);
  }

  // pImage->increaseRefCount();

  return pImage;
}

void ProcessImageCacheManager::returnImage(ProcessImage *pImage)
{
#if 0
  pImage->decreaseRefCount();
  if (pImage->getRefCount() <= 0 && pImage->isMarkedForDeletion())
  {
    delete pImage;
  }
#endif
}
