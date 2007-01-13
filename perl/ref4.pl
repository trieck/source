#!/usr/bin/perl

use strict 'vars';

# this is a reference to an anonymous hash
# the hash is a mapping of string keys to anonymous arrays

my $h = {
	flintstones => [ 'fred', 'barney' ],
	jetsons => [ 'george', 'jane', 'elroy' ],
	simpsons => [ 'homer', 'marge', 'bart' ]
};

# iterate over the keys in the anonymous hash
# and print each corresponding value
 
my $k;
foreach $k(keys %$h) {
	my $v;
	foreach $v(@{$h->{$k}}) {
		print "$v\n";
	}
}

