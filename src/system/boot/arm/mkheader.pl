#!/usr/bin/perl

open my $fd, ">", "autogen.h";
print $fd "/* Made from $ARGV[0] */\n";
print $fd "/* autogenerated by mkheader.pl, do not edit. */\n";
print $fd "uint8_t file[] = {\n";

open my $in, "<", $ARGV[0];
binmode($in);

$/ = undef;
$_ = <$in>;
@a = split "";
for(@a) {
  printf $fd "0x%02x, ", ord;
  print $fd "\n" unless ++$c % 20
}

print $fd "};\n";