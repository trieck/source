/*
 * 	CODE.C	code generation
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
#include "code.h"
#include "opcodes.h"
#include "assem.h"
#include "label.h"
#include "symbol.h"

#define MEMSIZE	4096

static void putmem(int ncount, ...);
static void acccode(byte);
static void immcode(byte);
static void zpgcode(byte);
static void zpxcode(byte);
static void zpycode(byte);
static void abscode(byte);
static void abxcode(byte);
static void abycode(byte);
static void impcode(byte);
static void relcode(byte);
static void idxcode(byte);
static void idycode(byte);
static void indcode(byte);

static byte memory[MEMSIZE];
static byte *pmem = memory;
extern SymbolTable table;		/* symbol table of kernel entries / opcodes */
extern LabelTable labels;		/* symbol table of labels */
extern Token token;				/* current token */
extern const char *pinput;		/* pointer to current input */
extern const char *infile;		/* input file name */
extern int lineno;				/* current line number */

void putmem(int ncount, ...)
{
	va_list arglist;
	va_start(arglist, ncount);
	while (ncount--) {
		*pmem++ = va_arg(arglist, int);
	}

	va_end(arglist);
}

/*
 * write a byte to memory
 */
void write_byte(byte b)
{
	putmem(1, b);
}

/* 
 * write assembled program to file
 */
void write_code(void)
{
	FILE *fpout;
	const byte *pmemory;
	char outfile[256], *pout;
	strcpy(outfile, infile);
	pout = strrchr(outfile, '.');
	strcpy(++pout, "o");
	fpout = fopen(outfile, "wb");
	if (fpout == NULL)
		error("unable to open output file %s.\n", outfile);
	pmemory = memory;
	for (; pmemory < pmem; pmemory++) {
		fputc(*pmemory, fpout);
	}

	fclose(fpout);
}

/*
 * in memory code generation
 */
void code(addrmode mode, byte opcode)
{
	switch (mode) {
	case acc:
		acccode(opcode);
		break;
	case imm:
		immcode(opcode);
		break;
	case zpg:
		zpgcode(opcode);
		break;
	case zpx:
		zpxcode(opcode);
		break;
	case zpy:
		zpycode(opcode);
		break;
	case absl:
		abscode(opcode);
		break;
	case abx:
		abxcode(opcode);
		break;
	case aby:
		abycode(opcode);
		break;
	case imp:
		impcode(opcode);
		break;
	case rel:
		relcode(opcode);
		break;
	case idx:
		idxcode(opcode);
		break;
	case idy:
		idycode(opcode);
		break;
	case ind:
		indcode(opcode);
		break;
	}
}
void acccode(byte opcode)
{
	putmem(1, opcode);
}

void immcode(byte opcode)
{
	word operand;
	token = gettok(&pinput);	/* '#' */
	token = gettok(&pinput);	/* operand */
	sscanf(token.value, "%hx", &operand);
	putmem(2, opcode, operand);
}

void zpgcode(byte opcode)
{
	word operand;
	token = gettok(&pinput);
	sscanf(token.value, "%hx", &operand);
	putmem(2, opcode, operand);
}

void zpxcode(byte opcode)
{
	word operand;
	token = gettok(&pinput);
	sscanf(token.value, "%hx", &operand);
	token = gettok(&pinput);	/* ',' */
	token = gettok(&pinput);	/* 'x' */
	putmem(2, opcode, operand);
}

void zpycode(byte opcode)
{
	word operand;
	token = gettok(&pinput);
	sscanf(token.value, "%hx", &operand);
	token = gettok(&pinput);	/* ',' */
	token = gettok(&pinput);	/* 'y' */
	putmem(2, opcode, operand);
}

void abscode(byte opcode)
{
	word operand = 0;
	PSYMBOL psym;
	token = gettok(&pinput);
	if (token.type == PSEUDO) {	/* label */
		token = gettok(&pinput);
		psym = symlookup(table, token.value);
		if (psym == NULL)
			labelinsert(&labels, token.value, pmem + 1, 0);
		else
			operand = psym->u.mem;
	} else if (token.type == STR) {	/* kernel jump */
		psym = symlookup(table, token.value);
		if (psym == NULL)
			error("undefined kernel jump found at line %d.\n", lineno);
		operand = psym->u.mem;
	} else
		sscanf(token.value, "%hx", &operand);

	putmem(3, opcode, lobyte(operand), hibyte(operand));
}

void abxcode(byte opcode)
{
	word operand = 0;
	PSYMBOL psym;
	token = gettok(&pinput);
	if (token.type == PSEUDO) {
		token = gettok(&pinput);
		psym = symlookup(table, token.value);
		if (psym == NULL)
			labelinsert(&labels, token.value, pmem + 1, 0);
		else
			operand = psym->u.mem;
	} else
		sscanf(token.value, "%hx", &operand);
	token = gettok(&pinput);	/* ',' */
	token = gettok(&pinput);	/* 'x' */
	putmem(3, opcode, lobyte(operand), hibyte(operand));
}

void abycode(byte opcode)
{
	word operand = 0;
	PSYMBOL psym;
	token = gettok(&pinput);
	if (token.type == PSEUDO) {
		token = gettok(&pinput);
		psym = symlookup(table, token.value);
		if (psym == NULL)
			labelinsert(&labels, token.value, pmem + 1, 0);
		else
			operand = psym->u.mem;
	} else
		sscanf(token.value, "%hx", &operand);
	token = gettok(&pinput);	/* ',' */
	token = gettok(&pinput);	/* 'y' */
	putmem(3, opcode, lobyte(operand), hibyte(operand));
}

void indcode(byte opcode)
{
	word operand = 0;
	PSYMBOL psym;
	token = gettok(&pinput);	/* '(' */

	token = gettok(&pinput);
	if (token.type == PSEUDO) {
		token = gettok(&pinput);
		psym = symlookup(table, token.value);
		if (psym == NULL)
			labelinsert(&labels, token.value, pmem + 1, 0);
		else
			operand = psym->u.mem;
	} else
		sscanf(token.value, "%hx", &operand);
	token = gettok(&pinput);	/* ')' */
	putmem(3, opcode, lobyte(operand), hibyte(operand));
}

void impcode(byte opcode)
{
	putmem(1, opcode);
}

void relcode(byte opcode)
{
	word operand = 0;
	PSYMBOL psym;
	token = gettok(&pinput);
	if (token.type == PSEUDO) {
		token = gettok(&pinput);
		psym = symlookup(table, token.value);
		if (psym == NULL)
			labelinsert(&labels, token.value, pmem + 1, 1);
		else
			operand = psym->u.mem;
	} else
		sscanf(token.value, "%hx", &operand);

	putmem(2, opcode, operand - (getmem() + 2));
}

void idxcode(byte opcode)
{
	word operand;

	token = gettok(&pinput);	/* '(' */

	token = gettok(&pinput);
	sscanf(token.value, "%hx", &operand);
	token = gettok(&pinput);	/* ',' */
	token = gettok(&pinput);	/* 'x' */
	token = gettok(&pinput);	/* ')' */
	putmem(2, opcode, operand);
}

void idycode(byte opcode)
{
	word operand;

	token = gettok(&pinput);	/* '(' */

	token = gettok(&pinput);
	sscanf(token.value, "%hx", &operand);
	token = gettok(&pinput);	/* ')' */
	token = gettok(&pinput);	/* ',' */
	token = gettok(&pinput);	/* 'y' */

	putmem(2, opcode, operand);
}
void resolve(void)
{
	label *plabels = labels;
	while (plabels != NULL) {
		Symbol *psym = symlookup(table, plabels->name);
		if (psym == NULL)
			error("label \"%s\" was not defined.\n", plabels->name);
		/* determine if this is a relative branch fix-up */
		if (plabels->isrel) {
			word mem = (word) (plabels->mem + 1 - memory);
			memory[plabels->mem - memory] = (byte) (psym->u.mem - mem);
		} else {
			memory[plabels->mem - memory] = lobyte(psym->u.mem);
			memory[plabels->mem - memory + 1] = hibyte(psym->u.mem);
		}
		plabels = plabels->next;
	}
}
word getmem(void)
{
	return (word) (pmem - memory);
}
