/*
 *	ASSEM.C : assembler
 *
 * 	Copyright (C) 2001 Thomas A. Rieck <trieck@bellsouth.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 */
#include "common.h"
#include "assem.h"
#include "opcodes.h"
#include "symbol.h"
#include "code.h"
#include "extern.h"

#define MAXLINE		1024
#define ISBYTE(x)	((x) < 0x100)
#define ISSTR(c)	(isalnum(c) || (c) == '_')

extern const char* infile; /* input file name */
extern SymbolTable table;  /* symbol table */
const char* pinput = NULL; /* pointer to current input */
Token token;               /* current token */
FILE* fpin = NULL;         /* input file pointer */
int lineno = 0;            /* current line number */

static void parse(void);
static void op(const Symbol*);
static int ismode(addrmode mode);
static int isword(const char** ppin);
static int isbyte(const char** ppin);
static int isacc(void);
static int isimm(void);
static int iszpg(void);
static int iszpx(void);
static int iszpy(void);
static int isabs(void);
static int isabx(void);
static int isaby(void);
static int isimp(void);
static int isrel(void);
static int isidx(void);
static int isidy(void);
static int isind(void);
static void base(void);
static void pseudo(void);
static void defbyte(void);
static void extrn(void);
static void escape(const char* in, char* out, size_t len);

/*
 * assemble input file
 */
void assemble(void)
{
    char line[MAXLINE];

    /* filename must end in .asm extension */
    size_t N = strlen(infile);
    if (strcmp(infile + N - 4, ".asm") != 0)
        error("file must end with .asm extension.\n");

    /* open the input file */
    fpin = fopen(infile, "r");
    if (fpin == NULL)
        error("unable to open file %s.\n", infile);

    for (lineno = 1; fgets(line, MAXLINE, fpin); lineno++) {
        pinput = line;
        parse();
    }

    fclose(fpin);

    fpin = NULL;

    /* resolve labels */
    resolve();
}

/*
 * parse the current line
 */
void parse(void)
{
    Symbol* psymbol;

    token = gettok(&pinput);

    while (token.value[0]) {
        switch (token.type) {
        case NUM:
        case STR:
            psymbol = symlookup(table, token.value);
            if (psymbol && psymbol->type == opcode) {
                op(psymbol);
            } else {
                error("unexpected token \"%s\""
                    " found at line %d.\n", token.value, lineno);
            }
            break;
        case BASE:
            base();
            break;
        case PSEUDO:
            pseudo();
            break;
        case SEMI: /* comment */
            return;
        case UNDEF:
            error("undefined token \"%s\" found at line %d.\n",
                  token.value, lineno);
            return;
        default:
            break;
        }
        token = gettok(&pinput);
    }
}

/*
 * determine current opcode and generate code
 */
void op(const Symbol* psym)
{
    /* compare the available modes with the current input */
    const Instr* instr = psym->u.instr;
    for (int mode = 0; mode < MODES; mode++) {
        const byte* opcode = (*instr)[mode];
        if (opcode && ismode(mode)) {
            code(mode, *opcode);
            return;
        }
    }

    error("invalid addressing mode found at line %d.\n", lineno);
}

/*
 * does the input match the specified mode
 */
int ismode(addrmode mode)
{
    switch (mode) {
    case acc:
        return isacc();
    case imm:
        return isimm();
    case zpg:
        return iszpg();
    case zpx:
        return iszpx();
    case zpy:
        return iszpy();
    case absl:
        return isabs();
    case abx:
        return isabx();
    case aby:
        return isaby();
    case imp:
        return isimp();
    case rel:
        return isrel();
    case idx:
        return isidx();
    case idy:
        return isidy();
    case ind:
        return isind();
    }

    return 0;
}

int isword(const char** ppin)
{
    Token tok = gettok(ppin);
    if (tok.type == NUM) {
        word operand;
        return sscanf(tok.value, "%hx", &operand) == 1;
    }

    return tok.type == STR; // label or kernal entry
}

int isbyte(const char** ppin)
{
    Token tok = gettok(ppin);
    if (tok.type == NUM) {
        word operand;
        return sscanf(tok.value, "%hx", &operand) == 1 && ISBYTE(operand);
    } if (tok.type == LT || tok.type == GT) {
        return isword(ppin);
    }

    return 0;
}

int isacc(void)
{
    Token tok = lookahead();
    return tok.value[0] == '\0' || tok.type == SEMI;
}

int isimm(void)
{
    const char* psave = pinput;

    Token tok1 = gettok(&psave);
    if (tok1.type != POUND) {
        return 0;
    }

    return isbyte(&psave);
}

int iszpg(void)
{
    const char* psave = pinput;
    if (!isbyte(&psave)) {
        return 0;
    }

    Token tok = gettok(&psave);
    if (tok.value[0] != '\0' && tok.type != SEMI) {
        return 0;
    }

    return 1;
}

int iszpx(void)
{
    const char* psave = pinput;

    if (!isbyte(&psave)) {
        return 0;
    }

    Token tok = gettok(&psave);
    if (tok.type != COMMA) {
        return 0;
    }

    tok = gettok(&psave);
    if (tok.value[0] != 'x' && tok.value[0] != 'X') {
        return 0;
    }

    return 1;
}

int iszpy(void)
{
    const char* psave = pinput;
    if (!isbyte(&psave)) {
        return 0;
    }

    Token tok = gettok(&psave);
    if (tok.type != COMMA) {
        return 0;
    }

    tok = gettok(&psave);
    if (tok.value[0] != 'y' && tok.value[0] != 'Y') {
        return 0;
    }

    return 1;
}

int isabs(void)
{
    const char* psave = pinput;

    if (!isword(&psave)) {
        return 0;
    }

    Token tok = gettok(&psave);

    return tok.value[0] == '\0' || tok.type == SEMI;
}

int isabx(void)
{
    const char* psave = pinput;

    if (!isword(&psave)) {
        return 0;
    }

    Token tok = gettok(&psave);
    if (tok.type != COMMA) {
        return 0;
    }

    tok = gettok(&psave);
    if (tok.value[0] != 'x' && tok.value[0] != 'X') {
        return 0;
    }

    return 1;
}

int isaby(void)
{
    const char* psave = pinput;

    if (!isword(&psave)) {
        return 0;
    }

    Token tok = gettok(&psave);
    if (tok.type != COMMA) {
        return 0;
    }

    tok = gettok(&psave);
    if (tok.value[0] != 'y' && tok.value[0] != 'Y') {
        return 0;
    }

    return 1;
}

int isind(void)
{
    const char* psave = pinput;

    Token tok = gettok(&psave);
    if (tok.type != LPAREN) {
        return 0;
    }

    if (!isword(&psave)) {
        return 0;
    }

    tok = gettok(&psave);
    if (tok.type != RPAREN)
        return 0;

    return 1;
}

int isimp(void)
{
    Token tok = lookahead();
    return tok.value[0] == '\0' || tok.type == SEMI;
}

int isrel(void)
{
    const char* psave = pinput;

    if (!isword(&psave)) {
        return 0;
    }

    return 1;
}

int isidx(void)
{
    const char* psave = pinput;

    Token tok = gettok(&psave);
    if (tok.type != LPAREN)
        return 0;

    if (!isbyte(&psave)) {
        return 0;
    }

    tok = gettok(&psave);
    if (tok.type != COMMA) {
        return 0;
    }

    tok = gettok(&psave);
    if (tok.value[0] != 'x' && tok.value[0] != 'X') {
        return 0;
    }

    tok = gettok(&psave);
    if (tok.type != RPAREN) {
        return 0;
    }

    return 1;
}

int isidy(void)
{
    const char* psave = pinput;

    Token tok = gettok(&psave);
    if (tok.type != LPAREN) {
        return 0;
    }

    if (!isbyte(&psave)) {
        return 0;
    }

    tok = gettok(&psave);
    if (tok.type != RPAREN) {
        return 0;
    }

    tok = gettok(&psave);
    if (tok.type != COMMA) {
        return 0;
    }

    tok = gettok(&psave);
    if (tok.value[0] != 'y' && tok.value[0] != 'Y') {
        return 0;
    }

    return 1;
}

void base(void)
{
    token = gettok(&pinput);
    if (token.type != EQUAL) {
        error("invalid base definition; expected '*= {ADDRESS}' at line %d.\n", lineno);
    }

    token = gettok(&pinput);
    if (token.type != NUM) {
        error("invalid base definition; expected '*= {ADDRESS}' at line %d.\n", lineno);
    }

    word base;
    sscanf(token.value, "%hx", &base);

    set_base(base);
}

void pseudo(void)
{
    token = gettok(&pinput);

    /* inline byte definitions */
    if (strcmp(token.value, "byte") == 0) {
        defbyte();
        return;
    }

    /* external function declarations */
    if (strcmp(token.value, "extern") == 0) {
        extrn();
        return;
    }

    /* don't allow the redefinition of labels */
    if (symlookup(table, token.value))
        error("redefinition of label \"%s\" encountered"
              " at line %d.\n", token.value, lineno);

    /* insert the label into the symbol table */
    linsert(table, token.value, getmem());
}

/*
 * assemble byte(s) inline
 */
void defbyte(void)
{
    byte b;
    char buffer[MAXTOK];
    const char* pbuffer = buffer;

    Token tok = lookahead();

    switch (tok.type) {
    case LITERAL: /* sequence of bytes */
        token = gettok(&pinput);
        escape(token.value, buffer, MAXTOK);
        while (*pbuffer)
            write_byte(*pbuffer++);
        break;
    case NUM: /* single numeric byte */
        token = gettok(&pinput);
        sscanf(token.value, "%hhx", &b);
        write_byte(b);
        break;
    case LT:
    case GT:
        b = get_byte(0);
        write_byte(b);
        break;
    default:
        error("expected numeric at byte definition"
              " at line %d.\n", lineno);
    }
}

/*
 * external function declarations
 */
void extrn(void)
{
    token = gettok(&pinput);
    for (;;) {
        if (token.type != STR) {
            error("expected string at extern declaration"
                  " at line %d.\n", token.value, lineno);
        }

        /* insert into external list */
        extern_insert(token.value);

        if (lookahead().type != COMMA)
            break;

        token = gettok(&pinput); /* ', ' */
        token = gettok(&pinput);
    }
}

Token lookahead(void)
{
    const char* dummy = pinput;
    return gettok(&dummy);
}

Token gettok(const char** ppin)
{
    Token tok;
    const char* pin = *ppin;

    memset(&tok, 0, sizeof(Token));

    for (;;) {
        switch (*pin) {
        case '\0':
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
            }
            return tok;
        case BASE:
        case COMMA:
        case EQUAL:
        case GT:
        case LPAREN:
        case LT:
        case POUND:
        case RPAREN:
        case SEMI:
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
                return tok;
            }
            tok.type = (TokenType)*pin;
            tok.value[0] = *(*ppin)++;
            return tok;
        case QUOTE:
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
                return tok;
            }
            pin++;
            (*ppin)++;

            while (*pin && *pin++ != QUOTE) {
            }

            strncpy(tok.value, *ppin, pin - *ppin - 1);
            *ppin = pin;
            tok.type = LITERAL;
            return tok;
        case PSEUDO:
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
                return tok;
            }
            tok.type = (TokenType)*pin;
            tok.value[0] = *(*ppin)++;
            return tok;
        case ' ': /* white space */
        case '\t':
        case '\r':
        case '\n':
            if (pin > *ppin) {
                strncpy(tok.value, *ppin, pin - *ppin);
                *ppin = pin;
                return tok;
            }
            (*ppin)++; /* eat white */
            break;
        case DOLLAR:
            if (isxdigit(*(pin + 1))) {
                pin++;
                (*ppin)++;
                while (isxdigit(*pin))
                    pin++;
                tok.type = NUM;
                continue;
            }
            tok.type = (TokenType)*pin;
            tok.value[0] = *(*ppin)++;
            return tok;
        default: {
            if (ISSTR(*pin)) {
                while (ISSTR(*pin))
                    pin++;
                tok.type = STR;
                continue;
            }
            tok.type = UNDEF;
            tok.value[0] = *(*ppin)++;
            return tok;
        }
        }
        pin++;
    }
}


/*
 * escape string literal
 * support for '\\', '\'', '\n', '\t', '\0'
 */
void escape(const char* in, char* out, size_t len)
{
    char* pout = out;
    for (; pout - out - len; in++) {
        switch (in[0]) {
        case '\0':
            *pout = '\0';
            return;
        case '\\':
            switch (in[1]) {
            case '\\':
                *pout++ = '\\';
                break;
            case '\'':
                *pout++ = '\'';
                break;
            case 'n':
                *pout++ = '\n';
                break;
            case 't':
                *pout++ = '\t';
                break;
            case '0':
                *pout++ = '\0';
                break;
            default:
                error("unrecognized escape sequence '%c' at line %d.\n",
                      in[1], lineno);
                break;
            }
            in++; /* skip escaped character */
            break;
        default:
            *pout++ = *in;
            break;
        }
    }
}
