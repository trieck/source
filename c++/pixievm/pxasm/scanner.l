%option yylineno

%{
#include "Common.h"
#include "SymbolTable.h"
#include "Parser.hpp"
#include "Exception.h"

#ifdef _MSC_VER
#include <io.h>
#endif /* _MSC_VER */

extern "C" int yywrap(void) { return 1; }
char backslash(const char **pp)
{
	static char transtab[] = "b\bf\fn\nr\rt\t";
	char c;

	if (**pp != '\\')
		return **pp;
	c = *++(*pp);
	if (c == '\0')
		return *--(*pp);
	if (strchr(transtab, c))
		return strchr(transtab, c)[1];
	return c;
}

SymbolTable *table = SymbolTable::getInstance();

%}

comment			;.*
newline			[\n]
hexnum			\$[a-fA-F0-9]+
identifier		[a-zA-Z][a-zA-Z0-9_]*
whitespace		[\t\r ]+
colon			:
quotedstr		\"[^"\n]+\"
pseudo_op		\.[a-zA-Z][a-zA-Z0-9_]*

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
		yylval.sym = table->installb(yytext, ST_CONST, IM8, (byte)d); 
		return IM8;
	} else {
		yylval.sym = table->installw(yytext, ST_CONST, IM16, d); 
		return IM16;
	}
}
{newline}					;
{identifier}				{
	LPSYMBOL sym;
	if ((sym = table->lookup(yytext)) == NULL) {
		yylval.sym = table->install(yytext);
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
{pseudo_op}					{ 
	LPSYMBOL sym;
	if ((sym = table->lookup(yytext)) == NULL) {
		throw Exception("unrecognized pseudo-op \"%s\" near line %d",
			yytext, yylineno);
	}
	
	return sym->sub;
 }

{quotedstr}					{
	const char *ptext = yytext+1;	// eat '"' 
	string str;

	for ( ; *ptext != '"'; ptext++) {
		if (ptext[0] == '\0' || ptext[0] == '\n') {			
			throw Exception("unterminated string literal near line %d.", yylineno);
		}
		
		str += backslash(&ptext);
	}

	yylval.sym = table->installs(str);
	
	return STRING;
}
.							{ return yytext[0]; }
%%
