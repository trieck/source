/*
 * PROCTAB.H
 *
 * Procedure table
 *
 * Pixie Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#ifndef __PROCTAB_H__
#define __PROCTAB_H__

typedef Symbol *(*proc) (Node *);

extern proc proctab[];

#endif							/* __PROCTAB_H__ */
