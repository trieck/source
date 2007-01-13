/*
 *
 * 	SYMBOL.C : symbol table
 *
 * 	Copyright (C) 2001 Thomas A. Rieck <trieck@bellsouth.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 */
#include "common.h"
#include "opcodes.h"
#include "symbol.h"
/* Helper functions */
static void freesymbol(PSYMBOL);
static unsigned hash(const char *);
/* 
 * allocate symbol table
 */
SymbolTable symalloc()
{
	SymbolTable table;
	table = (PSYMBOL *) malloc(sizeof(PSYMBOL) * TBLSIZE);
	memset(table, 0, sizeof(PSYMBOL) * TBLSIZE);
	return table;
}

/* 
 * initialize symbol table
 */
void syminit(SymbolTable table)
{
	/* insert opcodes */
	opinsert(table, "adc", &adc);
	opinsert(table, "and", &and);
	opinsert(table, "asl", &asl);
	opinsert(table, "bcc", &bcc);
	opinsert(table, "bcs", &bcs);
	opinsert(table, "beq", &beq);
	opinsert(table, "bit", &bit);
	opinsert(table, "bmi", &bmi);
	opinsert(table, "bne", &bne);
	opinsert(table, "bpl", &bpl);
	opinsert(table, "brk", &Brk);
	opinsert(table, "bvc", &bvc);
	opinsert(table, "bvs", &bvs);
	opinsert(table, "clc", &clc);
	opinsert(table, "cld", &cld);
	opinsert(table, "cli", &cli);
	opinsert(table, "clv", &clv);
	opinsert(table, "cmp", &cmp);
	opinsert(table, "cpx", &cpx);
	opinsert(table, "cpy", &cpy);
	opinsert(table, "dec", &dec);
	opinsert(table, "dex", &dex);
	opinsert(table, "dey", &dey);
	opinsert(table, "eor", &eor);
	opinsert(table, "inc", &inc);
	opinsert(table, "inx", &inx);
	opinsert(table, "iny", &iny);
	opinsert(table, "jmp", &jmp);
	opinsert(table, "jsr", &jsr);
	opinsert(table, "lda", &lda);
	opinsert(table, "ldx", &ldx);
	opinsert(table, "ldy", &ldy);
	opinsert(table, "lsr", &lsr);
	opinsert(table, "nop", &nop);
	opinsert(table, "ora", &ora);
	opinsert(table, "pha", &pha);
	opinsert(table, "php", &php);
	opinsert(table, "pla", &pla);
	opinsert(table, "plp", &plp);
	opinsert(table, "rol", &rol);
	opinsert(table, "ror", &ror);
	opinsert(table, "rti", &rti);
	opinsert(table, "rts", &rts);
	opinsert(table, "sbc", &sbc);
	opinsert(table, "sec", &sec);
	opinsert(table, "sed", &sed);
	opinsert(table, "sei", &sei);
	opinsert(table, "sta", &sta);
	opinsert(table, "stx", &stx);
	opinsert(table, "sty", &sty);
	opinsert(table, "tax", &tax);
	opinsert(table, "tay", &tay);
	opinsert(table, "tsx", &tsx);
	opinsert(table, "txa", &txa);
	opinsert(table, "txs", &txs);
	opinsert(table, "tya", &tya);
	/* insert kernel jump table entries */
	kinsert(table, "acptr", 0xffa5);
	kinsert(table, "chkin", 0xffc6);
	kinsert(table, "chrin", 0xffcf);
	kinsert(table, "chrout", 0xffd2);
	kinsert(table, "ciout", 0xffa8);
	kinsert(table, "cint", 0xff81);
	kinsert(table, "clall", 0xffe7);
	kinsert(table, "close", 0xffc3);
	kinsert(table, "clrchn", 0xffcc);
	kinsert(table, "getin", 0xffe4);
	kinsert(table, "iobase", 0xfff3);
	kinsert(table, "ioinit", 0xff84);
	kinsert(table, "listen", 0xffb1);
	kinsert(table, "load", 0xffd5);
	kinsert(table, "membot", 0xff9c);
	kinsert(table, "memtop", 0xff99);
	kinsert(table, "open", 0xffc0);
	kinsert(table, "plot", 0xfff0);
	kinsert(table, "ramtas", 0xff87);
	kinsert(table, "rdtim", 0xffde);
	kinsert(table, "readst", 0xff87);
	kinsert(table, "restor", 0xff8a);
	kinsert(table, "save", 0xffd8);
	kinsert(table, "scnkey", 0xff9f);
	kinsert(table, "screen", 0xffed);
	kinsert(table, "second", 0xff93);
	kinsert(table, "setlfs", 0xffba);
	kinsert(table, "setmsg", 0xff90);
	kinsert(table, "setnam", 0xffbd);
	kinsert(table, "settim", 0xffdb);
	kinsert(table, "settmo", 0xffa2);
	kinsert(table, "stop", 0xffe1);
	kinsert(table, "talk", 0xffb4);
	kinsert(table, "tksa", 0xff96);
	kinsert(table, "udtim", 0xffea);
	kinsert(table, "unlsn", 0xffae);
	kinsert(table, "untlk", 0xffab);
	kinsert(table, "vector", 0xff8d);
}

/* 
 * free symbol table
 */
void symfree(SymbolTable table)
{
	int i;
	for (i = 0; i < TBLSIZE; i++) {
		PSYMBOL ps = table[i];
		if (ps != NULL)
			freesymbol(ps);
	}
	free(table);
}

/* 
 * insert opcode 
 */
PSYMBOL opinsert(SymbolTable table, const char *name, const Instr * instr)
{
	PSYMBOL ps;
	unsigned int index;

	ps = (Symbol *) malloc(sizeof(Symbol));
	index = hash(name);

	ps->name = strcopy(name);
	ps->type = opcode;
	ps->u.instr = instr;

	ps->next = table[index];
	table[index] = ps;

	return ps;
}

/*
 * insert kernel jump table entry 
 */
PSYMBOL kinsert(SymbolTable table, const char *name, const word kjmp)
{
	PSYMBOL ps;
	unsigned int index;

	ps = (Symbol *) malloc(sizeof(Symbol));
	index = hash(name);

	ps->name = strcopy(name);
	ps->type = kentry;
	ps->u.kjmp = kjmp;

	ps->next = table[index];
	table[index] = ps;

	return ps;
}

/*
 * insert a label
 */
PSYMBOL linsert(SymbolTable table, const char *name, word pmem)
{
	PSYMBOL ps;
	unsigned int index;

	ps = (Symbol *) malloc(sizeof(Symbol));
	index = hash(name);

	ps->name = strcopy(name);
	ps->type = lentry;
	ps->u.mem = pmem;

	ps->next = table[index];
	table[index] = ps;

	return ps;
}

/* 
 * lookup entry in symbol table 
 */
PSYMBOL symlookup(SymbolTable table, const char *name)
{
	unsigned int index;
	PSYMBOL ps = NULL;
	index = hash(name);
	for (ps = table[index]; ps != NULL; ps = ps->next) {
		if (strcmp(ps->name, name) == 0)
			break;
	}
	return ps;
}

/* Helper functions */
/*
 * free a symbol
 */
void freesymbol(PSYMBOL ps)
{
	while (ps != NULL) {
		PSYMBOL next = ps->next;
		free(ps->name);
		free(ps);
		ps = next;
	}
}

/*
 * hash function
 */
unsigned int hash(const char *p)
{
	unsigned n = 0;
	while (*p) {
		n = (n << 1) ^ toupper(*p++);
	}
	n %= TBLSIZE;

	return n;
}
