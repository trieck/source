/*
 * GLOBAL.C
 *
 * Global symbols
 *
 * Pixie Language
 * Copyright(c) 2002, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#include <stdlib.h>
#include "pixie.h"
#include "global.h"
#include "symbol.h"
#include "tree.h"
#include "parse.h"
#include "memcheck.h"

static SymbolTable symbols;		/* global symbols */

/* keywords */
static struct {
    const char *name;
    int kval;
} keywords[] = {
    {
        "print", PRINT
    }, {
        "println", PRINTLN
    }, {
        "length", LENGTH
    }, {
        "shift", SHIFT
    }, {
        "unshift", UNSHIFT
    }, {
        "push", PUSH
    }, {
        "pop", POP
    }, {
        "while", WHILE
    }, {
        "if", IF
    }, {
        "else", ELSE
    }, {
        "var", VAR
    }, {
        "def", DEF
    }, {
        "return", RETURN
    }, {
        "break", BREAK
    }, {
        "continue", CONTINUE
    }, {
        "foreach", FOREACH
    }, {
        "in", IN
    }, {
        "strlen", STRLEN
    }, {
        "substr", SUBSTR
    }, {
        "strcat", STRCAT
    }, {
        "index", INDEX
    }, {
        "asc", ASC
    }, {
        "chr", CHR
    }, {
        0, 0
    }
};

/* built-ins */
static struct {
    const char *name;
    int val;
} bltins[] = {
    {
        "sin", SIN
    }, {
        "cos", COS
    }, {
        "atan", ATAN
    }, {
        "log", LOG
    }, {
        "log10", LOG10
    }, {
        "sqrt", SQRT
    }, {
        "int", INT
    }, {
        "abs", ABS
    }, {
        0, 0
    }
};

static void globfree(void);

/* allocate and initialize global symbol table */
void globinit(void)
{
    int i;

    mcatexit(globfree);
    symbols = maketab();

    /* install keywords */
    for (i = 0; keywords[i].name; i++)
        install(symbols, keywords[i].name, SKEYWD, keywords[i].kval, 0);

    /* install built-ins */
    for (i = 0; bltins[i].name; i++)
        install(symbols, bltins[i].name, SBLTIN, bltins[i].val, 0);

    /* install global "special" variables */
    install(symbols, "argv", SVAR, SARRAY, 0);
}

/* lookup s in symbol table */
Symbol *glookup(const char *s)
{
    return lookup(symbols, s);
}

/* install s in symbol table */
Symbol *ginstall(const char *s, int t, int sub, double d)
{
    return install(symbols, s, t, sub, d);
}

/* install string s in symbol table */
Symbol *ginstalls(const char *s, const char *v)
{
    return installs(symbols, s, v);
}

/* free global symbol table */
void globfree(void)
{
    tabfree(symbols);
    symbols = 0;
}
