%{
#include "common.h"
#include "opcodes.h"
#include "symbol.h"
#include "code.h"

extern char *yytext;
extern int yylineno;
extern int yylex(void);
extern int yyterminate(void);

extern SymbolTable table;

int yyerror(const char *s);

%}

%union {
    int n;
    byte byte_value;
    word word_value;
    char id[256];
    struct Symbol* sym;
}

%token <byte_value> BYTE 
%token <word_value> WORD
%token <id> STRING UNDEF
%token <n> NEWLINE X_INDEX Y_INDEX DECL_BYTE DECL_WORD
%token <n> DECL_TEXT DECL_ZTEXT LOBYTE HIBYTE
%token <n> PLUS MINUS STAR DIV
%token <sym> OPCODE BYTE_ID WORD_ID
%token <sym> GRP1_OP GRP2_OP GRP3_OP GRP3_BRANCH_OP OTHER_OP

%type <word_value> word_expr word_prim word opword brword declwords declword
%type <byte_value> byte opbyte declbytes declbyte

%right UNDEF OPCODE STAR
%right  '='

%left PLUS MINUS
%left MULT DIV

%expect 0

%%  /* begin grammar */

prog:       stmts
            ;

stmts:      stmt
        |   stmts stmt
            ;

stmt:       defbase
        |   defbyte
        |   defword
        |   deflabel 
        |   instr
        |   pseudo
        |   '\n'
            ;

defbase:    STAR '=' word_expr {
                defbase($3);
            }

defbyte:    UNDEF '=' BYTE {
                byteinsert(table, $1, $3);
            }
            ;

defword:    UNDEF '=' word_expr {
                wordinsert(table, $1, $3);
            }
            ;

deflabel:   UNDEF  {
                deflabel($1);
            }
            ;

instr:      OPCODE                              { imp_acc_code($1->u.instr); }
        |   OPCODE '#' opbyte                   { imm_code($1->u.instr, $3); }
        |   OPCODE opbyte                       { zp_code($1->u.instr, $2); }
        |   OPCODE opbyte X_INDEX               { zpx_code($1->u.instr, $2); }
        |   OPCODE opbyte Y_INDEX               { zpy_code($1->u.instr, $2); }
        |   OPCODE opword                       { abs_code($1->u.instr, $2); }
        |   OPCODE opword X_INDEX               { abx_code($1->u.instr, $2); }
        |   OPCODE opword Y_INDEX               { aby_code($1->u.instr, $2); }
        |   OPCODE '(' opbyte X_INDEX ')'       { idx_code($1->u.instr, $3); }
        |   OPCODE '(' opbyte ')' Y_INDEX       { idy_code($1->u.instr, $3); }
        |   OPCODE '(' opword ')'               { ind_code($1->u.instr, $3); }
        |   GRP3_BRANCH_OP brword               { rel_code($1->u.instr, $2); }
            ;

pseudo:     DECL_BYTE declbytes
        |   DECL_WORD declwords
        |   DECL_TEXT STRING                { text_code($2); }
        |   DECL_ZTEXT STRING               { ztext_code($2); }
            ;

brword:     word_expr
        |   UNDEF                           { branch_fixup($1); $$ = 0; }
            ;

opword:     word_expr
        |   UNDEF                           { op_fixup($1); $$ = 0;}
            ;

opbyte:     byte  
        |   LOBYTE UNDEF                    { op_lobyte_fixup($2); $$ = 0; }
        |   HIBYTE UNDEF                    { op_hibyte_fixup($2); $$ = 0; }
            ;

declwords:  declword
        |   declwords ',' declword
            ;

declword:   word_expr                       { word_code($1); $$ = $1; }
        |   UNDEF                           { declword_fixup($1); word_code(0); $$ = 0; }
            ;

declbytes:  declbyte
        |   declbytes ',' declbyte
            ;

declbyte:   byte                            { byte_code($1); $$ = 1; }
        |   LOBYTE UNDEF                    { decl_lobyte_fixup($2); byte_code(0); $$ = 0; }
        |   HIBYTE UNDEF                    { decl_hibyte_fixup($2); byte_code(0); $$ = 0; }
            ;

word_expr:  word_prim       
        |   word_expr PLUS word_expr        { $$ = $1 + $3; }
        |   byte PLUS word_expr             { $$ = $1 + $3; }
        |   word_expr PLUS byte             { $$ = $1 + $3; }
        |   word_expr MINUS word_expr       { $$ = $1 - $3; }
        |   word_expr MINUS byte            { $$ = $1 - $3; }
        |   word_expr MULT word_expr        { $$ = $1 * $3; }
        |   word_expr MULT byte             { $$ = $1 * $3; }
        |   byte MULT word_expr             { $$ = $1 * $3; }
        |   word_expr DIV word_expr         { $$ = $1 / $3; }
        |   word_expr DIV byte              { $$ = $1 / $3; }
            ;

word_prim:  word
            ;

word:       WORD                            { $$ = $1; }
        |   WORD_ID                         { $$ = symevalword(table, $1->name); }
        |   STAR                            { $$ = symevalword(table, "*"); }
            ;

byte:       BYTE                            { $$ = $1; }
        |   BYTE_ID                         { $$ = $1->u.byte_value; }
        |   LOBYTE word                     { $$ = lobyte($2); }
        |   HIBYTE word                     { $$ = hibyte($2); }
            ;

%%
    /* end grammar */

int yyerror(const char *s)
{
    error("%s: \"%s\" on line %d.\n", s, yytext, yylineno);

    return 1;
}
