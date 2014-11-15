/*
 * TEMP.C
 *
 * Temporary symbols
 *
 * Pixie Language
 * Copyright(c) 2002, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#include <stdlib.h>
#include "pixie.h"
#include "temp.h"
#include "symbol.h"
#include "tree.h"
#include "parse.h"
#include "memcheck.h"

static SymbolTable symbols;		/* temp symbols */

static void tfree(void);

/* allocate and initialize temporary symbol table */
void tinit(void)
{
    mcatexit(tfree);
    symbols = maketab();
}

/* lookup s in symbol table */
Symbol *tlookup(const char *s)
{
    return lookup(symbols, s);
}

/* install s in symbol table */
Symbol *tinstall(const char *s, int t, int sub, double d)
{
    Symbol *sym;

    if ((sym = tlookup(s)))
        return sym;

    return install(symbols, s, t, sub, d);
}

/* install string s in symbol table */
Symbol *tinstalls(const char *s, const char *v)
{
    Symbol *sym;

    if ((sym = tlookup(s)))
        return sym;

    return installs(symbols, s, v);
}

/* free temporary symbol table */
void tfree(void)
{
    tabfree(symbols);
    symbols = 0;
}
