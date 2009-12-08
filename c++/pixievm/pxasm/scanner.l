%{
#include "Common.h"
#include "Parser.hpp"
#include "SymbolTable.h"

#ifdef _MSC_VER
#include <io.h>
#endif /* _MSC_VER */

extern "C" int yywrap(void) { return 1; }

int lineno = 1;	/* current line number */

%}

comment			;.*
newline			[\n]
identifier		[a-zA-Z][a-zA-Z0-9_]*

%%
{comment}					;
{newline}					{ lineno++; }
{identifier}				{
	/*
	LPSYMBOL sym = table->lookup(yytext);
	if (sym == NULL) {
		throw Exception("unexpected token \"%s\".", yytext);
	}
	
	switch (sym->type) {
	case ST_REG:
	case ST_INSTRUCTION:
		yylval.sym = sym;
		return sym->sub;
	case ST_ID:
		yylval.n = sym->sub;
		return yylval.n;
	default:
		throw Exception("unsupported symbol \"%s\".", yytext);
	}
	*/
	
	return 0;
}
.							{ return yytext[0]; }
%%
