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
  set(DWARF OFF CACHE INTERNAL "DWARF" FORCE)
  set(X64 OFF CACHE BOOL "X64" FORCE)
  set(MIPS_MALTA OFF CACHE BOOL "MIPS_MALTA" FORCE)
  set(MIPS_AU1500 OFF CACHE BOOL "MIPS_AU1500" FORCE)
  set(OMIT_FRAMEPOINTER OFF CACHE INTERNAL "OMIT_FRAMEPOINTER" FORCE)
  set(SMP_NOTICE OFF CACHE INTERNAL "SMP_NOTICE" FORCE)
  set(ARM_VERSATILE OFF CACHE BOOL "ARM_VERSATILE" FORCE)
  set(SMP OFF CACHE BOOL "SMP" FORCE)
  mark_as_advanced(FORCE SMP)
  set(ACPI OFF CACHE BOOL "ACPI" FORCE)
  mark_as_advanced(FORCE ACPI)
  set(MIPS32 OFF CACHE BOOL "MIPS32" FORCE)
  set(DEBUGGER_RUN_AT_START OFF CACHE INTERNAL "DEBUGGER_RUN_AT_START" FORCE)
  set(BITS_64 OFF CACHE INTERNAL "BITS_64" FORCE)
  set(MIPS_COMMON OFF CACHE INTERNAL "MIPS_COMMON" FORCE)
  set(SMP_ERROR OFF CACHE INTERNAL "SMP_ERROR" FORCE)
  set(MIPS_MALTA_BONITO64 OFF CACHE BOOL "MIPS_MALTA_BONITO64" FORCE)
  set(ACPI_NOTICE OFF CACHE INTERNAL "ACPI_NOTICE" FORCE)
  set(LITTLE_ENDIAN OFF CACHE INTERNAL "LITTLE_ENDIAN" FORCE)
  set(ARM_INTEGRATOR OFF CACHE BOOL "ARM_INTEGRATOR" FORCE)
  set(DEBUGGER_QWERTY ON CACHE BOOL "DEBUGGER_QWERTY" FORCE)
  set(BITS_32 OFF CACHE INTERNAL "BITS_32" FORCE)
  set(DEBUGGER ON CACHE BOOL "DEBUGGER" FORCE)
  set(ARM_COMMON OFF CACHE INTERNAL "ARM_COMMON" FORCE)
  set(ACPI_ERROR OFF CACHE INTERNAL "ACPI_ERROR" FORCE)
  set(X86 ON CACHE BOOL "X86" FORCE)
  set(X86_COMMON OFF CACHE INTERNAL "X86_COMMON" FORCE)
  set(KERNEL_STANDALONE OFF CACHE INTERNAL "KERNEL_STANDALONE" FORCE)
  set(DEBUGGER_QWERTZ OFF CACHE BOOL "DEBUGGER_QWERTZ" FORCE)
  set(ARM926E OFF CACHE BOOL "ARM926E" FORCE)
  set(MIPS_AU1500_DB1500 OFF CACHE BOOL "MIPS_AU1500_DB1500" FORCE)
endif(NOT DEFINED RULES_DEFINED)

# Loop five times - hopefully then no more variables will be being changed.
foreach(CHANGED RANGE 5)

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
    # Set flags BITS_64 LITTLE_ENDIAN KERNEL_STANDALONE X86_COMMON.
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
    # Set flags DEBUGGER MIPS_COMMON BITS_32 LITTLE_ENDIAN.
    set(DEBUGGER ON CACHE BOOL "DEBUGGER" FORCE)
    set(DEFINES ${DEFINES} DEBUGGER)
    set(MIPS_COMMON ON CACHE INTERNAL "MIPS_COMMON" FORCE)
    set(DEFINES ${DEFINES} MIPS_COMMON)
    set(BITS_32 ON CACHE INTERNAL "BITS_32" FORCE)
    set(DEFINES ${DEFINES} BITS_32)
    set(LITTLE_ENDIAN ON CACHE INTERNAL "LITTLE_ENDIAN" FORCE)
    set(DEFINES ${DEFINES} LITTLE_ENDIAN)
  else(MIPS32)
    if(MIPS32-PREV STREQUAL ON)
      set(MIPS32-PREV OFF CACHE INTERNAL "" FORCE)
      list(REMOVE_ITEM DEFINES DEBUGGER)
      set(MIPS_COMMON OFF CACHE INTERNAL "MIPS_COMMON" FORCE)
      list(REMOVE_ITEM DEFINES MIPS_COMMON)
      set(BITS_32 OFF CACHE INTERNAL "BITS_32" FORCE)
      list(REMOVE_ITEM DEFINES BITS_32)
      set(LITTLE_ENDIAN OFF CACHE INTERNAL "LITTLE_ENDIAN" FORCE)
      list(REMOVE_ITEM DEFINES LITTLE_ENDIAN)
    endif(MIPS32-PREV STREQUAL ON)
  endif(MIPS32)
  # Rule: MIPS_COMMON.
  if(MIPS_COMMON)
    set(MIPS_COMMON-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} MIPS_COMMON)
    # Set flags OMIT_FRAMEPOINTER.
    set(OMIT_FRAMEPOINTER ON CACHE INTERNAL "OMIT_FRAMEPOINTER" FORCE)
    set(DEFINES ${DEFINES} OMIT_FRAMEPOINTER)
  else(MIPS_COMMON)
    if(MIPS_COMMON-PREV STREQUAL ON)
      set(MIPS_COMMON-PREV OFF CACHE INTERNAL "" FORCE)
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
  # Rule: DEBUGGER.
  if(DEBUGGER)
    set(DEBUGGER-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} DEBUGGER)
    # Set flags DEBUGGER_RUN_AT_START DWARF.
    set(DEBUGGER_RUN_AT_START ON CACHE INTERNAL "DEBUGGER_RUN_AT_START" FORCE)
    set(DEFINES ${DEFINES} DEBUGGER_RUN_AT_START)
    set(DWARF ON CACHE INTERNAL "DWARF" FORCE)
    set(DEFINES ${DEFINES} DWARF)
  else(DEBUGGER)
    if(DEBUGGER-PREV STREQUAL ON)
      set(DEBUGGER-PREV OFF CACHE INTERNAL "" FORCE)
      set(DEBUGGER_RUN_AT_START OFF CACHE INTERNAL "DEBUGGER_RUN_AT_START" FORCE)
      list(REMOVE_ITEM DEFINES DEBUGGER_RUN_AT_START)
      set(DWARF OFF CACHE INTERNAL "DWARF" FORCE)
      list(REMOVE_ITEM DEFINES DWARF)
    endif(DEBUGGER-PREV STREQUAL ON)
  endif(DEBUGGER)
  # Rule: X86.
  if(X86)
    set(X86-PREV ON CACHE INTERNAL "" FORCE)
    set(DEFINES ${DEFINES} X86)
    # Set flags BITS_32 LITTLE_ENDIAN KERNEL_STANDALONE X86_COMMON.
    set(BITS_32 ON CACHE INTERNAL "BITS_32" FORCE)
    set(DEFINES ${DEFINES} BITS_32)
    set(LITTLE_ENDIAN ON CACHE INTERNAL "LITTLE_ENDIAN" FORCE)
    set(DEFINES ${DEFINES} LITTLE_ENDIAN)
    set(KERNEL_STANDALONE ON CACHE INTERNAL "KERNEL_STANDALONE" FORCE)
    set(DEFINES ${DEFINES} KERNEL_STANDALONE)
    set(X86_COMMON ON CACHE INTERNAL "X86_COMMON" FORCE)
    set(DEFINES ${DEFINES} X86_COMMON)
  else(X86)
    if(X86-PREV STREQUAL ON)
      set(X86-PREV OFF CACHE INTERNAL "" FORCE)
      set(BITS_32 OFF CACHE INTERNAL "BITS_32" FORCE)
      list(REMOVE_ITEM DEFINES BITS_32)
      set(LITTLE_ENDIAN OFF CACHE INTERNAL "LITTLE_ENDIAN" FORCE)
      list(REMOVE_ITEM DEFINES LITTLE_ENDIAN)
      set(KERNEL_STANDALONE OFF CACHE INTERNAL "KERNEL_STANDALONE" FORCE)
      list(REMOVE_ITEM DEFINES KERNEL_STANDALONE)
      set(X86_COMMON OFF CACHE INTERNAL "X86_COMMON" FORCE)
      list(REMOVE_ITEM DEFINES X86_COMMON)
    endif(X86-PREV STREQUAL ON)
  endif(X86)
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
