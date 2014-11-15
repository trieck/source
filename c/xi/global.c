/*
 * GLOBAL.C
 *
 * Global symbol table
 *
 * 'X' Programming Language
 * Copyright(c) 2004, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#include <stdlib.h>
#include "x.h"
#include "global.h"
#include "tree.h"
#include "parser.h"

static SymbolTable symbols;		/* global symbols */

/* keywords */
static struct {
    const char *name;
    int kval;
} keywords[] = {
    {
        "print", PRINT
    }, {
        "println", PRINTLN
    }, {
        "let", LET
    }, {
        0, 0
    }
};

static void globfree(void);

/* allocate and initialize global symbol table */
void globinit(void)
{
    int i;

    atexit(globfree);
    symbols = mksymtab();

    /* install keywords */
    for (i = 0; keywords[i].name; i++)
        ginstallf(keywords[i].name, SKEYWD, keywords[i].kval, 0);
}

/* lookup s in symbol table */
PSYMBOL glookup(const char *s)
{
    return symlookup(symbols, s);
}

/* install s in symbol table */
PSYMBOL ginstallf(const char *s, int t, int subtype, double d)
{
    return syminsertf(symbols, s, t, subtype, d);
}

/* install string s in symbol table */
PSYMBOL ginstall(const char *s, int type, int subtype, const char *v)
{
    return syminsert(symbols, s, type, subtype, v);
}

/* free global symbol table */
void globfree(void)
{
    freesymtab(symbols);
    symbols = NULL;
}
