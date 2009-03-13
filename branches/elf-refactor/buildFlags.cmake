#
# Copyright (c) 2008 James Molloy, James Pritchett, Jörg Pfähler, Matthew Iselin
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#

#
# AUTOGENERATED BY 'scripts/parseBuildFlags.pl' FROM 'buildFlags' -- DO NOT EDIT!
#                                                                    ===========

# Define rules initially.
if(NOT DEFINED RULES_DEFINED)
  set(RULES_DEFINED YES CACHE INTERNAL "Rules defined." FORCE)
  set(X64 OFF CACHE BOOL "X64")
  set(MIPS_MALTA OFF CACHE BOOL "MIPS_MALTA")
  set(MIPS_AU1500 OFF CACHE BOOL "MIPS_AU1500")
  set(APIC OFF CACHE BOOL "APIC")
  mark_as_advanced(FORCE APIC)
  set(OMIT_FRAMEPOINTER OFF CACHE INTERNAL "OMIT_FRAMEPOINTER")
  set(SMP_NOTICE OFF CACHE INTERNAL "SMP_NOTICE")
  set(SERIAL_IS_FILE OFF CACHE BOOL "SERIAL_IS_FILE")
  mark_as_advanced(FORCE SERIAL_IS_FILE)
  set(KERNEL_NEEDS_ADDRESS_SPACE_SWITCH OFF CACHE INTERNAL "KERNEL_NEEDS_ADDRESS_SPACE_SWITCH")
  set(ARM_VERSATILE OFF CACHE BOOL "ARM_VERSATILE")
  set(BIG_ENDIAN OFF CACHE INTERNAL "BIG_ENDIAN")
  set(KERNEL_PROCESSOR_NO_PORT_IO OFF CACHE INTERNAL "KERNEL_PROCESSOR_NO_PORT_IO")
  set(ASIDS OFF CACHE INTERNAL "ASIDS")
  set(THREADS ON CACHE BOOL "THREADS")
  set(DEBUGGER_RUN_AT_START ON CACHE BOOL "DEBUGGER_RUN_AT_START")
  set(SMP_ERROR OFF CACHE INTERNAL "SMP_ERROR")
  set(OPENFIRMWARE OFF CACHE INTERNAL "OPENFIRMWARE")
  set(SMBIOS OFF CACHE BOOL "SMBIOS")
  mark_as_advanced(FORCE SMBIOS)
  set(LITTLE_ENDIAN OFF CACHE INTERNAL "LITTLE_ENDIAN")
  set(BITS_32 OFF CACHE INTERNAL "BITS_32")
  set(ADDITIONAL_CHECKS OFF CACHE INTERNAL "ADDITIONAL_CHECKS")
  set(ECHO_CONSOLE_TO_SERIAL ON CACHE BOOL "ECHO_CONSOLE_TO_SERIAL")
  set(MULTIPROCESSOR OFF CACHE BOOL "MULTIPROCESSOR")
  mark_as_advanced(FORCE MULTIPROCESSOR)
  set(OMIT_FRAME_POINTER OFF CACHE BOOL "OMIT_FRAME_POINTER")
  mark_as_advanced(FORCE OMIT_FRAME_POINTER)
  set(X86_COMMON OFF CACHE INTERNAL "X86_COMMON")
  set(DEBUGGER_QWERTZ OFF CACHE BOOL "DEBUGGER_QWERTZ")
  set(MIPS_AU1500_DB1500 OFF CACHE BOOL "MIPS_AU1500_DB1500")
  set(PPC32 OFF CACHE INTERNAL "PPC32")
  set(DWARF ON CACHE BOOL "DWARF")
  set(SMP OFF CACHE BOOL "SMP")
  mark_as_advanced(FORCE SMP)
  set(ACPI OFF CACHE BOOL "ACPI")
  mark_as_advanced(FORCE ACPI)
  set(MIPS32 OFF CACHE BOOL "MIPS32")
  set(BITS_64 OFF CACHE INTERNAL "BITS_64")
  set(MIPS_COMMON OFF CACHE INTERNAL "MIPS_COMMON")
  set(MIPS_MALTA_BONITO64 OFF CACHE BOOL "MIPS_MALTA_BONITO64")
  set(PPC_MAC OFF CACHE BOOL "PPC_MAC")
  set(ACPI_NOTICE OFF CACHE INTERNAL "ACPI_NOTICE")
  set(ARM_INTEGRATOR OFF CACHE BOOL "ARM_INTEGRATOR")
  set(DEBUGGER_QWERTY ON CACHE BOOL "DEBUGGER_QWERTY")
  set(PPC_COMMON OFF CACHE INTERNAL "PPC_COMMON")
  set(DEBUGGER ON CACHE BOOL "DEBUGGER")
  set(VERBOSE_MEMORY_MANAGER OFF CACHE BOOL "VERBOSE_MEMORY_MANAGER")
  mark_as_advanced(FORCE VERBOSE_MEMORY_MANAGER)
  set(ACPI_ERROR OFF CACHE INTERNAL "ACPI_ERROR")
  set(X86 ON CACHE BOOL "X86")
  set(ARM_COMMON OFF CACHE INTERNAL "ARM_COMMON")
  set(KERNEL_STANDALONE OFF CACHE INTERNAL "KERNEL_STANDALONE")
  set(ARM926E OFF CACHE BOOL "ARM926E")
endif(NOT DEFINED RULES_DEFINED)

# Loop five times - hopefully then no more variables will be being changed.
foreach(CHANGED RANGE 5)

  # Rule: DWARF.
  if(DWARF)
    set(DWARF-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} DWARF)
    # Set flags  .
  else(DWARF)
    if(DWARF-PREV STREQUAL ON)
      set(DWARF-PREV OFF CACHE INTERNAL "" FORCE)
    endif(DWARF-PREV STREQUAL ON)
  endif(DWARF)
  # Rule: MIPS_MALTA.
  if(MIPS_MALTA)
    set(MIPS_MALTA-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} MIPS_MALTA)
    # Set flags MIPS32.
    set(MIPS32 ON CACHE BOOL "MIPS32" FORCE)
    set(DEFINES ${DEFINES} MIPS32)
  else(MIPS_MALTA)
    if(MIPS_MALTA-PREV STREQUAL ON)
      set(MIPS_MALTA-PREV OFF CACHE INTERNAL "" FORCE)
      list(REMOVE_ITEM DEFINES MIPS32)
    endif(MIPS_MALTA-PREV STREQUAL ON)
  endif(MIPS_MALTA)
  # Rule: X64.
  if(X64)
    set(X64-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} X64)
    # Set flags ADDITIONAL_CHECKS BITS_64 LITTLE_ENDIAN KERNEL_STANDALONE X86_COMMON.
    set(ADDITIONAL_CHECKS ON CACHE INTERNAL "ADDITIONAL_CHECKS" FORCE)
    set(DEFINES ${DEFINES} ADDITIONAL_CHECKS)
    set(BITS_64 ON CACHE INTERNAL "BITS_64" FORCE)
    set(DEFINES ${DEFINES} BITS_64)
    set(LITTLE_ENDIAN ON CACHE INTERNAL "LITTLE_ENDIAN" FORCE)
    set(DEFINES ${DEFINES} LITTLE_ENDIAN)
    set(KERNEL_STANDALONE ON CACHE INTERNAL "KERNEL_STANDALONE" FORCE)
    set(DEFINES ${DEFINES} KERNEL_STANDALONE)
    set(X86_COMMON ON CACHE INTERNAL "X86_COMMON" FORCE)
    set(DEFINES ${DEFINES} X86_COMMON)
  else(X64)
    if(X64-PREV STREQUAL ON)
      set(X64-PREV OFF CACHE INTERNAL "" FORCE)
      set(ADDITIONAL_CHECKS OFF CACHE INTERNAL "ADDITIONAL_CHECKS" FORCE)
      list(REMOVE_ITEM DEFINES ADDITIONAL_CHECKS)
      set(BITS_64 OFF CACHE INTERNAL "BITS_64" FORCE)
      list(REMOVE_ITEM DEFINES BITS_64)
      set(LITTLE_ENDIAN OFF CACHE INTERNAL "LITTLE_ENDIAN" FORCE)
      list(REMOVE_ITEM DEFINES LITTLE_ENDIAN)
      set(KERNEL_STANDALONE OFF CACHE INTERNAL "KERNEL_STANDALONE" FORCE)
      list(REMOVE_ITEM DEFINES KERNEL_STANDALONE)
      set(X86_COMMON OFF CACHE INTERNAL "X86_COMMON" FORCE)
      list(REMOVE_ITEM DEFINES X86_COMMON)
    endif(X64-PREV STREQUAL ON)
  endif(X64)
  # Rule: APIC.
  if(APIC)
    set(APIC-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} APIC)
    # Set flags  .
  else(APIC)
    if(APIC-PREV STREQUAL ON)
      set(APIC-PREV OFF CACHE INTERNAL "" FORCE)
    endif(APIC-PREV STREQUAL ON)
  endif(APIC)
  # Rule: MIPS_AU1500.
  if(MIPS_AU1500)
    set(MIPS_AU1500-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} MIPS_AU1500)
    # Set flags MIPS32.
    set(MIPS32 ON CACHE BOOL "MIPS32" FORCE)
    set(DEFINES ${DEFINES} MIPS32)
  else(MIPS_AU1500)
    if(MIPS_AU1500-PREV STREQUAL ON)
      set(MIPS_AU1500-PREV OFF CACHE INTERNAL "" FORCE)
      list(REMOVE_ITEM DEFINES MIPS32)
    endif(MIPS_AU1500-PREV STREQUAL ON)
  endif(MIPS_AU1500)
  # Rule: SERIAL_IS_FILE.
  if(SERIAL_IS_FILE)
    set(SERIAL_IS_FILE-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} SERIAL_IS_FILE)
    # Set flags  .
  else(SERIAL_IS_FILE)
    if(SERIAL_IS_FILE-PREV STREQUAL ON)
      set(SERIAL_IS_FILE-PREV OFF CACHE INTERNAL "" FORCE)
    endif(SERIAL_IS_FILE-PREV STREQUAL ON)
  endif(SERIAL_IS_FILE)
  # Rule: SMP.
  if(SMP)
    set(SMP-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} SMP)
    # Set flags SMP_NOTICE SMP_ERROR.
    set(SMP_NOTICE ON CACHE INTERNAL "SMP_NOTICE" FORCE)
    set(DEFINES ${DEFINES} SMP_NOTICE)
    set(SMP_ERROR ON CACHE INTERNAL "SMP_ERROR" FORCE)
    set(DEFINES ${DEFINES} SMP_ERROR)
  else(SMP)
    if(SMP-PREV STREQUAL ON)
      set(SMP-PREV OFF CACHE INTERNAL "" FORCE)
      set(SMP_NOTICE OFF CACHE INTERNAL "SMP_NOTICE" FORCE)
      list(REMOVE_ITEM DEFINES SMP_NOTICE)
      set(SMP_ERROR OFF CACHE INTERNAL "SMP_ERROR" FORCE)
      list(REMOVE_ITEM DEFINES SMP_ERROR)
    endif(SMP-PREV STREQUAL ON)
  endif(SMP)
  # Rule: ARM_VERSATILE.
  if(ARM_VERSATILE)
    set(ARM_VERSATILE-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} ARM_VERSATILE)
    # Set flags ARM926E.
    set(ARM926E ON CACHE BOOL "ARM926E" FORCE)
    set(DEFINES ${DEFINES} ARM926E)
  else(ARM_VERSATILE)
    if(ARM_VERSATILE-PREV STREQUAL ON)
      set(ARM_VERSATILE-PREV OFF CACHE INTERNAL "" FORCE)
      list(REMOVE_ITEM DEFINES ARM926E)
    endif(ARM_VERSATILE-PREV STREQUAL ON)
  endif(ARM_VERSATILE)
  # Rule: ACPI.
  if(ACPI)
    set(ACPI-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} ACPI)
    # Set flags ACPI_NOTICE ACPI_ERROR.
    set(ACPI_NOTICE ON CACHE INTERNAL "ACPI_NOTICE" FORCE)
    set(DEFINES ${DEFINES} ACPI_NOTICE)
    set(ACPI_ERROR ON CACHE INTERNAL "ACPI_ERROR" FORCE)
    set(DEFINES ${DEFINES} ACPI_ERROR)
  else(ACPI)
    if(ACPI-PREV STREQUAL ON)
      set(ACPI-PREV OFF CACHE INTERNAL "" FORCE)
      set(ACPI_NOTICE OFF CACHE INTERNAL "ACPI_NOTICE" FORCE)
      list(REMOVE_ITEM DEFINES ACPI_NOTICE)
      set(ACPI_ERROR OFF CACHE INTERNAL "ACPI_ERROR" FORCE)
      list(REMOVE_ITEM DEFINES ACPI_ERROR)
    endif(ACPI-PREV STREQUAL ON)
  endif(ACPI)
  # Rule: MIPS32.
  if(MIPS32)
    set(MIPS32-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} MIPS32)
    # Set flags MIPS_COMMON BITS_32 LITTLE_ENDIAN ASIDS.
    set(MIPS_COMMON ON CACHE INTERNAL "MIPS_COMMON" FORCE)
    set(DEFINES ${DEFINES} MIPS_COMMON)
    set(BITS_32 ON CACHE INTERNAL "BITS_32" FORCE)
    set(DEFINES ${DEFINES} BITS_32)
    set(LITTLE_ENDIAN ON CACHE INTERNAL "LITTLE_ENDIAN" FORCE)
    set(DEFINES ${DEFINES} LITTLE_ENDIAN)
    set(ASIDS ON CACHE INTERNAL "ASIDS" FORCE)
    set(DEFINES ${DEFINES} ASIDS)
  else(MIPS32)
    if(MIPS32-PREV STREQUAL ON)
      set(MIPS32-PREV OFF CACHE INTERNAL "" FORCE)
      set(MIPS_COMMON OFF CACHE INTERNAL "MIPS_COMMON" FORCE)
      list(REMOVE_ITEM DEFINES MIPS_COMMON)
      set(BITS_32 OFF CACHE INTERNAL "BITS_32" FORCE)
      list(REMOVE_ITEM DEFINES BITS_32)
      set(LITTLE_ENDIAN OFF CACHE INTERNAL "LITTLE_ENDIAN" FORCE)
      list(REMOVE_ITEM DEFINES LITTLE_ENDIAN)
      set(ASIDS OFF CACHE INTERNAL "ASIDS" FORCE)
      list(REMOVE_ITEM DEFINES ASIDS)
    endif(MIPS32-PREV STREQUAL ON)
  endif(MIPS32)
  # Rule: THREADS.
  if(THREADS)
    set(THREADS-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} THREADS)
    # Set flags  .
  else(THREADS)
    if(THREADS-PREV STREQUAL ON)
      set(THREADS-PREV OFF CACHE INTERNAL "" FORCE)
    endif(THREADS-PREV STREQUAL ON)
  endif(THREADS)
  # Rule: DEBUGGER_RUN_AT_START.
  if(DEBUGGER_RUN_AT_START)
    set(DEBUGGER_RUN_AT_START-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} DEBUGGER_RUN_AT_START)
    # Set flags  .
  else(DEBUGGER_RUN_AT_START)
    if(DEBUGGER_RUN_AT_START-PREV STREQUAL ON)
      set(DEBUGGER_RUN_AT_START-PREV OFF CACHE INTERNAL "" FORCE)
    endif(DEBUGGER_RUN_AT_START-PREV STREQUAL ON)
  endif(DEBUGGER_RUN_AT_START)
  # Rule: MIPS_COMMON.
  if(MIPS_COMMON)
    set(MIPS_COMMON-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} MIPS_COMMON)
    # Set flags KERNEL_PROCESSOR_NO_PORT_IO OMIT_FRAMEPOINTER.
    set(KERNEL_PROCESSOR_NO_PORT_IO ON CACHE INTERNAL "KERNEL_PROCESSOR_NO_PORT_IO" FORCE)
    set(DEFINES ${DEFINES} KERNEL_PROCESSOR_NO_PORT_IO)
    set(OMIT_FRAMEPOINTER ON CACHE INTERNAL "OMIT_FRAMEPOINTER" FORCE)
    set(DEFINES ${DEFINES} OMIT_FRAMEPOINTER)
  else(MIPS_COMMON)
    if(MIPS_COMMON-PREV STREQUAL ON)
      set(MIPS_COMMON-PREV OFF CACHE INTERNAL "" FORCE)
      set(KERNEL_PROCESSOR_NO_PORT_IO OFF CACHE INTERNAL "KERNEL_PROCESSOR_NO_PORT_IO" FORCE)
      list(REMOVE_ITEM DEFINES KERNEL_PROCESSOR_NO_PORT_IO)
      set(OMIT_FRAMEPOINTER OFF CACHE INTERNAL "OMIT_FRAMEPOINTER" FORCE)
      list(REMOVE_ITEM DEFINES OMIT_FRAMEPOINTER)
    endif(MIPS_COMMON-PREV STREQUAL ON)
  endif(MIPS_COMMON)
  # Rule: MIPS_MALTA_BONITO64.
  if(MIPS_MALTA_BONITO64)
    set(MIPS_MALTA_BONITO64-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} MIPS_MALTA_BONITO64)
    # Set flags MIPS_MALTA.
    set(MIPS_MALTA ON CACHE BOOL "MIPS_MALTA" FORCE)
    set(DEFINES ${DEFINES} MIPS_MALTA)
  else(MIPS_MALTA_BONITO64)
    if(MIPS_MALTA_BONITO64-PREV STREQUAL ON)
      set(MIPS_MALTA_BONITO64-PREV OFF CACHE INTERNAL "" FORCE)
      list(REMOVE_ITEM DEFINES MIPS_MALTA)
    endif(MIPS_MALTA_BONITO64-PREV STREQUAL ON)
  endif(MIPS_MALTA_BONITO64)
  # Rule: SMBIOS.
  if(SMBIOS)
    set(SMBIOS-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} SMBIOS)
    # Set flags  .
  else(SMBIOS)
    if(SMBIOS-PREV STREQUAL ON)
      set(SMBIOS-PREV OFF CACHE INTERNAL "" FORCE)
    endif(SMBIOS-PREV STREQUAL ON)
  endif(SMBIOS)
  # Rule: PPC_MAC.
  if(PPC_MAC)
    set(PPC_MAC-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} PPC_MAC)
    # Set flags PPC_COMMON PPC32 BITS_32 BIG_ENDIAN.
    set(PPC_COMMON ON CACHE INTERNAL "PPC_COMMON" FORCE)
    set(DEFINES ${DEFINES} PPC_COMMON)
    set(PPC32 ON CACHE INTERNAL "PPC32" FORCE)
    set(DEFINES ${DEFINES} PPC32)
    set(BITS_32 ON CACHE INTERNAL "BITS_32" FORCE)
    set(DEFINES ${DEFINES} BITS_32)
    set(BIG_ENDIAN ON CACHE INTERNAL "BIG_ENDIAN" FORCE)
    set(DEFINES ${DEFINES} BIG_ENDIAN)
  else(PPC_MAC)
    if(PPC_MAC-PREV STREQUAL ON)
      set(PPC_MAC-PREV OFF CACHE INTERNAL "" FORCE)
      set(PPC_COMMON OFF CACHE INTERNAL "PPC_COMMON" FORCE)
      list(REMOVE_ITEM DEFINES PPC_COMMON)
      set(PPC32 OFF CACHE INTERNAL "PPC32" FORCE)
      list(REMOVE_ITEM DEFINES PPC32)
      set(BITS_32 OFF CACHE INTERNAL "BITS_32" FORCE)
      list(REMOVE_ITEM DEFINES BITS_32)
      set(BIG_ENDIAN OFF CACHE INTERNAL "BIG_ENDIAN" FORCE)
      list(REMOVE_ITEM DEFINES BIG_ENDIAN)
    endif(PPC_MAC-PREV STREQUAL ON)
  endif(PPC_MAC)
  # Rule: ARM_INTEGRATOR.
  if(ARM_INTEGRATOR)
    set(ARM_INTEGRATOR-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} ARM_INTEGRATOR)
    # Set flags ARM926E.
    set(ARM926E ON CACHE BOOL "ARM926E" FORCE)
    set(DEFINES ${DEFINES} ARM926E)
  else(ARM_INTEGRATOR)
    if(ARM_INTEGRATOR-PREV STREQUAL ON)
      set(ARM_INTEGRATOR-PREV OFF CACHE INTERNAL "" FORCE)
      list(REMOVE_ITEM DEFINES ARM926E)
    endif(ARM_INTEGRATOR-PREV STREQUAL ON)
  endif(ARM_INTEGRATOR)
  # Rule: DEBUGGER_QWERTY.
  if(DEBUGGER_QWERTY)
    set(DEBUGGER_QWERTY-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} DEBUGGER_QWERTY)
    # Set flags  .
  else(DEBUGGER_QWERTY)
    if(DEBUGGER_QWERTY-PREV STREQUAL ON)
      set(DEBUGGER_QWERTY-PREV OFF CACHE INTERNAL "" FORCE)
    endif(DEBUGGER_QWERTY-PREV STREQUAL ON)
  endif(DEBUGGER_QWERTY)
  # Rule: PPC_COMMON.
  if(PPC_COMMON)
    set(PPC_COMMON-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} PPC_COMMON)
    # Set flags KERNEL_PROCESSOR_NO_PORT_IO OMIT_FRAMEPOINTER OPENFIRMWARE.
    set(KERNEL_PROCESSOR_NO_PORT_IO ON CACHE INTERNAL "KERNEL_PROCESSOR_NO_PORT_IO" FORCE)
    set(DEFINES ${DEFINES} KERNEL_PROCESSOR_NO_PORT_IO)
    set(OMIT_FRAMEPOINTER ON CACHE INTERNAL "OMIT_FRAMEPOINTER" FORCE)
    set(DEFINES ${DEFINES} OMIT_FRAMEPOINTER)
    set(OPENFIRMWARE ON CACHE INTERNAL "OPENFIRMWARE" FORCE)
    set(DEFINES ${DEFINES} OPENFIRMWARE)
  else(PPC_COMMON)
    if(PPC_COMMON-PREV STREQUAL ON)
      set(PPC_COMMON-PREV OFF CACHE INTERNAL "" FORCE)
      set(KERNEL_PROCESSOR_NO_PORT_IO OFF CACHE INTERNAL "KERNEL_PROCESSOR_NO_PORT_IO" FORCE)
      list(REMOVE_ITEM DEFINES KERNEL_PROCESSOR_NO_PORT_IO)
      set(OMIT_FRAMEPOINTER OFF CACHE INTERNAL "OMIT_FRAMEPOINTER" FORCE)
      list(REMOVE_ITEM DEFINES OMIT_FRAMEPOINTER)
      set(OPENFIRMWARE OFF CACHE INTERNAL "OPENFIRMWARE" FORCE)
      list(REMOVE_ITEM DEFINES OPENFIRMWARE)
    endif(PPC_COMMON-PREV STREQUAL ON)
  endif(PPC_COMMON)
  # Rule: DEBUGGER.
  if(DEBUGGER)
    set(DEBUGGER-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} DEBUGGER)
    # Set flags  .
  else(DEBUGGER)
    if(DEBUGGER-PREV STREQUAL ON)
      set(DEBUGGER-PREV OFF CACHE INTERNAL "" FORCE)
    endif(DEBUGGER-PREV STREQUAL ON)
  endif(DEBUGGER)
  # Rule: VERBOSE_MEMORY_MANAGER.
  if(VERBOSE_MEMORY_MANAGER)
    set(VERBOSE_MEMORY_MANAGER-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} VERBOSE_MEMORY_MANAGER)
    # Set flags  .
  else(VERBOSE_MEMORY_MANAGER)
    if(VERBOSE_MEMORY_MANAGER-PREV STREQUAL ON)
      set(VERBOSE_MEMORY_MANAGER-PREV OFF CACHE INTERNAL "" FORCE)
    endif(VERBOSE_MEMORY_MANAGER-PREV STREQUAL ON)
  endif(VERBOSE_MEMORY_MANAGER)
  # Rule: MULTIPROCESSOR.
  if(MULTIPROCESSOR)
    set(MULTIPROCESSOR-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} MULTIPROCESSOR)
    # Set flags APIC.
    set(APIC ON CACHE BOOL "APIC" FORCE)
    set(DEFINES ${DEFINES} APIC)
  else(MULTIPROCESSOR)
    if(MULTIPROCESSOR-PREV STREQUAL ON)
      set(MULTIPROCESSOR-PREV OFF CACHE INTERNAL "" FORCE)
      list(REMOVE_ITEM DEFINES APIC)
    endif(MULTIPROCESSOR-PREV STREQUAL ON)
  endif(MULTIPROCESSOR)
  # Rule: ECHO_CONSOLE_TO_SERIAL.
  if(ECHO_CONSOLE_TO_SERIAL)
    set(ECHO_CONSOLE_TO_SERIAL-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} ECHO_CONSOLE_TO_SERIAL)
    # Set flags  .
  else(ECHO_CONSOLE_TO_SERIAL)
    if(ECHO_CONSOLE_TO_SERIAL-PREV STREQUAL ON)
      set(ECHO_CONSOLE_TO_SERIAL-PREV OFF CACHE INTERNAL "" FORCE)
    endif(ECHO_CONSOLE_TO_SERIAL-PREV STREQUAL ON)
  endif(ECHO_CONSOLE_TO_SERIAL)
  # Rule: X86.
  if(X86)
    set(X86-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} X86)
    # Set flags ADDITIONAL_CHECKS BITS_32 LITTLE_ENDIAN KERNEL_STANDALONE X86_COMMON KERNEL_NEEDS_ADDRESS_SPACE_SWITCH.
    set(ADDITIONAL_CHECKS ON CACHE INTERNAL "ADDITIONAL_CHECKS" FORCE)
    set(DEFINES ${DEFINES} ADDITIONAL_CHECKS)
    set(BITS_32 ON CACHE INTERNAL "BITS_32" FORCE)
    set(DEFINES ${DEFINES} BITS_32)
    set(LITTLE_ENDIAN ON CACHE INTERNAL "LITTLE_ENDIAN" FORCE)
    set(DEFINES ${DEFINES} LITTLE_ENDIAN)
    set(KERNEL_STANDALONE ON CACHE INTERNAL "KERNEL_STANDALONE" FORCE)
    set(DEFINES ${DEFINES} KERNEL_STANDALONE)
    set(X86_COMMON ON CACHE INTERNAL "X86_COMMON" FORCE)
    set(DEFINES ${DEFINES} X86_COMMON)
    set(KERNEL_NEEDS_ADDRESS_SPACE_SWITCH ON CACHE INTERNAL "KERNEL_NEEDS_ADDRESS_SPACE_SWITCH" FORCE)
    set(DEFINES ${DEFINES} KERNEL_NEEDS_ADDRESS_SPACE_SWITCH)
  else(X86)
    if(X86-PREV STREQUAL ON)
      set(X86-PREV OFF CACHE INTERNAL "" FORCE)
      set(ADDITIONAL_CHECKS OFF CACHE INTERNAL "ADDITIONAL_CHECKS" FORCE)
      list(REMOVE_ITEM DEFINES ADDITIONAL_CHECKS)
      set(BITS_32 OFF CACHE INTERNAL "BITS_32" FORCE)
      list(REMOVE_ITEM DEFINES BITS_32)
      set(LITTLE_ENDIAN OFF CACHE INTERNAL "LITTLE_ENDIAN" FORCE)
      list(REMOVE_ITEM DEFINES LITTLE_ENDIAN)
      set(KERNEL_STANDALONE OFF CACHE INTERNAL "KERNEL_STANDALONE" FORCE)
      list(REMOVE_ITEM DEFINES KERNEL_STANDALONE)
      set(X86_COMMON OFF CACHE INTERNAL "X86_COMMON" FORCE)
      list(REMOVE_ITEM DEFINES X86_COMMON)
      set(KERNEL_NEEDS_ADDRESS_SPACE_SWITCH OFF CACHE INTERNAL "KERNEL_NEEDS_ADDRESS_SPACE_SWITCH" FORCE)
      list(REMOVE_ITEM DEFINES KERNEL_NEEDS_ADDRESS_SPACE_SWITCH)
    endif(X86-PREV STREQUAL ON)
  endif(X86)
  # Rule: ARM_COMMON.
  if(ARM_COMMON)
    set(ARM_COMMON-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} ARM_COMMON)
    # Set flags OMIT_FRAMEPOINTER.
    set(OMIT_FRAMEPOINTER ON CACHE INTERNAL "OMIT_FRAMEPOINTER" FORCE)
    set(DEFINES ${DEFINES} OMIT_FRAMEPOINTER)
  else(ARM_COMMON)
    if(ARM_COMMON-PREV STREQUAL ON)
      set(ARM_COMMON-PREV OFF CACHE INTERNAL "" FORCE)
      set(OMIT_FRAMEPOINTER OFF CACHE INTERNAL "OMIT_FRAMEPOINTER" FORCE)
      list(REMOVE_ITEM DEFINES OMIT_FRAMEPOINTER)
    endif(ARM_COMMON-PREV STREQUAL ON)
  endif(ARM_COMMON)
  # Rule: OMIT_FRAME_POINTER.
  if(OMIT_FRAME_POINTER)
    set(OMIT_FRAME_POINTER-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} OMIT_FRAME_POINTER)
    # Set flags  .
  else(OMIT_FRAME_POINTER)
    if(OMIT_FRAME_POINTER-PREV STREQUAL ON)
      set(OMIT_FRAME_POINTER-PREV OFF CACHE INTERNAL "" FORCE)
    endif(OMIT_FRAME_POINTER-PREV STREQUAL ON)
  endif(OMIT_FRAME_POINTER)
  # Rule: DEBUGGER_QWERTZ.
  if(DEBUGGER_QWERTZ)
    set(DEBUGGER_QWERTZ-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} DEBUGGER_QWERTZ)
    # Set flags  .
  else(DEBUGGER_QWERTZ)
    if(DEBUGGER_QWERTZ-PREV STREQUAL ON)
      set(DEBUGGER_QWERTZ-PREV OFF CACHE INTERNAL "" FORCE)
    endif(DEBUGGER_QWERTZ-PREV STREQUAL ON)
  endif(DEBUGGER_QWERTZ)
  # Rule: ARM926E.
  if(ARM926E)
    set(ARM926E-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} ARM926E)
    # Set flags ARM_COMMON BITS_32 LITTLE_ENDIAN.
    set(ARM_COMMON ON CACHE INTERNAL "ARM_COMMON" FORCE)
    set(DEFINES ${DEFINES} ARM_COMMON)
    set(BITS_32 ON CACHE INTERNAL "BITS_32" FORCE)
    set(DEFINES ${DEFINES} BITS_32)
    set(LITTLE_ENDIAN ON CACHE INTERNAL "LITTLE_ENDIAN" FORCE)
    set(DEFINES ${DEFINES} LITTLE_ENDIAN)
  else(ARM926E)
    if(ARM926E-PREV STREQUAL ON)
      set(ARM926E-PREV OFF CACHE INTERNAL "" FORCE)
      set(ARM_COMMON OFF CACHE INTERNAL "ARM_COMMON" FORCE)
      list(REMOVE_ITEM DEFINES ARM_COMMON)
      set(BITS_32 OFF CACHE INTERNAL "BITS_32" FORCE)
      list(REMOVE_ITEM DEFINES BITS_32)
      set(LITTLE_ENDIAN OFF CACHE INTERNAL "LITTLE_ENDIAN" FORCE)
      list(REMOVE_ITEM DEFINES LITTLE_ENDIAN)
    endif(ARM926E-PREV STREQUAL ON)
  endif(ARM926E)
  # Rule: MIPS_AU1500_DB1500.
  if(MIPS_AU1500_DB1500)
    set(MIPS_AU1500_DB1500-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} MIPS_AU1500_DB1500)
    # Set flags MIPS_AU1500.
    set(MIPS_AU1500 ON CACHE BOOL "MIPS_AU1500" FORCE)
    set(DEFINES ${DEFINES} MIPS_AU1500)
  else(MIPS_AU1500_DB1500)
    if(MIPS_AU1500_DB1500-PREV STREQUAL ON)
      set(MIPS_AU1500_DB1500-PREV OFF CACHE INTERNAL "" FORCE)
      list(REMOVE_ITEM DEFINES MIPS_AU1500)
    endif(MIPS_AU1500_DB1500-PREV STREQUAL ON)
  endif(MIPS_AU1500_DB1500)

endforeach(CHANGED RANGE 5)

list(REMOVE_DUPLICATES DEFINES)
set(EMUL invalid)
if(X86_COMMON)
  set(EMUL qemu)
endif(X86_COMMON)
if(MIPS_COMMON)
  set(EMUL qemu-mipsel)
endif(MIPS_COMMON)
if(ARM_COMMON)
  set(EMUL qemu-arm)
endif(ARM_COMMON)
if(x86-debug OR x64-debug OR mips-debug OR 1)
  add_test(TraceCommand ../tests/TraceCommand.exp ${EMUL})
endif(x86-debug OR x64-debug OR mips-debug OR 1)
if(x86-debug OR x64-debug OR mips-debug OR 1)
  add_test(DebuggerStart ../tests/DebuggerStart.exp ${EMUL})
endif(x86-debug OR x64-debug OR mips-debug OR 1)