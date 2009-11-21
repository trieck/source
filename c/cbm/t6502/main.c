/*
 * MAIN.C
 *
 * a very teeny-tiny 6502 assembler
 *
 */
#include "common.h"
#include "opcodes.h"
#include "symbol.h"
#include "label.h"
#include "extern.h"
#include "assem.h"
#include "code.h"
static void init(void);
static void cleanup(void);
static void usage(void);
LabelTable labels;				/* symbol table for resolving labels */
SymbolTable table;				/* symbol table of opcodes */
const char *infile;				/* input file name */
const char *log_file_name = NULL;	/* stderr */
/*
 * main entry point
 */
int main(int argc, char *argv[])
{
	if (argc < 2)
		usage();
	argc--;
	argv++;
	infile = argv[0];

	atexit(cleanup);
	/* initialize data structures */
	init();
	/* assemble the input file */
	assemble();
	/* write the generated program */
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
	if (table == NULL)
		error("unable to allocate hash table.\n");
	syminit(table);

	/* initialize the external list */
	extern_init();
}

/*
 * tidy up
 */
void cleanup(void)
{
	extern FILE *fpin;
	/* free the symbol table */
	if (table != NULL) {
		symfree(table);
		table = NULL;
	}
	/* free the label table */
	if (labels != NULL) {
		labelfree(labels);
		labels = NULL;
	}

	/* free the external list */
	extern_free();
	/* close the input file */
	if (fpin != NULL) {
		fclose(fpin);
		fpin = NULL;
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
