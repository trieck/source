/*
 * PROCTAB.H
 *
 * Procedure table
 *
 * 'X' Programming Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#ifndef __PROCTAB_H__
#define __PROCTAB_H__

typedef PSYMBOL(*proc) (PNODE);

extern proc proctab[];

#endif							/* __PROCTAB_H__ */
