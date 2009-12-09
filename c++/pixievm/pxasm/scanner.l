%{
#include "Common.h"
#include "SymbolTable.h"
#include "Parser.hpp"
#include "Exception.h"

#ifdef _MSC_VER
#include <io.h>
#endif /* _MSC_VER */

extern "C" int yywrap(void) { return 1; }

int lineno = 1;	/* current line number */
SymbolTable *table = SymbolTable::getInstance();

%}

comment			;.*
newline			[\n]
hexnum			\$[a-fA-F0-9]+
identifier		[a-zA-Z][a-zA-Z0-9_]*
whitespace		[\t\r ]+
colon			:

%%
{whitespace}	;
{comment}		;
{colon}			{ return COLON; }
{hexnum}		{
	word d;	
	if (!sscanf(&yytext[1], "%hx", &d)) {
		throw Exception("invalid hex number \"%s\".", yytext);
	}		
	if (d < 0x100) {
		yylval.sym = table->installw(yytext, ST_CONST, IM8, d); 
		return IM8;
	} else {
		yylval.sym = table->installw(yytext, ST_CONST, IM16, d); 
		return IM16;
	}
}
{newline}					{ lineno++; }
{identifier}				{
	LPSYMBOL sym;
	if ((sym = table->lookup(yytext)) == NULL) {
		/*yylval.sym = table->idinsert(yytext, 0);*/
		return ID;
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
	
	return 0;
}
.							{ return yytext[0]; }
%%
