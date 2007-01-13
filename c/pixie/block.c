/*
 * BLOCK.C
 *
 * Block scope
 *
 * Pixie Language
 * Copyright(c) 2002, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#include <stdlib.h>
#include "pixie.h"
#include "symbol.h"
#include "global.h"
#include "block.h"
#include "memcheck.h"

#define NBLOCK 1024
#define BLOCKSTOP ((SymbolTable)0)

static SymbolTable blocks[NBLOCK];
static SymbolTable *blockp;

static void blockpush(SymbolTable table);
static SymbolTable blockpop(void);
static void blockfree(void);

/* initialize */
void blockinit(void)
{
	mcatexit(blockfree);
	blockp = blocks;
}

/* free all remaining symbol tables */
void blockfree(void)
{
	SymbolTable table;

	while (blockp > blocks) {
		table = blockpop();
		if (table == BLOCKSTOP)
			continue;

		tabfree(table);
	}
}

/* enter a code block */
void blockenter(void)
{
	SymbolTable block;
	block = maketab();
	blockpush(block);
}

/* leave a code block */
void blockleave(void)
{
	SymbolTable block;
	block = blockpop();
	tabfree(block);
}

/* lookup a symbol */
Symbol *blookup(const char *s)
{
	Symbol *sp = 0;
	SymbolTable *bp;

	ASSERT(blockp > blocks);

	/* walk the stack of hash table pointers */
	for (bp = blockp - 1; bp >= blocks; bp--) {
		if (*bp == BLOCKSTOP)
			break;

		sp = lookup(*bp, s);
		if (sp)
			break;
	}


	/* try global "special" variables */
	if (!sp)
		sp = glookup(s);

	return sp;
}

/* does a local already exist */
int islocal(const char *s)
{
	SymbolTable *block;

	ASSERT(blockp > blocks);

	block = blockp - 1;			/* current block */
	if (lookup(*block, s))
		return 1;

	return 0;
}

/* install s */
Symbol *binstall(const char *s, int t, int sub, double val)
{
	SymbolTable *block;

	ASSERT(blockp > blocks);

	block = blockp - 1;			/* current block */
	return install(*block, s, t, sub, val);
}

/* push a symbol table */
void blockpush(SymbolTable table)
{
	if (blockp >= &blocks[NBLOCK]) {
		error("block nested too deep.");
	}

	*blockp++ = table;
}

/* pop a symbol table */
SymbolTable blockpop(void)
{
	if (blockp == blocks) {
		error("block stack underrun.");
	}

	return *--blockp;
}
