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
#ifndef KERNEL_PROCESSOR_X86_STATE_H
#define KERNEL_PROCESSOR_X86_STATE_H

#include <compiler.h>
#include <processor/types.h>

/** @addtogroup kernelprocessorx86 x86
 * x86 processor-specific kernel
 *  @ingroup kernelprocessor
 * @{ */

/** x86 Interrupt State */
class X86InterruptState
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

    //
    // InterruptState Interface
    //
    /** Get the interrupt number
     *\return the interrupt number */
    inline size_t getInterruptNumber() const;

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
    /** The default constructor
     *\note NOT implemented */
    X86InterruptState();
    /** The copy-constructor
     *\note NOT implemented */
    X86InterruptState(const X86InterruptState &);
    /** The assignement operator
     *\note NOT implemented */
    X86InterruptState &operator = (const X86InterruptState &);
    /** The destructor
     *\note NOT implemented */
    ~X86InterruptState();

    /** The DS segment register (zero-extended to 32bit) */
    uint32_t m_Ds;
    /** The EDI general purpose register */
    uint32_t m_Edi;
    /** The ESI general purpose register */
    uint32_t m_Esi;
    /** The base-pointer register */
    uint32_t m_Ebp;
    /** Reserved/Unused (ESP) */
    uint32_t m_Res;
    /** The EBX general purpose register */
    uint32_t m_Ebx;
    /** The EDX general purpose register */
    uint32_t m_Edx;
    /** The ECX general purpose register */
    uint32_t m_Ecx;
    /** The EAX general purpose register */
    uint32_t m_Eax;
    /** The interrupt number */
    uint32_t m_IntNumber;
    /** The error-code (if any) */
    uint32_t m_Errorcode;
    /** The instruction pointer */
    uint32_t m_Eip;
    /** The CS segment register (zero-extended to 32bit) */
    uint32_t m_Cs;
    /** The extended flags (EFLAGS) */
    uint32_t m_Eflags;
    /** The stack-pointer */
    uint32_t m_Esp;
    /** The SS segment register */
    uint32_t m_Ss;
} PACKED;

/** x86 SyscallState */
typedef X86InterruptState X86SyscallState;

/** @} */

//
// Part of the Implementation
//
uintptr_t X86InterruptState::getStackPointer() const
{
  return m_Esp;
}
void X86InterruptState::setStackPointer(uintptr_t stackPointer)
{
  m_Esp = stackPointer;
}
uintptr_t X86InterruptState::getInstructionPointer() const
{
  return m_Eip;
}
void X86InterruptState::setInstructionPointer(uintptr_t instructionPointer)
{
  m_Eip = instructionPointer;
}
uintptr_t X86InterruptState::getBasePointer() const
{
  return m_Ebp;
}
void X86InterruptState::setBasePointer(uintptr_t basePointer)
{
  m_Ebp = basePointer;
}

size_t X86InterruptState::getInterruptNumber() const
{
  return m_IntNumber;
}

size_t X86InterruptState::getSyscallService() const
{
  return ((m_Eax >> 16) & 0xFFFF);
}
size_t X86InterruptState::getSyscallNumber() const
{
  return (m_Eax & 0xFFFF);
}

#endif