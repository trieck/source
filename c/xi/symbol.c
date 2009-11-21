/*
 * SYMBOL.C
 *
 * Symbol table
 *
 * 'X' Programming Language
 * Copyright (c) 2004, Thomas A. Rieck
 * All Rights Reserved
 */

#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "symbol.h"
#include "list.h"
#include "xmalloc.h"

#define TBLSIZE 1103

static unsigned hash(const char *);

/* make symbol table */
SymbolTable mksymtab(void)
{
	SymbolTable symbols = (SymbolTable) xmalloc(sizeof(PSYMBOL) * TBLSIZE);
	memset(symbols, 0, sizeof(PSYMBOL) * TBLSIZE);
	return symbols;
}

/* Sedgewick 14.1 hash for string keys */
unsigned hash(const char *key)
{
	int h = 0, a = 127;

	for (; *key; key++)
		h = (a * h + *key) % TBLSIZE;

	return h;
}

/* free the symbol table */
void freesymtab(SymbolTable symbols)
{
	int i;

	for (i = 0; i < TBLSIZE; i++) {
		PSYMBOL sym = symbols[i];
		if (sym != 0)
			symfree(sym);
	}

	xfree(symbols);
}

/* find s in symbol table */
PSYMBOL symlookup(SymbolTable table, const char *s)
{
	PSYMBOL sym;

	unsigned i = hash(s);

	for (sym = table[i]; sym != 0; sym = sym->next) {
		if (strcmp(sym->name, s) == 0)
			break;
	}

	return sym;
}

/* insert string symbol */
PSYMBOL syminsert(SymbolTable table, const char *name, int type,
                  int subtype, const char *val)
{
	int i = hash(name);

	PSYMBOL sym = (PSYMBOL) xmalloc(sizeof(Symbol));
	sym->name = xstrdup(name);
	sym->type = type;
	sym->subtype = subtype | SSTRING;
	sym->u.sval = xstrdup(val);
	sym->next = table[i];
	table[i] = sym;
	return sym;
}

/* insert float symbol */
PSYMBOL syminsertf(SymbolTable table, const char *name, int type,
                   int subtype, double val)
{
	int i = hash(name);

	PSYMBOL sym = (PSYMBOL) xmalloc(sizeof(Symbol));
	sym->name = xstrdup(name);
	sym->type = type;
	sym->subtype = subtype | SFLOAT;
	sym->u.fval = val;
	sym->next = table[i];
	table[i] = sym;
	return sym;
}

/* free a symbol and all chains */
void symfree(PSYMBOL sym)
{
	while (sym != 0) {
		PSYMBOL next = sym->next;

		xfree(sym->name);

		if (sym->subtype & SSTRING)
			xfree(sym->u.sval);
		if (sym->subtype & SLIST)
			listfree(sym->u.lval);

		xfree(sym);
		sym = next;
	}
}

/* copy a symbol */
PSYMBOL symcopy(PSYMBOL src)
{
	PSYMBOL dest = xmalloc(sizeof(Symbol));

	dest->type = src->type;
	dest->subtype = src->subtype;

	dest->name = src->name ? xstrdup(src->name) : NULL;

	if (src->subtype & SFLOAT)
		dest->u.fval = src->u.fval;
	if (src->subtype & SSTRING)
		dest->u.sval = xstrdup(src->u.sval);
	if (src->subtype & SLIST)
		dest->u.lval = listcopy(src->u.lval);

	dest->next = NULL;			/* not chained */

	return dest;
}

/* duplicate a symbol */
void symdup(PSYMBOL dest, PSYMBOL src)
{
	if (dest->subtype & SSTRING)
		xfree(dest->u.sval);
	else if (dest->subtype & SLIST)
		listfree(dest->u.lval);

	if (src->subtype & SFLOAT)
		dest->u.fval = src->u.fval;
	if (src->subtype & SSTRING)
		dest->u.sval = xstrdup(src->u.sval);
	if (src->subtype & SLIST)
		dest->u.lval = listcopy(src->u.lval);

	dest->subtype = src->subtype;
}