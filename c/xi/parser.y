%{
#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"
#include "tree.h"
#include "x.h"

extern int yylex(void);
static int yyerror(const char *s);

extern int lineno;
extern Node *root;

%}

%union {
	PNODE node;		/* node in parse tree */
	PSYMBOL sym;	/* symbol table pointer */
	int n;			/* token id */
}

%token	<n>		FIRSTTOKEN	/* must be first */
%token	<n>		PLUS SUB MULT DIV MOD
%token	<n>		RANGE MKLIST PRINT PRINTLN LET

%token	<n>		LASTTOKEN	/* place holder */

/* lexical tokens only */
%token	<n>		ARROW CALL
%token	<sym>	NUMBER ID KEYWORD

%type	<node>	stmts expr list items 
%type	<node>	item_list member primary range

%%	/* begin grammar */

prog:		/* nothing */
			| stmts
				{ root = mkstmt(MKLIST, $1); return 1; } 
			| prog error
				{ yyerrok; }
			;

stmts:		expr
			| stmts expr
				{ $$ = lknodes($1, $2); }
			;

expr:		list
			| expr '+'
				{ $$ = mkstmt(PLUS, $1); }
			| expr '-'
				{ $$ = mkstmt(SUB, $1); }
			| expr '*'
				{ $$ = mkstmt(MULT, $1); }
			| expr '/'
				{ $$ = mkstmt(DIV, $1); }
			| expr '%'
				{ $$ = mkstmt(MOD, $1); }
			| expr KEYWORD
				{ $$ = mkstmt($2->subtype, $1); }	
			| expr ARROW ID
				{ $$ = mkstmt2(CALL, $1, mkleaf($3)); }
			;
					
list:		'[' items ']'
				{ $$ = mkstmt(MKLIST, $2); }
			;

items:		/* nothing */
				{ $$ = 0; }
			| item_list
			;

item_list:	member
			| member item_list				
				{ $$ = lknodes($1, $2); }
			;

member:		expr
			| primary
			| range
			;
	
primary: 	NUMBER
				{ $$ = mkleaf($1); }
			| ID
				{ $$ = mkleaf($1); }
			;

range:		primary RANGE primary
				{ $$ = mkstmt2(RANGE, $1, $3); }
			;
		    
%%	
    /* end grammar */

/* parse error */
int yyerror(const char *s)
{
	error("%s near line no %d.", s, lineno);
	return 0;
}

