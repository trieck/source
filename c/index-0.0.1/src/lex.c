/*
 * LEX.C
 *
 * Lexical analyzer
 * Copyright (c) 2008 Thomas A. Rieck
 */

#include "global.h"
#include "lex.h"

/*
 * input file pointer
 */
extern FILE *fpin;

/*
 * lexical buffer
 */
static char lexbuf[BSIZE];

/*
 * get next token from input
 */
const char *gettok(void)
{
	int c;
	for (;;) {
		c = fgetc(fpin);
		if (isalnum(c) || c == '_') {
			int b = 0;
			while (isalnum(c) || c == '_') {
				lexbuf[b++] = c;
				if (b >= BSIZE)
					error("lexical buffer overflow.");
				c = fgetc(fpin);
			}
			lexbuf[b] = '\0';
			return lexbuf;
		} else if (c == EOF) {
			return NULL;
		}
	}
}
