#!/usr/bin/perl -w

use strict 'vars';

# look up the keys in the main package
# and all the variables

my $symname;
foreach $symname (sort keys %main::) {
	local *sym = $main::{$symname};
	print "\$$symname is defined\n" if defined $sym;
	print "\@$symname is defined\n" if defined @sym;
	print "\%$symname is defined\n" if defined %sym;
}