%{
%}

%token	<n>		PLUS SUB MULT DIV MOD EXP SIN COS ATAN LOG LOG10 SQRT INT ABS


%%	/* begin grammar */

prog:	/* nothing */

%%	
    /* end grammar */

int yyerror(const char *s)
{	return 0;
}

int yylex(void)
{
	return 0;
}