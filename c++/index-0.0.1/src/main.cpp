/////////////////////////////////////////////////////////////////////////////
//
// MAIN.CPP : Main application entry point
//
// Copyright (c) 2008 Thomas A. Rieck, All Rights Reserved
//

#include "global.h"
#include "content.h"

/////////////////////////////////////////////////////////////////////////////
void usage(void)
{
	error("usage: index -o outfile infiles");
}

/////////////////////////////////////////////////////////////////////////////
int getopt(int argc, char **argv, const char *opts, char **optarg)
{
	for ( ; argc; argc--, argv++) {
		if (argv[0][0] != '-') continue;
		if (argv[0][1] != opts[0]) continue;
		
		if (optarg != NULL && argc > 1) {
			*optarg = argv[1];
		} else if (optarg) {
			*optarg = NULL;
		}
		return opts[0];	
	}
	return EOF;
}
 
/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	if (argc < 2)
		usage();
	
	char *outfile = NULL;
	if (getopt(argc, argv, "o", &outfile) == EOF)
		usage();
	if (outfile == NULL)
		usage();

	argc -= 3; argv += 3;
	if (argc <= 0)
		usage();

	Content content;
	content.index(argc, argv, outfile);
	
	return 0;
}
