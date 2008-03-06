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
#ifndef KERNEL_PROCESSOR_MIPS32_STATE_H
#define KERNEL_PROCESSOR_MIPS32_STATE_H

#include <compiler.h>
#include <processor/types.h>

/** @ingroup kernelprocessorMIPS32
 * @{ */

/** MIPS32 Interrupt State */
class MIPS32InterruptState
{
  public:
    //
    // General Interface (both InterruptState and SyscallState)
    //
    /** Get the stack-pointer before the interrupt occured
     *\return the stack-pointer before the interrupt */
    inline uintptr_t getStackPointer() const;
    /** Set the userspace stack-pointer
     *\param[in] stackPointer the new stack-pointer */
    inline void setStackPointer(uintptr_t stackPointer);
    /** Get the instruction-pointer of the next instruction that is executed
     * after the interrupt is processed
     *\return the instruction-pointer */
    inline uintptr_t getInstructionPointer() const;
    /** Set the instruction-pointer
     *\param[in] instructionPointer the new instruction-pointer */
    inline void setInstructionPointer(uintptr_t instructionPointer);
    /** Get the base-pointer
     *\return the base-pointer */
    inline uintptr_t getBasePointer() const;
    /** Set the base-pointer
     *\param[in] basePointer the new base-pointer */
    inline void setBasePointer(uintptr_t basePointer);
    /** Get the number of registers
     *\return the number of registers */
    size_t getRegisterCount() const;
    /** Get a specific register
     *\param[in] index the index of the register (from 0 to getRegisterCount() - 1)
     *\return the value of the register */
    processor_register_t getRegister(size_t index) const;
    /** Get the name of a specific register
     *\param[in] index the index of the register (from 0 to getRegisterCount() - 1)
     *\return the name of the register */
    const char *getRegisterName(size_t index) const;
    /** Get the register's size in bytes
     *\param[in] index the index of the register (from 0 to getRegisterCount() - 1)
     *\return the register size in bytes */
    inline size_t getRegisterSize(size_t index) const;

    //
    // InterruptState Interface
    //
    /** Did the interrupt happen in kernel-mode?
     *\return true, if the interrupt happened in kernel-mode, false otherwise */
    inline bool kernelMode() const;
    /** Get the interrupt number
     *\return the interrupt number */
    inline size_t getInterruptNumber() const;

  private:
    /** The default constructor
     *\note NOT implemented */
    MIPS32InterruptState();
    /** The copy-constructor
     *\note NOT implemented */
    MIPS32InterruptState(const MIPS32InterruptState &);
    /** The assignement operator
     *\note NOT implemented */
    MIPS32InterruptState &operator = (const MIPS32InterruptState &);
    /** The destructor
     *\note NOT implemented */
    ~MIPS32InterruptState();
} PACKED;

class MIPS32SyscallState
{
  public:
    //
    // General Interface (both InterruptState and SyscallState)
    //
    /** Get the stack-pointer before the syscall occured
     *\return the stack-pointer before the syscall */
    inline uintptr_t getStackPointer() const;
    /** Set the userspace stack-pointer
     *\param[in] stackPointer the new stack-pointer */
    inline void setStackPointer(uintptr_t stackPointer);
    /** Get the instruction-pointer of the next instruction that is executed
     * after the syscall is processed
     *\return the instruction-pointer */
    inline uintptr_t getInstructionPointer() const;
    /** Set the instruction-pointer
     *\param[in] instructionPointer the new instruction-pointer */
    inline void setInstructionPointer(uintptr_t instructionPointer);
    /** Get the base-pointer
     *\return the base-pointer */
    inline uintptr_t getBasePointer() const;
    /** Set the base-pointer
     *\param[in] basePointer the new base-pointer */
    inline void setBasePointer(uintptr_t basePointer);
    /** Get the number of registers
     *\return the number of registers */
    size_t getRegisterCount() const;
    /** Get a specific register
     *\param[in] index the index of the register (from 0 to getRegisterCount() - 1)
     *\return the value of the register */
    processor_register_t getRegister(size_t index) const;
    /** Get the name of a specific register
     *\param[in] index the index of the register (from 0 to getRegisterCount() - 1)
     *\return the name of the register */
    const char *getRegisterName(size_t index) const;
    /** Get the register's size in bytes
     *\param[in] index the index of the register (from 0 to getRegisterCount() - 1)
     *\return the register size in bytes */
    inline size_t getRegisterSize(size_t index) const;

    //
    // SyscallState Interface
    //
    /** Get the syscall service number
     *\return the syscall service number */
    inline size_t getSyscallService() const;
    /** Get the syscall function number
     *\return the syscall function number */
    inline size_t getSyscallNumber() const;

  private:
} PACKED;

/** @} */

//
// Part of the Implementation
//
uintptr_t MIPS32InterruptState::getStackPointer() const
{
  return 0;
}
void MIPS32InterruptState::setStackPointer(uintptr_t stackPointer)
{
}
uintptr_t MIPS32InterruptState::getInstructionPointer() const
{
  return 0;
}
void MIPS32InterruptState::setInstructionPointer(uintptr_t instructionPointer)
{
}
uintptr_t MIPS32InterruptState::getBasePointer() const
{
  return 0;
}
void MIPS32InterruptState::setBasePointer(uintptr_t basePointer)
{
}
size_t MIPS32InterruptState::getRegisterSize(size_t index) const
{
  return 4;
}

bool MIPS32InterruptState::kernelMode() const
{
  return false;
}
size_t MIPS32InterruptState::getInterruptNumber() const
{
  return 0;
}

uintptr_t MIPS32SyscallState::getStackPointer() const
{
  return 0;
}
void MIPS32SyscallState::setStackPointer(uintptr_t stackPointer)
{
}
uintptr_t MIPS32SyscallState::getInstructionPointer() const
{
  return 0;
}
void MIPS32SyscallState::setInstructionPointer(uintptr_t instructionPointer)
{
}
uintptr_t MIPS32SyscallState::getBasePointer() const
{
  return 0;
}
void MIPS32SyscallState::setBasePointer(uintptr_t basePointer)
{
}
size_t MIPS32SyscallState::getRegisterSize(size_t index) const
{
  return 4;
}

size_t MIPS32SyscallState::getSyscallService() const
{
  return 0;
}
size_t MIPS32SyscallState::getSyscallNumber() const
{
  return 0;
}

#endif
