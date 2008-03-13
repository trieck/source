#!/usr/bin/perl

use warnings;
use strict 'vars';
use Benchmark;

print "truncating tables...\n";
spawn('mysql --user=root --password=erskine1 --database=user --execute="truncate table users;"');
spawn('sqlplus system/erskine1 @"d:\\dbtests\oracle10g\truncate.sql"');

# test mysql bulk import
my $start = new Benchmark;
mysql_import();
my $end = new Benchmark;
my $diff = timediff($end, $start);
print "total time:", timestr($diff), "\n\n";

# test oracle bulk import
$start = new Benchmark;
oracle_import();
$end = new Benchmark;
$diff = timediff($end, $start);
print "total time:", timestr($diff), "\n\n";
	
# mysql5 bulk import
#
sub mysql_import {
	print "bulk importing into mysql...\n";
	spawn('mysqlimport --fields-terminated-by="," --fields-enclosed-by="" --lines-terminated-by="\n" --user=root --password=erskine1 user "d:\dbtests\users.txt"');
}

# oracle10g bulk import {
sub oracle_import {
	print "bulk importing into oracle...\n";
	spawn('sqlldr "control=d:\dbtests\oracle10g\bulk-table.ctl,userid=system/erskine1"');
}

# spawn a subprocess
#
sub spawn {
	my $cmd = shift or die "no command provided.";
	my $results = `$cmd`;
}