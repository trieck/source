/*
 * TREE.H
 *
 * Parse tree construction
 *
 * Pixie Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#ifndef __TREE_H__
#define __TREE_H__

extern Node *root;

/* initialize tree */
void treeinit(void);

/* node construction */
Node *stmt0(int n);
Node *stmt1(int n, Node * arg);
Node *stmt2(int n, Node * arg1, Node * arg2);
Node *stmt3(int n, Node * arg1, Node * arg2, Node * arg3);
Node *op1(int n, Node * arg);
Node *op2(int n, Node * arg1, Node * arg2);
Node *lknodes(Node * n1, Node * n2);
Node *symtonode(Symbol *);

#endif							/* __TREE_H__ */
