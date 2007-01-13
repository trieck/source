#!/usr/bin/perl -w

package Person;
use strict qw(vars);

#############################################################################
# ctor
sub new {
	my $proto = shift;
	my $class = ref($proto) || $proto;
    my $self = {};    
	$self->{NAME} = undef;
	$self->{AGE} = undef;
	$self->{PEERS} = [];
    return bless($self), $class;
}

#############################################################################
# properties
sub name {
	my $self = shift;
    if (@_) { $self->{NAME} = shift }
    return $self->{NAME};
}

sub age {
	my $self = shift;
	if (@_) { $self->{AGE} = shift }
	return $self->{AGE};
}

sub peers {
	my $self = shift;
    if (@_) { @{ $self->{PEERS} } = @_ }
    return @{ $self->{PEERS} };
}
    
#############################################################################
# EOF
1;  # so the require or use succeeds  