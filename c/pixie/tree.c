/*
 * TREE.C
 *
 * Parse tree construction
 *
 * Pixie Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#include <stdlib.h>
#include "pixie.h"
#include "tree.h"
#include "xmalloc.h"
#include "parse.h"
#include "memcheck.h"

static Node *nodealloc(int n);
static void nodefree(Node * N);
static void cleanup(void);

extern int lineno;

Node *root = 0;

void treeinit(void)
{
	mcatexit(cleanup);
}

void cleanup(void)
{
	nodefree(root);
}

/* free a node */
void nodefree(Node * N)
{
	int i;

	while (N) {
		Node *next = N->next;

		/* free children */
		for (i = 0; N->type != NVALUE && i < N->nargs; i++) {
			nodefree(N->args[i]);
		}

		xfree(N);
		N = next;
	}
}

/* allocate a node */
Node *nodealloc(int n)
{
	Node *N = (Node *) xmalloc(sizeof(Node) + ((n - 1) * sizeof(Node *)));
	N->type = NUNDEF;
	N->lineno = lineno;
	N->nobj = 0;
	N->nargs = n;
	N->next = 0;
	return N;
}

/* link nodes */
Node *lknodes(Node * n1, Node * n2)
{
	Node *p;

	if (n1 == 0)
		return n2;

	if (n2 == 0)
		return n1;

	/* put at end of list */
	for (p = n1; p->next; p = p->next);

	p->next = n2;

	return n1;
}

Node *stmt0(int n)
{
	Node *node = nodealloc(0);
	node->type = NSTMT;
	node->nobj = n;
	return node;
}

Node *stmt1(int n, Node * arg)
{
	Node *node = nodealloc(1);
	node->type = NSTMT;
	node->nobj = n;
	node->args[0] = arg;
	return node;
}

Node *stmt2(int n, Node * arg1, Node * arg2)
{
	Node *node = nodealloc(2);
	node->type = NSTMT;
	node->nobj = n;
	node->args[0] = arg1;
	node->args[1] = arg2;
	return node;
}

Node *stmt3(int n, Node * arg1, Node * arg2, Node * arg3)
{
	Node *node = nodealloc(3);
	node->type = NSTMT;
	node->nobj = n;
	node->args[0] = arg1;
	node->args[1] = arg2;
	node->args[2] = arg3;
	return node;
}

Node *op1(int n, Node * arg)
{
	Node *node = nodealloc(1);
	node->type = NSTMT;
	node->nobj = n;
	node->args[0] = arg;
	return node;
}

Node *op2(int n, Node * arg1, Node * arg2)
{
	Node *node = nodealloc(2);
	node->type = NSTMT;
	node->nobj = n;
	node->args[0] = arg1;
	node->args[1] = arg2;
	return node;
}

Node *symtonode(Symbol * sym)
{
	Node *N = nodealloc(1);
	N->args[0] = (Node *) sym;
	N->type = NVALUE;
	return N;
}
