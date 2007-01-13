/*
 * X.C
 *
 * 'X' Programming Language
 * Copyright (c) 2004, Thomas A. Rieck
 * All Rights Reserved
 */

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "symbol.h"
#include "tree.h"
#include "x.h"
#include "eval.h"
#include "temp.h"
#include "tree.h"
#include "global.h"
#include "block.h"

#define BSIZE 1000

static void cleanup(void);
static void getinput(int argc, char **argv);
static void fpecatch(int signum);
extern int yyparse(void);

extern FILE *yyin;				/* input file pointer */
extern char *module_name;		/* module filename */

/* initialize the interpreter */
void x_init(int argc, char **argv)
{
	signal(SIGFPE, fpecatch);
	atexit(cleanup);
	globinit();
	tinit();
	treeinit();
	blockinit();
	getinput(argc, argv);
}

/* run the interpreter */
void x_run(void)
{
	yyparse();
	eval();
}

/* fatal error */
void error(const char *fmt, ...)
{
	char buf[BSIZE];
	va_list arglist;

	va_start(arglist, fmt);
	vsprintf(buf, fmt, arglist);
	va_end(arglist);

	fprintf(stderr, "%s\n", buf);

	exit(EXIT_FAILURE);
}

/* cleanup */
void cleanup(void)
{
	if (yyin && yyin != stdin) {
		fclose(yyin);
		yyin = 0;
	}

	if (module_name) {
		free(module_name);
		module_name = 0;
	}
}

/* catch floating point exceptions */
void fpecatch(int signum)
{
	error("floating point exception (%d).", signum);
}

/* open input file if specified; default to stdin */
void getinput(int argc, char **argv)
{
	if (yyin && yyin != stdin)
		fclose(yyin);

	if (argc <= 1 || strcmp(argv[1], "--") == 0) {
		yyin = stdin;
		return;
	}

	if ((yyin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "%s: can't open \"%s\".\n", argv[0], argv[1]);
		exit(EXIT_FAILURE);
	}

	module_name = strdup(argv[1]);
}

#ifdef _DEBUG
/* assertion message */
void AssertMessage(const char *msg, const char *file, int line)
{
	error("ASSERTION FAILURE (%s)! File %s at line %d.", msg, file, line);
}
#endif							/* _DEBUG */
