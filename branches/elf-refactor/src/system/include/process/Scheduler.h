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

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <processor/types.h>
#include <processor/state.h>
#include <machine/TimerHandler.h>
#include <process/Mutex.h>
#include <process/Process.h>
#include <Atomic.h>

class SchedulingAlgorithm;
class Thread;
class Processor;

/**
 * \brief This class manages how processes and threads are scheduled across processors.
 * It delegates the task of selecting when to run each process to a SchedulingAlgorithm,
 * and attempts to run in a tickless fashion, if the hardware supports it (Local APIC present).
 */
class Scheduler : public TimerHandler
{
public:
  /** Get the instance of the scheduler */
  inline static Scheduler &instance() {return m_Instance;}

  /** Initialises the scheduler. */
  bool initialise(Thread *pInitialThread);
  
  /** Retrieves the current SchedulingAlgorithm */
  SchedulingAlgorithm *getAlgorithm();
  /** Sets the current SchedulingAlgorithm */
  void setAlgorithm(SchedulingAlgorithm *pAlgorithm);

  /** Adds a thread to be scheduled. */
  void addThread(Thread *pThread);
  /** Removes a thread from being scheduled. */
  void removeThread(Thread *pThread);
  
  /** Adds a process.
   *  \note This is purely for enumeration purposes.
   *  \return The ID that should be applied to this Process. */
  size_t addProcess(Process *pProcess);
  /** Removes a process.
   *  \note This is purely for enumeration purposes. */
  void removeProcess(Process *pProcess);

  /** Called by a thread when its status changes. Should be propagated directly to the
   *  SchedulingAlgorithm. */
  void threadStatusChanged(Thread *pThread);
  
  /** The main schedule function - picks another thread and switches to it.
      \param pProcessor The current processor, in case the SchedulingAlgorithm wants
                        it for heuristics such as core affinity.
      \param pThread    The thread to schedule. This is only designed to be used by
                        the debugger. */
  void schedule(Processor *pProcessor, InterruptState &state, Thread *pThread=0);

  /** Causes a syscall to yield the processor to a given thread
      If pThread is 0, the next available thread is chosen. */
  void yield(Thread *pThread=0);

#ifdef DEBUGGER
  void switchToAndDebug(InterruptState &state, Thread *pThread);
#endif

  /** Returns the number of processes currently in operation. */
  size_t getNumProcesses();
  
  /** Returns the n'th process currently in operation. */
  Process *getProcess(size_t n);
  
  /** TimerHandler callback. */
  void timer(uint64_t delta, InterruptState &state);

  /** Our "unsafe to reschedule" mutex.
   *  \note This is public so it can be accessed by the thread start trampoline. */
  Spinlock m_Mutex;

private:
  /** Default constructor
   *  \note Private - singleton class. */
  Scheduler();
  /** Copy-constructor
   *  \note Not implemented - singleton class. */
  Scheduler(const Scheduler &);
  /** Destructor
   *  \note Private - singleton class. */
  ~Scheduler();
  /** Assignment operator
   *  \note Not implemented - singleton class */
  Scheduler &operator = (const Scheduler &);

  /** The current SchedulingAlgorithm */
  SchedulingAlgorithm *m_pSchedulingAlgorithm;
  
  /** The Scheduler instance. */
  static Scheduler m_Instance;
  
  /** All the processes currently in operation, for enumeration purposes. */
  List<Process*> m_Processes;

  /** The next available process ID. */
  Atomic<size_t> m_NextPid;
};

#endif