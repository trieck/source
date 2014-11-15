/*
 * PROCTAB.C
 *
 * Procedure table
 *
 * 'X' Programming Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#include "symbol.h"
#include "tree.h"
#include "parser.h"
#include "proctab.h"
#include "eval.h"

#define NULLPROC	((proc)0)
#define TBLSIZE		(LASTTOKEN-FIRSTTOKEN-1)

/* procedure table */
proc proctab[TBLSIZE] = {
    arith,						/* PLUS */
    arith,						/* SUB */
    arith,						/* MULT */
    arith,						/* DIV */
    arith,						/* MOD */
    range,						/* RANGE */
    mklist,						/* MKLIST */
    print,						/* PRINT */
    println,					/* PRINTLN */
    let,						/* LET */
};
