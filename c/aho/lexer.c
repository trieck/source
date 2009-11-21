/**** lexer.c ***************************************************************/

#include "global.h"

char lexbuf[BSIZE];
int lineno = 1;
int tokenval = NONE;

extern int lookup(char s[]);
extern int insert(char s[], int tok);

int lexan()		/* lexical analyzer */
{
	int t;
	while (1) {
		t = getchar();
		if (t == ' ' || t == '\t')
			;	/* strip out white space */
		else if (t == '\n')
			lineno = lineno + 1;
		else if (isdigit(t)) {	/* t is a digit */
			ungetc(t, stdin);
			scanf("%d", &tokenval);
			return NUM;
		} else if (isalpha(t)) {		/* t is a letter */
			int p, b = 0;
			while (isalnum(t)) {	/* t is alphanumeric */
				lexbuf[b] = t;
				t = getchar();
				b = b + 1;
				if (b >= BSIZE)
					error("compiler error");
			}
			lexbuf[b] = EOS;
			if (t != EOF)
				ungetc(t, stdin);
			p = lookup(lexbuf);
			if (p == 0)
				p = insert(lexbuf, ID);
			tokenval = p;
			return symtable[p].token;
		} else if (t == EOF)
			return DONE;
		else {
			tokenval = NONE;
			return t;
		}
	}
}
