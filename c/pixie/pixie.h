/*
 * PIXIE.H
 *
 * Pixie Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#ifndef __PIXIE_H__
#define __PIXIE_H__

/* float buffer size */
#define FBSIZE 50

/* node types */
#define NUNDEF 	0
#define NSTMT	1
#define NVALUE	2

/* node in the parse tree */
typedef struct Node {
    int type;					/* NUNDEF|NSTMT|NVALUE */
    int lineno;					/* line number during parsing */
    int nobj;
    int nargs;					/* number of children */
    struct Node *next;			/* next node if chained */
    struct Node *args[1];		/* variable size for child nodes */
} Node;

/* symbol types */
#define SUNDEF	0
#define SCONST	1
#define SVAR	2
#define SFUNC	3
#define SKEYWD	4
#define SBLTIN	5

/* symbol subtypes */
#define	SFLOAT	1
#define	SSTRING	2
#define SARRAY	4
#define STEMP	8

struct Symbol;

/* array of symbols */
typedef struct {
    struct Symbol **v;			/* vector of symbols */
    unsigned size;				/* size of array in elements */
    unsigned alloced;			/* allocated size */
} Array;

/* all information about a variable or constant */
typedef struct Symbol {
    int type;					/* SUNDEF|SCONST|SVAR|SFUNC, etc. */
    int sub;					/* SFLOAT|SSTRING|SARRAY, etc. */
    char *name;					/* name for variable / function */
    union {
        char *sval;				/* string value */
        double fval;			/* floating point value */
        Array *aval;			/* array value */
        struct Node *defn;		/* function definition */
    } u;
    struct Symbol *next;		/* next symbol */
} Symbol;

#undef ASSERT
#ifdef _DEBUG
void AssertMessage(const char *msg, const char *file, int line);
#define ASSERT(f) { if (!(f)) AssertMessage(#f, __FILE__, __LINE__); }
#else
#define ASSERT(f) ((void)0)
#endif

void dprint(const char *, ...);
void error(const char *, ...);
void pixie_init(int, char **);
void pixie_run(void);
Symbol *symcopy(Symbol *);
void symfree(Symbol *);
char *xstrdup(const char *);

#define isvar(s)	(s->type == SVAR)
#define isarray(s)	(s->sub & SARRAY)
#define isstring(s)	(s->sub & SSTRING)
#define istemp(s)	(s->sub & STEMP)

#endif							/* __PIXIE_H__ */
