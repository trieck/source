/*
 * EVAL.C
 *
 * Evaluate parse tree
 *
 * Pixie Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "pixie.h"
#include "eval.h"
#include "tree.h"
#include "proctab.h"
#include "block.h"
#include "xmalloc.h"
#include "global.h"
#include "array.h"
#include "strutil.h"
#include "parse.h"

#define CHECKARGS(n, x, y)											\
	do {															\
		if (n->nargs != x) {										\
			error("wrong number of arguments to %s near line %d.", 	\
				y, n->lineno);										\
		}															\
	} while (0)

#define STRCONV(s)													\
	do {															\
		if (!isstring(s)) {											\
			char buf[FBSIZE];										\
			double d = s->u.fval;									\
			sprintf(buf, "%.8g", d);								\
			s->u.sval = xstrdup(buf);								\
			s->sub &= ~SFLOAT;										\
			s->sub |= SSTRING;										\
		}															\
	} while (0)

#define tempfree(t)	if (t && (t->sub & STEMP)) symfree(t)

static Symbol empty = { SCONST, SSTRING, "", {""}, 0 };
static Symbol *EMPTY = &empty;

static Symbol *evalnode(Node *);
static Symbol *evalexpr(Node *);
static Symbol *evalval(Node *);
static Symbol *map(Node *);
static Symbol *maketemp(void);
static Symbol *tempsym(Symbol *);
static void printv(Array *);
static int array_assign(Symbol *, Array *);
static double floatval(Node *);
static Symbol *stringval(Node *);
static void copysym(Symbol *, Symbol *);

static int returning, breaking, continuing;

/* eval:  evaluate parse tree */
void eval(void)
{
	Symbol *t = evalnode(root);
	tempfree(t);
}

/* evalnode:  evaluate a node */
Symbol *evalnode(Node * N)
{
	if (N == 0)
		return EMPTY;

	switch (N->type) {
	case NSTMT:
		return evalexpr(N);
	case NVALUE:
		return evalval(N);
	default:
		error("unknown node type %d near line %d.", N->type, N->lineno);
	}

	return EMPTY;
}

/* evalexpr:  evaluate expression */
Symbol *evalexpr(Node * N)
{
	int index = N->nobj - FIRSTTOKEN - 1;
	return (*proctab[index]) (N);
}

/* evalval:  evaluate variable, constant */
Symbol *evalval(Node * N)
{
	Symbol *s, *t = EMPTY;

	CHECKARGS(N, 1, "evalval");

	s = (Symbol *) N->args[0];

	switch (s->type) {
	case SCONST:
		t = s;
		break;
	case SVAR:
		t = tempsym(map(N));
		break;
	case SUNDEF:
		error("%s undefined near line %d.", s->name, N->lineno);
		break;
	default:
		error("unknown symbol type %d near line %d.", s->type, N->lineno);
	}

	return t;
}

/* arith:  arithmetic expression */
Symbol *arith(Node * N)
{
	Symbol *t;
	double d;

	CHECKARGS(N, 2, "arith");
	t = maketemp();

	switch (N->nobj) {
	case PLUS:
		t->u.fval = floatval(N->args[0]) + floatval(N->args[1]);
		break;
	case SUB:
		t->u.fval = floatval(N->args[0]) - floatval(N->args[1]);
		break;
	case MULT:
		t->u.fval = floatval(N->args[0]) * floatval(N->args[1]);
		break;
	case DIV:
		d = floatval(N->args[1]);
		if (d == 0)
			error("division by zero near line %d.", N->lineno);
		t->u.fval = floatval(N->args[0]) / d;
		break;
	case MOD:
		d = floatval(N->args[1]);
		if (d == 0)
			error("modulo division by zero near line %d.", N->lineno);
		t->u.fval = (int) floatval(N->args[0]) % (int) d;
		break;
	case EXP:
		t->u.fval = pow(floatval(N->args[0]), floatval(N->args[1]));
		break;
	default:
		error("unknown arithmetic procedure [%d] near line %d.",
		      N->nobj, N->lineno);
	}

	return t;
}

/* bltin:  built-in function */
Symbol *bltin(Node * N)
{
	Symbol *t;

	CHECKARGS(N, 1, "bltin");

	t = maketemp();

	switch (N->nobj) {
	case SIN:
		t->u.fval = sin(floatval(N->args[0]));
		break;
	case COS:
		t->u.fval = cos(floatval(N->args[0]));
		break;
	case ATAN:
		t->u.fval = atan(floatval(N->args[0]));
		break;
	case LOG:
		t->u.fval = log(floatval(N->args[0]));
		break;
	case LOG10:
		t->u.fval = log10(floatval(N->args[0]));
		break;
	case SQRT:
		t->u.fval = sqrt(floatval(N->args[0]));
		break;
	case INT:
		t->u.fval = (int) floatval(N->args[0]);
		break;
	case ABS:
		t->u.fval = abs((int) floatval(N->args[0]));
		break;
	default:
		error("unknown built-in [%d] near line %d.", N->nobj, N->lineno);
	}

	return t;
}

/* print:  print an expression */
Symbol *print(Node * N)
{
	Node *p;
	Symbol *sym = EMPTY;

	CHECKARGS(N, 1, "print");

	for (p = N->args[0]; p; p = p->next) {
		tempfree(sym);
		sym = evalnode(p);
		if (isarray(sym)) {
			printv(sym->u.aval);
		} else if (isstring(sym)) {
			printf("%s", sym->u.sval);
		} else {
			printf("%.8g", sym->u.fval);
		}
	}

	return sym;
}

/* println:  print expression followed by \n */
Symbol *println(Node * N)
{
	Symbol *sym = print(N);
	putchar('\n');
	fflush(stdout);
	return sym;
}

/* printv:  print array */
void printv(Array * array)
{
	unsigned i;
	for (i = 0; array && i < array->size; i++) {
		if (i > 0)
			putchar(' ');

		if (isarray(array->v[i])) {
			printv(array->v[i]->u.aval);
		} else if (isstring(array->v[i])) {
			printf("%s", array->v[i]->u.sval);
		} else {
			printf("%.8g", array->v[i]->u.fval);
		}
	}

	fflush(stdout);
}

/* asgn:  assignment */
Symbol *asgn(Node * N)
{
	Symbol *sym, *res;

	CHECKARGS(N, 2, "assign");
	CHECKARGS(N->args[0], 1, "assign");

	sym = map(N->args[0]);

	res = evalnode(N->args[1]);
	copysym(sym, res);
	tempfree(res);

	return tempsym(sym);
}

/* length:  length of an array */
Symbol *length(Node * N)
{
	Symbol *sym, *temp;

	CHECKARGS(N, 1, "length");

	sym = map(N->args[0]);
	if (!isarray(sym)) {
		error("array %s expected near line %d.", sym->name, N->lineno);
	}

	temp = maketemp();
	temp->u.fval = sym->u.aval->size;

	return temp;
}

/* shift:  shift an array */
Symbol *shift(Node * N)
{
	Symbol *sym, *temp;

	CHECKARGS(N, 1, "shift");

	sym = map(N->args[0]);
	if (!isarray(sym)) {
		error("array %s expected near line %d.", sym->name, N->lineno);
	}

	if (sym->u.aval->size == 0)
		error("unable to shift empty array near line %d.", N->lineno);

	temp = array_shift(sym->u.aval);
	temp->sub |= STEMP;

	return temp;
}

/* unshift:  unshift an array */
Symbol *unshift(Node * N)
{
	Symbol *sym, *rhs;

	CHECKARGS(N, 2, "unshift");

	sym = map(N->args[0]);
	if (!isarray(sym)) {
		error("array %s expected near line %d.", sym->name, N->lineno);
	}

	rhs = evalnode(N->args[1]);

	array_unshift(sym->u.aval, rhs);

	return rhs;
}

/* push:  push an array */
Symbol *push(Node * N)
{
	Symbol *sym, *rhs;

	CHECKARGS(N, 2, "push");

	sym = map(N->args[0]);
	if (!isarray(sym)) {
		error("array %s expected near line %d.", sym->name, N->lineno);
	}

	rhs = evalnode(N->args[1]);
	array_push(sym->u.aval, rhs);

	return rhs;
}

/* pop:  pop an array */
Symbol *pop(Node * N)
{
	Symbol *sym, *temp;

	CHECKARGS(N, 1, "pop");

	sym = map(N->args[0]);
	if (!isarray(sym)) {
		error("array %s expected near line %d.", sym->name, N->lineno);
	}

	if (sym->u.aval->size == 0)
		error("unable to pop empty array near line %d.", N->lineno);

	temp = array_pop(sym->u.aval);
	temp->sub |= STEMP;

	return temp;
}

/* whilestmt:  while statement */
Symbol *whilestmt(Node * N)
{
	Symbol *b = EMPTY;
	double d;

	CHECKARGS(N, 2, "while");

	for (; !breaking && !returning; continuing = 0) {
		d = floatval(N->args[0]);	/* condition */
		if (!d)
			break;

		tempfree(b);
		b = evalnode(N->args[1]);	/* loop body */
	}

	breaking = continuing = 0;

	return b;
}

/* ifstmt:  if statement */
Symbol *ifstmt(Node * N)
{
	Symbol *b = EMPTY;
	double d;

	CHECKARGS(N, 3, "if");

	d = floatval(N->args[0]);	/* condition */
	if (d) {
		b = evalnode(N->args[1]);	/* stmt if true */
	} else if (N->args[2]) {
		b = evalnode(N->args[2]);	/* else block */
	}

	return b;
}

/* negate:  unary minus */
Symbol *negate(Node * N)
{
	Symbol *temp;

	CHECKARGS(N, 1, "negate");;

	temp = maketemp();
	temp->u.fval = -floatval(N->args[0]);

	return temp;
}

/* gt:  greater than */
Symbol *gt(Node * N)
{
	Symbol *res1, *res2, *temp;

	CHECKARGS(N, 2, "gt");

	res1 = evalnode(N->args[0]);
	res2 = evalnode(N->args[1]);

	temp = maketemp();

	if (isarray(res1) || isarray(res2)) {
		error("unexpected array found near line %d.", N->lineno);
	} else if (isstring(res1) || isstring(res2)) {
		STRCONV(res1);
		STRCONV(res2);
		temp->u.fval = (strcmp(res1->u.sval, res2->u.sval) > 0);
	} else {
		temp->u.fval = res1->u.fval > res2->u.fval;
	}

	tempfree(res1);
	tempfree(res2);

	return temp;
}

/* ge:  greater than or equal */
Symbol *ge(Node * N)
{
	Symbol *res1, *res2, *temp;

	CHECKARGS(N, 2, "ge");

	res1 = evalnode(N->args[0]);
	res2 = evalnode(N->args[1]);

	temp = maketemp();

	if (isarray(res1) || isarray(res2)) {
		error("unexpected array found near line %d.", N->lineno);
	} else if (isstring(res1) || isstring(res2)) {
		STRCONV(res1);
		STRCONV(res2);
		temp->u.fval = (strcmp(res1->u.sval, res2->u.sval) >= 0);
	} else {
		temp->u.fval = res1->u.fval >= res2->u.fval;
	}

	tempfree(res1);
	tempfree(res2);

	return temp;
}

/* lt:  less than */
Symbol *lt(Node * N)
{
	Symbol *res1, *res2, *temp;

	CHECKARGS(N, 2, "lt");

	res1 = evalnode(N->args[0]);
	res2 = evalnode(N->args[1]);

	temp = maketemp();

	if (isarray(res1) || isarray(res2)) {
		error("unexpected array found near line %d.", N->lineno);
	} else if (isstring(res1) || isstring(res2)) {
		STRCONV(res1);
		STRCONV(res2);
		temp->u.fval = (strcmp(res1->u.sval, res2->u.sval) < 0);
	} else {
		temp->u.fval = res1->u.fval < res2->u.fval;
	}

	tempfree(res1);
	tempfree(res2);

	return temp;
}

/* le:  less than or equal */
Symbol *le(Node * N)
{
	Symbol *res1, *res2, *temp;

	CHECKARGS(N, 2, "le");

	res1 = evalnode(N->args[0]);
	res2 = evalnode(N->args[1]);

	temp = maketemp();

	if (isarray(res1) || isarray(res2)) {
		error("unexpected array found near line %d.", N->lineno);
	} else if (isstring(res1) || isstring(res2)) {
		STRCONV(res1);
		STRCONV(res2);
		temp->u.fval = (strcmp(res1->u.sval, res2->u.sval) <= 0);
	} else {
		temp->u.fval = res1->u.fval <= res2->u.fval;
	}

	tempfree(res1);
	tempfree(res2);

	return temp;
}

/* eq:  equal to */
Symbol *eq(Node * N)
{
	Symbol *res1, *res2, *temp;

	CHECKARGS(N, 2, "eq");

	res1 = evalnode(N->args[0]);
	res2 = evalnode(N->args[1]);

	temp = maketemp();

	if (isarray(res1) || isarray(res2)) {
		error("unexpected array found near line %d.", N->lineno);
	} else if (isstring(res1) || isstring(res2)) {
		STRCONV(res1);
		STRCONV(res2);
		temp->u.fval = (strcmp(res1->u.sval, res2->u.sval) == 0);
	} else {
		temp->u.fval = res1->u.fval == res2->u.fval;
	}

	tempfree(res1);
	tempfree(res2);

	return temp;
}

/* ne:  not equal */
Symbol *ne(Node * N)
{
	Symbol *res1, *res2, *temp;

	CHECKARGS(N, 2, "ne");

	res1 = evalnode(N->args[0]);
	res2 = evalnode(N->args[1]);

	temp = maketemp();

	if (isarray(res1) || isarray(res2)) {
		error("unexpected array found near line %d.", N->lineno);
	} else if (isstring(res1) || isstring(res2)) {
		STRCONV(res1);
		STRCONV(res2);
		temp->u.fval = (strcmp(res1->u.sval, res2->u.sval) != 0);
	} else {
		temp->u.fval = res1->u.fval != res2->u.fval;
	}

	tempfree(res1);
	tempfree(res2);

	return temp;
}

/* and:  logical and expression */
Symbol *and(Node * N)
{
	Symbol *temp;

	CHECKARGS(N, 2, "and");

	temp = maketemp();
	temp->u.fval = floatval(N->args[0]) && floatval(N->args[1]);

	return temp;
}

/* or:  logical or expression */
Symbol *or(Node * N)
{
	Symbol *temp;

	CHECKARGS(N, 2, "or");

	temp = maketemp();
	temp->u.fval = floatval(N->args[0]) || floatval(N->args[1]);

	return temp;
}

/* not:  logical not */
Symbol *not(Node * N)
{
	Symbol *temp;

	CHECKARGS(N, 1, "not");

	temp = maketemp();
	temp->u.fval = !floatval(N->args[0]);

	return temp;
}

/* decl:  declare variables */
Symbol *decl(Node * N)
{
	Node *p;
	Symbol *sym = 0, *t;

	CHECKARGS(N, 1, "decl");

	for (p = N->args[0]; p; p = p->next) {
		tempfree(sym);

		switch (p->type) {
		case NSTMT:			/* assignment */
			CHECKARGS(p, 2, "decl");
			CHECKARGS(p->args[0], 1, "decl");
			sym = (Symbol *) p->args[0]->args[0];

			if (islocal(sym->name)) {
				error("local %s already declared near line %d.",
				      sym->name, p->args[0]->lineno);
			}

			binstall(sym->name, SVAR, SFLOAT, 0);

			sym = evalnode(p);	/* perform assignment */
			break;
		case NVALUE:
			CHECKARGS(p, 1, "decl");
			sym = (Symbol *) p->args[0];

			if (islocal(sym->name)) {
				error("local %s already declared near line %d.",
				      sym->name, p->lineno);
			}

			sym = binstall(sym->name, SVAR, SFLOAT, 0);
			break;
		default:
			error("unknown node type [%d] near line %d.",
			      p->type, p->lineno);
		}
	}

	t = tempsym(sym);
	tempfree(sym);

	return t;
}

/* block:  code block */
Symbol *block(Node * N)
{
	Node *p;
	Symbol *sym = EMPTY;

	CHECKARGS(N, 1, "block");

	blockenter();

	for (p = N->args[0];
	        p && !returning && !breaking && !continuing; p = p->next) {
		tempfree(sym);
		sym = evalnode(p);
	}

	blockleave();

	return sym;
}

/* def:  define a function */
Symbol *def(Node * N)
{
	Symbol *sym;

	CHECKARGS(N, 2, "def");
	CHECKARGS(N->args[0], 1, "def");

	sym = (Symbol *) N->args[0]->args[0];
	sym->type = SFUNC;
	sym->u.defn = N->args[1];

	return sym;
}

/* call:  call a function */
Symbol *call(Node * N)
{
	Symbol *sym, *a, *r, *t = 0;
	Array *save, *v;
	Node *p;

	CHECKARGS(N, 2, "call");
	CHECKARGS(N->args[0], 1, "call");

	sym = (Symbol *) N->args[0]->args[0];
	if (sym->type != SFUNC)
		error("undefined function %s near line %d.", sym->name, N->lineno);

	if ((a = glookup("argv")) == 0)
		error("argv undefined near line %d", N->lineno);

	/* save current value of argv */
	save = a->u.aval == 0 ? 0 : array_copy(a->u.aval);

	v = array_alloc(0);

	for (p = N->args[1]; p; p = p->next) {
		t = evalnode(p);
		array_push(v, t);
		tempfree(t);
	}

	array_assign(a, v);

	r = evalnode(sym->u.defn);

	array_free(a->u.aval);

	a->u.aval = save;

	returning = 0;

	return r;
}

/* funcret:  return from a function */
Symbol *funcret(Node * N)
{
	Symbol *res;

	CHECKARGS(N, 1, "return");

	res = evalnode(N->args[0]);

	returning = 1;

	return res;
}

/* breakstmt:  break statement */
Symbol *breakstmt(Node * N)
{
	CHECKARGS(N, 0, "break");

	breaking = 1;

	return EMPTY;
}

/* contstmt:  continue statement */
Symbol *contstmt(Node * N)
{
	CHECKARGS(N, 0, "break");

	continuing = 1;

	return EMPTY;
}

/* foreach:  foreach statement */
Symbol *foreach(Node * N)
{
	Symbol *s, *a, *r = EMPTY;
	unsigned i, n;

	CHECKARGS(N, 3, "foreach");
	CHECKARGS(N->args[0], 1, "foreach");
	CHECKARGS(N->args[1], 1, "foreach");

	s = map(N->args[0]);
	a = evalnode(N->args[1]);

	if (!isarray(a)) {
		error("expected array near line %d.", N->lineno);
	}

	n = a->u.aval->size;

	for (i = 0; i < n && !breaking && !returning; i++, continuing = 0) {
		copysym(s, array_elementat(a->u.aval, i));
		tempfree(r);
		r = evalnode(N->args[2]);
	}

	breaking = continuing = 0;

	return r;
}

/* strlength:  string length */
Symbol *strlength(Node * N)
{
	Symbol *t1, *t2;

	CHECKARGS(N, 1, "strlength");

	t1 = stringval(N->args[0]);

	t2 = maketemp();
	t2->u.fval = strlen(t1->u.sval);

	tempfree(t1);

	return t2;
}

/* substr:  sub-string */
Symbol *substr(Node * N)
{
	Symbol *t1, *t2;
	String s;
	char *pstart, *pend;
	int i, n, k;

	CHECKARGS(N, 3, "substr");

	t1 = stringval(N->args[0]);
	n = strlen(t1->u.sval);
	i = (int) floatval(N->args[1]);
	k = (int) floatval(N->args[2]);

	if (i < 0 || i >= n)
		error("index out of range near line %d.", N->lineno);

	if (k < 0 || k > n - i)
		error("index out of range near line %d.", N->lineno);

	t2 = maketemp();
	t2->sub &= ~SFLOAT;
	t2->sub |= SSTRING;

	s = stringalloc();

	pstart = t1->u.sval + i;
	pend = pstart + k;

	while (pstart < pend) {
		stringpush(s, *pstart++);
	}

	t2->u.sval = xstrdup(stringptr(s));

	stringfree(s);

	tempfree(t1);

	return t2;
}

/* strconcat:  string concatenation */
Symbol *strconcat(Node * N)
{
	Symbol *t1, *t2, *t3;
	String s;

	CHECKARGS(N, 2, "strconcat");

	t1 = stringval(N->args[0]);
	t2 = stringval(N->args[1]);

	t3 = maketemp();
	t3->sub &= ~SFLOAT;
	t3->sub |= SSTRING;

	s = stringalloc();
	stringvpush(s, t1->u.sval);
	stringvpush(s, t2->u.sval);

	tempfree(t1);
	tempfree(t2);

	t3->u.sval = xstrdup(stringptr(s));

	stringfree(s);

	return t3;
}

/* nindex:  string index */
Symbol *nindex(Node * N)
{
	Symbol *t1, *t2, *t3;
	char *p;

	CHECKARGS(N, 2, "nindex");

	t1 = stringval(N->args[0]);
	t2 = stringval(N->args[1]);

	p = strstr(t1->u.sval, t2->u.sval);

	t3 = maketemp();
	t3->u.fval = p ? p - t1->u.sval : -1;

	tempfree(t1);
	tempfree(t2);

	return t3;
}

/* mklist:  make list */
Symbol *mklist(Node * N)
{
	Node *p;
	Symbol *s, *t = EMPTY;

	CHECKARGS(N, 1, "mklist");

	s = maketemp();
	s->sub &= ~SFLOAT;
	s->sub |= SARRAY;
	s->u.aval = array_alloc(0);

	for (p = N->args[0]; p; p = p->next) {
		tempfree(t);
		t = evalnode(p);
		array_push(s->u.aval, t);
	}

	tempfree(t);

	return s;
}

/* subscr:  array subscript */
Symbol *subscr(Node * N)
{
	Symbol *sym;
	unsigned index;

	CHECKARGS(N, 2, "subscr");

	sym = map(N->args[0]);
	if (!isarray(sym)) {
		error("array %s expected near line %d.", sym->name, N->lineno);
	}

	index = (unsigned) floatval(N->args[1]);
	if (index >= sym->u.aval->size) {
		error("array index out of bounds near line %d.", N->lineno);
	}

	return tempsym(array_elementat(sym->u.aval, index));
}

/* subasgn:  array subscript assignment */
Symbol *subasgn(Node * N)
{
	Symbol *sym, *rhs;
	unsigned index;

	CHECKARGS(N, 3, "subasgn");

	sym = map(N->args[0]);
	if (!isarray(sym)) {
		error("array %s expected near line %d.", sym->name, N->lineno);
	}

	index = (unsigned) floatval(N->args[1]);
	if (index >= sym->u.aval->size) {
		error("array index out of bounds near line %d.", N->lineno);
	}

	rhs = evalnode(N->args[2]);

	array_setelementat(sym->u.aval, index, rhs);

	return tempsym(rhs);
}

/* bnot:  bitwise not */
Symbol *bnot(Node * N)
{
	Symbol *temp;

	CHECKARGS(N, 1, "bnot");

	temp = maketemp();
	temp->u.fval = ~(int)floatval(N->args[0]);

	return temp;
}

/* lshift:  left shift */
Symbol *lshift(Node * N)
{
	Symbol *temp;

	CHECKARGS(N, 2, "lshift");

	temp = maketemp();
	temp->u.fval = (int)floatval(N->args[0]) << (int)floatval(N->args[1]);

	return temp;
}

/* rshift:  right shift */
Symbol *rshift(Node * N)
{
	Symbol *temp;

	CHECKARGS(N, 2, "rshift");

	temp = maketemp();
	temp->u.fval = (int)floatval(N->args[0]) >> (int)floatval(N->args[1]);

	return temp;
}

/* band:  bitwise and expression */
Symbol *band(Node * N)
{
	Symbol *temp;

	CHECKARGS(N, 2, "band");

	temp = maketemp();
	temp->u.fval = (int)floatval(N->args[0]) & (int)floatval(N->args[1]);

	return temp;
}

/* bor:  bitwise or expression */
Symbol *bor(Node * N)
{
	Symbol *temp;

	CHECKARGS(N, 2, "or");

	temp = maketemp();
	temp->u.fval = (int)floatval(N->args[0]) | (int)floatval(N->args[1]);

	return temp;
}

/* asc:  ASCII digit */
Symbol *asc(Node * N)
{
	Symbol *temp, *res;

	CHECKARGS(N, 1, "asc");

	res = stringval(N->args[0]);
	if (strlen(res->u.sval) == 0)
		error("zero-length string unexpected near line %d.", N->lineno);

	temp = maketemp();
	temp->u.fval = res->u.sval[0];

	return temp;
}

/* chr:  character value of ASCII digit */
Symbol *chr(Node * N)
{
	Symbol *temp;
	char buf[2] = { 0 };

	CHECKARGS(N, 1, "chr");

	buf[0] = (char)floatval(N->args[0]);

	temp = maketemp();
	temp->sub &= ~SFLOAT;
	temp->sub |= SSTRING;
	temp->u.sval = xstrdup(buf);

	return temp;
}

/* map:  translate parser symbol into block scoped symbol */
Symbol *map(Node * N)
{
	Symbol *s, *org;

	CHECKARGS(N, 1, "map");

	org = (Symbol *) N->args[0];

	if ((s = blookup(org->name)) == 0)
		error("%s undefined near line %d.", org->name, N->lineno);

	if (s->type == SUNDEF)
		error("%s undefined near line %d.", s->name, N->lineno);

	return s;
}

/* tempsym:  make a temp copy of a symbol */
Symbol *tempsym(Symbol * src)
{
	Symbol *t = symcopy(src);
	t->sub |= STEMP;
	return t;
}

/* maketemp:  make temporary */
Symbol *maketemp(void)
{
	Symbol *t = xmalloc(sizeof(Symbol));
	t->name = 0;
	t->type = SCONST;
	t->sub = SFLOAT | STEMP;
	t->u.fval = 0;
	t->next = 0;
	return t;
}

/* array_assign:  assign array to symbol */
int array_assign(Symbol * sym, Array * array)
{
	if (sym->sub & SARRAY) {
		array_free(sym->u.aval);
	}

	sym->type = SVAR;
	sym->sub |= SARRAY;
	sym->u.aval = array;

	return array->size;
}

/* floatval:  return floating point value of symbol */
double floatval(Node * N)
{
	Symbol *sym;
	double d = 0;

	sym = evalnode(N);

	switch (sym->type) {
	case SCONST:
	case SVAR:
		if (sym->sub & SFLOAT) {
			d = sym->u.fval;
		} else if (sym->sub & SSTRING) {
			d = atof(sym->u.sval);
		} else if (sym->sub & SARRAY) {
			error("array %s unexpected near line %d.",
			      sym->name, N->lineno);
		} else {
			error("unknown symbol sub-type %d near line %d.",
			      sym->sub, N->lineno);
		}
		break;
	case SUNDEF:
		error("%s undefined near line %d.", sym->name, N->lineno);
		break;
	default:
		error("unknown symbol type %d near line %d.",
		      sym->type, N->lineno);
	}

	tempfree(sym);

	return d;
}

/* stringval:  return string value of symbol */
Symbol *stringval(Node * N)
{
	Symbol *sym, *t;

	sym = evalnode(N);

	t = maketemp();
	t->sub &= ~SFLOAT;
	t->sub |= SSTRING;

	switch (sym->type) {
	case SCONST:
	case SVAR:
		if (sym->sub & SFLOAT) {
			char buf[FBSIZE];
			sprintf(buf, "%.8g", sym->u.fval);
			t->u.sval = xstrdup(buf);
		} else if (sym->sub & SSTRING) {
			t->u.sval = xstrdup(sym->u.sval);
		} else if (sym->sub & SARRAY) {
			error("array %s unexpected near line %d.",
			      sym->name, N->lineno);
		} else {
			error("unknown symbol sub-type %d near line %d.",
			      sym->sub, N->lineno);
		}
		break;
	case SUNDEF:
		error("%s undefined near line %d.", sym->name, N->lineno);
		break;
	default:
		error("unknown symbol type %d near line %d.",
		      sym->type, N->lineno);
	}

	tempfree(sym);

	return t;
}

/* copysym:  copy dest symbol onto source */
void copysym(Symbol * dest, Symbol * src)
{
	if (isstring(dest))
		xfree(dest->u.sval);
	else if (isarray(dest))
		array_free(dest->u.aval);

	if (isstring(src))
		dest->u.sval = xstrdup(src->u.sval);
	else if (isarray(src))
		dest->u.aval = array_copy(src->u.aval);
	else
		dest->u.fval = src->u.fval;

	dest->sub = src->sub;
}
