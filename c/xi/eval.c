/*
 * EVAL.C
 *
 * Evaluate parse tree
 *
 * 'X' Programming Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#include <stdlib.h>
#include <stdio.h>
#include "symbol.h"
#include "tree.h"
#include "eval.h"
#include "x.h"
#include "parser.h"
#include "proctab.h"
#include "list.h"
#include "xmalloc.h"
#include "block.h"

#define tempfree(t)	if (t && (t->subtype & STEMP)) symfree(t)

#define CHECKARGS(n, x, y)											\
	do {															\
		if (n->nargs != x) {										\
			error("wrong number of arguments to %s near line %d.", 	\
				y, n->lineno);										\
		}															\
	} while (0)

static PSYMBOL evalnode(PNODE);
static PSYMBOL evalstmt(PNODE);
static PSYMBOL evalatomic(PNODE);
static PSYMBOL mktlist(void);
static PSYMBOL maketemp(void);
static PSYMBOL map(PNODE N);
static double floatval(PNODE);
static double symfloatval(PSYMBOL sym);
static void printsym(PSYMBOL sym);

static Symbol empty = { "", SCONST | SFLOAT, {0}, NULL };
static PSYMBOL EMPTY = &empty;

extern PNODE root;

/* evaluate parse tree */
void eval(void)
{
	PSYMBOL t = evalnode(root);
	tempfree(t);
}

/* evaluate node in parse tree */
PSYMBOL evalnode(PNODE N)
{
	if (N == NULL)
		return EMPTY;

	switch (N->type) {
	case NSTMT:
		return evalstmt(N);
	case NATOMIC:
		return evalatomic(N);
	default:
		error("unknown parse node type %d near line %d.",
		      N->type, N->lineno);
	}

	return EMPTY;
}

/* evaluate statement node */
PSYMBOL evalstmt(PNODE N)
{
	int index = N->nobj - FIRSTTOKEN - 1;
	ASSERT(index >= 0 && index < (LASTTOKEN - FIRSTTOKEN - 1));
	return (*proctab[index]) (N);
}

/* evaluate atomic node */
PSYMBOL evalatomic(PNODE N)
{
	PSYMBOL s, t;

	CHECKARGS(N, 1, "evalatomic");
	ASSERT(N->type == NATOMIC);

	s = (PSYMBOL) N->args[0];
	switch (s->type) {
	case SCONST:
		t = s;
		break;
	case SVAR:
		t = map(N);
		break;
	case SUNDEF:
		error("\"%s\" undefined near line %d.", s->name, N->lineno);
	default:
		error("unknown symbol type %d near line %d.", s->type, N->lineno);
	}

	return t;
}

/* arith:  arithmetic expression */
PSYMBOL arith(PNODE N)
{
	PSYMBOL t, a, total;
	PLISTNODE n;

	CHECKARGS(N, 1, "arith");

	a = evalnode(N->args[0]);
	t = mktlist();
	total = maketemp();

	if (a->u.lval->size > 0) {	/* non empty */
		n = a->u.lval->head;
		total->u.fval = symfloatval(n->sym);
		switch (N->nobj) {
		case PLUS:
			for (n = n->next; n; n = n->next) {
				total->u.fval += symfloatval(n->sym);
			}
			break;
		case SUB:
			for (n = n->next; n; n = n->next) {
				total->u.fval -= symfloatval(n->sym);
			}
			break;
		case MULT:
			for (n = n->next; n; n = n->next) {
				total->u.fval *= symfloatval(n->sym);
			}
			break;
		case DIV:
			for (n = n->next; n; n = n->next) {
				double d = symfloatval(n->sym);
				if ((int) d == 0)
					error("division by zero near line %d.", N->lineno);
				total->u.fval /= d;
			}
			break;
		case MOD:
			for (n = n->next; n; n = n->next) {
				double d = symfloatval(n->sym);
				if ((int) d == 0)
					error("modulo division by zero near line %d.",
					      N->lineno);
				total->u.fval = (int) total->u.fval % (int) d;
			}
			break;
		default:
			error("unknown arithmetic procedure [%d] near line %d.",
			      N->nobj, N->lineno);
		}
	}

	listadd_head(t->u.lval, total);

	tempfree(a);
	tempfree(total);

	return t;
}

/* make a range */
PSYMBOL range(PNODE N)
{
	CHECKARGS(N, 1, "range");
	ASSERT(0);
	return NULL;
}

/* make a list, ie. code block */
PSYMBOL mklist(PNODE N)
{
	PSYMBOL t, l;
	PNODE p;

	CHECKARGS(N, 1, "mklist");
	l = mktlist();

	blockenter();

	for (p = N->args[0]; p; p = p->next) {
		t = evalnode(p);
		listadd_tail(l->u.lval, t);
		tempfree(t);
	}

	blockleave();

	return l;
}

/* print a node in parse tree */
PSYMBOL print(PNODE N)
{
	PSYMBOL a, l;

	CHECKARGS(N, 1, "print");

	l = mktlist();
	a = evalnode(N->args[0]);
	printsym(a);
	tempfree(a);
	return l;
}

/* print a node in parse tree with newline */
PSYMBOL println(PNODE N)
{
	PSYMBOL a = print(N);
	putchar('\n');
	return a;
}

/* variable assignment */
PSYMBOL let(PNODE N)
{
	int i;
	PNODE p;
	PLISTNODE n;
	PSYMBOL a, t, l;
	CHECKARGS(N, 1, "let");

	l = mktlist();

	/* pre-evaluation for implicit declaration */
	for (i = 0, p = N->args[0]->args[0]; p; p = p->next, i++) {
		if (i % 2 == 0) {
			if (p->type != NATOMIC)
				error("'let' expects pairs of the form (id expr) near line %d.",
				      N->lineno);
			t = (PSYMBOL)p->args[0];
			if (t->type != SVAR && t->type != SUNDEF)
				error("'let' expects pairs of the form (id expr) near line %d.",
				      N->lineno);
			if (t->type == SUNDEF)
				binstall(t->name, t->type = SVAR, SFLOAT, 0);
		}
	}

	if (i == 0 || i % 2 != 0)
		error("'let' expects pairs of the form (id expr) near line %d.",
		      N->lineno);

	a = evalnode(N->args[0]);

	/* assignment */
	for (i = 0, n = a->u.lval->head; n; n = n->next) {
		if (i % 2 == 0) {
			symdup(n->sym, n->next->sym);
			if (i == a->u.lval->size - 2)
				listadd_tail(l->u.lval, n->sym);
			n = n->next;
		}
	}

	tempfree(a);

	return l;
}

/* helper functions */

/* translate parser symbol into block scoped symbol */
PSYMBOL map(PNODE N)
{
	PSYMBOL s, org;

	CHECKARGS(N, 1, "map");
	ASSERT(N->type & NATOMIC);

	org = (PSYMBOL) N->args[0];
	if ((s = blookup(org->name)) == 0)
		error("%s undefined near line %d.", org->name, N->lineno);

	if (s->type == SUNDEF)
		error("%s undefined near line %d.", s->name, N->lineno);

	return s;
}

/* print symbol */
void printsym(PSYMBOL sym)
{
	if (sym->subtype & SFLOAT) {
		printf("%.8f", sym->u.fval);
	} else if (sym->subtype & SSTRING) {
		printf("%s", sym->u.sval);
	} else if (sym->subtype & SLIST) {
		if (sym->u.lval->size == 0) {
			printf("[]");
		} else if (sym->u.lval->size == 1) {
			PLISTNODE n = sym->u.lval->head;
			printsym(n->sym);
		} else {
			PLISTNODE n = sym->u.lval->head;
			printf("[ ");
			for (; n; n = n->next) {
				if (n != sym->u.lval->head)
					printf(" ");
				printsym(n->sym);
			}
			printf(" ]");
		}
	}
}

/* coerce node to a numeric representation */
double floatval(PNODE N)
{
	PSYMBOL sym;
	double d = 0;

	sym = evalnode(N);
	d = symfloatval(sym);
	tempfree(sym);

	return d;
}

/* coerce symbol to a numeric representation */
double symfloatval(PSYMBOL sym)
{
	double d = 0;

	if (sym->subtype & SFLOAT) {
		d = sym->u.fval;
	} else if (sym->subtype & SSTRING) {
		d = atof(sym->u.sval);
	} else if (sym->subtype & SLIST) {
		/*
		 * The symfloatval of a list with size = 0 is 0.
		 * The symfloatval of a list with size > 0 is
		 * defined recursively to be symfloatval(h),
		 * where h is the head of the list.
		 */
		if (sym->u.lval->size > 0) {
			return symfloatval(sym->u.lval->head->sym);
		}
	}

	return d;
}

/* make a temporary list symbol */
PSYMBOL mktlist(void)
{
	PSYMBOL t = xmalloc(sizeof(Symbol));
	t->name = NULL;
	t->type = SCONST;
	t->subtype = SLIST | STEMP;
	t->u.lval = listalloc();
	t->next = NULL;				/* not linked */
	return t;
}


/* maketemp:  make temporary */
PSYMBOL maketemp(void)
{
	PSYMBOL t = xmalloc(sizeof(Symbol));
	t->name = NULL;
	t->type = SCONST;
	t->subtype = SFLOAT | STEMP;
	t->u.fval = 0;
	t->next = NULL;				/* not linked */
	return t;
}
