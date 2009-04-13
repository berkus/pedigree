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

#include "ProcessImage.h"
#include "ElfImage.h"
#include "FileBackedImage.h"
#include <Log.h>
#include <linker/DynamicLinker.h>
#include <vfs/VFS.h>

ProcessImage::ProcessImage(File *pFile) :
  m_pElfImage(0), m_Libraries(), m_FBImages(), m_bIsValid(false)
{
  // Lazily map in pFile.
  FileBackedImage *pFBFile = new FileBackedImage(pFile);

  // Load it into the address space, retrieving a pointer to it.
  uintptr_t buffer = pFBFile->load();

  m_FBImages.pushBack(pFBFile);

  // Now, lazily map that file as an Elf.
  m_pElfImage = new ElfImage(buffer, pFBFile->getExtent(), 0);

  if (!m_pElfImage->isValid())
    return;

  m_pElfImage->load();

  // Grab that Elf, and look for libraries to load!.
  Elf *pElf = m_pElfImage->getElf();

  DynamicLinker::instance().registerElf(pElf);

  List<char*> neededLibraries = pElf->neededLibraries();
  for (List<char*>::Iterator it = neededLibraries.begin();
       it != neededLibraries.end();
       it++)
  {
    char *stubname = *it;
    String fileName;
    fileName += "root:/libraries/";
    fileName += stubname;

    // Attempt to open the file.
    File *file = VFS::instance().find(fileName);

    if (!file)
    {
      ERROR("ProcessImage: Unable to load object \"" << fileName << "\"");
      return;
    }

    // Lazily map in pFile.
    FileBackedImage *pFBFile = new FileBackedImage(file);

    // Load it into the address space, retrieving a pointer to it.
    uintptr_t buffer = pFBFile->load();
  
    m_FBImages.pushBack(pFBFile);

    // Now, lazily map that file as an Elf.
    ElfImage *pElfImage = new ElfImage(buffer, pFBFile->getExtent(), pElf->getSymbolTable());

    if (!pElfImage->isValid())
    {
      ERROR("Shared dependency '" << *it << "' not found.");
      return;
    }

    pElfImage->load();

    m_Libraries.pushBack(pElfImage);

    List<char*> neededLibraries2 = pElfImage->getElf()->neededLibraries();
    for (List<char*>::Iterator it2 = neededLibraries2.begin();
         it2 != neededLibraries2.end();
         it2++)
    {
      /// \todo Check for cyclic dependencies.
      neededLibraries.pushBack(*it2);
    }

  }
  
//  DynamicLinker::instance().initialiseElf(pElf);

  m_bIsValid = true;
}

ProcessImage::~ProcessImage()
{
}

uintptr_t ProcessImage::load()
{
  m_pElfImage->load();
  DynamicLinker::instance().initialiseElf(m_pElfImage->getElf());
  for (List<FileBackedImage*>::Iterator it = m_FBImages.begin();
       it != m_FBImages.end();
       it++)
  {
    (*it)->load();
  }
  for (List<ElfImage*>::Iterator it = m_Libraries.begin();
       it != m_Libraries.end();
       it++)
  {
    (*it)->load();
    ElfImage *pElfImage = *it;
    if (!DynamicLinker::instance().initialiseLibrary(pElfImage->getElf(), pElfImage->getLoadBase()))
    {
      ERROR("Shared dependency not found.");
      return 0;
    }
  }
}

size_t ProcessImage::getExtent()
{
  return 0;
}

void ProcessImage::trap(uintptr_t address, size_t nAdjust)
{
  FATAL("ProcessImage::trap() called!");
}
