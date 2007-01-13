%{
#include <stdlib.h>
#include "symbol.h"
#include "tree.h"
#include "parser.h"
#include "temp.h"
#include "global.h"
#include "x.h"

#define YY_NO_UNPUT

int yywrap (void) { return 1; }

int lineno = 1;

/* current module name */
char *module_name;

%}
comment			#.*
decimal			\.
digit			[0-9]
whitespace		[\t\r ]+
eol				\n
identifier		[a-zA-Z][a-zA-Z0-9_]*
arrow			<-
range			\.\.

%%
{whitespace}	;
{comment}		;
{eol}			{ lineno++; }
{digit}+ |
{digit}*{decimal}{digit}+	{ yylval.sym = tinstallf(yytext, SCONST | SFLOAT, atof(yytext)); return NUMBER;  }
{identifier}	{ 
	PSYMBOL sym = glookup(yytext);
	if (sym == 0 && (sym = tlookup(yytext)) == 0) {
		yylval.sym = tinstallf(yytext, SUNDEF, 0);
		return ID;
	}

	switch (sym->type) {
	case SKEYWD:
		yylval.sym = sym;
		return KEYWORD;
	case SVAR:
		yylval.sym = sym;
		return ID;
	default:
		error("unknown symbol \"%s\" near line %d.", sym->name, lineno);
	}
}

{arrow}			{ return ARROW; }
{range}			{ return RANGE; }
.				{ return yytext[0]; }
%%
