%{
#include "Common.h"

#ifdef _MSC_VER
#pragma warning(disable:4996)	// disable deprecation warnings
#include <io.h>
#endif /* _MSC_VER */

%}
hexnum			\$[a-fA-F0-9]+
identifier		[a-zA-Z]+
offset-reg		[a-zA-Z]+[\r\t ]*\+[\r\t ]*[xX]
whitespace		[\t\r ]+
newline			[\n]

%%
{whitespace}				;
.							{ return yytext[0]; }
%%
