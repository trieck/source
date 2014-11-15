/*
 * 	SYMBOL.C
 *
 * 	Instruction Symbol Table
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
 */
#include "common.h"
#include "instr.h"
#include "symbol.h"
#define TBLSIZE 1103
static void freesymbol(PSYMBOL);
static unsigned hash (const char *key);
/*
 * allocate symbol table
 */
SymbolTable symalloc()
{
    SymbolTable table;
    table = (PSYMBOL *)malloc(sizeof(PSYMBOL) * TBLSIZE);
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
PSYMBOL opinsert(SymbolTable table, const char *name, const instr *instr)
{
    PSYMBOL ps;
    unsigned int index;

    ps = (Symbol *)malloc(sizeof(Symbol));
    index = hash(name);

    ps->name = strcopy(name);
    ps->instr = instr;

    ps->next = table[index];
    table[index] = ps;

    return ps;
}
/*
 * lookup entry in symbol table
 */
PSYMBOL lookup(SymbolTable table, const char *name)
{
    unsigned int index;
    PSYMBOL ps;
    index = hash(name);
    for (ps = table[index]; ps != NULL; ps = ps->next) {
        if (strcmp(ps->name, name) == 0)
            return ps;
    }
    return NULL;
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
unsigned int hash (const char * p)
{
    unsigned n = 0;
    while (*p) {
        n = (n << 1) ^ toupper(*p++);
    }
    n %= TBLSIZE;

    return n;
}
