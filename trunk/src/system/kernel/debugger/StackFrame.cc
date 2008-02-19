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
#include "StackFrame.h"
#include <Log.h>

StackFrame::StackFrame(unsigned int nBasePointer, const char *pMangledSymbol) :
  m_nBasePointer(nBasePointer)
{
  NOTICE(pMangledSymbol);
  demangle(pMangledSymbol, &m_Symbol);
}


StackFrame::~StackFrame()
{
}

void StackFrame::prettyPrint(char *pBuf, unsigned int nBufLen)
{
  sprintf(pBuf, "%s(", m_Symbol.name);
  for (int i = 0; i < m_Symbol.nParams; i++)
  {
    if (i != 0)
      strcat(pBuf, ", ");
    strcat(pBuf, m_Symbol.params[i]);
  }
  strcat(pBuf, ")\n");
}

unsigned int StackFrame::getParameter(unsigned int n)
{
  unsigned int *pPtr = reinterpret_cast<unsigned int *>(m_nBasePointer-n*sizeof(unsigned int));
  return *pPtr;
}
  
void StackFrame::format(unsigned int n, const char *pType, char *pDest)
{
}
