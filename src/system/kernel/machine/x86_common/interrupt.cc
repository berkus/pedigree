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
#include "interrupt.h"

x86_common::InterruptManager x86_common::InterruptManager::m_Instance;

InterruptManager &InterruptManager::instance()
{
  return x86_common::InterruptManager::m_Instance;
}

void x86_common::InterruptManager::initialise()
{
  // TODO: Create an IDT
  // TODO: Load the IDT
}
bool x86_common::InterruptManager::registerInterruptHandler(size_t interruptNumber, InterruptHandler *handler)
{
  // TODO: Needs locking
  if (interruptNumber >= 256 ||
      m_Handler[interruptNumber][0] != 0)
    return false;
  
  m_Handler[interruptNumber][0] = handler;
  return true;
}
bool x86_common::InterruptManager::registerInterruptHandlerDebugger(size_t interruptNumber, InterruptHandler *handler)
{
  // TODO: Needs locking
  if (interruptNumber >= 256 ||
      m_Handler[interruptNumber][1] != 0)
    return false;
  
  m_Handler[interruptNumber][1] = handler;
  return true;
}
size_t x86_common::InterruptManager::getBreakpointInterruptNumber()
{
  return 3;
}
size_t x86_common::InterruptManager::getDebugInterruptNumber()
{
  return 1;
}

void x86_common::InterruptManager::interrupt(size_t interruptNumber, InterruptState &interruptState)
{
  // TODO: Needs locking
  /// Call the kernel debugger's handler, if any
  if (m_Instance.m_Handler[interruptNumber][1] != 0)
    m_Instance.m_Handler[interruptNumber][1]->interrupt(interruptNumber, interruptState);
  
  /// Call the normal interrupt handler, if any
  if (m_Instance.m_Handler[interruptNumber][0] != 0)
    m_Instance.m_Handler[interruptNumber][0]->interrupt(interruptNumber, interruptState);
}

x86_common::InterruptManager::InterruptManager()
{
}
x86_common::InterruptManager::~InterruptManager()
{
}
