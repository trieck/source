/*
 *	CODE.C	
 *	code generation
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
#include "code.h"
#include "opcodes.h"
#include "mem.h"
#include "parser.h"
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
extern const char **ppin;	/* pointer to current input */
static word pmem;	
void putmem(int ncount, ...)
{
	va_list arglist;
   	va_start(arglist, ncount);
	while (ncount--) {
		byte c = va_arg(arglist, char);
		store_byte(pmem++, c);
	}
   
	va_end (arglist);
}
/*
 * code generation
 */
word code(word start, addrmode mode, byte opcode)
{
	pmem = start;
	switch(mode) {
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
	return pmem;
}
/*
 * accumlator addressing mode
 */
void acccode(byte opcode)
{
	putmem(1, opcode);
}
/* 
 * immediate addressing mode
 */
void immcode(byte opcode)
{
	word operand;
	Token token;
	token = gettok(ppin);	/* '#' */
	token = gettok(ppin);	/* operand */
	sscanf(token.value, "%hx", &operand);
	putmem(2, opcode, operand);
}
/* 
 * zero page addressing mode
 */
void zpgcode(byte opcode)
{
	word operand;
	Token token;
	token = gettok(ppin);
	sscanf(token.value, "%hx", &operand);
	putmem(2, opcode, operand);
}
/*
 * zero page, x addressing mode
 */
void zpxcode(byte opcode)
{
	word operand;
	Token token;
	token = gettok(ppin);
	sscanf(token.value, "%hx", &operand);
	token = gettok(ppin);	/* ',' */
	token = gettok(ppin);	/* 'x' */
	putmem(2, opcode, operand);
}
/* 
 * zero page, y addressing mode
 */
void zpycode(byte opcode)
{
	word operand;
	Token token;
	token = gettok(ppin);
	sscanf(token.value, "%hx", &operand);
	token = gettok(ppin);	/* ',' */
	token = gettok(ppin);	/* 'y' */
	putmem(2, opcode, operand);
}
/*
 * absolute addressing mode
 */
void abscode(byte opcode)
{
	word operand;
	Token token;
	token = gettok(ppin);
	sscanf(token.value, "%hx", &operand);
	
	putmem(3, opcode, lobyte(operand), hibyte(operand));
}
/*
 * absolute, x addressing mode
 */
void abxcode(byte opcode)
{
	word operand;
	Token token;
	token = gettok(ppin);
	sscanf(token.value, "%hx", &operand);
	token = gettok(ppin);	/* ',' */
	token = gettok(ppin);	/* 'x' */
	putmem(3, opcode, lobyte(operand), hibyte(operand));
}
/*
 * absolute, y addressing mode 
 */
void abycode(byte opcode)
{
	word operand;
	Token token;
	token = gettok(ppin);
	sscanf(token.value, "%hx", &operand);
	token = gettok(ppin);	/* ',' */
	token = gettok(ppin);	/* 'y' */
	putmem(3, opcode, lobyte(operand), hibyte(operand));
}
/*
 * indirect addressing mode
 */
void indcode(byte opcode)
{
	word operand;
	Token token;
	token = gettok(ppin);	/* '(' */
	token = gettok(ppin);
	sscanf(token.value, "%hx", &operand);
	token = gettok(ppin);	/* ')' */
	putmem(3, opcode, lobyte(operand), hibyte(operand));
}
/* 
 * implied addressing mode
 */
void impcode(byte opcode)
{
	putmem(1, opcode);
}
/* 
 * relative addressing mode 
 */
void relcode(byte opcode)
{
	word operand;
	Token token;
	token = gettok(ppin);
	sscanf(token.value, "%hx", &operand);
		
	putmem(2, opcode, operand - (pmem + 2));
}
/*
 * indirect, x addressing mode
 */
void idxcode(byte opcode)
{
	word operand;
	Token token;
	
	token = gettok(ppin);	/* '(' */
	
	token = gettok(ppin);
	sscanf(token.value, "%hx", &operand);
	token = gettok(ppin);	/* ',' */
	token = gettok(ppin);	/* 'x' */
	token = gettok(ppin);	/* ')' */
	putmem(2, opcode, operand);
}
/*
 * indirect, y addressing mode
 */
void idycode(byte opcode)
{
	word operand;
	Token token;
	
	token = gettok(ppin);	/* '(' */
	
	token = gettok(ppin);
	sscanf(token.value, "%hx", &operand);
	token = gettok(ppin);	/* ')' */
	token = gettok(ppin);	/* ',' */
	token = gettok(ppin);	/* 'y' */
	
	putmem(2, opcode, operand);
}
