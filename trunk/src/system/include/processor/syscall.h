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
#ifndef KERNEL_PROCESSOR_SYSCALL_H
#define KERNEL_PROCESSOR_SYSCALL_H

#include <processor/state.h>

/** @addtogroup kernelprocessor processor-specifc kernel
 * processor-specific kernel interface
 *  @ingroup kernel
 * @{ */

/** Abstract base class for all syscall-handlers. All syscall-handlers mustbe
 * derived from this class */
class SyscallHandler
{
  public:
    /** Called when the handler is registered with the syscall manager and a syscall occurred
     *\param[in] State reference to the state before the syscall */
    virtual void syscall(SyscallState &State) = 0;

  protected:
    /** Virtual destructor */
    inline virtual ~SyscallHandler(){}
};

/** The syscall manager allows syscall handler registrations and handles syscalls */
class SyscallManager
{
  public:
    /** Standard syscall service numbers */
    enum Service_t
    {
      /** Syscall service number of the kernel core */
      kernelCore = 0,
      // TODO: Add more syscall service numbers

      /** The number of syscall service numbers */
      serviceEnd
    };

    /** Get the syscall manager instance
     *\return instance of the syscall manager */
    static SyscallManager &instance();
    /** Register a syscall handler
     *\param[in] Service the service number you want to register
     *\param[in] handler the interrupt handler
     *\return true, if successfully registered, false otherwise */
    virtual bool registerSyscallHandler(Service_t Service, SyscallHandler *handler) = 0;

  protected:
    /** The constructor */
    inline SyscallManager();
    /** The destructor */
    inline virtual ~SyscallManager();

  private:
    /** The copy-constructor
     *\note Not implemented (singleton) */
    SyscallManager(const SyscallManager &);
    /** The copy-constructor
     *\note Not implemented (singleton) */
    SyscallManager &operator = (const SyscallManager &);
};

/** @} */

//
// Part of the Implementation
//
SyscallManager::SyscallManager()
{
}
SyscallManager::~SyscallManager()
{
}

#endif