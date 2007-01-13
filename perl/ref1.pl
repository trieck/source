#!/usr/bin/perl -w

# create some strings
my $a = 'this';
my $b = 'that';
my $c = 'other';

# create an array of references
my @array = ( \$a, \$b, \$c );

${$array[3]} .= '+';	# append '+' to 4th element; implicitly adds

# iterate over the references and 
# dereference them
my $ref;
foreach $ref(@array) {
	print $$ref, "\n";
}
