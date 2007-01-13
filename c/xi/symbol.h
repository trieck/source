/*
 * SYMBOL.H
 *
 * Symbol table
 *
 * 'X' Programming Language
 * Copyright (c) 2004, Thomas A. Rieck
 * All Rights Reserved
 */

#ifndef __SYMBOL_H__
#define __SYMBOL_H__

/* symbol types */
#define SUNDEF	0x0000			/* undefined symbol */
#define SCONST	0x0001			/* an atomic constant */
#define SVAR	0x0002			/* an atomic variable */
#define SFUNC	0x0003			/* a function */
#define SKEYWD	0x0004			/* a keyword */
#define SBLTIN	0x0005			/* a builtin procedure */

/* symbol subtypes */
#define SFLOAT	0x0001			/* a floating point variable / constant */
#define SSTRING	0x0002			/* a string variable / constant */
#define SLIST	0x0004			/* a list */
#define STEMP	0x0008			/* a temporary symbol */

/* forward declarations */
struct LinkedList;

/* symbol table entry */
typedef struct Symbol {
	char *name;					/* name of symbol */
	int type;					/* type of symbol */
	int subtype;				/* sub-type of symbol */
	union u {
		char *sval;				/* string value */
		double fval;			/* floating point value */
		struct LinkedList *lval;	/* linked list */
	} u;
	struct Symbol *next;		/* next symbol if chained */
} Symbol, *PSYMBOL, **PPSYMBOL;

typedef PPSYMBOL SymbolTable;

SymbolTable mksymtab(void);
void freesymtab(SymbolTable table);
PSYMBOL syminsert(SymbolTable table, const char *name, int type,
				  int subtype, const char *val);
PSYMBOL syminsertf(SymbolTable table, const char *name, int type,
				   int subtype, double val);
PSYMBOL symlookup(SymbolTable table, const char *name);
void symfree(PSYMBOL sym);
PSYMBOL symcopy(PSYMBOL src);
void symdup(PSYMBOL dest, PSYMBOL src);

#endif							/* __SYMBOL_H__ */
