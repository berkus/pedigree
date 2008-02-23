/*
 * Copyright (c) 2008 James Molloy, James Pritchett, J�rg Pf�hler, Matthew Iselin
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
#include "BreakpointCommand.h"
#include <Log.h>
#include <utility.h>
#include <DebuggerIO.h>

BreakpointCommand::BreakpointCommand()
 : DebuggerCommand()
{
}

BreakpointCommand::~BreakpointCommand()
{
}

void BreakpointCommand::autocomplete(char *input, char *output, int len)
{
}

bool BreakpointCommand::execute(char *input, char *output, int len, InterruptState &state, DebuggerIO *pScreen)
{
  // Did we get any input?

  return true;
}