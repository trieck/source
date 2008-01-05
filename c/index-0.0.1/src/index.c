/*
 * INDEX.C
 * 
 * Index content
 */

#include "global.h"
#include "index.h"
#include "lex.h"

static void cleanup(void);
static void parse(void);

FILE *fpin = NULL;

/* index content */
void mkindex(int nfiles, char **files)
{
	int i;
	atexit(cleanup);

	for (i = 0; i < nfiles; i++) {
		if ((fpin = fopen(files[i], "r")) == NULL) {
			error("unable to open file \"%s\".", files[i]);
		}
		parse();

		fclose(fpin);
		fpin = NULL;
	}
}

/* parse input stream */
void parse(void)
{
	const char *tok;
	while ((tok = gettok()) != NULL) {
		printf("%s\n", tok);
	}
}

/* perform at exit cleanup */
void cleanup(void)
{
	if (fpin != NULL) {
		fclose(fpin);
		fpin = NULL;
	}
}
