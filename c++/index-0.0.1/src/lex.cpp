/////////////////////////////////////////////////////////////////////////////
//
// LEX.CPP : Lexical Analyzer
//
// Copyright (c) 2008 Thomas A. Rieck, All Rights Reserved
//

#include "global.h"
#include "lex.h"

/////////////////////////////////////////////////////////////////////////////
Lex::Lex()
	: fp(NULL)
{
}

/////////////////////////////////////////////////////////////////////////////
Lex::~Lex()
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
void Lex::close()
{
	if (fp != NULL) {
		fclose(fp);
		fp = NULL;
	};
}

/////////////////////////////////////////////////////////////////////////////
bool Lex::open(const char *filename)
{
	close();
	return ((fp = fopen(filename, "r")) != NULL);
}

/////////////////////////////////////////////////////////////////////////////
const char *Lex::gettok(void)
{
	int c;
	for (;;) {
		c = fgetc(fp);
		if (isalnum(c) || c == '_') {
			int b = 0;
			while (isalnum(c) || c == '_') {
				buf[b++] = tolower(c);
				if (b >= PATH_MAX)
					error("lexical buffer overflow.");
				c = fgetc(fp);
			}

			buf[b] = '\0';

			return buf;
		} else if (c == EOF) {
			return NULL;
		}
	}
}
