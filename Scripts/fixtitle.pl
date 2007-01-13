###################################################
#
#	MODULE	:	FIXTITLE.PL
#	AUTHOR	:	Thomas A. Rieck
#	DATE	:	11/21/1998
#	PURPOSE	:	set titles based on filename
#

use strict;
use FileHandle;

my (@files, $dir);
$dir = $ARGV[0] or die "No directory specified.";
opendir DIR, $dir;
@files = grep(/^.*\.html/, readdir(DIR));
foreach(@files) {
	my $file = $dir . "/" . $_;
	my $fh = new FileHandle($file);
	if (!defined $fh) {
		die "could not open file $file.";
	}
	my $gulp = FileToString($fh);
	undef $fh;

	$gulp =~ s/<HEAD>(.+?)<\/HEAD>//mg;

	StringToFile($gulp, $file);
}
closedir(DIR);
exit;

########################################
#
#	FileToString
#
#	Arguments	:	File Handle
#	Return Value	:	String
#
sub FileToString
{
	my $fh = shift or die "Invalid Arguments";
	my $line;

	while (<$fh>) { $line .= $_; }

	return $line;
}

########################################
#
#	StringToFile
#
#	Arguments	:	String, FileName
#	Return Value	:	None
#
sub StringToFile
{
	my $str 		= shift or die "Invalid Arguments";
	my $fileName 	= shift or die "Invalid Arguments";

	my ( $fh );
	
	$fh = new FileHandle "> $fileName";
	if (!defined $fh)
	{
		die "Could not open file $fileName";
	}

	print $fh $str;

	undef $fh;
}
