#!/usr/bin/env perl

# determine file dependencies
# for inclusion in Makefile

use strict 'vars';

my $patt = shift || die "no files.";
my @files = sort glob($patt);

my ($obj, $file, $dep, @deps);

foreach $file(@files) {
	undef @deps;
	open FH, $file or warn "unable to read file \"$file\".";
	while (<FH>) {
		chomp;
		push @deps, $1 if /#include \"(.+)\"/o
	}
	close FH;	
	
	$obj = $file;
	$obj =~ s/\.c/\.o/;
	
	print "$obj : \\\n\t$file";
	print " \\" if scalar @deps;
	print "\n";
	
	my $n = 0;
	foreach $dep(sort @deps) {
		print "\t$dep";
		print " \\" if ($n < scalar @deps - 1);
		print "\n";
		$n = $n + 1;		
	}
	print "\n";
}