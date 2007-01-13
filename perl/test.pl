#!/usr/bin/perl -w

sub thingfunc { 
	my $x = shift; 
	return sub { my $y = shift; print "$x-$y\n"; } 
}

my $a = thingfunc(2);

# ...
$a->('wow');