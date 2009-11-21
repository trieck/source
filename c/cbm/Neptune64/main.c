/*
 * 	MAIN.C
 *
 * 	main entry point
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
#include "common.h"
#include "machine.h"
#include "monitor.h"
static void cleanup(void);
static void init(void);
static void notice(void);
const char *kernal_name = "kernal";
const char *basic_name = "basic";
const char *chargen_name = "chargen";
const char *log_file_name = NULL;
/*
 * main entry point
 */
int main(void)
{
	init();
	notice();
	monitor_run();
	return 0;
}
/*
 * initialization
 */
void init(void)
{
	/* set up exit handler */
	atexit(cleanup);
	/* initialize the machine */
	machine_init();
	/* initialize the monitor */
	monitor_init();
}
/*
 * main entry point
 */
void cleanup(void)
{
}
/*
 * copyright notice
 */
void notice(void)
{
	printf("\nNeptune64 version 0.0.1, Copyright (c) 2001 Thomas A. Rieck\n"
	       "Neptune64 comes with ABSOLUTELY NO WARRANTY.\n"
	       "This is free software, and you are welcome to redistribute it\n"
	       "under certain conditions.\n"
	      );
}
