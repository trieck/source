/**** global.h *************************************************************/

#ifndef __GLOBAL_H_INCLUDED
#define __GLOBAL_H_INCLUDED

#include <stdio.h>	/* load i/o routines */
#include <ctype.h>	/* load character test routines */
#include <stdlib.h>
#include <string.h>

#define BSIZE	128	/* buffer size */
#define NONE	-1
#define EOS		'\0'

#define NUM		256
#define DIV		257
#define MOD		258
#define ID		259
#define DONE	260

int tokenval;	/* value of token attribute */
int lineno;

struct entry {	/* form of symbol table entry */
	char *lexptr;
	int token;
};

struct entry symtable[];	/* symbol table */

extern void error(char *m);

#endif /* __GLOBAL_H__INCLUDED */
