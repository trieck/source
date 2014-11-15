/*
 *	DISASSEM.C
 *
 *	code disassembly
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
#include "mem.h"
#include "opcodes.h"
#include "disassem.h"
#include "parser.h"
#include <limits.h>
static void instruction(const Instr *p);
static void immediate(const Instr *p);
static void zeropage(const Instr *p);
static void zeropgx(const Instr *p);
static void zeropgy(const Instr *p);
static void absolute(const Instr *p);
static void abslx(const Instr *p);
static void absly(const Instr *p);
static void relative(const Instr *p);
static void indirect(const Instr *p);
static void indrctx(const Instr *p);
static void indrcty(const Instr *p);
static void accumulator(const Instr *p);
static void implied(const Instr *p);
static void printpc(void);
static void disassemble_machine(const word *pstart,
                                const word *pend);
#define getbyte() fetch_byte(pc++)
#define getword() (fetch_byte(pc++) + fetch_byte(pc++) * 256)
#define LINES 23
static word pc = 0; /* program counter used during disassembly */
/*
 * disassemble
 */
void disassemble(const char **ppin)
{
    word starta, enda;
    word *pstart = 0, *pend = 0;
    const char *dusage = "usage: d [start] [end]\n";
    Token start = gettok(ppin);
    Token end = gettok(ppin);
    if (UNDEF != start.type && NUM != start.type) {
        warning(dusage);
        return;
    }
    if (UNDEF != end.type && NUM != end.type) {
        warning(dusage);
        return;
    }
    if (NUM == start.type) {
        sscanf(start.value, "%hx", &starta);
        pstart = &starta;
    }
    if (NUM == end.type) {
        sscanf(end.value, "%hx", &enda);
        pend = &enda;
    }
    disassemble_machine(pstart, pend);
}
/*
 * disassemble a single instruction
 */
void disassemble_instr(const word addr)
{
    byte N;
    const Instr *p;
    pc = addr;
    printpc();
    N = getbyte();
    p = instructions[N];
    printf("%.2x", N);
    instruction(p);
    printf("\n");
}
/*
 * disassemble machine
 */
void disassemble_machine(const word *start,
                         const word *end)
{
    byte N;
    const Instr *p;
    int i = 0, roll;
    if (NULL != start)
        pc = *start;
    do {
        roll = (pc == USHRT_MAX);
        printpc();
        N = getbyte();
        p = instructions[N];
        printf("%.2x", N);
        instruction(p);
        printf("\n");
    } while (!roll && (NULL == end ? ++i < LINES : pc <= *end));
}
/*
 * display program counter
 */
void printpc(void)
{
    printf("$%.4x\t", pc);
}
/*
 * disassemble an instruction
 */
void instruction (const Instr *p)
{
    if (NULL == p) {
        printf("\t\t???");
        return;
    }

    switch (p->mode) {
    case acc:
        accumulator(p);
        break;
    case imm:
        immediate(p);
        break;
    case zpg:
        zeropage(p);
        break;
    case zpx:
        zeropgx(p);
        break;
    case zpy:
        zeropgy(p);
        break;
    case absl:
        absolute(p);
        break;
    case abx:
        abslx(p);
        break;
    case aby:
        absly(p);
        break;
    case imp:
        implied(p);
        break;
    case rel:
        relative(p);
        break;
    case ind:
        indirect(p);
        break;
    case idx:
        indrctx(p);
        break;
    case idy:
        indrcty(p);
        break;
    default:
        warning("unrecognized addressing mode: %d\n", p->mode);
        break;
    };
}
/*
 * immediate mode instruction
 */
void immediate(const Instr *p)
{
    byte b = getbyte();
    printf(" %.2x\t\t%s\t#%.2x", b, *p->name, b);
}
/*
 * zero page instruction
 */
void zeropage (const Instr *p)
{
    byte b = getbyte();
    printf(" %.2x\t\t%s\t$%.2x", b, *p->name, b);
}
/*
 * zero page, x instruction
 */
void zeropgx(const Instr *p)
{
    byte b = getbyte();
    printf(" %.2x\t\t%s\t$%.2x, x", b, *p->name, b);
}
/*
 * zero page, y instruction
 */
void zeropgy(const Instr *p)
{
    byte b = getbyte();
    printf(" %.2x\t\t%s\t$%.2x, y", b, *p->name, b);
}
/*
 * absolute instruction
 */
void absolute(const Instr *p)
{
    word A = getword();
    printf(" %.2x %.2x\t%s\t$%.4hx",
           lobyte(A), hibyte(A), *p->name, A);
}
/*
 * absolute, x instruction
 */
void abslx(const Instr *p)
{
    word A = getword();
    printf(" %.2x %.2x\t%s\t$%.4hx, x",
           lobyte(A), hibyte(A), *p->name, A);
}
/*
 * absolute, y instruction
 */
void absly(const Instr *p)
{
    word A = getword();
    printf(" %.2x %.2x\t%s\t$%.4hx, y",
           lobyte(A), hibyte(A), *p->name, A);
}
/*
 * relative instruction
 */
void relative(const Instr *p)
{
    /*
     * we must convert the relative address
     * to an absolute address for disassembly
     */
    byte b = getbyte();
    word A;

    if (b < 0x80)
        A = (word)(pc + b);
    else A = (word)(pc - (0x100 - b));
    printf(" %.2x \t\t%s\t$%.4hx",
           b, *p->name, A);
}
/*
 * indirect instruction
 */
void indirect(const Instr *p)
{
    word A = getword();
    printf(" %.2x %.2x\t%s\t($%.4hx)",
           lobyte(A), hibyte(A), *p->name, A);
}
/*
 * indirect, x instruction
 */
void indrctx(const Instr *p)
{
    byte b = getbyte();
    printf(" %.2x\t\t%s\t($%.2x, x)", b, *p->name, b);
}
/*
 * indirect, y instruction
 */
void indrcty(const Instr *p)
{
    byte b = getbyte();
    printf(" %.2x\t\t%s\t($%.2x), y", b, *p->name, b);
}
/*
 * accumulator instruction
 */
void accumulator(const Instr *p)
{
    printf("\t\t%s", *p->name);
}
/*
 * implied instruction
 */
void implied(const Instr *p)
{
    printf("\t\t%s", *p->name);
}
