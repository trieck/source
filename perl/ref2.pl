#!/usr/bin/perl -w

# create a reference to an anonymous array
# the last element of which is a reference
# to another anonymous array
my $ref = [1, 2, ['a', 'b', 'c']];

# dereference each element and print them
print $$ref[0], "\n";
print $$ref[1], "\n";
print $$ref[2][0], "\n";
print $$ref[2][1], "\n";
print $$ref[2][2], "\n";

# create a reference to an anonymous hash
my $href = {
	'Adam' => 'Eve',
	'Clyde' => 'Bonnie'
};

# lookup values in the anonymous hash 
# and print them
print $$href{'Adam'}, "\n";
print $$href{'Clyde'}, "\n";

# do the same thing using some "syntactic sugar"
print $href->{'Adam'}, "\n";
print $href->{'Clyde'}, "\n";
