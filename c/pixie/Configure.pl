#!/usr/bin/perl -w

use strict qw(vars);

sub depend($);

# variables
#
my %env = ('CC' => 'gcc',
	'TARGET' => 'pixie',
	'YACC' => 'bison -y',
	'LEX' => 'flex -l',
	'YFLAGS' => '-d',
	'CFLAGS' => '-Wall -Wstrict-prototypes',
	'LIBS' => '-lm',
	'PACKAGE' => 'pixie.tar'
);

# targets
#
my %targets = ('pretty' => "\n\t\@indent -kr --use-tabs --tab-size4 *.c *.h\n\t\@-rm *~",
	'clean' => "\n\t\@-rm -f *.o *.exe *~ core y.tab.* \$(TARGET) \$(PACKAGE) \$(PACKAGE).bz2 \\\n\ty.output parse.c lex.c",
	'package' => "\tpretty clean\n\t\@tar cf \$(PACKAGE) *\n\t\@bzip2 -9 \$(PACKAGE)"
);

# objects
#
my @objects = sort glob("*.y");
push @objects, sort glob("*.l");
push @objects, sort glob("*.c");
	
my $EXT = 'o';

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
	$obj =~ s/\.l/\.$EXT/;
	$obj =~ s/\.y/\.$EXT/;
	print "\t$obj";
	print " \\" if ($i < $n - 1);
	print "\n";
	$i++;
}

# suffix rules
#
print <<"EOF";
\n.SUFFIXES: .o .c .y .l
.c.o:
\t\$(CC) \$(CFLAGS) -c \$<

.y.c:
\t\$(YACC) \$(YFLAGS) \$<
\t\@mv y.tab.c \$\@

.l.c:
\t\$(LEX) -o\$@ \$<

EOF

print "pixie: \$(OBJECTS)\n\t\$(CC) -o \$@ \$(OBJECTS) \$(LIBS)\n\n";

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