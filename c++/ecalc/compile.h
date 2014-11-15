/////////////////////////////////////////////////////////////////////////////
//
//	COMPILE.H
//
//	Compiles an expression into a program for a runtime
//	machine.  The grammar for the language is:
//
//	compstmt :=		expr '\n'
//
//	expr:			expr '&&' comp-expr
//					expr '&' comp-expr
//					expr '||' comp-expr
//					expr '|' comp-expr
//					comp-expr
//
//	comp-expr:		comp-expr '<' shift-expr
//					comp-expr '>' shift-expr
//					comp-expr '<=' shift-expr
//					comp-expr '>=' shift-expr
//					comp-expr '==' shift-expr
//					comp-expr '!=' shift-expr
//					shift-expr
//
//	shift-expr:		shift-expr '<<' add-expr
//					shift-expr '>>' add-expr
//					add-expr
//
//	add-expr :=		add-expr '+' mult-expr
//					add-expr '-' mult-expr
//					mult-expr
//
//	mult-expr :=	mult-expr '/' primary
//					mult-expr '*' primary
//					mult-expr '%' primary
//					primary
//
//	primary :=		number
//					name
//					arg
//					name '=' expr
//					arg '=' expr
//					'-' primary
//					'!' primary
//					'"' characters '"'
//					'(' expr ')'
//					'{' compstmt '}'
//
//	Copyright (c) 1999 Thomas A. Rieck
//

#ifndef __COMPILE_H__
#define __COMPILE_H__

#define MAXTOK 256

enum TokenType {
    UNDEF = 0,		/* undefined token */
    STR,			/* string literal */
    NUM,			/* number */
    SYMBOL,			/* variable / builtin */
    ARG = '$',		/* argument */
    PLUS = '+',		/* addition */
    MINUS = '-',	/* subtraction */
    MULT = '*',		/* multiply */
    DIV = '/',		/* division */
    MOD = '%',		/* modulo */
    LT = '<',		/* less than */
    GT = '>',		/* greater than */
    EQUAL = '=',	/* equal */
    NOT = '!',		/* not */
    AND = '&',		/* and */
    OR = '|',		/* or */
    LPAREN = '(',	/* left paren */
    RPAREN = ')',	/* right paren */
    LBRACE = '{',	/* left brace */
    RBRACE = '}',	/* right brace */
    COMMA = ',',	/* comma */
    EOS = ';'		/* end of statement */
};

typedef struct {
    TokenType type;
    char value[MAXTOK];
} Token;

/////////////////////////////////////////////////////////////////////////////
class Compile {
public:
// Construction / Destruction
    Compile();
    ~Compile();

// Interface
    void compile(const char **);
protected:
// Implementation
    void compstmt();
    void expr(bool get = true);
    void compexpr(bool get = true);
    void shiftexpr(bool get = true);
    void addexpr(bool get = true);
    void multexpr(bool get = true);
    void prim(bool get = true);
    void plus();
    void minus();
    void unaryminus();
    void mult();
    void divide();
    void mod();
    void assign();
    void constant();
    void shiftleft();
    void shiftright();
    void whilecode();
    void ifcode();
    void printf();
    void string();
    void lt();
    void gt();
    void le();
    void ge();
    void not();
    void eq();
    void ne();
    void bitand();
    void bitor();
    void logand();
    void logor();
    void symbol();
    void funcdef();
    void procdef();
    void ret();
    void arg();
    int arglist();

    void kword(const Symbol *);
    void var(const Symbol *);
    void builtin(const Symbol *);
    void call(const Symbol *);
    void argassign(int);

    Token gettok(const char**);
    Token lookahead();
private:
    const char** ppin;	// address of input pointer
    Token token;		// current token
    bool indef;			// in a function / procedure definition
};
/////////////////////////////////////////////////////////////////////////////

#endif // __COMPILE_H__

