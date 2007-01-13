#!/usr/bin/perl -w

use lib 'lib';
use strict qw(vars);
use TCipher;

my $plain = shift @ARGV or die "usage: tcipher.pl input";
my $enc = TCipher::tencipher($plain, 0xcafebabe);
my $dec = TCipher::tencipher($enc, 0xcafebabe);
print "$enc\n$dec\n";
