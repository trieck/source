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
#include "symbol.h"
#include "parser.h"

/* Helper functions */
static void freesymbol(PSYMBOL);
static unsigned hash(const char*);

/*
 * allocate symbol table
 */
SymbolTable symalloc()
{
    SymbolTable table = malloc(sizeof(PSYMBOL) * TBLSIZE);
    memset(table, 0, sizeof(PSYMBOL) * TBLSIZE);
    return table;
}

/*
 * initialize symbol table
 */
void syminit(SymbolTable table)
{
    /* insert opcodes */
    opinsert(table, "adc", &adc, GRP1_OP);
    opinsert(table, "and", &and, GRP1_OP);
    opinsert(table, "asl", &asl, GRP2_OP);
    opinsert(table, "bcc", &bcc, GRP3_BRANCH_OP);
    opinsert(table, "bcs", &bcs, GRP3_BRANCH_OP);
    opinsert(table, "beq", &beq, GRP3_BRANCH_OP);
    opinsert(table, "bit", &bit, GRP3_OP);
    opinsert(table, "bmi", &bmi, GRP3_BRANCH_OP);
    opinsert(table, "bne", &bne, GRP3_BRANCH_OP);
    opinsert(table, "bpl", &bpl, GRP3_BRANCH_OP);
    opinsert(table, "brk", &Brk, GRP3_OP);
    opinsert(table, "bvc", &bvc, GRP3_OP);
    opinsert(table, "bvs", &bvs, GRP3_OP);
    opinsert(table, "clc", &clc, GRP3_OP);
    opinsert(table, "cld", &cld, GRP3_OP);
    opinsert(table, "cli", &cli, GRP3_OP);
    opinsert(table, "clv", &clv, GRP3_OP);
    opinsert(table, "cmp", &cmp, GRP1_OP);
    opinsert(table, "cpx", &cpx, GRP3_OP);
    opinsert(table, "cpy", &cpy, GRP3_OP);
    opinsert(table, "dec", &dec, GRP2_OP);
    opinsert(table, "dex", &dex, GRP2_OP);
    opinsert(table, "dey", &dey, GRP3_OP);
    opinsert(table, "eor", &eor, GRP1_OP);
    opinsert(table, "inc", &inc, GRP2_OP);
    opinsert(table, "inx", &inx, GRP3_OP);
    opinsert(table, "iny", &iny, GRP3_OP);
    opinsert(table, "jmp", &jmp, GRP3_OP);
    opinsert(table, "jsr", &jsr, GRP3_OP);
    opinsert(table, "lda", &lda, GRP1_OP);
    opinsert(table, "ldx", &ldx, GRP2_OP);
    opinsert(table, "ldy", &ldy, GRP3_OP);
    opinsert(table, "lsr", &lsr, GRP2_OP);
    opinsert(table, "nop", &nop, GRP3_OP);
    opinsert(table, "ora", &ora, GRP1_OP);
    opinsert(table, "pha", &pha, GRP3_OP);
    opinsert(table, "php", &php, GRP3_OP);
    opinsert(table, "pla", &pla, GRP3_OP);
    opinsert(table, "plp", &plp, GRP3_OP);
    opinsert(table, "rol", &rol, GRP2_OP);
    opinsert(table, "ror", &ror, GRP2_OP);
    opinsert(table, "rti", &rti, GRP3_OP);
    opinsert(table, "rts", &rts, GRP3_OP);
    opinsert(table, "sbc", &sbc, GRP1_OP);
    opinsert(table, "sec", &sec, GRP3_OP);
    opinsert(table, "sed", &sed, GRP3_OP);
    opinsert(table, "sei", &sei, GRP3_OP);
    opinsert(table, "sta", &sta, GRP1_OP);
    opinsert(table, "stx", &stx, GRP2_OP);
    opinsert(table, "sty", &sty, GRP3_OP);
    opinsert(table, "tax", &tax, GRP3_OP);
    opinsert(table, "tay", &tay, GRP3_OP);
    opinsert(table, "tsx", &tsx, GRP2_OP);
    opinsert(table, "txa", &txa, GRP3_OP);
    opinsert(table, "txs", &txs, GRP2_OP);
    opinsert(table, "tya", &tya, GRP3_OP);

    /* insert kernel jump table entries */
    wordinsert(table, "acptr", 0xffa5);
    wordinsert(table, "chkin", 0xffc6);
    wordinsert(table, "chrin", 0xffcf);
    wordinsert(table, "chrout", 0xffd2);
    wordinsert(table, "ciout", 0xffa8);
    wordinsert(table, "cint", 0xff81);
    wordinsert(table, "clall", 0xffe7);
    wordinsert(table, "close", 0xffc3);
    wordinsert(table, "clrchn", 0xffcc);
    wordinsert(table, "getin", 0xffe4);
    wordinsert(table, "iobase", 0xfff3);
    wordinsert(table, "ioinit", 0xff84);
    wordinsert(table, "listen", 0xffb1);
    wordinsert(table, "load", 0xffd5);
    wordinsert(table, "membot", 0xff9c);
    wordinsert(table, "memtop", 0xff99);
    wordinsert(table, "open", 0xffc0);
    wordinsert(table, "plot", 0xfff0);
    wordinsert(table, "ramtas", 0xff87);
    wordinsert(table, "rdtim", 0xffde);
    wordinsert(table, "readst", 0xff87);
    wordinsert(table, "restor", 0xff8a);
    wordinsert(table, "save", 0xffd8);
    wordinsert(table, "scnkey", 0xff9f);
    wordinsert(table, "screen", 0xffed);
    wordinsert(table, "second", 0xff93);
    wordinsert(table, "setlfs", 0xffba);
    wordinsert(table, "setmsg", 0xff90);
    wordinsert(table, "setnam", 0xffbd);
    wordinsert(table, "settim", 0xffdb);
    wordinsert(table, "settmo", 0xffa2);
    wordinsert(table, "stop", 0xffe1);
    wordinsert(table, "talk", 0xffb4);
    wordinsert(table, "tksa", 0xff96);
    wordinsert(table, "udtim", 0xffea);
    wordinsert(table, "unlsn", 0xffae);
    wordinsert(table, "untlk", 0xffab);
    wordinsert(table, "vector", 0xff8d);

    /* insert identifier entries */
    idinsert(table, ".byte", DECL_BYTE);
    idinsert(table, ".word", DECL_WORD);
    idinsert(table, ".text", DECL_TEXT);
    idinsert(table, ".ztext", DECL_ZTEXT);
}

/*
 * free symbol table
 */
void symfree(SymbolTable table)
{
    for (int i = 0; i < TBLSIZE; i++) {
        PSYMBOL ps = table[i];
        if (ps != NULL)
            freesymbol(ps);
    }
    free(table);
}

/*
 * insert identifier
 */
PSYMBOL idinsert(SymbolTable table, const char* name, int sub_type)
{
    PSYMBOL ps = malloc(sizeof(Symbol));
    memset(ps, 0, sizeof(Symbol));

    unsigned int index = hash(name);

    ps->name = strcopy(name);
    ps->type = SYM_ID;
    ps->sub_type = sub_type;

    ps->next = table[index];
    table[index] = ps;

    return ps;
}

/*
 * insert opcode
 */
PSYMBOL opinsert(SymbolTable table, const char* name, const Instr* instr, int sub_type)
{
    PSYMBOL ps = malloc(sizeof(Symbol));
    memset(ps, 0, sizeof(Symbol));

    unsigned int index = hash(name);

    ps->name = strcopy(name);
    ps->type = SYM_OPCODE;
    ps->sub_type = sub_type;
    ps->u.instr = instr;

    ps->next = table[index];
    table[index] = ps;

    return ps;
}

/*
 * insert word symbol
 */
PSYMBOL wordinsert(SymbolTable table, const char* name, word value)
{
    PSYMBOL ps = malloc(sizeof(Symbol));
    memset(ps, 0, sizeof(Symbol));

    unsigned int index = hash(name);

    ps->name = strcopy(name);
    ps->type = SYM_WORD;
    ps->u.word_value = value;

    ps->next = table[index];
    table[index] = ps;

    return ps;
}

/*
 * insert byte symbol
 */
PSYMBOL byteinsert(SymbolTable table, const char* name, byte value)
{
    PSYMBOL ps = malloc(sizeof(Symbol));
    memset(ps, 0, sizeof(Symbol));

    unsigned int index = hash(name);

    ps->name = strcopy(name);
    ps->type = SYM_BYTE;
    ps->u.byte_value = value;

    ps->next = table[index];
    table[index] = ps;

    return ps;
}

PSYMBOL fncinsert(SymbolTable table, const char* name, SymFnc fnc)
{
    PSYMBOL ps = malloc(sizeof(Symbol));
    memset(ps, 0, sizeof(Symbol));

    unsigned int index = hash(name);

    ps->name = strcopy(name);
    ps->type = SYM_FUNC;
    ps->u.fnc = fnc;

    ps->next = table[index];
    table[index] = ps;

    return ps;
}

word symevalword(SymbolTable table, const char* name)
{
    PSYMBOL sym = symlookup(table, name);
    if (sym == NULL) {
        error("symbol \"%s\" was not defined.\n", name);
    }

    if (sym->type == SYM_WORD) {
        return sym->u.word_value;
    }

    if (sym->type == SYM_FUNC) {
        return sym->u.fnc();
    }

    error("symbol \"%s\" cannot be evaluated in a word context.\n", name);

    return 0;
}

/*
 * lookup entry in symbol table
 */
PSYMBOL symlookup(SymbolTable table, const char* name)
{
    PSYMBOL ps;

    unsigned int index = hash(name);

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
unsigned int hash(const char* key)
{
    unsigned n = 0;
    while (*key) {
        n = n << 1 ^ toupper(*key++);
    }
    n %= TBLSIZE;

    return n;
}
