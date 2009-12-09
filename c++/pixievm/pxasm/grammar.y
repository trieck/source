%{

#include "Common.h"
#include "SymbolTable.h"
#include "Code.h"
#include "Exception.h"

extern int lineno;
extern int yylex(void);
extern int yyterminate(void);
static int yyerror(const char *s);

ANON_BEGIN
Code *code = Code::getInstance();
ANON_END

%}

%union {
	int n;			// token id 
	LPSYMBOL sym;	// symbol 
}

%token	<n>		BYTE WORD EOL EQ COLON

%token	<sym>	DECL_ORG DECL_BYTE DECL_WORD DECL_TEXT
%token	<sym>	STRING

%token	<sym>	I1 I2 I3 I4 I5 I6 I7
%token	<sym>	R8 R16 RX16
%token	<sym>	IM8 IM16
%token	<sym>	ID

%type	<sym>	immediate

%%	/* begin grammar */

prog:	stmts			{ YYACCEPT; }
		| prog error	{ yyclearin; yyerrok; }
		;

stmts:	stmt
		| stmts stmt
		;

stmt:	definition 
		| label
		| instr
		| pseudo_op
		;

definition:	ID EQ immediate
		;
		
label:	ID COLON
		;

instr:	I1 R8 ',' R8 		{ ; }	
		;
		
pseudo_op:	
		DECL_ORG immediate	{ 
				if (code->isOriginSet()) {
					throw new Exception("origin already declared at line %d.", lineno);
				}
				code->setOrigin($2->val16); 
			}
		| DECL_BYTE IM8		{ code->putByte($2->val8); }
		| DECL_WORD IM16	{ code->putWord($2->val16); }
		| DECL_TEXT STRING	{ code->putString($2->name); }
		;

immediate: IM8	| IM16	
		;

%%	
    /* end grammar */

int yyerror(const char *s)
{
	throw Exception(s);	
	return 0;
}
