#ifndef YYERRCODE
#define YYERRCODE 256
#endif

#define FIRSTTOKEN 257
#define PLUS 258
#define SUB 259
#define MULT 260
#define DIV 261
#define MOD 262
#define RANGE 263
#define MKLIST 264
#define PRINT 265
#define PRINTLN 266
#define LET 267
#define LASTTOKEN 268
#define ARROW 269
#define CALL 270
#define NUMBER 271
#define ID 272
#define KEYWORD 273
typedef union {
    PNODE node;		/* node in parse tree */
    PSYMBOL sym;	/* symbol table pointer */
    int n;			/* token id */
} YYSTYPE;
extern YYSTYPE yylval;
