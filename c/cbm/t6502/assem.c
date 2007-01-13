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
#define ISZADDR(x)	(x < 0x100)
#define ISSTR(c)	(isalpha(c) || c == '_')
extern const char *infile;		/* input file name */
extern SymbolTable table;		/* symbol table */
const char *pinput = NULL;		/* pointer to current input */
Token token;					/* current token */
FILE *fpin = NULL;				/* input file pointer */
int lineno = 0;					/* current line number */
static void parse(void);
static Token lookahead(void);
static void op(const Symbol *);
static int ismode(addrmode mode);
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
static void pseudo(void);
static void defbyte(void);
static void extrn(void);
static void escape(const char *in, char *out, size_t len);
/* 
 * assemble input file
 */
void assemble()
{
	char line[MAXLINE];
	size_t N;
	/* filename must end in .asm extension */
	N = strlen(infile);
	if (strcmp(infile + N - 4, ".asm"))
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
	Symbol *psymbol;
	token = gettok(&pinput);
	while (token.value[0]) {
		switch (token.type) {
		case NUM:
		case STR:
			psymbol = symlookup(table, token.value);
			if (psymbol && psymbol->type == opcode)
				op(psymbol);
			else
				error("unexpected token \"%s\""
					  " found at line %d.\n", token.value, lineno);
			break;
		case PSEUDO:
			pseudo();
			break;
		case SEMI:				/* comment */
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
void op(const Symbol * psym)
{
	/* compare the available modes with the current input */
	const Instr *instr = psym->u.instr;
	int mode;
	for (mode = 0; mode < MODES; mode++) {
		const byte *opcode = (*instr)[mode];
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
int isacc(void)
{
	Token tok = lookahead();
	return tok.value[0] == '\0' || tok.type == SEMI;
}
int isimm(void)
{
	word operand;
	Token tok1, tok2;
	const char *psave = pinput;
	tok1 = gettok(&psave);
	tok2 = gettok(&psave);
	if (tok1.type != POUND)
		return 0;
	return sscanf(tok2.value, "%hx", &operand) == 1 && ISZADDR(operand);
}
int iszpg(void)
{
	word operand;
	const char *psave = pinput;
	Token tok;
	tok = gettok(&psave);
	if (tok.type != NUM)
		return 0;
	sscanf(tok.value, "%hx", &operand);

	tok = gettok(&psave);
	if (tok.value[0] != '\0' && tok.type != SEMI)
		return 0;
	return ISZADDR(operand);
}
int iszpx(void)
{
	word operand;
	const char *psave = pinput;
	Token tok;
	tok = gettok(&psave);
	if (tok.type != NUM)
		return 0;
	sscanf(tok.value, "%hx", &operand);

	tok = gettok(&psave);
	if (tok.type != COMMA)
		return 0;
	tok = gettok(&psave);
	if (tok.value[0] != 'x' && tok.value[0] != 'X')
		return 0;
	return ISZADDR(operand);
}
int iszpy(void)
{
	word operand;
	const char *psave = pinput;
	Token tok;
	tok = gettok(&psave);
	if (tok.type != NUM)
		return 0;
	sscanf(tok.value, "%hx", &operand);

	tok = gettok(&psave);
	if (tok.type != COMMA)
		return 0;
	tok = gettok(&psave);
	if (tok.value[0] != 'y' && tok.value[0] != 'Y')
		return 0;
	return ISZADDR(operand);
}
int isabs(void)
{
	word operand;
	const char *psave = pinput;
	Token tok;
	tok = gettok(&psave);
	switch (tok.type) {
	case NUM:					/* absolute address */
		sscanf(tok.value, "%hx", &operand);
		if (ISZADDR(operand))
			return 0;
		break;
	case PSEUDO:				/* label */
		tok = gettok(&psave);
		break;
	case STR:					/* kernel jump table entry */
		break;
	default:
		return 0;
	}
	tok = gettok(&psave);
	return tok.value[0] == '\0' || tok.type == SEMI;
}
int isabx(void)
{
	word operand;
	const char *psave = pinput;
	Token tok;
	tok = gettok(&psave);
	if (tok.type != NUM && tok.type != PSEUDO)
		return 0;
	if (tok.type == NUM) {
		sscanf(tok.value, "%hx", &operand);
		if (ISZADDR(operand))
			return 0;
	} else
		tok = gettok(&psave);

	tok = gettok(&psave);
	if (tok.type != COMMA)
		return 0;
	tok = gettok(&psave);
	if (tok.value[0] != 'x' && tok.value[0] != 'X')
		return 0;
	return 1;
}
int isaby(void)
{
	word operand;
	const char *psave = pinput;
	Token tok;
	tok = gettok(&psave);
	if (tok.type != NUM && tok.type != PSEUDO)
		return 0;
	if (tok.type == NUM) {
		sscanf(tok.value, "%hx", &operand);
		if (ISZADDR(operand))
			return 0;
	} else
		tok = gettok(&psave);

	tok = gettok(&psave);
	if (tok.type != COMMA)
		return 0;
	tok = gettok(&psave);
	if (tok.value[0] != 'y' && tok.value[0] != 'Y')
		return 0;
	return 1;
}
int isind(void)
{
	Token tok;
	word operand;
	const char *psave = pinput;
	tok = gettok(&psave);
	if (tok.type != LPAREN)
		return 0;
	tok = gettok(&psave);
	if (tok.type != PSEUDO && tok.type != NUM)
		return 0;
	if (tok.type == NUM) {
		sscanf(tok.value, "%hx", &operand);
		if (ISZADDR(operand))
			return 0;
	} else
		tok = gettok(&psave);
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
	word operand;
	const char *psave = pinput;
	Token tok;
	tok = gettok(&psave);
	if (tok.type != NUM && tok.type != PSEUDO)
		return 0;
	if (tok.type == NUM) {
		sscanf(tok.value, "%hx", &operand);
		if (ISZADDR(operand))
			return 0;
	}
	return 1;
}
int isidx(void)
{
	Token tok;
	word operand;
	const char *psave = pinput;

	tok = gettok(&psave);
	if (tok.type != LPAREN)
		return 0;

	tok = gettok(&psave);
	if (tok.type != NUM)
		return 0;
	sscanf(tok.value, "%hx", &operand);

	tok = gettok(&psave);
	if (tok.type != COMMA)
		return 0;
	tok = gettok(&psave);
	if (tok.value[0] != 'x' && tok.value[0] != 'X')
		return 0;
	tok = gettok(&psave);
	if (tok.type != RPAREN)
		return 0;
	return ISZADDR(operand);
}
int isidy(void)
{
	Token tok;
	word operand;
	const char *psave = pinput;
	tok = gettok(&psave);
	if (tok.type != LPAREN)
		return 0;

	tok = gettok(&psave);
	if (tok.type != NUM)
		return 0;
	sscanf(tok.value, "%hx", &operand);
	tok = gettok(&psave);
	if (tok.type != RPAREN)
		return 0;
	tok = gettok(&psave);
	if (tok.type != COMMA)
		return 0;
	tok = gettok(&psave);
	if (tok.value[0] != 'y' && tok.value[0] != 'Y')
		return 0;

	return ISZADDR(operand);
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
	unsigned short operand;
	char buffer[MAXTOK];
	const char *pbuffer = buffer;
	token = gettok(&pinput);
	switch (token.type) {
	case LITERAL:				/* sequence of bytes */
		escape(token.value, buffer, MAXTOK);
		while (*pbuffer)
			write_byte(*pbuffer++);
		break;
	case NUM:					/* single numeric byte */
		sscanf(token.value, "%hx", &operand);
		write_byte((unsigned char) operand);
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

		token = gettok(&pinput);	/* ', ' */
		token = gettok(&pinput);
	}
}
Token lookahead(void)
{
	const char *dummy = pinput;
	return gettok(&dummy);
}

Token gettok(const char **ppin)
{
	Token tok;
	const char *pin = *ppin;
	memset(&tok, 0, sizeof(Token));
	for (;;) {
		switch (*pin) {
		case '\0':
			if (pin > *ppin) {
				strncpy(tok.value, *ppin, pin - *ppin);
				*ppin = pin;
			}
			return tok;
		case LPAREN:
		case RPAREN:
		case COMMA:
		case POUND:
		case SEMI:
			if (pin > *ppin) {
				strncpy(tok.value, *ppin, pin - *ppin);
				*ppin = pin;
				return tok;
			}
			tok.type = *pin;
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
			while (*pin && *pin++ != QUOTE);
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
			tok.type = *pin;
			tok.value[0] = *(*ppin)++;
			return tok;
		case ' ':				/* white space */
		case '\t':
		case '\r':
		case '\n':
			if (pin > *ppin) {
				strncpy(tok.value, *ppin, pin - *ppin);
				*ppin = pin;
				return tok;
			}
			(*ppin)++;			/* eat white */
			break;
		default:
			if (isxdigit(*pin)) {
				while (isxdigit(*pin))
					pin++;
				tok.type = NUM;
				continue;
			} else if (ISSTR(*pin)) {
				while (ISSTR(*pin))
					pin++;
				tok.type = STR;
				continue;
			} else {
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
void escape(const char *in, char *out, size_t len)
{
	char *pout = out;
	for (; (pout - out) - len; in++) {
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
			in++;				/* skip escaped character */
			break;
		default:
			*pout++ = *in;
			break;
		}
	}
}
