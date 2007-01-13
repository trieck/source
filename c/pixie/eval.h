/*
 * EVAL.H
 *
 * Evaluate parse tree
 *
 * Pixie Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#ifndef __EVAL_H__
#define __EVAL_H__

void eval(void);

Symbol *arith(Node * node);
Symbol *bltin(Node * node);
Symbol *print(Node * node);
Symbol *println(Node * node);
Symbol *asgn(Node * node);
Symbol *subasgn(Node * node);
Symbol *length(Node * node);
Symbol *shift(Node * node);
Symbol *unshift(Node * node);
Symbol *push(Node * node);
Symbol *pop(Node * node);
Symbol *whilestmt(Node * node);
Symbol *ifstmt(Node * node);
Symbol *negate(Node * node);
Symbol *gt(Node * node);
Symbol *ge(Node * node);
Symbol *lt(Node * node);
Symbol *le(Node * node);
Symbol *eq(Node * node);
Symbol *ne(Node * node);
Symbol *and(Node * node);
Symbol *or(Node * node);
Symbol *not(Node * node);
Symbol *decl(Node * node);
Symbol *block(Node * node);
Symbol *def(Node * node);
Symbol *call(Node * node);
Symbol *funcret(Node * node);
Symbol *breakstmt(Node * node);
Symbol *contstmt(Node * node);
Symbol *foreach(Node * node);
Symbol *strlength(Node * node);
Symbol *substr(Node * node);
Symbol *strconcat(Node * node);
Symbol *nindex(Node * node);
Symbol *mklist(Node * node);
Symbol *subscr(Node * node);
Symbol *bnot(Node * node);
Symbol *lshift(Node * node);
Symbol *rshift(Node * node);
Symbol *band(Node * node);
Symbol *bor(Node * node);
Symbol *asc(Node * node);
Symbol *chr(Node * node);

#endif							/* __EVAL_H__ */
