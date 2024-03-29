/////////////////////////////////////////////////////////////////////////////
//
// COMPILE.CPP
//
// Compiles an expression into a program for a runtime
// machine.
//
// Copyright (c) 1999 Thomas A. Rieck
//

#include "common.h"
#include "compile.h"
#include "program.h"
#include "symbol.h"
#include "machine.h"

SymbolTable symbols;
Program program;	// compiled program

//
// Constructor
//
Compile::Compile()
{
    memset(&token, 0, sizeof(Token));
    ppin = NULL;
    indef = false;
}

//
// Destructor
//
Compile::~Compile()
{
}

//
// compile
//
void Compile::compile(const char ** pp)
{
    memset(&token, 0, sizeof(Token));
    ppin = pp;
    expr();
    program.code(STOP);
}

//
// compstmt
//
void Compile::compstmt()
{
    Token tok = lookahead();

    for (; tok.type != RBRACE; tok = lookahead()) {
        expr();
    }
}

//
// expr
//
void Compile::expr(bool get)
{
    compexpr(get);

    for (;;) {
        switch (token.type) {
        case AND:
            if (lookahead().type == AND) {
                token = gettok(ppin); // '&'
                logand();
            } else bitand();
            break;
        case OR:
            if (lookahead().type == OR) {
                token = gettok(ppin); // '|'
                logor();
            } else bitor();
            break;
        default:
            return;
        }
    }
}

//
// compexpr
//
void Compile::compexpr(bool get)
{
    shiftexpr(get);

    for (;;) {
        switch (token.type) {
        case EQUAL:	// ==
            prim();
            if (token.type == EQUAL)
                eq();
            break;
        case NOT:	// !=
            prim();
            if (token.type == EQUAL)
                ne();
            break;
        case LT:
            if (lookahead().type == EQUAL) {
                token = gettok(ppin);   // '='
                le();
            } else lt();
            break;
        case GT:
            if (lookahead().type == EQUAL) {
                token = gettok(ppin);   // '='
                ge();
            } else gt();
            break;
        default:
            return;
        }
    }
}

//
// shiftexpr
//
void Compile::shiftexpr(bool get)
{
    addexpr(get);

    for (;;) {
        switch (token.type) {
        case LT:
            if (lookahead().type == LT) {
                token = gettok(ppin);   // '<'
                shiftleft();
            } else return;
            break;
        case GT:
            if (lookahead().type == GT) {
                token = gettok(ppin);   // '>'
                shiftright();
            } else return;
            break;
        default:
            return;
        }
    }
}

//
// addexpr
//
void Compile::addexpr(bool get)
{
    multexpr(get);

    for (;;) {
        switch (token.type) {
        case PLUS:
            plus();
            break;
        case MINUS:
            minus();
            break;
        default:
            return;
        }
    }
}

//
// multexpr
//
void Compile::multexpr(bool get)
{
    prim(get);

    for (;;) {
        switch (token.type) {
        case MULT:
            mult();
            break;
        case DIV:
            divide();
            break;
        case MOD:
            mod();
            break;
        default:
            return;
        }
    }
}

//
// prim
//
void Compile::prim(bool get)
{
    if (get) token = gettok(ppin);

    switch (token.type) {
    case SYMBOL:
        symbol();
        break;
    case NUM:
        constant();
        token = gettok(ppin);
        break;
    case LPAREN:
        arglist();
        token = gettok(ppin);   // eat ')'
        break;
    case LBRACE:
        compstmt();
        token = gettok(ppin);
        break;
    case MINUS:
        unaryminus();
        break;
    case NOT:
        not();
        break;
    case STR:
        string();
        token = gettok(ppin);
        break;
    case ARG:
        arg();
        break;
    default:
        return;
    }
}

//
// gettok
//
Token Compile::gettok(const char** ppin)
{
    Token tok;
    memset(&tok, 0, sizeof(Token));

    const char* pin = *ppin;

    for (;;) {
        switch (*pin) {
        case '\0':
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
            }
            return tok;
        case PLUS:
        case MINUS:
        case MULT:
        case DIV:
        case MOD:
        case EQUAL:
        case NOT:
        case LPAREN:
        case RPAREN:
        case LBRACE:
        case RBRACE:
        case EOS:
        case COMMA:
        case LT:
        case GT:
        case AND:
        case OR:
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
                return tok;
            }
            tok.type = TokenType(*pin);
            *tok.value = *(*ppin)++;
            return tok;
        case ' ':		// white space
        case '\t':
        case '\r':
        case '\n':
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
                return tok;
            }
            (*ppin)++; // eat white
            break;
        case '"':		// string literal
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
                return tok;
            }
            pin++;
            (*ppin)++;
            while (*pin && *pin++ != '"')
                ;
            strncpy(tok.value, *ppin, pin - *ppin - 1);
            *ppin = pin;
            tok.type = STR;
            return tok;
        case ARG:		// argument
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
                return tok;
            }
            pin++;
            (*ppin)++;
            while (isdigit(*pin))
                pin++;
            strncpy(tok.value, *ppin, pin - *ppin);
            *ppin = pin;
            tok.type = ARG;
            return tok;
        default:
            if (isdigit(*pin) || *pin == '.') {
                while (isdigit(*pin) || *pin == '.')
                    pin++;
                tok.type = NUM;
                continue;
            } else if (isalnum(*pin)) {
                while (isalnum(*pin))
                    pin++;
                tok.type = SYMBOL;
                continue;
            }
        }
        pin++;
    }

    return tok; // can't happen
}

//
// lookahead
//
Token Compile::lookahead()
{
    const char * dummy = *ppin;
    return gettok(&dummy);
}

//
// lt
//
void Compile::lt()
{
    shiftexpr();
    program.code(&Machine::lt);
}

//
// gt
//
void Compile::gt()
{
    shiftexpr();
    program.code(&Machine::gt);
}

//
// le
//
void Compile::le()
{
    shiftexpr();
    program.code(&Machine::le);
}

//
// ge
//
void Compile::ge()
{
    shiftexpr();
    program.code(&Machine::ge);
}

//
// eq
//
void Compile::eq()
{
    shiftexpr();
    program.code(&Machine::eq);
}

//
// ne
//
void Compile::ne()
{
    shiftexpr();
    program.code(&Machine::ne);
}

//
// bitand
//
void Compile::bitand()
{
    compexpr();
    program.code(&Machine::bitand);
}

//
// logand
//
void Compile::logand()
{
    compexpr();
    program.code(&Machine::logand);
}

//
// bitor
//
void Compile::bitor()
{
    compexpr();
    program.code(&Machine::bitor);
}

//
// logor
//
void Compile::logor()
{
    compexpr();
    program.code(&Machine::logor);
}

//
// shiftleft
//
void Compile::shiftleft()
{
    addexpr();
    program.code(&Machine::shiftleft);
}

//
// shiftright
//
void Compile::shiftright()
{
    addexpr();
    program.code(&Machine::shiftright);
}

//
// plus
//
void Compile::plus()
{
    multexpr();
    program.code(&Machine::plus);
}

//
// minus
//
void Compile::minus()
{
    multexpr();
    program.code(&Machine::minus);
}

//
// unaryminus
//
void Compile::unaryminus()
{
    prim();
    program.code(&Machine::unaryminus);
}

//
// mult
//
void Compile::mult()
{
    prim();
    program.code(&Machine::mult);
}

//
// divide
//
void Compile::divide()
{
    prim();
    program.code(&Machine::divide);
}

//
// mod
//
void Compile::mod()
{
    prim();
    program.code(&Machine::mod);
}

//
// assign
//
void Compile::assign()
{
    expr();
    program.code(&Machine::assign);
    program.code(&Machine::pop);
}

//
// argassign
//
void Compile::argassign(int narg)
{
    expr();
    program.code(&Machine::argassign);
    program.code(*(Instr *)&narg);
    program.code(&Machine::pop);
}

//
// var
//
void Compile::var(const Symbol * psymbol)
{
    if (psymbol == NULL)
        psymbol = symbols.install(token.value, undefined, 0.00);

    program.code(&Machine::varpush);
    program.code(psymbol);

    token = gettok(ppin);
    if (token.type == EQUAL && lookahead().type != EQUAL) // assignment
        assign();
    else program.code(&Machine::eval);
}

//
// builtin
//
void Compile::builtin(const Symbol * psymbol)
{
    prim();
    program.code(psymbol->instruction);
}

//
// constant
//
void Compile::constant()
{
    const Symbol* psymbol = symbols.install(token.value,
                                            number,
                                            atof(token.value));

    program.code(&Machine::constpush);
    program.code(psymbol);
}

//
// whilecode
//
void Compile::whilecode()
{
    program.code(&Machine::whilecode);

    // reserve spots for pointers to loop body
    // and next statement
    const Instr * loopbody = program++;
    const Instr * next = program++;

    expr();         // condition
    program.code(STOP);

    // assign the current memory pointer
    // to the space allocated for the loop body
    program.setjumpat(loopbody);

    expr(false);     // loop body
    program.code(STOP);

    // assign the current memory pointer
    // to the space allocated for the next statement
    program.setjumpat(next);
}

//
// ifcode
//
void Compile::ifcode()
{
    program.code(&Machine::ifcode);

    // reserve spots for pointers to then, else
    // and next statement
    const Instr * then = program++;
    const Instr * pelse = program++;
    const Instr * next = program++;

    expr();         // condition
    program.code(STOP);

    // assign the current memory pointer
    // to the space allocated for the then statement
    program.setjumpat(then);

    expr(false);     // then statement
    program.code(STOP);

    // else
    if (strcmp(lookahead().value, "else") == 0) {
        program.setjumpat(pelse);
        expr();
        program.code(STOP);
    } else program.set(pelse, STOP);

    // assign the current memory pointer
    // to the space allocated for the next statement
    program.setjumpat(next);
}

//
// not
//
void Compile::not()
{
    prim();
    program.code(&Machine::not);
}

//
// printf
//
void Compile::printf()
{
    token = gettok(ppin);	// '('
    int nargs = arglist();
    token = gettok(ppin);	// eat ')'
    program.code(&Machine::printf);
    program.code(*(Instr *)&nargs);
}

//
// string
//
void Compile::string()
{
    const Symbol * psymbol = symbols.install(token.value, token.value);
    program.code(&Machine::strpush);
    program.code(psymbol);
}

//
// symbol
//
void Compile::symbol()
{
    const Symbol * psymbol = symbols.lookup(token.value);
    if (psymbol && psymbol->type == bltin)
        builtin(psymbol);
    else if (psymbol && psymbol->type == keyword)
        kword(psymbol);
    else if (psymbol && (psymbol->type == function ||
                         psymbol->type == procedure))
        call(psymbol);
    else var(psymbol);
}

//
// kword
//
void Compile::kword(const Symbol * psymbol)
{
    switch (psymbol->keyword) {
    case FUNC:
        funcdef();
        break;
    case PROC:
        procdef();
        break;
    case RETURN:
        ret();
        break;
    case WHILE:
        whilecode();
        break;
    case IF:
        ifcode();
        break;
    case ELSE:
        expr();
        break;
    case PRINTF:
        printf();
        break;
    default:
        break;
    };
}

//
// funcdef
//
void Compile::funcdef()
{
    char name[MAXTOK];

    indef = true;
    token = gettok(ppin);	// function name
    strcpy(name, token.value);

    // insert the function in the symbol table
    // this is needed for recursion to work
    symbols.install(name, function, (Instr *)NULL);

    token = gettok(ppin);	// '('
    token = gettok(ppin);	// ')'
    expr();					// function body
    program.code(&Machine::procret);
    program.define(name, function);
    indef = false;
}

//
// procdef
//
void Compile::procdef()
{
    char name[MAXTOK];

    indef = true;
    token = gettok(ppin);	// procedure name
    strcpy(name, token.value);

    // insert the procedure in the symbol table
    // this is needed for recursion to work
    symbols.install(name, procedure, (Instr *)NULL);

    token = gettok(ppin);	// '('
    token = gettok(ppin);	// ')'
    expr();					// procedure body
    program.code(&Machine::procret);
    program.define(name, procedure);
    indef = false;
}

//
// call
//
void Compile::call(const Symbol * psymbol)
{
    token = gettok(ppin);	// '('
    int nargs = arglist();
    token = gettok(ppin);	// eat ')'
    program.code(&Machine::call);
    program.code(psymbol);
    program.code(*(Instr *)&nargs);
}

//
// ret
//
void Compile::ret()
{
    if (lookahead().type != EOS) {
        expr();
        program.code(&Machine::funcret);
    } else program.code(&Machine::procret);
}

//
// arg
//
void Compile::arg()
{
    int arg = atoi(token.value);

    token = gettok(ppin);
    if (token.type == EQUAL && lookahead().type != EQUAL) {
        argassign(arg);
    } else {
        program.code(&Machine::arg);
        program.code(*(Instr*)&arg);
    }
}

//
// arglist
//
int Compile::arglist()
{
    int nargs = 0;

    if (lookahead().type == RPAREN)
        expr();

    for (; token.type != EOS && token.type != RPAREN; nargs++) {
        expr();
    }

    return nargs;
}



