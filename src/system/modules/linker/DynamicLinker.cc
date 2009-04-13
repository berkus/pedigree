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

#include "DynamicLinker.h"
#include <Log.h>
#include <vfs/VFS.h>
#include <utilities/StaticString.h>
#include <Module.h>
#include <processor/Processor.h>
#include <processor/VirtualAddressSpace.h>
#include <processor/PhysicalMemoryManager.h>
#include <processor/KernelCoreSyscallManager.h>
#include <process/Scheduler.h>
#include <panic.h>

DynamicLinker DynamicLinker::m_Instance;

uintptr_t DynamicLinker::resolve(const char *str)
{
  Process *pProcess = Processor::information().getCurrentThread()->getParent();

  Elf* thisElf = m_ProcessElfs.lookup(pProcess);
  SymbolTable *pSymtab = thisElf->getSymbolTable();
  
  uintptr_t ret = pSymtab->lookup(String(str), thisElf);
  if(ret == ~0)
    ret = 0;

  return ret;
}

uintptr_t DynamicLinker::resolvePlt(SyscallState &state)
{
  uintptr_t ret= DynamicLinker::instance().resolvePltSymbol(state.getSyscallParameter(0), state.getSyscallParameter(1));
  return ret;
}

DynamicLinker::DynamicLinker() :
  m_ProcessObjects(),
  m_Objects(),
  m_ProcessElfs()
{
  KernelCoreSyscallManager::instance().registerSyscall(KernelCoreSyscallManager::link, &resolvePlt);
}

DynamicLinker::~DynamicLinker()
{
}

bool DynamicLinker::initialiseLibrary(Elf *pElf, uintptr_t loadBase)
{
  Process *pProcess = Processor::information().getCurrentThread()->getParent();

  SharedObject *pSo = new SharedObject;
  pSo->pFile = pElf;
  pSo->refCount = 1;
  pSo->name = String("unnamed");

  List<SharedObject*> *pList = m_ProcessObjects.lookup(pProcess);
  if (!pList)
  {
    pList = new List<SharedObject*>();
    m_ProcessObjects.insert(pProcess, pList);
  }
  pList->pushBack(pSo);

  pSo->addresses.insert(pProcess, reinterpret_cast<uintptr_t*>(loadBase));

  m_Objects.pushBack(pSo);

  initPlt(pSo->pFile, loadBase);

  return true;
}

uintptr_t DynamicLinker::resolveSymbol(const char *sym, bool useElf)
{
  Process *pProcess = Processor::information().getCurrentThread()->getParent();

  Elf *pElf = m_ProcessElfs.lookup(pProcess);
  if (!pElf)
  {
    ERROR("Resolve called on unregistered process");
    return 0;
  }

  if (useElf)
  {
    // LoadBase for the program itself is of course zero.
    uintptr_t addr = pElf->lookupDynamicSymbolAddress(sym,0);
    if (addr) return addr;
  }

  List<SharedObject*> *pList;

  pList = m_ProcessObjects.lookup(pProcess);
  if (!pList)
  {
    ERROR("Resolve called on nonregistered process");
    return 0;
  }

  // Look through the shared object list.
  for (List<SharedObject*>::Iterator it = pList->begin();
       it != pList->end();
       it++)
  {
    uintptr_t ptr = resolveInLibrary(sym, *it);
    if (ptr != 0) return ptr;
  }
}

uintptr_t DynamicLinker::resolveInLibrary(const char *sym, SharedObject *obj)
{
  Process *pProcess = Processor::information().getCurrentThread()->getParent();

  // Grab the load address of this object in this process.
  uintptr_t loadBase = reinterpret_cast<uintptr_t>
                         (obj->addresses.lookup(pProcess));
  // Sanity check
  if (loadBase == 0)
  {
    // Something went horrendously wrong!
    FATAL("DynamicLinker: Loadbase is 0!");
    panic("DynamicLinker: Loadbase is 0!");
  }

  uintptr_t addr = obj->pFile->lookupDynamicSymbolAddress(sym, loadBase);

  if (addr)
    return addr;

  // Not found - try the dependencies.
  for (int i = 0; i < obj->nDependencies; i++)
  {
    addr = resolveInLibrary(sym, obj->pDependencies[i]);
    if (addr)
      return addr;
  }

  // Failed.
  return 0;
}

Elf *DynamicLinker::findElf(uintptr_t libraryId, SharedObject *pSo, uintptr_t &_loadBase)
{
  // Grab the load address of this object in this process.
  uintptr_t loadBase = reinterpret_cast<uintptr_t>
                         (pSo->addresses.lookup(Processor::information().getCurrentThread()->getParent()));

  // Sanity check
  if (loadBase == 0)
  {
    // Something went horrendously wrong!
    FATAL("DynamicLinker: Loadbase is 0!");
    panic("DynamicLinker: Loadbase is 0!");
  }

  if (loadBase == libraryId)
  {
    _loadBase = loadBase;
    return pSo->pFile;
  }

  // Not found - try the dependencies.
  for (int i = 0; i < pSo->nDependencies; i++)
  {
    Elf *pElf = findElf(libraryId, pSo->pDependencies[i], _loadBase);
    if (pElf)
      return pElf;
  }

  // Failed.
  return 0;
}

void DynamicLinker::unregisterProcess(Process *pProcess)
{
  m_ProcessElfs.remove(pProcess);
  m_ProcessObjects.remove(pProcess);
  for (List<SharedObject*>::Iterator it = m_Objects.begin();
       it != m_Objects.end();
       it++)
  {
    SharedObject *pSo = *it;
    uintptr_t *ptr;
    if ((ptr=pSo->addresses.lookup(pProcess)))
    {
      pSo->addresses.remove(pProcess);
    }
  }
}

void DynamicLinker::registerElf(Elf *pElf)
{
  Process *pProcess = Processor::information().getCurrentThread()->getParent();

  m_ProcessElfs.remove(pProcess);
  m_ProcessElfs.insert(pProcess, pElf);
}

void DynamicLinker::initialiseElf(Elf *pElf)
{
  initPlt(pElf, 0);
}

void DynamicLinker::registerProcess(Process *pProcess)
{
  Elf *pElf = m_ProcessElfs.lookup(Processor::information().getCurrentThread()->getParent());
  m_ProcessElfs.insert(pProcess, pElf);

  for (List<SharedObject*>::Iterator it = m_Objects.begin();
       it != m_Objects.end();
       it++)
  {
    SharedObject *pSo = *it;
    uintptr_t *ptr;
    if ((ptr=pSo->addresses.lookup(Processor::information().getCurrentThread()->getParent())))
    {
      pSo->addresses.insert(pProcess, ptr);
    }
  }

  m_ProcessObjects.insert ( pProcess, m_ProcessObjects.lookup(Processor::information().getCurrentThread()->getParent()) );
}

void init()
{
}

void destroy()
{
}

MODULE_NAME("linker");
MODULE_ENTRY(&init);
MODULE_EXIT(&destroy);
MODULE_DEPENDS(0);
