/*
 * MAIN.C
 *
 * Main application entry point
 */

#include <stdarg.h>
#include "global.h"
#include "index.h"

extern int vsnprintf(char *, size_t n, char const *, va_list);

/* print usage message and exit */
void usage(void)
{
	error("usage: index pattern");
}

/* main entry point */
int main(int argc, char *argv[])
{
	if (argc < 2)
		usage();

	mkindex(--argc, ++argv);

	return 0;
}

/* error routine */
void error(const char *fmt, ...)
{
	va_list arglist;
	char msg[BSIZE];

	va_start(arglist, fmt);
	vsnprintf(msg, BSIZE, fmt, arglist);
	va_end(arglist);

	fprintf(stderr, "%s\n", msg);
	exit(1);
}
