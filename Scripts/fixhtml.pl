###################################################
#
#	MODULE	:	FIXHTML.PL
#	AUTHOR	:	Thomas A. Rieck
#	DATE	:	11/21/1998
#	PURPOSE	:	Fix legacy HTML links
#

use strict;
use FileHandle;
use File::Find;

my (@files, $dir);
$dir = $ARGV[0] or die "No directory specified.";
opendir DIR, $dir;
@files = grep(/^.*\.htm/, readdir(DIR));
foreach(@files) {
	my $file = $dir . "/" . $_;
	my $fh = new FileHandle($file);
	if (!defined $fh) {
		die "could not open file $file.";
	}
	my $gulp = FileToString($fh);
	undef $fh;
	
	# remove anything that looks like 'http://*/*/'
	$gulp =~ s/http:\/\/(.+?)\/(.+?)\///mg;
	
	# remove anything that looks like '$xsearch'
	$gulp =~ s/\$xsearch\///mg;
	
	# change '../imgs/' to 'imgs/'
	# change '../include/' to 'include/'
	$gulp =~ s/..\/(imgs|IMGS)\//imgs\//mg;
	$gulp =~ s/..\/include\//include\//mg;
		
	# change 'href="*.exe?form=*.htm' to 'href=home.exe?form=home/*.htm'
	$gulp =~ s/href=\"(.+?)\.exe\?form=(.+?)\.htm/href=\"$1\.exe\?form=$1\/$2\.htm/mg;
	
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
