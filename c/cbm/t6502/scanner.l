%option yylineno

%{
#define YY_NO_UNISTD_H (1)
#define YY_SKIP_YYWRAP (1)

#include "common.h"
#include "parser.h"
#include "symbol.h"

#include <io.h>

extern int yyerror(const char *s);
static int yywrap(void) { return 1; }

extern SymbolTable table;
%}

comment             ;.*
div                 \/
decnum              [0-9]+
hexbyte             \$[a-fA-F0-9]{1,2}
hexword             \$[a-fA-F0-9]{3,4}
hibyte              >
identifier          [a-zA-Z][a-zA-Z0-9_]*
lobyte              <
minus               -
star                \*
newline             [\n]+
plus                \+
pseudo_op           \.[a-zA-Z][a-zA-Z0-9_]*
string              '.+'
whitespace          [\t\r ]+
x_index             ,[ ]*[xX]
y_index             ,[ ]*[yY]

%%
{whitespace}        ;
{comment}           ;  
{newline}           {
    yyless(1);
    return yytext[0];
}

{decnum} {
    word w;
    if (sscanf(yytext, "%hd", &w) != 1) {
        yyerror("invalid number");
        return 0;
    }

    if (w < 256) {
        yylval.byte_value = lobyte(w);
        return BYTE;
    }

    yylval.word_value = w;

    return WORD;
}

{hexbyte} {
    byte b;
    if (sscanf(&yytext[1], "%hhx", &b) != 1) {
        yyerror("invalid hex byte");
        return 0;
    }

    yylval.byte_value = b;

    return BYTE;
}

{hexword} {
    word w;
    if (sscanf(&yytext[1], "%hx", &w) != 1) {
        yyerror("invalid hex word");
        return 0;
    } 

    yylval.word_value = w;

    return WORD;
}

{identifier} {
    PSYMBOL sym;
    if ((sym = symlookup(table, yytext)) == NULL) {
        strcpy(yylval.id, yytext);
        return UNDEF;
    }

    if (sym->type == SYM_OPCODE) {
        yylval.sym = sym;
        if (sym->sub_type == GRP3_BRANCH_OP) { 
            return GRP3_BRANCH_OP;  // special handling
        }

        return OPCODE;
    }

    if (sym->type == SYM_BYTE) {
        yylval.sym = sym;
        return BYTE_ID;
    }

    if (sym->type == SYM_WORD || sym->type == SYM_FUNC) {
        yylval.sym = sym;
        return WORD_ID;
    }

    return 0;
}

{string} {
    
    size_t len = strlen(yytext);
    strcpy(yylval.id, &yytext[1]);
    yylval.id[len-2] = '\0';
    
    return STRING;
}

{pseudo_op} { 
    PSYMBOL sym;
    if ((sym = symlookup(table, yytext)) == NULL) {
        yyerror("unrecognized pseudo-op");
        return 0;
    }
    
    return sym->sub_type;
 }

{x_index} {
    return X_INDEX;
}

{y_index} {
    return Y_INDEX;
}

{lobyte} {
    return LOBYTE;
}

{hibyte} {
    return HIBYTE;
}

{plus} { 
    return PLUS; 
}

{minus} { 
    return MINUS; 
}

{star} { 
    return STAR; 
}

{div} { 
    return DIV; 
}

. { return yytext[0]; }

%%
