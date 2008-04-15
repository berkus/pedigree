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

# void __arm_vector_table();
.global __arm_vector_table
.extern arm_swint_handler

intentry:
  b arm_swint_handler

# ARM vector table starting at 0x0
__arm_vector_table:

__armvec_reset:
  ldr pc,=arm_reset_handler
__armvec_undefinst:
  ldr pc,=arm_instundef_handler
__armvec_swint:
  ldr pc,=arm_swint_handler
__armvec_prefetchabort:
.long 0
__armvec_dataabort:
.long 0
__armvec_addrexcept:
.long 0
__armvec_irq:
  ldr pc,=arm_irq_handler
__armvec_fiq:
  ldr pc,=arm_fiq_handler
