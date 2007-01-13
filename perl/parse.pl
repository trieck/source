#!/usr/bin/perl -w

use strict qw(vars);

my %ops = (
	'PROGRAM' => \&prog,
	'ENDP.' => \&endp
);

my $lineno = 1;	# current lineno
my $progname;	# program name

parse(*STDIN);

sub parse {
	my ($fh, $line) = @_;
	while ($line = next_line($fh)) {
		expr($line);
		$lineno++;
	}
}

sub expr {
	my ($line, @toks) = @_;
	return unless @toks = split /\s+/, $line;
	bail ("unknown keyword \"$toks[0]\"") unless exists $ops{$toks[0]};
	bail ("no program declared") unless 
		(defined($progname) or $toks[0] eq 'PROGRAM');
	&{$ops{shift @toks}}(\@toks); # call routine with args
}

sub next_line {
	my ($fh, $line) = @_;
	if (defined($line = readline $fh)) {
		chomp $line;
		return $line;
	}
}
		
sub prog {
	my $args = shift;
	bail ("program already declared") if defined($progname);
	$progname = shift @{$args}; # declare program name
	bail ("invalid program decl") unless 
		(defined ($progname) and not scalar @{$args});
}

sub endp {
	my $args = shift;
	bail ("invalid ENDP.") unless not scalar @{$args};	
}

sub bail {
	my $err = shift;
	print STDERR "$err @ line #$lineno.\n";
	exit 1;
}
