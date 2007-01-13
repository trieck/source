%token	NUMBER LINENO ID LET PRINT
%token	IF GOTO INPUT GOSUB RETURN CLEAR
%token	LIST RUN END THEN ELSE

%nonassoc	LOWER_THAN_ELSE
%nonassoc	ELSE

%%	/* begin grammar */

prog:		/* nothing */
			| lines
			| prog error
			;

lines:		line
			| lines line
			;
	
line:		LINENO stmts
			;
		
stmts:		stmt
			| stmts ':' stmt
			;
		
stmt:		/* nothing */
			| LET ID '=' expr
			| PRINT exprlist
			| IF expr THEN stmt %prec LOWER_THAN_ELSE
			| IF expr THEN stmt ELSE stmt
			| GOTO expr
			| INPUT varlist
			| GOSUB expr
			| RETURN
			| CLEAR
			| LIST
			| RUN
			| END
			;
		
expr:		prim
			;
		
exprlist:	expr
			| exprlist ',' expr
			;
			
varlist:	ID
			| varlist ',' ID
			;

prim:		NUMBER		
			| '(' expr ')'
			;

%%	
    /* end grammar */