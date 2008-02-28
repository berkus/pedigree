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
#include <processor/processor.h>
#include <Log.h>

uintptr_t Processor::getDebugBreakpoint(uint32_t nBpNumber, DebugFlags::FaultType &nFaultType, DebugFlags::Length &nLength, bool &bEnabled)
{
  uintptr_t nLinearAddress;
  switch(nBpNumber)
  {
  case 0:
    asm volatile("mov %%db0, %0" : "=r" (nLinearAddress));
    break;
  case 1:
    asm volatile("mov %%db1, %0" : "=r" (nLinearAddress));
    break;
  case 2:
    asm volatile("mov %%db2, %0" : "=r" (nLinearAddress));
    break;
  case 3:
    asm volatile("mov %%db3, %0" : "=r" (nLinearAddress));
    break;
  }
  
  uintptr_t nStatus;
  asm volatile("mov %%db7, %0" : "=r" (nStatus));

  bEnabled = static_cast<bool> (nStatus & (1 << (nBpNumber*2+1))); // See intel manual 3b.
  nFaultType = static_cast<DebugFlags::FaultType> ( (nStatus >> (nBpNumber*4+16)) & 0x3 );
  nLength = static_cast<DebugFlags::Length> ( (nStatus >> (nBpNumber*4+18)) & 0x3 );

  return nLinearAddress;
}

void Processor::enableDebugBreakpoint(uint32_t nBpNumber, uintptr_t nLinearAddress, DebugFlags::FaultType nFaultType, DebugFlags::Length nLength)
{
  switch(nBpNumber)
  {
  case 0:
    asm volatile("mov %0, %%db0" :: "r" (nLinearAddress));
    break;
  case 1:
    asm volatile("mov %0, %%db1" :: "r" (nLinearAddress));
    break;
  case 2:
    asm volatile("mov %0, %%db2" :: "r" (nLinearAddress));
    break;
  case 3:
    asm volatile("mov %0, %%db3" :: "r" (nLinearAddress));
    break;
  }
  
  uintptr_t nStatus;
  asm volatile("mov %%db7, %0" : "=r" (nStatus));
  
  nStatus |= 1 << (nBpNumber*2+1);
  nStatus |= (nFaultType&0x3) << (nBpNumber*4+16);
  nStatus |= (nLength&0x3) << (nBpNumber*4+18);
  asm volatile("mov %0, %%db7" :: "r" (nStatus));
}

void Processor::disableDebugBreakpoint(uint32_t nBpNumber)
{
  uintptr_t nStatus;
  asm volatile("mov %%db7, %0" : "=r" (nStatus));
  
  nStatus &= ~(1 << (nBpNumber*2+1));
  asm volatile("mov %0, %%db7" :: "r" (nStatus));
}

void Processor::setInterrupts(bool bEnable)
{
  asm volatile("sti");
}

void Processor::setSingleStep(bool bEnable)
{
}