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

StackFrame::StackFrame(unsigned int nBasePointer, LargeStaticString mangledSymbol) :
  m_nBasePointer(nBasePointer), m_Symbol()
{
  // Demangle the given symbol, storing in m_Symbol for future use.
  demangle(mangledSymbol, &m_Symbol);
}


StackFrame::~StackFrame()
{
}

void StackFrame::prettyPrint(HugeStaticString &buf)
{
  bool bIsMember = isClassMember();
  
  buf += static_cast<const char*>(m_Symbol.name);
  buf += '(';
  
  if (bIsMember)
  {
    buf += "this=0x";
    buf.append(getParameter(0), 16);
    buf += ", ";
  }
  
  for (int i = 0; i < m_Symbol.nParams; i++)
  {
    if (i != 0)
      buf += ", ";
    
    format(getParameter((bIsMember)?i+1:i), m_Symbol.params[i], buf);
  }
  
  buf += ")\n";
}

unsigned int StackFrame::getParameter(unsigned int n)
{
  unsigned int *pPtr = reinterpret_cast<unsigned int *>(m_nBasePointer+(n+2)*sizeof(unsigned int));
  return *pPtr;
}
  
void StackFrame::format(unsigned int n, const LargeStaticString &type, HugeStaticString &dest)
{
  // Is the type a char * or const char *?
  if (type == "char*" || type == "const char*")
  {
    dest += '"';
    dest += static_cast<const char *>(type.left(32)); // Only 22 characters max.
    dest += '"';
  }
  // char? or const char?
  else if (type == "char" || type == "const char")
  {
    dest += '\'';
    dest += static_cast<char>(n);
    dest += '\'';
  }
  // bool?
  else if (type == "bool" || type == "const bool")
  {
    bool b = static_cast<bool>(n);
    if (b)
      dest += "true";
    else
      dest += "false";
  }
  // Else just use a hex integer, represented as a cast.
  else
  {
    dest += "(";
    dest += static_cast<const char*> (type);
    dest += ")0x";
    dest.append(n, 16);
  }
}

bool StackFrame::isClassMember()
{
  int nScopeIdx = m_Symbol.name.last(':');
  if (nScopeIdx == -1)
    return false;
  
  int i;
  for (i = nScopeIdx-2;
       m_Symbol.name[i] != 0 && m_Symbol.name[i] != ':';
       i--)
    ;
  i++;
  
  if (m_Symbol.name[i] >= 'A' && m_Symbol.name[i] <= 'Z')
    return true;
  else
    return false;
}