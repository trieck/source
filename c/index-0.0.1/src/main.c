/*
 * MAIN.C
 *
 * Main application entry point
 * Copyright (c) 2008 Thomas A. Rieck
 */

#include "global.h"
#include "index.h"

/*
 * print usage message and exit
 */
void usage(void)
{
	error("usage: index files");
}

/*
 * main entry point
 */
int main(int argc, char *argv[])
{
	if (argc < 2)
		usage();

	mkindex(--argc, ++argv);

	return 0;
}
