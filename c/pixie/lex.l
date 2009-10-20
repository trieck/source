%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pixie.h"
#include "parse.h"
#include "global.h"
#include "temp.h"
#include "strutil.h"

#ifdef _MSC_VER
#define YY_NO_UNISTD_H
#include <io.h>
#endif /* _MSC_VER */

#define MAX_INCLUDE_DEPTH 10

static YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
static int include_stack_ptr = 0;

/* current line number */
int lineno = 1;

/* current module name */
char *module_name;

static char *module_name_stack[MAX_INCLUDE_DEPTH];
static int lineno_stack[MAX_INCLUDE_DEPTH];

int yywrap (void) { return 1; }

char backslash(const char **pp)
{
	static char transtab[] = "b\bf\fn\nr\rt\t";
	char c;

	if (**pp != '\\')
		return **pp;
	c = *++(*pp);
	if (c == '\0')
		return *--(*pp);
	if (strchr(transtab, c))
		return strchr(transtab, c)[1];
	return c;
}

%}

and				&&
band			&
bnot			~
bor				\|
comment			#.*
decimal			\.
digit			[0-9]
eol				\n
eq				==
ge				>=
gt				>
hexnum			0[xX][a-fA-F0-9]+
identifier		[a-zA-Z][a-zA-Z0-9_]*
iname			'[^ \t\r\n]+'
le				<=
lshift			<<
lt				<
ne				!=
not				!
or				\|\|
quotedstr		\"[^"\n]*["\n]
rshift			>>
whitespace		[\t\r ]+


/* the "incl" state is used for picking up the name
 * of an include file
 */
%x incl

%%
include						BEGIN(incl);
{whitespace}				;
{comment}					;
{eol}						{ lineno++; }
{digit}+					|
{digit}*{decimal}{digit}+	{ yylval.sym = tinstall(yytext, SCONST, SFLOAT, atof(yytext)); return NUMBER;  }
{hexnum}					{
	int d;
	if (!sscanf(yytext, "%x", &d))
		error("invalid hex digit %s near line %d.", yytext, lineno);
	yylval.sym = tinstall(yytext, SCONST, SFLOAT, d); 
	return NUMBER;  
}
{identifier}				{
	Symbol *sym = glookup(yytext);
	if (sym == 0 && (sym = tlookup(yytext)) == 0) {
		yylval.sym = tinstall(yytext, SUNDEF, 0, 0);
		return ID;
	}

	switch (sym->type) {
	case SBLTIN:
		yylval.sym = sym;
		return BLTIN;
	case SFUNC:
	case SVAR:
		yylval.sym = sym;
		return ID;
	case SKEYWD:
		yylval.n = sym->sub;
		return yylval.n;
	case SUNDEF:
		error("%s undefined near line %d.", sym->name, lineno);
	default:
		error("unknown symbol %s near line %d.", sym->name, lineno);
	}
}
<incl>{whitespace}		;
<incl>{iname}			{
	String s = stringalloc();	
	const char *pname = yytext+1;
	const char *pstr;
	
	for ( ; *pname != '\''; pname++) {
		if (pname[0] == '\0' || pname[0] == '\n') {
			stringfree(s);
			error("unterminated include name %s.", yytext);
		}
		stringpush(s, *pname);
	}
	
	stringvpush(s, ".pixie");
	
	pstr = stringptr(s);

	if (include_stack_ptr >= MAX_INCLUDE_DEPTH) {
		stringfree(s);
		error("include nested too deeply.");
	}
	
	module_name_stack[include_stack_ptr] = module_name;
	lineno_stack[include_stack_ptr] = lineno;
	include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;
	
	if (!(yyin = fopen(pstr, "r"))) {
		error("unable to open include file \"%s\".", pstr);
	}	
	
	module_name = xstrdup(pstr);
	lineno = 1;
	yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
	
	BEGIN(INITIAL);		
	stringfree(s);
}

<<EOF>>						{ 
	if (--include_stack_ptr < 0) {
		yyterminate();
	} else {
		yy_delete_buffer(YY_CURRENT_BUFFER);
		free(module_name);
		module_name = module_name_stack[include_stack_ptr];
		lineno = lineno_stack[include_stack_ptr];
		yy_switch_to_buffer(include_stack[include_stack_ptr]);
	}		
}

{quotedstr}					{

	String s = stringalloc();
	const char *ptext = yytext+1;	/* eat '"' */
	const char *pstr;

	for ( ; *ptext != '"'; ptext++) {
		if (ptext[0] == '\0' || ptext[0] == '\n') {
			stringfree(s);
			error("unterminated string literal near line %d.", lineno);
		}
		stringpush(s, backslash(&ptext));
	}

	pstr = stringptr(s);
	yylval.sym = tinstalls(pstr, pstr);
	stringfree(s);
	return STRING;
}
{and}						{ return AND; }
{band}						{ return BAND; }
{bnot}						{ return BNOT; }
{bor}						{ return BOR; }
{eq}						{ return EQ; }
{ge}						{ return GE; }
{gt}						{ return GT; }
{le}						{ return LE; }
{lt}						{ return LT; }
{lshift}					{ return LSHIFT; }
{ne}						{ return NE; }
{not}						{ return NOT; }
{or}						{ return OR; }
{rshift}					{ return RSHIFT; }
.							{ return yytext[0]; }
%%
