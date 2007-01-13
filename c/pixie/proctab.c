/*
 * PROCTAB.C
 *
 * Procedure table
 *
 * Pixie Language
 * Copyright (c) 2002, Thomas A. Rieck
 * All Rights Reserved
 */

#include "pixie.h"
#include "symbol.h"
#include "tree.h"
#include "eval.h"
#include "proctab.h"

#define NULLPROC ((proc)0)

/* procedure table */
proc proctab[] = {
	arith,						/* PLUS */
	arith,						/* SUB */
	arith,						/* MULT */
	arith,						/* DIV */
	arith,						/* MOD */
	arith,						/* EXP */
	bltin,						/* SIN */
	bltin,						/* COS */
	bltin,						/* ATAN */
	bltin,						/* LOG */
	bltin,						/* LOG10 */
	bltin,						/* SQRT */
	bltin,						/* INT */
	bltin,						/* ABS */
	print,						/* PRINT */
	println,					/* PRINTLN */
	asgn,						/* ASGN */
	subasgn,					/* SUBASGN */
	length,						/* LENGTH */
	shift,						/* SHIFT */
	unshift,					/* UNSHIFT */
	push,						/* PUSH */
	pop,						/* POP */
	whilestmt,					/* WHILE */
	ifstmt,						/* IF */
	NULLPROC,					/* ELSE */
	negate,						/* UNARYMINUS */
	gt,							/* GT */
	ge,							/* GE */
	lt,							/* LT */
	le,							/* LE */
	eq,							/* EQ */
	ne,							/* NE */
	and,						/* AND */
	or,							/* OR */
	not,						/* NOT */
	decl,						/* VAR */
	block,						/* BLOCK */
	def,						/* DEF */
	call,						/* CALL */
	funcret,					/* RETURN */
	breakstmt,					/* BREAK */
	contstmt,					/* CONTINUE */
	foreach,					/* FOREACH */
	NULLPROC,					/* IN */
	strlength,					/* STRLEN */
	substr,						/* SUBSTR */
	strconcat,					/* STRCAT */
	nindex,						/* INDEX */
	mklist,						/* MKLIST */
	subscr,						/* SUBSCR */
	bnot,						/* BNOT */
	lshift,						/* LSHIFT */
	rshift,						/* RSHIFT */
	band,						/* BAND */
	bor,						/* BOR */
	asc,						/* ASC */
	chr							/* CHR */
};
