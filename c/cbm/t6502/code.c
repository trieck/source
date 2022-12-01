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

#define MEMSIZE	65536

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
static word get_address(label_type type, int offset);

static word base_address = -1;
static byte memory[MEMSIZE];
static byte* pmem = memory;

extern SymbolTable table;  /* symbol table of kernel entries / opcodes */
extern LabelTable labels;  /* symbol table of labels */
extern Token token;        /* current token */
extern const char* pinput; /* pointer to current input */
extern const char* infile; /* input file name */
extern int lineno;         /* current line number */

void putmem(int ncount, ...)
{
    if (base_address == (word)-1) {
        error("base address must be specified.\n");
    }

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
    char outfile[_MAX_PATH];
    strcpy(outfile, infile);

    char* pout = strrchr(outfile, '.');
    strcpy(++pout, "o");

    FILE* fpout = fopen(outfile, "wb");
    if (fpout == NULL)
        error("unable to open output file %s.\n", outfile);

    /* write base address */
    fwrite(&base_address, sizeof(word), 1, fpout);

    /* write code */
    const byte* pmemory = memory;
    for (; pmemory < pmem; pmemory++) {
        fputc(*pmemory, fpout);
    }

    fclose(fpout);
}

/*
 * set base address for assembly
 */
void set_base(word base)
{
    base_address = base;
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
    token = gettok(&pinput); /* '#' */
    
    byte operand = get_byte(1);

    putmem(2, opcode, operand);
}

void zpgcode(byte opcode)
{
    byte operand = get_byte(1);

    putmem(2, opcode, operand);
}

void zpxcode(byte opcode)
{
    byte operand = get_byte(1);

    token = gettok(&pinput); /* ',' */
    token = gettok(&pinput); /* 'x' */

    putmem(2, opcode, operand);
}

void zpycode(byte opcode)
{
    byte operand = get_byte(1);

    token = gettok(&pinput); /* ',' */
    token = gettok(&pinput); /* 'y' */

    putmem(2, opcode, operand);
}

void abscode(byte opcode)
{
    word operand = get_address(REG, 1);
    
    putmem(3, opcode, lobyte(operand), hibyte(operand));
}

void abxcode(byte opcode)
{
    word operand = get_address(REG, 1);

    token = gettok(&pinput); /* ',' */
    token = gettok(&pinput); /* 'x' */

    putmem(3, opcode, lobyte(operand), hibyte(operand));
}

void abycode(byte opcode)
{
    word operand = get_address(REG, 1);

    token = gettok(&pinput); /* ',' */
    token = gettok(&pinput); /* 'y' */

    putmem(3, opcode, lobyte(operand), hibyte(operand));
}

void indcode(byte opcode)
{
    gettok(&pinput); /* '(' */

    word operand = get_address(REG, 1);

    gettok(&pinput); /* ')' */

    putmem(3, opcode, lobyte(operand), hibyte(operand));
}

void impcode(byte opcode)
{
    putmem(1, opcode);
}

void relcode(byte opcode)
{
    word operand = get_address(REL, 1);

    putmem(2, opcode, operand - (getmem() + 2));
}

void idxcode(byte opcode)
{
    token = gettok(&pinput); /* '(' */

    byte operand = get_byte(1);

    token = gettok(&pinput); /* ',' */
    token = gettok(&pinput); /* 'x' */
    token = gettok(&pinput); /* ')' */

    putmem(2, opcode, operand);
}

void idycode(byte opcode)
{
    token = gettok(&pinput); /* '(' */

    byte operand = get_byte(1);

    token = gettok(&pinput); /* ')' */
    token = gettok(&pinput); /* ',' */
    token = gettok(&pinput); /* 'y' */

    putmem(2, opcode, operand);
}

void resolve(void)
{
    label* label = labels;
    while (label != NULL) {
        Symbol* psym = symlookup(table, label->name);
        if (psym == NULL) {
            error("label \"%s\" was not defined.\n", label->name);
        }

        if (label->type == REL) {    /* relative branch fix up*/
            size_t loffset = label->mem - memory;
            size_t soffset = psym->u.mem - base_address;
            byte branch = (byte)(soffset - loffset - 1);
            memory[label->mem - memory] = branch;
        } else if (label->type == LO) { /* lo-byte fix-up */
            memory[label->mem - memory] = lobyte(psym->u.mem);
        } else if (label->type == HI) { /* hi-byte fix-up */
            memory[label->mem - memory] = hibyte(psym->u.mem);
        } else if (label->type == REG) { /* regular */
            memory[label->mem - memory] = lobyte(psym->u.mem);
            memory[label->mem - memory + 1] = hibyte(psym->u.mem);
        }
        label = label->next;
    }
}

word getmem(void)
{
    word offset = (word)(pmem - &memory[0]);

    word address = base_address + offset;

    return address;
}

byte get_byte(int offset)
{
    byte b = 0;

    token = gettok(&pinput);
    if (token.type == NUM) {
        int rc = sscanf(token.value, "%hhx", &b);
        if (rc == 0 || rc == EOF) {
            error("unexpected token \"%s\""
                " found at line %d.\n", token.value, lineno);
        }
    } else if (token.type == LT) {
        word address = get_address(LO, offset);
        b = lobyte(address);
    } else if (token.type == GT) {
        word address = get_address(HI, offset);
        b = hibyte(address);
    } else {
        error("unexpected token \"%s\""
            " found at line %d.\n", token.value, lineno);
    }

    return b;
}

word get_address(label_type type, int offset)
{
    word address = 0;

    token = gettok(&pinput);
    if (token.type == STR) {
        PSYMBOL psym = symlookup(table, token.value);
        if (psym != NULL) {
            address = psym->u.mem;
        } else { // assume an as-of-yet undefined label
            labelinsert(&labels, token.value, pmem + offset, type);
        }
    } else if (token.type == NUM) {
        int rc = sscanf(token.value, "%hx", &address);
        if (rc == 0 || rc == EOF) {
            error("unexpected token \"%s\""
                " found at line %d.\n", token.value, lineno);
        }
    } else {
        error("unexpected token \"%s\""
            " found at line %d.\n", token.value, lineno);
    }

    return address;
}
