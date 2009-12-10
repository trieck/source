%option yylineno

%{
#include "Common.h"
#include "SymbolTable.h"
#include "Parser.hpp"
#include "Exception.h"
#include "Util.h"

#ifdef _MSC_VER
#include <io.h>
#endif	// _MSC_VER 

extern "C" int yywrap(void) { return 1; }
extern int yyerror(const char *s);

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
offset-reg		[a-zA-Z]+[\r\t ]*\+[\r\t ]*[xX]

%%
{whitespace}	;
{comment}		;
{colon}			{ return COLON; }
{hexnum}		{
	string error;
	word d;		
	if (!sscanf(&yytext[1], "%hx", &d)) {
		yyerror("invalid hex number");
	}		
	if (d < 0x100) {
		yylval.sym = table->installb(yytext, ST_CONST, IM8, (byte)d); 
		return IM8;
	} else {
		yylval.sym = table->installw(yytext, ST_CONST, IM16, d); 
		return IM16;
	}
}
{offset-reg}						{
	string error;
	string reg = trim(string(yytext, strchr(yytext, '+') - yytext));
	LPSYMBOL sym;
	if ((sym = table->lookup(reg)) == NULL) {
		yyerror("unexpected token");
	}
	if (sym->type != ST_REG) {
		yyerror("unsupported symbol");
	}

	// encode offset bit in register
	yylval.sym = table->installb(yytext, sym->type, sym->sub, sym->val8 | 0x08);
	return RX16;
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
		yyerror("unsupported symbol");
	}
	
	return 0;
}
{pseudo_op}					{ 
	LPSYMBOL sym;
	if ((sym = table->lookup(yytext)) == NULL) {
		yyerror("unrecognized pseudo-op");
	}
	
	return sym->sub;
 }

{quotedstr}					{
	const char *ptext = yytext+1;	// eat '"' 
	string str;

	for ( ; *ptext != '"'; ptext++) {
		if (ptext[0] == '\0' || ptext[0] == '\n') {
			yyerror("unterminated string literal");
		}
		
		str += backslash(&ptext);
	}

	yylval.sym = table->installs(str);
	
	return STRING;
}
.							{ return yytext[0]; }
%%
