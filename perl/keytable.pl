#!/usr/bin/perl

use strict qw(vars);

srand;
my %processed = ();

printf "static char key_table[256] = {";

for (my $i = 0; $i < 256; $i++) {
	my $c;
	do {
		$c = int(rand 256);			
	} while exists $processed{$c};
	
	if ($i % 8 == 0) { print "\n\t"; }
	
	$processed{$c} = 1;	
	printf "0x%.2x", $c;
	
	if ($i != 255) { print ", "; }
}

printf "\n};\n";