%{
#include "Common.h"
#include "Modes.h"
#include "Instructions.h"
#include "SymbolTable.h"
#include "Parser.hpp"
#include "Exception.h"
#include "Util.h"

#define YY_ALWAYS_INTERACTIVE	(1)
#define YY_NO_UNISTD_H (1)

#ifdef _MSC_VER
#include <io.h>
#endif /* _MSC_VER */

extern "C" int yywrap (void) { return 1; }
SymbolTable *table = SymbolTable::getInstance();
%}
hexnum			\$[a-fA-F0-9]+
identifier		[a-zA-Z]+
offset-reg		[a-zA-Z]+[\r\t ]*\+[\r\t ]*[xX]
whitespace		[\t\r ]+
newline			[\n]

%%
{whitespace}				;
{newline}					{ return EOL; }

{hexnum}					{
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

{offset-reg}						{
	string reg = trim(string(yytext, strchr(yytext, '+') - yytext));
	LPSYMBOL sym = table->lookup(reg);
	if (sym == NULL) {
		throw Exception("unexpected token \"%s\".", yytext);
	}
	if (sym->type != ST_REG) {
		throw Exception("unsupported symbol \"%s\".", yytext);
	}

	/* encode offset bit in register */
	yylval.sym = table->installb(yytext, sym->type, sym->sub, sym->val8 | 0x08);
	return RX16;
}

{identifier}				{
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
	
	return 0;
}
.							{ return yytext[0]; }
%%
