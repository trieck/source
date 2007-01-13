/*
 * 	LOG.C
 *
 * 	Logging module
 *
 *	Neptune64 Commodore 64 Emulator
 * 	Copyright (C) 2001 Thomas A. Rieck <trieck@bellsouth.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */
#include <time.h>
#include "common.h"
#include "log.h"
#define BUFFERSIZE 1024
static void write_log_entry(const char *entry);
extern const char *log_file_name;
/* 
 * log error and exit
 */
void error(const char *format, ...)
{
	char buffer[BUFFERSIZE], fmtbuff[BUFFERSIZE];
	va_list arglist;
	
	strcpy(fmtbuff, "error: ");
	strcat(fmtbuff, format);
	
   	va_start(arglist, format);
   	vsprintf(buffer, fmtbuff, arglist);
   	va_end(arglist);
   	
   	write_log_entry(buffer);
	
	exit(1);
}
/*
 * log warning
 */
void warning(const char *format, ...)
{
	char buffer[BUFFERSIZE];
	va_list arglist;
	
   	va_start(arglist, format);
   	vsprintf(buffer, format, arglist);
   	va_end(arglist);
   	
   	write_log_entry(buffer);
}
/*
 * append log file entry record
 */
void write_log_entry(const char *entry)
{
	if (NULL != log_file_name) {
		char tmpbuf[128];
		time_t ltime;
    	struct tm *today;
    	         	
		FILE *fp = fopen(log_file_name, "a");
		if (NULL == fp)
			return;	/* could not open log file */
				
		time(&ltime);
		today = localtime(&ltime);
    	
    	/* format current time as string */
    	strftime(tmpbuf, sizeof(tmpbuf),
         	"%m/%d/%Y %H:%M:%S", today);
         		
		fprintf(fp, "%s %s", tmpbuf, entry);
		
		fclose(fp);
	} else fputs(entry, stderr);
}
