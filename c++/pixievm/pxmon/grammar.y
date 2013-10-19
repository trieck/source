%{
#include "Common.h"
#include "Modes.h"
#include "Instructions.h"
#include "SymbolTable.h"
#include "Code.h"
#include "Exception.h"

extern int yylex(void);
extern int yyterminate(void);
static int yyerror(const char *s);
%}

%union {
	int n;					/* token id */
	LPSYMBOL sym;		/* symbol table pointer */
}

%token	<n>		BYTE_PTR WORD_PTR EOL
%token	<sym>	I1 I2 I3 I4 I5 I6 I7
%token	<sym>	R8 R16 RX16
%token	<sym>	IM8 IM16

%type	<sym>	M16	A16

%%	/* begin grammar */
prog:	EOL						{ YYABORT; }
		| instr	EOL				{ YYACCEPT; }
		;

instr:		I1 R8  ',' R8 		{ code3(AM_RR8, $1, $2, $4); }
				|	I1 R8  ',' IM8		{ code3(AM_RI8, $1, $2, $4); }
				|	I1 R8  ',' M16		{ code3(AM_RM8, $1, $2, $4); }
				|	I1 R8  ',' A16		{ code3(AM_RA8, $1, $2, $4); }
				|	I1 R16 ',' R16		{ code3(AM_RR16, $1, $2, $4); }
				|	I1 R16 ',' IM8		{ code3(AM_RI16, $1, $2, $4); }
				|	I1 R16 ',' IM16		{ code3(AM_RI16, $1, $2, $4); }
				|	I1 R16 ',' M16		{ code3(AM_RM16, $1, $2, $4); }
				|	I1 R16 ',' A16		{ code3(AM_RA16, $1, $2, $4); }
				|	I1 M16 ',' R8			{ code3(AM_MR8, $1, $2, $4); }
				|	I1 M16 ',' R16		{ code3(AM_MR16, $1, $2, $4); }
				|	I1 BYTE_PTR M16 ',' IM8	{ code3(AM_M8I8, $1, $3, $5); }
				|	I1 WORD_PTR M16 ',' IM8	{ code3(AM_M16I8, $1, $3, $5); }
				|	I1 M16 ',' IM16		{ code3(AM_MI16, $1, $2, $4); }	
				|	I1 A16 ',' R8			{ code3(AM_AR8, $1, $2, $4); }
				|	I1 A16 ',' R16		{ code3(AM_AR16, $1, $2, $4); }
				|	I1 BYTE_PTR A16 ',' IM8	{ code3(AM_A8I8, $1, $3, $5); }
				|	I1 WORD_PTR A16 ',' IM8	{ code3(AM_A16I8, $1, $3, $5); }
				|	I1 A16 ',' IM16		{ code3(AM_AI16, $1, $2, $4); }
				|	I2 R8							{ code2(AM_R8, $1, $2); }
				|	I2 R16						{ code2(AM_R16, $1, $2); }
				|	I2 BYTE_PTR M16		{ code2(AM_M8, $1, $3); }
				|	I2 WORD_PTR M16		{ code2(AM_M16, $1, $3); }
				|	I2 BYTE_PTR A16		{ code2(AM_A8, $1, $3); }
				|	I2 WORD_PTR A16		{ code2(AM_A16, $1, $3); }
				|	I3								{ code1(AM_IMPLIED, $1); }
				|	I4 R16						{ code2(AM_R16, $1, $2); }
				|	I4 M16						{ code2(AM_M16, $1, $2); }
				|	I4 A16						{ code2(AM_A16, $1, $2); }
				|	I4 IM8						{ code2(AM_I16, $1, $2); }
				|	I4 IM16						{ code2(AM_I16, $1, $2); }
				|	I5 IM8						{ code2(AM_I8, $1, $2); }
				|	I6 R8							{ code2(AM_R8, $1, $2); }
				|	I6 R16						{ code2(AM_R16, $1, $2); }
				|	I6 BYTE_PTR M16		{ code2(AM_M8, $1, $3); }
				|	I6 WORD_PTR M16		{ code2(AM_M16, $1, $3); }
				|	I6 BYTE_PTR A16		{ code2(AM_A8, $1, $3); }
				|	I6 WORD_PTR A16		{ code2(AM_A16, $1, $3); }
				|	I7 R8							{ code2(AM_R8, $1, $2); }
				|	I7 R16						{ code2(AM_R16, $1, $2); }
				|	I7 BYTE_PTR M16		{ code2(AM_M8, $1, $3); }
				|	I7 WORD_PTR M16		{ code2(AM_M16, $1, $3); }
				|	I7 BYTE_PTR A16		{ code2(AM_A8, $1, $3); }
				|	I7 WORD_PTR A16		{ code2(AM_A16, $1, $3); }
				|	I7 IM8						{ code2(AM_I8, $1, $2); }
				|	I7 IM16						{ code2(AM_I16, $1, $2); }
				;
	
M16:		'[' R16 ']'			{ $$ = $2; }
			|	'[' RX16 ']'		{ $$ = $2; }
			;

A16:		'[' IM8 ']'			{ $$ = $2; }
			|	'[' IM16 ']'		{ $$ = $2; }
		;

%%	/* end grammar */
	
int yyerror(const char *s)
{
	throw Exception(s);
	return 0;
}
