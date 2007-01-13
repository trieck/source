#!/usr/bin/perl

use strict 'vars';

# fun with "symbolic references"
my $name = "bam";

# here's the weird part...
# when you attempt to dereference a scalar
# that is not a hard reference, Perl will treat
# it as a "symbolic reference", that is the reference
# is interpreted as a string.  that string is taken to
# be the name of another variable!

$$name = 1;	# sets $bam
print ${$name}, "\n";

no strict 'vars';	# turn off variable declaration for the next thingy
print $bam, "\n";	# this is strange, strange, strange...
use strict 'vars';	# turn 'em back on
