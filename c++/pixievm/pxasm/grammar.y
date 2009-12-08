%{

#include "Common.h"
#include "Exception.h"

extern int yylex(void);
extern int yyterminate(void);
static int yyerror(const char *s);

%}

%union {
	int n;			// token id 
	LPSYMBOL sym;	// symbol 
}

%token	<n>		BYTE WORD EOL
%token	<sym>	I1 I2 I3 I4 I5 I6 I7
%token	<sym>	R8 R16 RX16
%token	<sym>	IM8 IM16

// %type	<sym>	M16	A16

%token	<n>	EQ

%%	/* begin grammar */

prog:	/* nothing */
		| stmts			{ YYACCEPT }
		;

stmts:	stmt
		| stmts stmt	{ ; }
		;

stmt:	definition 
		| label
		| instr
		| pseudo_op
		;

%%	
    /* end grammar */

int yyerror(const char *s)
{
	return 0;
}
