/* Link.ld -- Linker script for the kernel - ensure everything goes in the */
/*            Correct place.  */

ENTRY(start)
SECTIONS
{
  . = 0xFFFFFFFF80000000 + SIZEOF_HEADERS;

  . = ALIGN(4096);
  .init : AT(ADDR(.init) - 0xFFFFFFFF7FF00000)
  {
    init = .; _init = .; __init = .;
    *(.init.multiboot)
    *(.init.text);
    *(.init.data);
    trampoline = .;
    *(.trampoline.text);
    trampoline_end = .;
  }

  . = ALIGN(4096);

  .text : AT(ADDR(.text) - 0xFFFFFFFF7FF00000)
  {
    code = .; _code = .; __code = .;
    *(.text*)
  }

  . = ALIGN(4096);

  .data : AT(ADDR(.data) - 0xFFFFFFFF7FF00000)
  {
    start_ctors = .;
    *(.ctors)
    end_ctors = .;

    data = .; _data = .; __data = .;
    *(.data)
    *(.rodata*)
  }

  . = ALIGN(4096);

  .bss : AT(ADDR(.bss) - 0xFFFFFFFF7FF00000)
  {
    bss = .; _bss = .; __bss = .;
    *(.asm.bss)
    *(.bss)
  }

  . = ALIGN(4096);

  /DISCARD/ : { *(.comment) *(.eh_frame) *(.debug_abbrev) *(.debug_info) *(.debug_line) *(.debug_loc) *(.debug_pubnames) *(.debug_aranges) *(.debug_str) }

  end = .; _end = .; __end = .;
}
