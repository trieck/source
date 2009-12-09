%{

#include "Common.h"
#include "SymbolTable.h"
#include "Exception.h"

extern int yylex(void);
extern int yyterminate(void);
static int yyerror(const char *s);

%}

%union {
	int n;			// token id 
	LPSYMBOL sym;	// symbol 
}

%token	<n>		BYTE WORD EOL EQ COLON

%token	<sym>	I1 I2 I3 I4 I5 I6 I7
%token	<sym>	R8 R16 RX16
%token	<sym>	IM8 IM16

%token	<sym>	ID

// %type	<sym>	M16	A16

%%	/* begin grammar */

prog:	stmts			{ YYACCEPT; }
		| prog error	{ yyclearin; yyerrok; }
		;

stmts:	stmt
		| stmts stmt	{ ; }
		;

stmt:	definition 
		| label
		| instr
		| pseudo_op
		;

definition:	ID EQ IM8
		| ID EQ IM16
		;
		
label:	ID COLON
		;

instr:	I1 R8 ',' R8 		{ ; }	
		;
		
pseudo_op: '.' ID
		;

%%	
    /* end grammar */

int yyerror(const char *s)
{
	return 0;
}
