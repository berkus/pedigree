#!/usr/bin/perl
#
# mnemonics.pl - generates mnemonic{.h,.c} from mnemonics.dat
#
# Copyright (c) 2002, 2003, 2004 Vivek Mohan <vivek@sig9.com>
# All rights reserved.
# See (LICENSE)
#
#


open(mnm_c,">mnemonics.c") || die "Couldn't create mnemonics.c.";
open(mnm_h,">mnemonics.h") || die "Couldn't create mnemonics.h.";

print mnm_c "/* Do not edit, generated by mnemonics.pl */ \n";
print mnm_c "const char* ud_mnemonics[] = \n{\n";

print mnm_h "/* Do not edit, Generated by mnemonics.pl */ \n\n";
print mnm_h "#ifndef UD_MNEMONICS_H\n";
print mnm_h "#define UD_MNEMONICS_H\n\n";
print mnm_h "extern const char* ud_mnemonics[];\n\n";
print mnm_h "enum ud_mnemonic_code \n{ \n";

while($mnm = <STDIN>) {
	chop($mnm);
        my $mnm_padded = sprintf("%-8s", $mnm);
	print mnm_c "  \"$mnm_padded\",\n";
	print mnm_h "  UD_I$mnm,\n";
}

print mnm_c "  \"I3vil\",\n";
print mnm_h "  UD_I3vil\n";

print mnm_c "};\n";
print mnm_h "};\n";
print mnm_h "#endif\n";

close(mnm_c);
close(mnm_h);
