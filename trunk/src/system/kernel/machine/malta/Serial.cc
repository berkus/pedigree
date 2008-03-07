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
#include <machine/malta/Serial.h>
#include <machine/types.h>

MaltaSerial::MaltaSerial() :
  m_pBuffer(0),
  m_pRegs(0)
{
}

MaltaSerial::~MaltaSerial()
{
}

void MaltaSerial::setBase(uintptr_t nBaseAddr)
{
  // We use KSEG1 (uncached physical) for our IO accesses.
  m_pRegs = reinterpret_cast<serial*> (KSEG1(nBaseAddr));
}

void MaltaSerial::write(char c)
{
  while (!(m_pRegs->lstat & 0x20)) ;
  m_pRegs->rxtx = static_cast<uint8_t> (c);
}

char MaltaSerial::read()
{
  while (!(m_pRegs->lstat & 0x1)) ;
  return static_cast<char> (m_pRegs->rxtx);
}
