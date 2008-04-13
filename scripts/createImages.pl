#!/usr/bin/perl

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

use strict;
use warnings;

my $compiler = $ARGV[0];

# Are we making an X86 target?
if ($compiler =~ m/(i686|amd64)-elf/) {
  # Are we on cygwin?
  if ($ENV{TERM} =~ m/cygwin/i) {
    `cp ../images/floppy_fat.img ./floppy.img`;
    `mcopy -Do -i  ./floppy.img src/system/kernel/kernel ::/`;
  } else {
    `mkdir -p /tmp/pedigree-image`;
    `cp ../build/images/floppy_ext2.img ./floppy.img`;
    `sudo /sbin/losetup /dev/loop0 ./floppy.img`;
    `sudo mount -o loop /dev/loop0 /tmp/pedigree-image`;
    `sudo cp src/system/kernel/kernel /tmp/pedigree-image/kernel`;
    `sudo umount /dev/loop0`;
    `sudo /sbin/losetup -d /dev/loop0`;
  }
}

# How about a mips target?
if ($compiler =~ m/mips64el-elf/) {
  `../compilers/mips64el-elf/bin/objcopy src/system/kernel/kernel -O binary ./kernel.bin`;
  `../compilers/mips64el-elf/bin/objcopy src/system/kernel/kernel -O srec ./kernel.srec`;
  `../compilers/mips64el-elf/bin/objcopy src/system/boot/mips/bootloader -O srec ./bootloader.srec`;
}
exit 0;