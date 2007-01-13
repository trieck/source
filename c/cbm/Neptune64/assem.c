/*
 *	ASSEM.C
 *
 *	code assembly
 *
 *	Neptune64 Commodore 64 Emulator
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
 *
 */
#include "common.h"
#include "assem.h"
#include "instr.h"
#include "symbol.h"
#include "parser.h"
#include "code.h"
static int ismode(addrmode mode);
static int isacc(void);
static int isimm(void);
static int iszpg(void);
static int iszpx(void);
static int iszpy(void);
static int isabs(void);
static int isabx(void);
static int isaby(void);
static int isimp(void);
static int isrel(void);
static int isidx(void);
static int isidy(void);
static int isind(void);
static int op(const word addr, const instr *i);
static Token lookahead(void);
static void cleanup(void);
const char **ppin;			/* pointer to the current input */
int assemmode = 0;			/* are we in assembler mode ? */
word assemc = 0;			/* counter used during assembly */
static SymbolTable symbols;	/* symbol table of opcodes */
#define ISZADDR(x) (x < 0x100)
/*
 * initialize the assembler module
 */
void assem_init(void)
{
	atexit(cleanup);
	symbols = symalloc();
	if (NULL == symbols) 
		error("could not allocate symbol table.\n");
	syminit(symbols);
}
/* 
 * assemble input
 */
void assemble(const char **ppinput)
{
	PSYMBOL sym;
	word address;
	const char *usage = "usage: a address [opcode][operands]\n";
	Token tok;
	ppin = ppinput;
	assemmode = 0;
	tok = gettok(ppin);
	if (NUM != tok.type) {
		warning(usage);
		return;
	}
	sscanf(tok.value, "%hx", &address);
	tok = gettok(ppin);
	if (UNDEF == tok.type) {
		assemc = address;
		assemmode = 1;
		return;
	} 
 
	sym = lookup(symbols, tok.value);
	if (NULL == sym) {
		warning("unrecognized opcode [%s].\n", tok.value);
		return;
	}
	assemmode = op(address, sym->instr);
}
/*
 * assemble input in assembly mode
 */
void assemble_inmode(const char **ppinput)
{
	PSYMBOL sym;
	Token tok;
	word address = assemc;
	const char *usage = "usage: opcode [operands]\n";
	ppin = ppinput;
	assemmode = 0;
	tok = gettok(ppin);
	if ('\0' == tok.value[0])
		return;	/* clean exit from assembly mode */
	if (UNDEF == tok.type) {
		warning(usage);
		return;						
	}
	sym = lookup(symbols, tok.value);
	if (NULL == sym) {
		warning("unrecognized opcode [%s].\n", tok.value);
		return;
	}
	assemmode = op(address, sym->instr);
}
int op(const word addr, const instr *i)
{
	int mode;
	for (mode = 0; mode < MODES; mode++) {
		const byte *opcode = (*i)[mode];
		if (opcode && ismode(mode)) {
			assemc = code(addr, mode, *opcode);
			return 1;
		}
	}
	warning("invalid addressing mode.\n");
	return 0;
}
/* 
 * does the input match the specified mode 
 */
int ismode(addrmode mode)
{
	switch(mode) {
	case acc:
		return isacc();
	case imm:
		return isimm();
	case zpg:
		return iszpg();
	case zpx:
		return iszpx();
	case zpy:
		return iszpy();
	case absl:
		return isabs();
	case abx:
		return isabx();
	case aby:
		return isaby();
	case imp:
		return isimp();
	case rel:
		return isrel();
	case idx:
		return isidx();
	case idy:
		return isidy();
	case ind:
		return isind();
	}
	return 0;
}
/*
 * does the current input match the accumulator addressing mode
 */
int isacc(void)
{
	Token tok = lookahead();
	return tok.value[0] == '\0';
}
/*
 * does the current input match the immediate addressing mode
 */
int isimm(void)
{
	word operand;
	Token tok1, tok2;
	const char *psave = *ppin;
	tok1 = gettok(&psave);
	tok2 = gettok(&psave);
	if (tok1.type != POUND)
		return 0;
	return sscanf(tok2.value, "%hx", &operand) == 1 && ISZADDR(operand);
}
/*
 * does the current input match the zero page addressing mode
 */
int iszpg(void)
{
	word operand;
	const char *psave = *ppin;
	Token tok;
	tok = gettok(&psave);
	if (tok.type != NUM)
		return 0;
	sscanf(tok.value, "%hx", &operand);
	
	tok = gettok(&psave);
	if (tok.value[0] != '\0')
		return 0;
	return ISZADDR(operand);
}
/* 
 * does the current input match the zero page, x addressing mode
 */
int iszpx(void)
{
	word operand;
	const char *psave = *ppin;
	Token tok;
	tok = gettok(&psave);
	if (tok.type != NUM)
		return 0;
	sscanf(tok.value, "%hx", &operand);
	
	tok = gettok(&psave);
	if (tok.type != COMMA)
		return 0;
	tok = gettok(&psave);
	if (tok.value[0] != 'x' && tok.value[0] != 'X')
		return 0;
	return ISZADDR(operand);
}
/*
 * does the current input match the zero page, y addressing mode
 */
int iszpy(void)
{
	word operand;
	const char *psave = *ppin;
	Token tok;
	tok = gettok(&psave);
	if (tok.type != NUM)
		return 0;
	sscanf(tok.value, "%hx", &operand);
	
	tok = gettok(&psave);
	if (tok.type != COMMA)
		return 0;
	tok = gettok(&psave);
	if (tok.value[0] != 'y' && tok.value[0] != 'Y')
		return 0;
	return ISZADDR(operand);
}
/*
 * does the current input match the absolute addressing mode 
 */
int isabs(void)
{
	word operand;
	const char *psave = *ppin;
	Token tok;
	tok = gettok(&psave);
	if (tok.type != NUM)
		return 0;
	sscanf(tok.value, "%hx", &operand);
	if (ISZADDR(operand)) 
		return 0;
	tok = gettok(&psave);
	return tok.value[0] == '\0';
}
/*
 * does the current input match the absolute, x addressing mode
 */
int isabx(void)
{
	word operand;
	const char *psave = *ppin;
	Token tok;
	tok = gettok(&psave);
	if (tok.type != NUM)
		return 0;
	sscanf(tok.value, "%hx", &operand);
	if (ISZADDR(operand)) 
		return 0;
		
	tok = gettok(&psave);
	if (tok.type != COMMA)
		return 0;
	tok = gettok(&psave);
	if (tok.value[0] != 'x' && tok.value[0] != 'X')
		return 0;
	return 1;
}
/*
 * does the current input match the absolute, y addressing mode
 */
int isaby(void)
{	
	word operand;
	const char *psave = *ppin;
	Token tok;
	tok = gettok(&psave);
	if (tok.type != NUM)
		return 0;
	sscanf(tok.value, "%hx", &operand);
	if (ISZADDR(operand)) 
		return 0;
		
	tok = gettok(&psave);
	if (tok.type != COMMA)
		return 0;
	tok = gettok(&psave);
	if (tok.value[0] != 'y' && tok.value[0] != 'Y')
		return 0;
	return 1;
}
/* 
 * does the current input match the indirect addressing mode
 */
int isind(void)
{
	Token tok;
	word operand;
	const char *psave = *ppin;
	tok = gettok(&psave);
	if (tok.type != LPAREN)
		return 0;
	tok = gettok(&psave);
	if (tok.type != NUM) 
		return 0;
	sscanf(tok.value, "%hx", &operand);
	if (ISZADDR(operand)) 
		return 0;
	tok = gettok(&psave);
	if (tok.type != RPAREN)
		return 0;
	return 1;
}
/* 
 * does the current input match the indirect, x addressing mode
 */
int isidx(void)
{
	Token tok;
	word operand;
	const char *psave = *ppin;
	
	tok = gettok(&psave);
	if (tok.type != LPAREN)
		return 0;
	
	tok = gettok(&psave);
	if (tok.type != NUM)
		return 0;
	sscanf(tok.value, "%hx", &operand);
	
	tok = gettok(&psave);
	if (tok.type != COMMA)
		return 0;
	tok = gettok(&psave);
	if (tok.value[0] != 'x' && tok.value[0] != 'X')
		return 0;
	tok = gettok(&psave);
	if (tok.type != RPAREN)
		return 0;
	return ISZADDR(operand);
}
/*
 * does the current input match the indirect, y addressing mode
 */
int isidy(void)
{
	Token tok;
	word operand;
	const char *psave = *ppin;
	tok = gettok(&psave);
	if (tok.type != LPAREN)
		return 0;
	
	tok = gettok(&psave);
	if (tok.type != NUM)
		return 0;
	sscanf(tok.value, "%hx", &operand);
	tok = gettok(&psave);
	if (tok.type != RPAREN)
		return 0;
	tok = gettok(&psave);
	if (tok.type != COMMA)
		return 0;
	tok = gettok(&psave);
	if (tok.value[0] != 'y' && tok.value[0] != 'Y')
		return 0;
	
	return ISZADDR(operand);
}
/*
 * does the current input match the implied mode
 */
int isimp(void)
{
	Token tok = lookahead();
	return tok.value[0] == '\0';
}
/* 
 * does the current input match the relative addressing mode
 */
int isrel(void)
{
	word operand;
	const char *psave = *ppin;
	Token tok;
	tok = gettok(&psave);
	if (tok.type != NUM)
		return 0;
	sscanf(tok.value, "%hx", &operand);
	if (ISZADDR(operand)) 
		return 0;
	return 1;
}
/*
 * lookahead to next token
 */
Token lookahead(void)
{
	const char ** dummy = ppin;
	return gettok(dummy);
}
/*
 * perform cleanup
 */
void cleanup(void)
{
	if (NULL != symbols)
		symfree(symbols);
}
