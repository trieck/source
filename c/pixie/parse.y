%{
#include <stdlib.h>
#include <stdio.h>
#include "pixie.h"
#include "tree.h"

extern int yylex(void);
static int yyerror(const char *s);
static void defnonly(const char *s);
static void looponly(const char *s);

extern int lineno;
static int indef, inloop;
%}

%union {
	Node *node;			/* node in parse tree */
	Symbol *sym;		/* symbol table pointer */
	int n;				/* token id */
}

%token	<n>		FIRSTTOKEN	/* must be first */
%token	<n>		PLUS SUB MULT DIV MOD EXP SIN COS ATAN LOG LOG10 SQRT INT ABS
%token	<n>		PRINT PRINTLN ASGN SUBASGN LENGTH SHIFT UNSHIFT PUSH POP WHILE
%token	<n>		IF ELSE UNARYMINUS GT GE LT LE EQ NE AND OR NOT VAR BLOCK
%token	<n>		DEF CALL RETURN BREAK CONTINUE FOREACH IN STRLEN SUBSTR
%token	<n>		STRCAT INDEX MKLIST SUBSCR BNOT LSHIFT RSHIFT BAND BOR ASC CHR

%token	<sym>	ID BLTIN NUMBER STRING

%type	<node>	stmt_list stmts stmt expr_stmt block expr prim
%type	<node>	cond decl declarator decl_list prlist defn asgn
%type	<node>	subscr subasgn func args arglist

%nonassoc	LOWER_THAN_ELSE
%nonassoc	ELSE
%right		'='
%left		BOR OR
%left		BAND AND
%left		GT GE LT LE EQ NE
%left		LSHIFT RSHIFT
%left		'+' '-'
%left		'*' '/' '%'
%left		UNARYMINUS NOT BNOT
%right		'^'
%left		'[' '{'

%%	/* begin grammar */

prog:	/* nothing */
		| stmts				{ root = stmt1(BLOCK, $1); return 1; } 
		| prog error		{ yyclearin; yyerrok; }
		;

stmts:	stmt				
		| stmts stmt		{ $$ = lknodes($1, $2); }
		;

stmt:	expr_stmt ';'
		| WHILE cond 		{ inloop++; }
			block			{ $$ = stmt2(WHILE, $2, $4); inloop--; }
		| FOREACH ID IN expr { inloop++; }
			block { $$ = stmt3(FOREACH, symtonode($2), $4, $6); inloop--;}
		| IF cond stmt %prec LOWER_THAN_ELSE { $$ = stmt3(IF, $2, $3, 0); }
		| IF cond stmt ELSE stmt { $$ = stmt3(IF, $2, $3, $5); }
		| block
		| defn
		;

block:	'{' stmt_list '}' { $$ = stmt1(BLOCK, $2); }
		;

stmt_list:		/* nothing */	{ $$ = 0; }
		| stmts
		;

expr_stmt:	/* nothing */	{ $$ = 0; }
		| expr
		| decl
		| PRINT prlist 		{ $$ = stmt1(PRINT, $2); }
		| PRINTLN prlist	{ $$ = stmt1(PRINTLN, $2); }
		| RETURN expr		{ defnonly("return"); $$ = stmt1(RETURN, $2); }
		| BREAK				{ looponly("break"); $$ = stmt0(BREAK); }
		| CONTINUE			{ looponly("continue"); $$ = stmt0(CONTINUE); }
		;

expr:	prim
		| asgn
		| subasgn
		| subscr
		| func
		| expr LSHIFT expr	{ $$ = op2(LSHIFT, $1, $3); }
		| expr RSHIFT expr	{ $$ = op2(RSHIFT, $1, $3); }
		| expr '+' expr		{ $$ = op2(PLUS, $1, $3); }
		| expr '-' expr		{ $$ = op2(SUB, $1, $3); }
		| expr '*' expr 	{ $$ = op2(MULT, $1, $3); }
		| expr '/' expr		{ $$ = op2(DIV, $1, $3); }
		| expr '%' expr		{ $$ = op2(MOD, $1, $3); }
		| expr '^' expr		{ $$ = op2(EXP, $1, $3); }
		| '-' expr %prec UNARYMINUS { $$ = stmt1(UNARYMINUS, $2); }
		| expr GT expr		{ $$ = op2(GT, $1, $3); } 
		| expr GE expr		{ $$ = op2(GE, $1, $3); } 
		| expr LT expr		{ $$ = op2(LT, $1, $3); } 
		| expr LE expr		{ $$ = op2(LE, $1, $3); } 
		| expr EQ expr		{ $$ = op2(EQ, $1, $3); } 
		| expr NE expr		{ $$ = op2(NE, $1, $3); } 
		| expr AND expr		{ $$ = op2(AND, $1, $3); } 
		| expr BAND expr	{ $$ = op2(BAND, $1, $3); }
		| expr OR expr		{ $$ = op2(OR, $1, $3); } 
		| expr BOR expr		{ $$ = op2(BOR, $1, $3); }
		| BLTIN '(' expr ')' 	{ $$ = stmt1($1->sub, $3); }
		| NOT expr			{ $$ = op1(NOT, $2); } 
		| BNOT expr			{ $$ = op1(BNOT, $2); }
		| LENGTH ID			{ $$ = stmt1(LENGTH, symtonode($2)); }
		| SHIFT ID			{ $$ = stmt1(SHIFT, symtonode($2)); }
		| UNSHIFT '(' ID ',' expr ')' { $$ = stmt2(UNSHIFT, symtonode($3), $5); }
		| PUSH '(' ID ',' expr ')' { $$ = stmt2(PUSH, symtonode($3), $5); }
		| POP ID			{ $$ = stmt1(POP, symtonode($2)); }
		| STRLEN '(' expr ')'	{ $$ = stmt1(STRLEN, $3); }
		| SUBSTR '(' expr ',' expr ',' expr ')'	{ $$ = stmt3(SUBSTR, $3, $5, $7); }
		| STRCAT '(' expr ',' expr ')'	{ $$ = stmt2(STRCAT, $3, $5); }
		| INDEX '(' expr ',' expr ')'	{ $$ = stmt2(INDEX, $3, $5); }			
		| ASC '(' expr ')'				{ $$ = stmt1(ASC, $3); }
		| CHR '(' expr ')'				{ $$ = stmt1(CHR, $3); }
		| '[' args ']'		{ $$ = stmt1(MKLIST, $2); }
		;

prim:	NUMBER				{ $$ = symtonode($1); }
		| STRING			{ $$ = symtonode($1); }
		| ID				{ $$ = symtonode($1); }
		| '(' expr ')'		{ $$ = $2; }
		;

cond:	'(' expr ')'		{ $$ = $2; }
		;

decl:	VAR decl_list		{ $$ = stmt1($1, $2); }
		;
				
decl_list:	declarator
		| decl_list ',' declarator	{ $$ = lknodes($1, $3); }
		;

declarator:	ID	{ $1->type = SVAR; $$ = symtonode($1); }
		| asgn
		;

prlist:		expr			
		| prlist ',' expr		{ $$ = lknodes($1, $3); }
		;

asgn:	ID '=' expr				{ $1->type = SVAR; $$ = stmt2(ASGN, symtonode($1), $3); }
		;

subasgn:	ID '[' expr ']' '=' expr		{ $$ = stmt3(SUBASGN, symtonode($1), $3, $6); }
		;

subscr: ID '[' expr ']'	{ $$ = stmt2(SUBSCR, symtonode($1), $3); }
		;

defn:	DEF ID {
			if ($2->type != SUNDEF) {
				error("%s already defined near line %d.",
				$2->name, lineno);
			}
			$2->type = SFUNC; indef++;
		} 
		block { $$ = stmt2(DEF, symtonode($2), $4); indef--; }
		;

func:	ID '(' args ')'	{ 
			if ($1->type != SFUNC) {
				error("%s not a function near line %d.", $1->name, lineno);
			}
			$$ = stmt2(CALL, symtonode($1), $3); }
		;

args:	/* empty */				{ $$ = 0; }
		| arglist
		;
	
arglist: expr					
		| expr ',' arglist		{ $$ = lknodes($1, $3); }
		;
%%	
    /* end grammar */

void defnonly(const char *s)
{
	if (!indef)
		error("%s used outside definition near line %d.",
			s, lineno);
}

void looponly(const char *s)
{
	if (!inloop)
		error("%s used outside loop near line %d.",
			s, lineno);
}
    
/* error during parsing */
int yyerror(const char *s)
{
	error("%s near line number %d.", s, lineno);
	return 0;
}
