#!/usr/bin/perl -w

use strict qw(vars);

sub depend($);

# variables
#
my %env = ('CC' => 'cl',
	'TARGET' => 'index',
	'CFLAGS' => '-nologo -Iwin32 /W3 /Zi /MLd /Od /Fdindex.pdb /DDEBUG',
	'LFLAGS' => '-nologo /link /DEBUG /out:$@.exe'
);

# targets
#
my %targets = (
	'clean' => "\n\t\@erase /F /Q *.obj *.pdb *.exe *.ilk *.suo 2>/nul"
);

# objects
#
my @objects = sort glob("*.c");
	
my $EXT = 'obj';

my ($k, $v);
while (($k, $v) = each %env) {
	print "$k = $v\n";
}

print "OBJECTS = \\\n";
my ($obj, $i, $n);

$i = 0;
$n = scalar @objects;
foreach $obj(@objects) {
	$obj =~ s/\.c/\.$EXT/;
	print "\t$obj";
	print " \\" if ($i < $n - 1);
	print "\n";
	$i++;
}

# suffix rules
#
print <<"EOF";
\n.SUFFIXES: .o .c
.c.obj:
\t\@\$(CC) \$(CFLAGS) /c \$<
EOF

print "index: \$(OBJECTS)\n\t\@\$(CC) \$(OBJECTS) \$(LFLAGS)\n\n";

# targets
#
while (($k, $v) = each %targets) {
	print "$k: $v\n\n";
}

# file dependencies
#
foreach $obj(@objects) {
	depend($obj);
}

# generate dependencies 
#
sub depend($) {
	my $obj = shift or die ("invalid arguments to depend.");
	my $source = $obj;
	$source =~ s/\.$EXT/\.c/;
	
	my @deps;
	unless (open FH, $source)  {
		$source =~ s/\.c/\.y/;
		unless (open FH, $source) {
			$source =~ s/\.y/\.l/;
			open FH, $source or 
				die "unable to find matching source for \"$obj\".";
		}
	}
	
	
	while (<FH>) {
		chomp;
		push @deps, $1 if /#include \"(.+)\"/o
	}
	close FH;	
	
	print "$obj : \\\n\t$source";
	print " \\" if scalar @deps;
	print "\n";
	
	my ($n, $dep);
	$n = 0;
	foreach $dep(sort @deps) {
		print "\t$dep";
		print " \\" if ($n < scalar @deps - 1);
		print "\n";
		$n++;
	}
	print "\n";	
}
