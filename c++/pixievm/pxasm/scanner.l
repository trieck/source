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
string line;

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
quotedstr		\"[^"\n]+\"
pseudo_op		\.[a-zA-Z][a-zA-Z0-9_]*
offset-reg		[a-zA-Z]+[\r\t ]*\+[\r\t ]*[xX]
lt				<
gt				>
%%
{whitespace}	;
{comment}		;
{hexnum}		{
	string error;
	word d;		
	if (!sscanf(&yytext[1], "%hx", &d)) {
		yyerror("invalid hex number");
		return 0;
	}		
	
	if (d < 0x100) {
		yylval.sym = table->installw(ST_CONST, IM8, d); 
		return IM8;
	} else {
		yylval.sym = table->installw(ST_CONST, IM16, d); 
		return IM16;
	}
}
{offset-reg}						{
	string error;
	string reg = trim(string(yytext, strchr(yytext, '+') - yytext));
	LPSYMBOL sym;
	if ((sym = table->lookup(reg)) == NULL) {
		yyerror("unexpected token");
		return 0;
	}
	if (sym->type != ST_REG) {
		yyerror("unsupported symbol");
		return 0;
	}

	// encode offset bit in register
	yylval.sym = table->installw(yytext, sym->type, sym->sub, sym->val8 | 0x08);
	return RX16;
}
{newline}.*		{ 
		line = trim(yytext + 1);
		yyless(1); 
	}
{identifier}				{
	LPSYMBOL sym;
	if ((sym = table->lookup(yytext)) == NULL) {
		yylval.sym = table->install(yytext);
		return UNDEF;
	}
	
	switch (sym->type) {
	case ST_REG:
	case ST_INSTRUCTION:
	case ST_ID:
		yylval.sym = sym;
		return sym->sub;
	case ST_UNDEF:
		yylval.sym = sym;
		return UNDEF;
	default:
		yyerror("unsupported symbol");
	}
	
	return 0;
}
{pseudo_op}					{ 
	LPSYMBOL sym;
	if ((sym = table->lookup(yytext)) == NULL) {
		yyerror("unrecognized pseudo-op");
		return 0;
	}
	
	return sym->sub;
 }

{quotedstr}					{
	const char *ptext = yytext+1;	// eat '"' 
	string str;

	for ( ; *ptext != '"'; ptext++) {
		if (ptext[0] == '\0' || ptext[0] == '\n') {
			yyerror("unterminated string literal");
			return 0;
		}
		
		str += backslash(&ptext);
	}

	yylval.sym = table->installs(str);
	
	return STRING;
}
{lt}	{ return LO_BYTE; }
{gt}	{ return HI_BYTE; }
.		{ return yytext[0]; }
%%
