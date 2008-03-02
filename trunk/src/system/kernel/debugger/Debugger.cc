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
#include <Debugger.h>
#include <DebuggerIO.h>
#include <LocalIO.h>
#include <DisassembleCommand.h>
#include <QuitCommand.h>
#include <BreakpointCommand.h>
#include <DumpCommand.h>
#include <LogViewer.h>
#include <Backtracer.h>
#include <utility.h>

Debugger Debugger::m_Instance;

/// Helper function. Returns the index of a command in pCommands that matches prefix. Starts searching
/// through pCommands at index start. Returns -1 if none found.
static int getCommandMatchingPrefix(char *prefix, DebuggerCommand **pCommands, int nCmds, int start)
{
  for (int i = start; i < nCmds; i++)
  {
    if (!strncmp(pCommands[i]->getString(), prefix, strlen(prefix)))
      return i;
  }
  return -1;
}

/// Helper function. Returns true if the string in pStr matches pCommand. If so, pStr is changed
/// so that on return, it contains the parameters to that command (everything after the first space).
static bool matchesCommand(char *pStr, DebuggerCommand *pCommand)
{
  if (!strncmp(pCommand->getString(), pStr, strlen(pCommand->getString())))
  {
    int n = strlen(pCommand->getString());
    memcpy(pStr, pStr+n+1, strlen(pStr)-n);
    return true;
  }
  else
  {
    return false;
  }
}

Debugger::Debugger() :
  m_nIoType(DEBUGGER)
{

}

Debugger::~Debugger()
{
}

void Debugger::initialise()
{
  if (!InterruptManager::instance().registerInterruptHandlerDebugger(InterruptManager::instance().getBreakpointInterruptNumber(), this))
    ERROR("Debugger: breakpoint interrupt registration failed!");
  if (!InterruptManager::instance().registerInterruptHandlerDebugger(InterruptManager::instance().getDebugInterruptNumber(), this))
    ERROR("Debugger: debug interrupt registration failed!");
}

void Debugger::breakpoint(InterruptState &state)
{
  
  // IO interface.
  DebuggerIO *pIo;
  
  // IO implementations.
  LocalIO localIO;
  //SerialIO serialIO;
  
  // Commands.
  DisassembleCommand disassembler;
  LogViewer logViewer;
  Backtracer backtracer;
  QuitCommand quit;
  BreakpointCommand breakpoint;
  DumpCommand dump;
  
  int nCommands = 6;
  DebuggerCommand *pCommands[] = {&disassembler,
                                  &logViewer,
                                  &backtracer,
                                  &quit,
                                  &breakpoint,
                                  &dump};
  
  if (m_nIoType == MONITOR) pIo = &localIO;
  else
  {
    // serial
  }
  
  pIo->setCliUpperLimit(1); // Give us room for a status bar on top.
  pIo->setCliLowerLimit(1); // And a status bar on the bottom.
  pIo->enableCli(); // Start CLI mode.

  // Main CLI loop.
  bool bKeepGoing = false;
  do
  {
    // Clear the top and bottom status lines.
    pIo->drawHorizontalLine(' ', 0, 0, 79, DebuggerIO::White, DebuggerIO::DarkGrey);
    pIo->drawHorizontalLine(' ', 24, 0, 79, DebuggerIO::White, DebuggerIO::DarkGrey);
    // Write the correct text in the upper status line.
    pIo->drawString("Pedigree debugger", 0, 0, DebuggerIO::White, DebuggerIO::DarkGrey);
  
    bool matchedCommand = false;
    HugeStaticString command;
    DebuggerCommand *pAutoComplete = 0;
    while(1)
    {
      // Try and get a character from the CLI, passing in a buffer to populate and an
      // autocomplete command for if the user presses TAB (if one is defined).
      if (pIo->readCli(const_cast<char*>((const char*)command), 256, pAutoComplete))
        break; // Command complete, try and parse it.
  
      // The command wasn't complete - let's parse it and try and get an autocomplete string.
      HugeStaticString autoStr;
      char pStr2[64];
      matchedCommand = false;
      for (int i = 0; i < nCommands; i++)
      {
        if (matchesCommand(const_cast<char*>((const char*)command), pCommands[i]))
        {
          strcpy(pStr2, pCommands[i]->getString());
          strcat(pStr2, " ");
          pCommands[i]->autocomplete(command, autoStr);
          matchedCommand = true;
          break;
        }
      }
  
      HugeStaticString str;
      pAutoComplete = 0;
      if (!matchedCommand)
      {
        pStr2[0] = '\0';
        str = "";
        int i = -1;
        while ( (i = getCommandMatchingPrefix(const_cast<char*>((const char*)command), pCommands, nCommands, i+1)) != -1)
        {
          if (!pAutoComplete)
            pAutoComplete = pCommands[i];
          str += static_cast<const char*> (pCommands[i]->getString());
          str += " ";
        }
      }
      
      pIo->drawHorizontalLine(' ', 24, 0, 79, DebuggerIO::White, DebuggerIO::DarkGrey);
      pIo->drawString(pStr2, 24, 0, DebuggerIO::Yellow, DebuggerIO::DarkGrey);
      pIo->drawString(str, 24, strlen(pStr2), DebuggerIO::White, DebuggerIO::DarkGrey);
    }
  
    // A command was entered.
    bool bValidCommand = false;
    HugeStaticString output;
    for (int i = 0; i < nCommands; i++)
    {
      if (matchesCommand(const_cast<char*>((const char*)command), pCommands[i]))
      {
        bKeepGoing = pCommands[i]->execute(command, output, state, pIo);
        pIo->writeCli(output, DebuggerIO::LightGrey, DebuggerIO::Black);
        bValidCommand = true;
      }
    }
    
    if (!bValidCommand)
    {
      pIo->writeCli("Unrecognised command.\n", DebuggerIO::LightGrey, DebuggerIO::Black);
      bKeepGoing = true;
    }
  
  }
  while (bKeepGoing);

}

void Debugger::interrupt(size_t interruptNumber, InterruptState &state)
{
  // We switch here on the interrupt number, and dispatch accordingly.
  if (interruptNumber == InterruptManager::instance().getBreakpointInterruptNumber())
  {
    breakpoint(state);
  }
  else if (interruptNumber == InterruptManager::instance().getDebugInterruptNumber())
  {
    // debug(state);
  }
}
