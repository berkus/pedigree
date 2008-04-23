/*
 * Copyright (c) 2008 James Molloy, James Pritchett, Jörg Pfähler, Matthew Iselin
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

/**
 * \brief This class manages how processes and threads are scheduled across processors.
 * It delegates the task of selecting when to run each process to a SchedulingAlgorithm,
 * and attempts to run in a tickless fashion, if the hardware supports it (Local APIC present).
 */
class Scheduler
{
public:
  /** Get the instance of the scheduler */
  inline static Scheduler &instance() {return m_Instance;}

  /** Initialises the scheduler. */
  bool initialise();
  
  /** Retrieves the current SchedulingAlgorithm */
  SchedulingAlgorithm *getAlgorithm();
  /** Sets the current SchedulingAlgorithm */
  void setAlgorithm(SchedulingAlgorithm *pAlgorithm);

  /** Adds a thread to be scheduled. */
  void addThread(Thread *pThread);
  /** Removes a thread from being scheduled. */
  void removeThread(Thread *pThread);

  /** The main schedule function - picks another thread and switches to it.
      \param pProcessor The current processor, in case the SchedulingAlgorithm wants
                        it for heuristics such as core affinity. */
  void schedule(Processor *pProcessor);

private:
  /**
   * Default constructor
   * \note Private - singleton class.
   */
  Scheduler();
  /**
   * Destructor
   * \note Private - singleton class.
   */
  ~Scheduler();

  /** The Scheduler instance. */
  static Scheduler m_Instance;
};

#endif