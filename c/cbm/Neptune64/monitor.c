/*
 * 	MONITOR.C
 *
 * 	Monitor definitions
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
#include "6510.h"
#include "monitor.h"
#include "assem.h"
#include "disassem.h"
#include "parser.h"
#include "mem.h"
#include "machine.h"

static void dump(void);
static void go(void);
static void help(void);
static void printregs(void);
static void process_input(void);
static void step(void);
static const char* pinput = NULL; /* pointer to current input */
extern int assemmode;             /* are we in assembly mode ? */
extern word assemc;               /* counter used during assembly */
static void monitor_dump(const word* start,
                         const word* end);
#define BUFFSIZE 256

/*
 * initialize the monitor
 */
void monitor_init(void)
{
    atexit(monitor_term);
    /* initialize the assembler */
    assem_init();
}

/*
 * reclaim monitor resources
 */
void monitor_term(void)
{
}

/*
 * run the monitor
 */
void monitor_run(void)
{
    char line[BUFFSIZE];

    for (;;) {
        pinput = line;
        if (assemmode) {
            printf("($%.4hx) ", assemc);
            fgets(line, BUFFSIZE, stdin);
            assemble_inmode(&pinput);
        } else {
            putchar('>');
            putchar(' ');
            fgets(line, BUFFSIZE, stdin);
            process_input();
        }
        fflush(stdout);
    }
}

/*
 * print the machine registers
 */
void printregs(void)
{
    char buffer[BUFFSIZE];
    char sr[9];
    byte io = fetch_byte(1);
    sr[0] = get_neg_flag() ? '1' : '0';
    sr[1] = get_overflow_flag() ? '1' : '0';
    sr[2] = '1'; /* unused */
    sr[3] = get_brk_flag() ? '1' : '0';
    sr[4] = get_dec_flag() ? '1' : '0';
    sr[5] = get_int_disable_flag() ? '1' : '0';
    sr[6] = get_zero_flag() ? '1' : '0';
    sr[7] = get_carry_flag() ? '1' : '0';
    sr[8] = '\0';
    sprintf(buffer,
            "%.4x %.2x %.2x %.2x %.2x %.2x %s",
            cpu.pc, cpu.a, cpu.x,
            cpu.y,
            cpu.sp, io, sr);

    printf("ADDR AC XR YR SP 01 NV-BDIZC\n%s\n", buffer);
}

/*
 * process the current input option
 */
void process_input(void)
{
    Token t = gettok(&pinput);

    if (strcmp(t.value, "?") == 0) {
        help();
    } else if (strcmp(t.value, "a") == 0) {
        assemble(&pinput);
    } else if (strcmp(t.value, "d") == 0) {
        disassemble(&pinput);
    } else if (strcmp(t.value, "g") == 0) {
        go();
    } else if (strcmp(t.value, "m") == 0) {
        dump();
    } else if (strcmp(t.value, "r") == 0) {
        printregs();
    } else if (strcmp(t.value, "s") == 0) {
        step();
    } else if (strcmp(t.value, "x") == 0) {
        exit(0);
    } else if (strcmp(t.value, "z") == 0) {
        cpu_run();
    } else if (t.type == UNDEF) {
    } else {
        warning("unknown option specified.\n");
    }
}

/*
 * step the monitor
 */
void step(void)
{
    word addr;
    const word* paddr = NULL;
    Token tok = gettok(&pinput);
    if (NUM == tok.type) {
        sscanf(tok.value, "%hx", &addr);
        paddr = &addr;
    }
    machine_step(paddr);
}

/*
 * execute the machine
 */
void go(void)
{
    const char* usage = "usage: g address\n";
    word addr;

    Token tok = gettok(&pinput);
    if (NUM != tok.type) {
        warning(usage);
        return;
    }

    sscanf(tok.value, "%hx", &addr);
    machine_go(addr);
}

/*
 * dump memory
 */
void dump(void)
{
    word starta, enda;
    word* pstart = NULL,* pend = NULL;
    const char*usage = "usage: m [start] [end]\n";

    Token start = gettok(&pinput);
    Token end = gettok(&pinput);

    if (UNDEF != start.type && NUM != start.type) {
        warning(usage);
        return;
    }
    if (UNDEF != end.type && NUM != end.type) {
        warning(usage);
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
    monitor_dump(pstart, pend);
}

/*
 * dump memory
 */
void monitor_dump(const word* start,
                  const word* end)
{
    /*
     * this is a hack; rewrite this
     */
    int i = 0, j;
    const int LINESIZE = 16;
    const int LINES = 9;
    static word pc;
    static int initialized;

    if (!initialized) {
        pc = cpu.pc;
        initialized = 1;
    }

    if (NULL != start)
        pc = *start;
    do {
        printf("$%.4x\t", pc);

        for (j = 0; j < LINESIZE; j++) {
            byte b = fetch_byte((word)(pc + j));
            printf("%.2x", b);
            if (end && (word)(pc + j) == *end)
                break;
            if (j != LINESIZE - 1)
                putchar(' ');
        }

        do {
            putchar(' ');
            putchar(' ');
            putchar(' ');
        } while (++j < LINESIZE);

        for (j = 0; j < LINESIZE; j++) {
            byte b = fetch_byte((word)(pc + j));
            if (isprint(b))
                putchar(b);
            else
                putchar('.');
            if (end && (word)(pc + j) == *end)
                break;
        }

        putchar('\n');
        pc += j;

    } while (NULL == end ? ++i < LINES : pc != *end);
}

/*
 * command help
 */
void help(void)
{
    printf("a   assemble\td   disassemble\n"
        "g   go\t\tm   memory\n"
        "r   registers\ts   step\n"
        "x   exit\tz   run the cpu\n"
        "?   help\n");
}
