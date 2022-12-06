/*
 *	MAIN.C : A 6502 assembler
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
#include "assem.h"
#include "code.h"
#include "fixup.h"

static void init(void);
static void cleanup(void);
static void usage(void);

FixupTable fixups;  /* symbol table for resolving labels */
SymbolTable table;  /* symbol table of opcodes */
const char* infile; /* input file name */

/*
 * main entry point
 */
int main(int argc, char* argv[])
{
    if (argc < 2)
        usage();

    argv++;
    infile = argv[0];

    atexit(cleanup);

    /* initialize data structures */
    init();

    ///* assemble the input file */
    assemble();

    ///* write the generated program */
    write_code();

    return 0;
}

/*
 * initialize data structures
 */
void init(void)
{
    /* allocate and initialize the symbol table */
    table = symalloc();
    if (table == NULL) {
        error("unable to allocate hash table.\n");
    }

    syminit(table);
}

/*
 * tidy up
 */
void cleanup(void)
{
    extern FILE* yyin;

    /* free the symbol table */
    if (table != NULL) {
        symfree(table);
        table = NULL;
    }

    /* free the fixup table */
    if (fixups != NULL) {
        fixupfree(fixups);
        fixups = NULL;
    }

    /* close the input file */
    if (yyin != NULL) {
        fclose(yyin);
        yyin = NULL;
    }
}

/*
 * print usage
 */
void usage(void)
{
    fprintf(stderr, "usage: t6502 file\n");
    exit(1);
}
