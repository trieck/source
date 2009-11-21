/*
 * SYMBOL.C
 *
 * Symbol table
 *
 * Pixie Language
 * Copyright(c) 2002, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#include <stdlib.h>
#include <string.h>
#include "pixie.h"
#include "symbol.h"
#include "xmalloc.h"
#include "parse.h"

#define TBLSIZE 1103

static unsigned int hash(const char *p);

/* allocate the symbol table */
SymbolTable maketab(void)
{
	SymbolTable symbols =
	    (SymbolTable) xmalloc(sizeof(Symbol *) * TBLSIZE);
	memset(symbols, 0, sizeof(Symbol *) * TBLSIZE);
	return symbols;
}

/* free the symbol table */
void tabfree(SymbolTable symbols)
{
	int i;

	for (i = 0; i < TBLSIZE; i++) {
		Symbol *sym = symbols[i];
		if (sym != 0)
			symfree(sym);
	}

	xfree(symbols);
}

/* Sedgewick 14.1 hash for string keys */
unsigned int hash(const char *p)
{
	int h = 0, a = 127;

	for (; *p; p++)
		h = (a * h + *p) % TBLSIZE;

	return h;
}

/* find s in symbol table */
Symbol *lookup(SymbolTable table, const char *s)
{
	Symbol *sym;

	unsigned i = hash(s);

	for (sym = table[i]; sym != 0; sym = sym->next) {
		if (strcmp(sym->name, s) == 0)
			break;
	}

	return sym;
}

/* install s in symbol table */
Symbol *install(SymbolTable table, const char *s, int t, int sub,
                double val)
{
	int i = hash(s);

	Symbol *sym = (Symbol *) xmalloc(sizeof(Symbol));
	sym->name = xstrdup(s);
	sym->type = t;
	sym->sub = sub;
	sym->u.fval = val;
	sym->next = table[i];
	table[i] = sym;

	return sym;
}

/* installs:  install string s in symbol table */
Symbol *installs(SymbolTable table, const char *s, const char *v)
{
	int i = hash(s);

	Symbol *sym = (Symbol *) xmalloc(sizeof(Symbol));
	sym->name = xstrdup(s);
	sym->type = SCONST;
	sym->sub = SSTRING;
	sym->u.sval = xstrdup(v);
	sym->next = table[i];
	table[i] = sym;

	return sym;
}
