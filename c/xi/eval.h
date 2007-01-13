/*
 * EVAL.H
 *
 * Evaluate parse tree
 *
 * 'X' Programming Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#ifndef __EVAL_H__
#define __EVAL_H__

void eval(void);
PSYMBOL arith(PNODE node);
PSYMBOL range(PNODE node);
PSYMBOL mklist(PNODE node);
PSYMBOL print(PNODE node);
PSYMBOL println(PNODE node);
PSYMBOL let(PNODE node);

#endif							/* __EVAL_H__ */
