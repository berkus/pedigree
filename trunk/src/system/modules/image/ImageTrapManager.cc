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

#include "ImageTrapManager.h"

ImageTrapManager ImageTrapManager::m_Instance;

ImageTrapManager::ImageTrapManager()
{
  PageFaultHandler::instance().registerHandler(this);
}

ImageTrapManager::~ImageTrapManager()
{
}

bool ImageTrapManager::trap(uintptr_t address, bool bIsWrite)
{
  VirtualAddressSpace &va = Processor::information().getVirtualAddressSpace();
//  NOTICE("Trap handler");
  List<FBImage*> *pList = m_Images.lookup(&va);
  if (!pList) return false;
//  NOTICE("Waslist");
  for (List<FBImage*>::Iterator it = pList->begin();
       it != pList->end();
       it++)
  {
    FBImage *pFBImage = *it;
    if (address >= pFBImage->nAdjust && address < (pFBImage->nAdjust+pFBImage->nExtent))
    {
      pFBImage->pImage->trap(address-pFBImage->nAdjust, pFBImage->nAdjust);
      return true;
    }
  }

  return false;
}

void ImageTrapManager::clone(VirtualAddressSpace *va)
{
  VirtualAddressSpace &thisva = Processor::information().getVirtualAddressSpace();

  List<FBImage*> *pList = m_Images.lookup(&thisva);
  if (!pList) return;

  List<FBImage*> *pCurList = m_Images.lookup(va);
  if (pCurList)
  {
    m_Images.remove(va);

    for (List<FBImage*>::Iterator it = pCurList->begin();
         it != pCurList->end();
         it++)
    {
      delete *it;
    }
    delete pCurList;
  }

  List<FBImage*> *pList2 = new List<FBImage*>();

  for (List<FBImage*>::Iterator it = pList->begin();
       it != pList->end();
       it++)
  {
    FBImage *fbi = *it;
    FBImage *fbi2 = new FBImage(fbi->nAdjust, fbi->nExtent, fbi->pImage);
    pList2->pushBack(fbi2);
  }

  m_Images.insert(va, pList2);
}

void ImageTrapManager::removeAll()
{
  VirtualAddressSpace &va = Processor::information().getVirtualAddressSpace();

  List<FBImage*> *pList = m_Images.lookup(&va);
  if (!pList) return;

  m_Images.remove(&va);

  for (List<FBImage*>::Iterator it = pList->begin();
       it != pList->end();
       it++)
  {
    delete *it;
  }
  delete pList;
}

void ImageTrapManager::add(Image *pImage, uintptr_t nAdjust, size_t nExtent)
{
  FBImage *pFBImage = new FBImage(nAdjust, nExtent, pImage);
  VirtualAddressSpace &va = Processor::information().getVirtualAddressSpace();

  List<FBImage*> *pList = m_Images.lookup(&va);
  if (!pList)
  {
    pList = new List<FBImage*>;
    m_Images.insert(&va, pList);
  }
  pList->pushBack(pFBImage);
}
