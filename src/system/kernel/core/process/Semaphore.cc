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

#include <process/Semaphore.h>
#include <processor/Processor.h>
#include <process/Scheduler.h>
#include <Log.h>
#include "../BootIO.h"
extern BootIO bootIO;

// NOTE, this is in its own file purely so that a vtable can be generated.
Semaphore::Semaphore(size_t nInitialValue)
  : m_Counter(nInitialValue), m_BeingModified(false), m_Queue(), m_pParent(0), magic(0x1234)
{
}

Semaphore::~Semaphore()
{
}

void Semaphore::acquire(size_t n)
{
  // Spin 10 times in the case that the lock is about to be released on 
  // multiprocessor systems.
#ifdef SMP
  for (int i = 0; i < 10; i++)
    if (tryAcquire(n))
    {
      return;
    }
#endif
  while (true)
  {
    if (tryAcquire(n))
      return;
    
    m_BeingModified.acquire();

    // To avoid a race condition, check again here after we've disabled interrupts.
    // This stops the condition where the lock is released after tryAcquire returns false,
    // but before we grab the "being modified" lock, which means the lock could be released by this point!
    if (tryAcquire(n))
    {
      m_BeingModified.release();
      return;
    }
    Thread *pThread = Processor::information().getCurrentThread();

    if (Processor::information().getCurrentThread()->getStatus() != Thread::Sleeping)
    {
      m_Queue.pushBack(Processor::information().getCurrentThread());
      Processor::information().getCurrentThread()->setStatus(Thread::PreSleep);
    }
    m_BeingModified.release();

    Scheduler::instance().yield(0);
  }
  
}

bool Semaphore::tryAcquire(size_t n)
{
  ssize_t value = m_Counter;
 
  if ((value - static_cast<ssize_t>(n)) < 0)return false;
  if (m_Counter.compareAndSwap(value, value - n))
  {
    #ifdef STRICT_LOCK_ORDERING
      // TODO LockManager::acquired(*this);
    #endif
    return true;
  }
  return false;
}

void Semaphore::release(size_t n)
{
  m_Counter += n;
  
  m_BeingModified.acquire();
  
  for (size_t i = 0; i < m_Queue.count(); i++)
  {
    // TODO: Check for dead thread.
    Thread *pThread = m_Queue.popFront();
//    NOTICE("Releasing " << pThread->getParent()->getId() << ":" << pThread->getId());
    while (pThread->getStatus() == Thread::PreSleep) ;
//NOTICE("Released " << pThread->getParent()->getId() << ":" << pThread->getId());
    pThread->setStatus(Thread::Ready);

    if (pThread == 0)
    {
      FATAL("Semaphore: Null thread!");
      Processor::breakpoint();
    }
  }

  m_BeingModified.release();

  #ifdef STRICT_LOCK_ORDERING
    // TODO LockManager::released(*this);
  #endif
}
