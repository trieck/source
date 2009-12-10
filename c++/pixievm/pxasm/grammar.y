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
%token	<sym>	STRING LABEL

%token	<sym>	I1 I2 I3 I4 I5 I6 I7
%token	<sym>	R8 R16 RX16
%token	<sym>	IM8 IM16
%token	<sym>	ID

%type	<sym>	immediate
%type	<sym>	M16	A16

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

definition:	ID EQ IM8 {
				if ($1->type != ST_UNDEF) {
					throw Exception("\"%s\" already defined near line %d.",
						$1->name.c_str(), lineno);
				}
				
				$1->type = ST_ID;
				$1->sub = IM8;
				$1->val8 = $3->val8;
			}
		|	ID EQ IM16 {
				if ($1->type != ST_UNDEF) {
					throw Exception("\"%s\" already defined near line %d.",
						$1->name.c_str(), lineno);
				}
				
				$1->type = ST_ID;
				$1->sub = IM16;
				$1->val16 = $3->val16;
			}
		;
		
label:	ID COLON	{ 
			if ($1->type != ST_UNDEF) {
				throw Exception("label \"%s\" already defined near line %d.",
					$1->name.c_str(), lineno);
			}			
			code->setLabel($1);
		}
		;

instr:		I1 R8  ',' R8 		{ code->code3(AM_RR8, $1, $2, $4); }	
		|	I1 R8  ',' IM8		{ code->code3(AM_RI8, $1, $2, $4); }	
		|	I1 R8  ',' M16		{ code->code3(AM_RM8, $1, $2, $4); }	
		|	I1 R8  ',' A16      { code->code3(AM_RA8, $1, $2, $4); }	
        |	I1 R16 ',' R16		{ code->code3(AM_RR16, $1, $2, $4); }	
        |	I1 R16 ',' IM8		{ code->code3(AM_RI16, $1, $2, $4); }	
		|	I1 R16 ',' IM16		{ code->code3(AM_RI16, $1, $2, $4); }	
        |	I1 R16 ',' M16		{ code->code3(AM_RM16, $1, $2, $4); }	
        |	I1 R16 ',' A16		{ code->code3(AM_RA16, $1, $2, $4); }	
        |	I1 M16 ',' R8		{ code->code3(AM_MR8, $1, $2, $4); }	
        |	I1 M16 ',' R16		{ code->code3(AM_MR16, $1, $2, $4); }	
		|	I1 BYTE M16 ',' IM8	{ code->code3(AM_M8I8, $1, $3, $5); }
		|	I1 WORD M16 ',' IM8	{ code->code3(AM_M16I8, $1, $3, $5); }
		|	I1 M16 ',' IM16		{ code->code3(AM_MI16, $1, $2, $4); }		
        |	I1 A16 ',' R8		{ code->code3(AM_AR8, $1, $2, $4); }	
        |	I1 A16 ',' R16		{ code->code3(AM_AR16, $1, $2, $4); }	
        |	I1 BYTE A16 ',' IM8	{ code->code3(AM_A8I8, $1, $3, $5); }	
        |	I1 WORD A16 ',' IM8	{ code->code3(AM_A16I8, $1, $3, $5); }	
        |	I1 A16 ',' IM16		{ code->code3(AM_AI16, $1, $2, $4); }	
        |	I2 R8				{ code->code2(AM_R8, $1, $2); }	
        |	I2 R16				{ code->code2(AM_R16, $1, $2); }
        |	I2 BYTE M16			{ code->code2(AM_M8, $1, $3); }
        |	I2 WORD M16			{ code->code2(AM_M16, $1, $3); }
        |	I2 BYTE A16			{ code->code2(AM_A8, $1, $3); }
        |	I2 WORD A16			{ code->code2(AM_A16, $1, $3); }
        |	I3					{ code->code1(AM_IMPLIED, $1); }
        |	I4 R16				{ code->code2(AM_R16, $1, $2); }
        |	I4 M16				{ code->code2(AM_M16, $1, $2); }
        |	I4 A16				{ code->code2(AM_A16, $1, $2); }
		|	I4 IM8				{ code->code2(AM_I16, $1, $2); }
        |	I4 IM16				{ code->code2(AM_I16, $1, $2); }
        |	I5 IM8				{ code->code2(AM_I8, $1, $2); }
        |	I6 R8				{ code->code2(AM_R8, $1, $2); }
        |	I6 R16				{ code->code2(AM_R16, $1, $2); }
        |	I6 BYTE M16			{ code->code2(AM_M8, $1, $3); }
        |	I6 WORD M16			{ code->code2(AM_M16, $1, $3); }
        |	I6 BYTE A16			{ code->code2(AM_A8, $1, $3); }
        |	I6 WORD A16			{ code->code2(AM_A16, $1, $3); }
        |	I7 R8				{ code->code2(AM_R8, $1, $2); }
        |	I7 R16				{ code->code2(AM_R16, $1, $2); }
        |	I7 BYTE M16			{ code->code2(AM_M8, $1, $3); }
        |	I7 WORD M16			{ code->code2(AM_M16, $1, $3); }
        |	I7 BYTE A16			{ code->code2(AM_A8, $1, $3); }
        |	I7 WORD A16			{ code->code2(AM_A16, $1, $3); }
		|	I7 IM8				{ code->code2(AM_I8, $1, $2); }	
        |	I7 IM16				{ code->code2(AM_I16, $1, $2); }	
		;
		
M16:		'[' R16 ']'			{ $$ = $2; }
		|	'[' RX16 ']'		{ $$ = $2; }
		;

A16:		'[' IM8 ']'			{ $$ = $2; }
		|	'[' IM16 ']'		{ $$ = $2; }
		;
		
pseudo_op:	
		DECL_ORG immediate	{ 
				if (code->isGenerated()) {
					throw Exception("improper origin declaration at line %d.", lineno);
				}
				if (code->isOriginSet()) {
					throw Exception("origin already declared at line %d.", lineno);
				}
				code->setOrigin($2->val16); 
			}
		| DECL_BYTE IM8		{ code->putByte($2->val8); }
		| DECL_WORD IM16	{ code->putWord($2->val16); }
		| DECL_TEXT STRING	{ code->putString($2->name); }
		;

immediate:	IM8		{ $$ = $1; }
		|	IM16	{ $$ = $1; }
		;

%%	
    /* end grammar */

int yyerror(const char *s)
{
	throw Exception(s);	
	return 0;
}
