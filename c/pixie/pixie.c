/*
 * PIXIE.C
 *
 * Pixie Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include "pixie.h"
#include "xmalloc.h"
#include "array.h"
#include "tree.h"
#include "symbol.h"
#include "global.h"
#include "temp.h"
#include "block.h"
#include "eval.h"
#include "parse.h"
#include "memcheck.h"

#define BSIZE 1000

extern FILE *yyin;			/* input file pointer */
extern char *module_name;	/* module filename */

static void getinput(int argc, char **argv);
static void fpecatch(int signum);
static void cleanup(void);

extern int yyparse(void);

/* like strdup, using xmalloc */
char *xstrdup(const char *s)
{
	char *t = xmalloc(strlen(s) + 1);
	strcpy(t, s);
	return t;
}

/* copy a symbol */
Symbol *symcopy(Symbol * src)
{
	Symbol *dest = xmalloc(sizeof(Symbol));
	dest->type = src->type;
	dest->sub = src->sub;
	dest->name = src->name ? xstrdup(src->name) : 0;
	if (src->sub & SFLOAT)
		dest->u.fval = src->u.fval;
	if (src->sub & SSTRING)
		dest->u.sval = xstrdup(src->u.sval);
	if (src->sub & SARRAY)
		dest->u.aval = array_copy(src->u.aval);

	dest->next = 0;				/* not chained */

	return dest;
}


/* free a symbol and all chains */
void symfree(Symbol * sym)
{
	while (sym != 0) {
		Symbol *next = sym->next;

		xfree(sym->name);

		if (sym->sub & SSTRING)
			xfree(sym->u.sval);

		if (sym->sub & SARRAY)
			array_free(sym->u.aval);

		xfree(sym);
		sym = next;
	}
}

void dprint(const char *fmt, ...)
{
	char buf[BSIZE];
	va_list arglist;

	va_start(arglist, fmt);
	vsprintf(buf, fmt, arglist);
	va_end(arglist);

	fprintf(stderr, "(%s): %s\n", module_name, buf);
}

void error(const char *fmt, ...)
{
	char buf[BSIZE];
	va_list arglist;

	va_start(arglist, fmt);
	vsprintf(buf, fmt, arglist);
	va_end(arglist);

	fprintf(stderr, "(%s): %s\n", module_name, buf);

	exit(EXIT_FAILURE);
}

/* assertion message */
void AssertMessage(const char *msg, const char *file, int line)
{
	dprint("ASSERTION FAILURE (%s)! in file %s at line %d.", msg, file,
		   line);
	exit(EXIT_FAILURE);
}

/* catch floating point exceptions */
void fpecatch(int signum)
{
	error("floating point exception (%d).", signum);
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

/* initialize pixie */
void pixie_init(int argc, char **argv)
{
	mcatexit(cleanup);
	globinit();
	tinit();
	blockinit();
	treeinit();
	getinput(argc, argv);
}

/* run pixie */
void pixie_run(void)
{
	signal(SIGFPE, fpecatch);
	yyparse();
	eval();
}
