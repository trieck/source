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
#include "btree.h"
#include "concord.h"
#include "inverter.h"

static void cleanup(void);
static void parse(void);

/*
 * current input file 
 */
static const char *infile;

/*
 * btree index 
 */
static BTree_t *tree;

/* Concordance file */
static Concord_t *concord;

/* inverter */
static Inverter_t *inverter;

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
	
	/* create inverter */
	inverter = inverter_create();

	/*
	 * open btree 
	 */
	/*if ((tree = btree_open("index.idx", OM_WRITE)) == NULL) {
		error("unable to open index.idx");
	}*/

	/* open concordance */
	/*if ((concord = concord_open("index.dat", OM_WRITE)) == NULL) {
		error("unable to open index.dat");
	}*/

	for (i = 0; i < nfiles; i++, filenum++) {
		infile = files[i];
		if ((fpin = fopen(files[i], "r")) == NULL) {
			error("unable to open file \"%s\".", files[i]);
		}
		parse();

		fclose(fpin);
		fpin = NULL;
	}
	
	/* free inverter */
	if (inverter != NULL) {
		inverter_free(inverter);
		inverter = NULL;
	}
	
	/* close concordance     */
	if (concord != NULL) {
		concord_close(concord);
		concord = NULL;
	}

	/*
	 * close btree 
	 */
	if (tree != NULL) {
		btree_close(tree);
		tree = NULL;
	}
}

/*
 * parse input stream 
 */
void parse(void)
{
	const char *tok;
	Item_t item;

	while ((tok = gettok()) != NULL) {
		item.key = doublehash(tok, strlen(tok));
		item.val = filenum+1;
		
		printf("%s:%d\n", tok, filenum);
		
		inverter_insert(inverter, tok, filenum);
		
		/* btree_put(tree, item); */
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
	
	/* free inverter */
	if (inverter != NULL) {
		inverter_free(inverter);
		inverter = NULL;
	}

	/* close concordance */
	if (concord != NULL) {
		concord_close(concord);
		concord = NULL;
	}

	/*
	 * close btree 
	 */
	if (tree != NULL) {
		btree_close(tree);
		tree = NULL;
	}
}
