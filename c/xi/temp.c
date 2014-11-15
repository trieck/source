/*
 * TEMP.C
 *
 * Temporary symbols
 *
 * 'X' Programming Language
 * Copyright(c) 2004, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#include <stdlib.h>
#include "temp.h"

static SymbolTable symbols;		/* temp symbols */

static void tfree(void);

/* allocate and initialize temporary symbol table */
void tinit(void)
{
    atexit(tfree);
    symbols = mksymtab();
}

/* lookup s in symbol table */
PSYMBOL tlookup(const char *s)
{
    return symlookup(symbols, s);
}

/* install s in symbol table */
PSYMBOL tinstallf(const char *s, int t, double d)
{
    PSYMBOL sym;

    if ((sym = tlookup(s)))
        return sym;

    return syminsertf(symbols, s, t, 0, d);
}

/* install string s in symbol table */
PSYMBOL tinstall(const char *s, int t, const char *v)
{
    PSYMBOL sym;

    if ((sym = tlookup(s)))
        return sym;

    return syminsert(symbols, s, t, 0, v);
}

/* free temporary symbol table */
void tfree(void)
{
    freesymtab(symbols);
    symbols = NULL;
}
