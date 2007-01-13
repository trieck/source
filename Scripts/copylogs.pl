###################################################
#
#	MODULE	:	COPYLOGS.PL
#	AUTHOR	:	Bob Rhodes
#	DATE	:	05/16/2001
#	PURPOSE	:	Copy Web Logs for WebTrends
#

use strict;
use POSIX;
use Shell qw(mv); 

my $logfile;

# move previous day's log files to temp dir
mv "e:\\kzweb1b\\*.log", "e:\\kzweb1b\\temp_log";
mv "e:\\kzweb1c\\*.log", "e:\\kzweb1c\\temp_log";

# move today's log from production servers
$logfile = POSIX::strftime "ex%y%m%d.log", localtime;
mv "\\\\Kzweb1b\\Log_Drive\\LogFiles\\W3SVC9\\" . $logfile, "e:\\kzweb1b";
mv "\\\\Kzweb1c\\Log_Drive\\LogFiles\\W3SVC9\\" . $logfile, "e:\\kzweb1c";
