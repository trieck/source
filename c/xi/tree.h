/*
 * TREE.H
 *
 * Parse tree construction
 *
 * 'X' Programming Language
 * Copyright (c) 2004, Thomas A. Rieck
 * All Rights Reserved
 */

#ifndef __TREE_H__
#define __TREE_H__

/* node types */
#define NUNDEF	0x0000			/* undefined node */
#define NSTMT	0x0001			/* statement */
#define NATOMIC	0x0002			/* atomic */

/* node in the parse tree */
typedef struct Node {
	int type;					/* type of node */
	int nobj;					/* special */
	int nargs;					/* number of children */
	int lineno;					/* line number during parsing */
	struct Node *next;			/* next node if chained */
	struct Node *args[1];		/* variable size for child nodes */
} Node, *PNODE;

/* initialize tree */
void treeinit(void);

/* node construction */
PNODE mkleaf(PSYMBOL sym);
PNODE mkstmt(int id, PNODE args);
PNODE mkstmt2(int id, PNODE args, PNODE name);
PNODE lknodes(PNODE n1, PNODE n2);

#endif							/* __TREE_H__ */
