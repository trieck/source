%{

#include "Common.h"
#include "Exception.h"

extern int yylex(void);
extern int yyterminate(void);
static int yyerror(const char *s);

%}

%%	/* begin grammar */

prog:	/* nothing */

%%	
    /* end grammar */

int yyerror(const char *s)
{
	return 0;
}
