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
#include "fixup.h"
#include "symbol.h"
#include "petscii.h"

#define MEMSIZE	65536

extern int yyerror(const char* s);
static void putmem(int ncount, ...);

static word base_address = -1;
static byte memory[MEMSIZE];
static byte* pmem = memory;

extern SymbolTable table;  /* symbol table of kernel entries / opcodes */
extern FixupTable fixups;  /* symbol table of fixups */
extern const char* infile; /* input file name */
extern int yylineno;       /* current line number */

void putmem(int ncount, ...)
{
    if (base_address == (word)-1) {
        error("base address must be specified.\n");
    }

    va_list arglist;
    va_start(arglist, ncount);
    while (ncount--) {
        byte value = va_arg(arglist, byte);
        *pmem++ = value;
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
    strcpy(++pout, "prg");

    FILE* fpout = fopen(outfile, "wb");
    if (fpout == NULL) {
        error("unable to open output file %s.\n", outfile);
    }

    /* write base address */
    fwrite(&base_address, sizeof(word), 1, fpout);

    /* write code */
    const byte* pmemory = memory;
    for (; pmemory < pmem; pmemory++) {
        fputc(*pmemory, fpout);
    }

    fclose(fpout);
}

void resolve_fixups(void)
{
    fixup* fixup = fixups;
    while (fixup != NULL) {
        PSYMBOL sym = symlookup(table, fixup->name);
        if (sym == NULL) {
            error("label \"%s\" was not defined near line %d.\n",
                fixup->name, fixup->lineno);
        }

        word symvalue = symevalword(table, fixup->name);

        word offset = fixup->mem - base_address;

        switch (fixup->type) {
        case FIXUP_REG:
            memory[offset] = lobyte(symvalue);
            memory[offset + 1] = hibyte(symvalue);
            break;
        case FIXUP_BRANCH:
            /* relative branch fix up*/
            size_t soffset = symvalue - base_address;
            int branch = (int)(soffset - offset - 1);
            if (branch > 127 || branch < -128) {
                error("label \"%s\" branch out of range near line %d.\n",
                    fixup->name, fixup->lineno);
            }

            memory[offset] = (byte)branch;
            break;
        case FIXUP_LO:
            /* lo-byte fix-up */
            memory[offset] = lobyte(symvalue);
            break;
        case FIXUP_HI:
            /* hi-byte fix-up */
            memory[offset] = hibyte(symvalue);
            break;
        default:
            error("unknown fixup type.");
            break;
        }

        fixup = fixup->next;
    }
}

word getmem(void)
{
    word offset = (word)(pmem - &memory[0]);

    word address = base_address + offset;

    return address;
}

void defbase(word address)
{
    if (base_address != (word)- 1) {
        error("cannot redefine base address near line %d.\n", yylineno);
    }

    base_address = address;

    fncinsert(table, "*", getmem);
}

void deflabel(const char* name)
{
    if (base_address == (word)-1) {
        error("base address must be specified near line %d.\n", yylineno);
    }

    wordinsert(table, name, getmem());
}

void byte_code(byte value)
{
    putmem(1, value);
}

void decl_hibyte_fixup(const char* name)
{
    fixupinsert(&fixups, name, getmem(), FIXUP_HI);
}

void decl_lobyte_fixup(const char* name)
{
    fixupinsert(&fixups, name, getmem(), FIXUP_LO);
}

void declword_fixup(const char* name)
{
    fixupinsert(&fixups, name, getmem(), FIXUP_REG);
}

void word_code(word value)
{
    putmem(2, lobyte(value), hibyte(value));
}

void text_code(const char* value)
{
    while (*value) {
        byte p = ascii2petscii(*value++);
        putmem(1, p);
    }
}

void ztext_code(const char* value)
{
    text_code(value);
    putmem(1, 0);
}

void imp_acc_code(const Instr* instr)
{
    const byte* opcode = (*instr)[IMP];
    if (opcode == NULL) {
        opcode = (*instr)[ACC]; // try accumulator mode
    }

    if (opcode == NULL) {
        error("instruction does not support addressing mode near line %d.\n", yylineno);
    }

    putmem(1, *opcode);
}

void imm_code(const Instr* instr, byte operand)
{
    const byte* opcode = (*instr)[IMM];
    if (opcode == NULL) {
        error("instruction does not support immediate addressing near line %d.\n", yylineno);
    }

    putmem(2, *opcode, operand);
}

void zp_code(const Instr* instr, byte operand)
{
    const byte* opcode = (*instr)[ZPG];
    if (opcode == NULL) {
        error("instruction does not support zero-page addressing near line %d.\n", yylineno);
    }

    putmem(2, *opcode, operand);
}

void zpx_code(const Instr* instr, byte operand)
{
    const byte* opcode = (*instr)[ZPX];
    if (opcode == NULL) {
        error("instruction does not support zero-page, x addressing near line %d.\n", yylineno);
    }

    putmem(2, *opcode, operand);
}

void zpy_code(const Instr* instr, byte operand)
{
    const byte* opcode = (*instr)[ZPY];
    if (opcode == NULL) {
        error("instruction does not support zero-page, y addressing near line %d.\n", yylineno);
    }

    putmem(2, *opcode, operand);
}

void abs_code(const Instr* instr, word operand)
{
    const byte* opcode = (*instr)[ABS];
    if (opcode == NULL) {
        error("instruction does not support absolute addressing near line %d.\n", yylineno);
    }

    putmem(3, *opcode, lobyte(operand), hibyte(operand));
}

void rel_code(const Instr* instr, word operand)
{
    const byte* opcode = (*instr)[REL];
    if (opcode == NULL) {
        error("instruction does not support relative addressing near line %d.\n", yylineno);
    }

    if (operand == 0) {
        putmem(2, *opcode, 0);
    } else {
        int offset = operand - (getmem() + 2);
        if (offset > 127 || offset < -128) {
            error("relative branch out of range near line %d.\n", yylineno);
        }

        putmem(2, *opcode, offset);
    }
}

void abx_code(const Instr* instr, word operand)
{
    const byte* opcode = (*instr)[ABX];
    if (opcode == NULL) {
        error("instruction does not support absolute, x addressing near line %d.\n", yylineno);
    }

    putmem(3, *opcode, lobyte(operand), hibyte(operand));
}

void aby_code(const Instr* instr, word operand)
{
    const byte* opcode = (*instr)[ABY];
    if (opcode == NULL) {
        error("instruction does not support absolute, y addressing near line %d.\n", yylineno);
    }

    putmem(3, *opcode, lobyte(operand), hibyte(operand));
}

void branch_fixup(const char* name)
{
    // an operator fix-up is one byte past the operator
    fixupinsert(&fixups, name, getmem() + 1, FIXUP_BRANCH);
}

void idx_code(const Instr* instr, byte operand)
{
    const byte* opcode = (*instr)[IDX];
    if (opcode == NULL) {
        error("instruction does not support indexed-indirect addressing near line %d.\n", yylineno);
    }

    putmem(2, *opcode, operand);
}

void idy_code(const Instr* instr, byte operand)
{
    const byte* opcode = (*instr)[IDY];
    if (opcode == NULL) {
        error("instruction does not support indirect-indexed addressing near line %d.\n", yylineno);
    }

    putmem(2, *opcode, operand);
}

void ind_code(const Instr* instr, word operand)
{
    const byte* opcode = (*instr)[IND];
    if (opcode == NULL) {
        error("instruction does not support indirect addressing near line %d.\n", yylineno);
    }

    putmem(3, *opcode, lobyte(operand), hibyte(operand));
}

void op_fixup(const char* name)
{
    // an operator fix-up is one byte past the operator
    fixupinsert(&fixups, name, getmem() + 1, FIXUP_REG);
}

void op_lobyte_fixup(const char* name)
{
    // an operator fix-up is one byte past the operator
    fixupinsert(&fixups, name, getmem() + 1, FIXUP_LO);
}

void op_hibyte_fixup(const char* name)
{
    // an operator fix-up is one byte past the operator
    fixupinsert(&fixups, name, getmem() + 1, FIXUP_HI);
}
