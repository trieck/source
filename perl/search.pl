#!/usr/bin/perl -w
#
# MODULE: SEARCH.PL
# AUTHOR: Thomas A. Rieck
# VERSION: 0.0.0
# DATE: 11-02-2002
#
# The purpose of this program 
# is to combine the facilities
# of 'grep' and 'find' in a convenient manner
# in order to find regular expression patterns
# using a wildcard file pattern recursively.
# 
# Although 'grep' supports recursively searching a directory,
# experiments have shown that it stops as soon as it does not
# find a matching file in a directory.
#
# There are two ways to call this program:
# 1.) using a list of files from stdin (usually provided by find)
#	Here is an example:
#	find / -name *.h | search.pl "^/\*"	
#	This will print all lines for header files 
#	starting with C style comments
#
# 2.) specify a file glob on the command line
#	Here is an example:
#	search.pl "/usr/include/*.h" "^/\*"
#	This will print all lines for header files
#	in /usr/include with C style comments
#
# Copyright(c) 2002, Thomas A. Rieck
# Comments to: trieck@bellsouth.net
#

# function prototypes
#
sub usage();
sub error($);
sub warning($);
sub match($);
sub matchglob($);
sub matchfile($$);

# main
my $args = scalar @ARGV;
if ($args == 1) { # just regex
	match(\@ARGV);
} elsif ($args == 2) { #file glob, regex
	matchglob(\@ARGV);
} else {
	usage();
}

# print error message and exit
#
sub error($) {
	my $err = shift;
	print STDERR "$err\n";
	exit(1);
}

# like error but don't exit
#
sub warning($) {
	my $warn = shift;
	print STDERR "$warn\n";	
}

# print matching lines for stdin
#
sub match($) {
	my $rpatt = @{+ shift }[0];
	while (<STDIN>) { 
		chomp; 
		matchfile($_, $rpatt); 
	}
}

# print matching lines for file glob
#
sub matchglob($) {
	my ($fpatt, $rpatt) = @{+ shift };
	my @files = glob($fpatt); 
	my $file;
	foreach $file(@files) {
		matchfile($file, $rpatt);
	}
}

# print matching lines for a file
#
sub matchfile($$) {
	my ($file, $patt) = @_;
	if (-T $file) { # only text files
		open FH, $file or warning "unable to read file \"$file\".";
		while (<FH>) { print "$file: $_" if /$patt/o; }
		close FH;
	}	
}

# print a usage message and exit
#
sub usage() {
	print STDERR "usage: search.pl [<STDIN>] | [filepatt] regex\n";
	exit(1);
}



