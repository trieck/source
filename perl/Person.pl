#!/usr/bin/perl -w

use strict qw(vars);
use lib './';
use Person;

my $me = new Person;
$me->name("Thomas A. Rieck");
$me->age(32);
$me->peers("Bob", "Peter", "Jerome", "Eric", "Tamila");

print "Name: ", $me->name(), "\n";
print "Age: ", $me->age(), "\n";
print "Peers:\n";

my @peers = $me->peers();
my $peer;
foreach $peer(sort @peers) {
	print "\t$peer\n";
}

