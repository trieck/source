/*
 * TREE.C
 *
 * Parse tree construction
 *
 * 'X' Programming Language
 * Copyright (c) 2004, Thomas A. Rieck
 * All Rights Reserved
 */

#include <stdlib.h>
#include "symbol.h"
#include "tree.h"
#include "xmalloc.h"

static PNODE nodealloc(int n);
static void nodefree(PNODE N);
static void cleanup(void);

extern int lineno;
PNODE root = 0;

/* initialize tree */
void treeinit(void)
{
    atexit(cleanup);
}

void cleanup(void)
{
    nodefree(root);
}

/* allocate a node */
PNODE nodealloc(int n)
{
    PNODE N = (PNODE) xmalloc(sizeof(Node) + ((n - 1) * sizeof(PNODE)));
    N->type = NUNDEF;
    N->lineno = lineno;
    N->nobj = 0;
    N->nargs = n;
    N->next = 0;
    return N;
}

/* free a node */
void nodefree(PNODE N)
{
    int i;

    while (N) {
        PNODE next = N->next;

        /* free children */
        for (i = 0; N->type != NATOMIC && i < N->nargs; i++) {
            nodefree(N->args[i]);
        }

        xfree(N);
        N = next;
    }
}

/* make a leaf node */
PNODE mkleaf(PSYMBOL sym)
{
    PNODE N = nodealloc(1);
    N->args[0] = (PNODE) sym;
    N->type = NATOMIC;
    return N;
}

/* make a statemt node */
PNODE mkstmt(int id, PNODE args)
{
    PNODE N = nodealloc(1);
    N->nobj = id;
    N->type = NSTMT;
    N->args[0] = args;
    return N;
}

/* make a statement node */
PNODE mkstmt2(int id, PNODE args, PNODE name)
{
    PNODE N = nodealloc(2);
    N->nobj = id;
    N->type = NSTMT;
    N->args[0] = args;
    N->args[1] = name;
    return N;
}

/* link nodes */
PNODE lknodes(PNODE n1, PNODE n2)
{
    PNODE p;

    if (n1 == 0)
        return n2;

    if (n2 == 0)
        return n1;

    /* put at end of list */
    for (p = n1; p->next; p = p->next);

    p->next = n2;

    return n1;
}
