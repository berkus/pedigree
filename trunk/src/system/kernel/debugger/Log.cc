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

#include <Log.h>
#include <utility.h>

Log g_Log;

Log::Log () :
  m_nEntries(0)
{
}

Log::~Log ()
{
}

Log &Log::operator<< (const char *str)
{
  // Ensure that we don't overrun the buffer.
  int nExtraCharsAllowed = LOG_LENGTH - strlen(m_Buffer.str);
  
  strncat(m_Buffer.str, str, nExtraCharsAllowed);
  return *this;
}

Log &Log::operator<< (int n)
{
  // TODO
  return *this;
}

Log &Log::operator<< (SeverityLevel level)
{
  switch (level)
  {
  case Fatal:
  case Error:
  case Warning:
  case Notice:
    // Zero the buffer.
    m_Buffer.str[0] = '\0';
    m_Buffer.type = level;
    m_Buffer.timestamp = 0; // TODO: add timestamps.
    break;

  case End:
    // Flush the buffer.
    m_pLog[m_nEntries++] = m_Buffer;
  }
  return *this;
}

Log &Log::operator<< (NumberType type)
{
  return *this;
}