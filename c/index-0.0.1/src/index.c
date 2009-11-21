/*
 * INDEX.C
 *
 * Index content
 * Copyright (c) 2008 Thomas A. Rieck
 */

#include "global.h"
#include "index.h"
#include "lex.h"
#include "blockio.h"
#include "concord.h"

static void cleanup(void);
static void parse(void);

/*
 * current input file
 */
static const char *infile;

/* Concordance file */
static Concord_t *concord;

/* current file number */
static uint32_t filenum;

/*
 * current input file ptr
 */
FILE *fpin = NULL;

/*
 * index content
 */
void mkindex(int nfiles, char **files)
{
	int i;

	atexit(cleanup);

	/* open concordance */
	/*if ((concord = concord_open("index.dat", OM_WRITE)) == NULL) {
	   error("unable to open index.dat");
	   } */

	for (i = 0; i < nfiles; i++, filenum++) {
		infile = files[i];
		if ((fpin = fopen(files[i], "r")) == NULL) {
			error("unable to open file \"%s\".", files[i]);
		}
		parse();

		fclose(fpin);
		fpin = NULL;
	}

	/* close concordance     */
	if (concord != NULL) {
		concord_close(concord);
		concord = NULL;
	}
}

/*
 * parse input stream
 */
void parse(void)
{
	const char *tok;
	while ((tok = gettok()) != NULL) {
		concord_insert(concord, tok, filenum);
	}
}

/*
 * perform at exit cleanup
 */
void cleanup(void)
{
	/*
	 * close current input file
	 */
	if (fpin != NULL) {
		fclose(fpin);
		fpin = NULL;
	}

	/* close concordance */
	if (concord != NULL) {
		concord_close(concord);
		concord = NULL;
	}
}
