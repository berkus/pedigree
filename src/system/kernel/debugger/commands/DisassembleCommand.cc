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

#include <DisassembleCommand.h>
#include <DebuggerIO.h>
#include <udis86.h>
#include <Elf32.h>
#include <Log.h>
#include <demangle.h>

// TEMP!
extern Elf32 elf;

DisassembleCommand::DisassembleCommand()
{
}

DisassembleCommand::~DisassembleCommand()
{
}

void DisassembleCommand::autocomplete(const HugeStaticString &input, HugeStaticString &output)
{
  // TODO: add symbols.
  output = "<address>";
}

bool DisassembleCommand::execute(const HugeStaticString &input, HugeStaticString &output, InterruptState &state, DebuggerIO *screen)
{
  // This command can take either an address or a symbol name (or nothing).
  uintptr_t address;
  
  // If we see just "disassemble", no parameters were matched.
  if (input == "disassemble")
    address = state.getInstructionPointer();
  else
  {
    // Is it an address?
    address = input.intValue();

    if (address == 0)
    {
      // No, try a symbol name.
      // TODO.
      output = "Not a valid address or symbol name: `";
      output += input;
      output += "'.\n";
      return true;
    }
  }

  // Dissassemble around address.
  int nInstructions = 10;
  
  ud_t ud_obj;
  ud_init(&ud_obj);
#ifdef X86
  ud_set_mode(&ud_obj, 32);
#endif
#ifdef X86_64
  ud_set_mode(&ud_obj, 64);
#endif
  ud_set_syntax(&ud_obj, UD_SYN_INTEL);
  ud_set_pc(&ud_obj, address);
  ud_set_input_buffer(&ud_obj, reinterpret_cast<uint8_t*>(address), 256);

  for(int i = 0; i < nInstructions; i++)
  {
    ud_disassemble(&ud_obj);
    
    unsigned int location = ud_insn_off(&ud_obj);
    
    // What symbol are we in?
    // TODO grep the memory map for the right ELF to look at.
    unsigned int symStart = 0;
    const char *pSym = elf.lookupSymbol(location, &symStart);

    // Are we actually at the start location of this symbol?
    if (symStart == location)
    {
      // Print it.
#ifdef X86
      output.append(location, 16, 8, '0');
#endif
#ifdef X86_64
      output.append(location, 16, 16, '0');
#endif
      output += " <";
      
      // Demangle the symbol.
      LargeStaticString tmpStr(pSym);
      symbol_t sym;
      demangle(tmpStr, &sym);
      
      output += sym.name;
      if (sym.nParams > 0)
      {
        output += "(";
        for (int i = 0; i < sym.nParams; i++)
        {
          if (i != 0)
            output += ", ";
          output += sym.params[i];
        }
        output += ")";
      }
      output += ">:\n";
    }
    
#ifdef X86
    output.append(location, 16, 8, ' ');
#endif
#ifdef X86_64
    output.append(location, 16, 16, ' ');
#endif
    output += ": ";
    output += ud_insn_asm(&ud_obj);
    output += '\n';
  }
  
  return true;
}

const NormalStaticString DisassembleCommand::getString()
{
  return NormalStaticString("disassemble");
}