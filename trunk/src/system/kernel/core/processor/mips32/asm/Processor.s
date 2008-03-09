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

# uintptr_t Processor::getBasePointer()
.global _ZN9Processor14getBasePointerEv
# uintptr_t Processor::getStackPointer()
.global _ZN9Processor15getStackPointerEv
# uintptr_t Processor::getInstructionPointer()
.global _ZN9Processor21getInstructionPointerEv
# uintptr_t Processor::getDebugStatus()
.global _ZN9Processor14getDebugStatusEv

_ZN9Processor14getBasePointerEv:
  addu $v0, $fp, 0 # $v0 = $fp+0. It's the only way to do a register swap.
  jr $ra

_ZN9Processor15getStackPointerEv:
  addu $v0, $sp, 0 # $v0 = $sp+0. It's the only way to do a register swap.
  jr $ra

_ZN9Processor21getInstructionPointerEv:
  addu $v0, $ra, 0 # $v0 = $ra+0. We return the return address.
  jr $ra
