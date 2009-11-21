/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
/* Put the tokens into the symbol table, so that GDB and other debuggers
   know about them.  */
enum yytokentype {
	FIRSTTOKEN = 258,
	PLUS = 259,
	SUB = 260,
	MULT = 261,
	DIV = 262,
	MOD = 263,
	EXP = 264,
	SIN = 265,
	COS = 266,
	ATAN = 267,
	LOG = 268,
	LOG10 = 269,
	SQRT = 270,
	INT = 271,
	ABS = 272,
	PRINT = 273,
	PRINTLN = 274,
	ASGN = 275,
	SUBASGN = 276,
	LENGTH = 277,
	SHIFT = 278,
	UNSHIFT = 279,
	PUSH = 280,
	POP = 281,
	WHILE = 282,
	IF = 283,
	ELSE = 284,
	UNARYMINUS = 285,
	GT = 286,
	GE = 287,
	LT = 288,
	LE = 289,
	EQ = 290,
	NE = 291,
	AND = 292,
	OR = 293,
	NOT = 294,
	VAR = 295,
	BLOCK = 296,
	DEF = 297,
	CALL = 298,
	RETURN = 299,
	BREAK = 300,
	CONTINUE = 301,
	FOREACH = 302,
	IN = 303,
	STRLEN = 304,
	SUBSTR = 305,
	STRCAT = 306,
	INDEX = 307,
	MKLIST = 308,
	SUBSCR = 309,
	BNOT = 310,
	LSHIFT = 311,
	RSHIFT = 312,
	BAND = 313,
	BOR = 314,
	ASC = 315,
	CHR = 316,
	ID = 317,
	BLTIN = 318,
	NUMBER = 319,
	STRING = 320,
	LOWER_THAN_ELSE = 321
};
#endif
/* Tokens.  */
#define FIRSTTOKEN 258
#define PLUS 259
#define SUB 260
#define MULT 261
#define DIV 262
#define MOD 263
#define EXP 264
#define SIN 265
#define COS 266
#define ATAN 267
#define LOG 268
#define LOG10 269
#define SQRT 270
#define INT 271
#define ABS 272
#define PRINT 273
#define PRINTLN 274
#define ASGN 275
#define SUBASGN 276
#define LENGTH 277
#define SHIFT 278
#define UNSHIFT 279
#define PUSH 280
#define POP 281
#define WHILE 282
#define IF 283
#define ELSE 284
#define UNARYMINUS 285
#define GT 286
#define GE 287
#define LT 288
#define LE 289
#define EQ 290
#define NE 291
#define AND 292
#define OR 293
#define NOT 294
#define VAR 295
#define BLOCK 296
#define DEF 297
#define CALL 298
#define RETURN 299
#define BREAK 300
#define CONTINUE 301
#define FOREACH 302
#define IN 303
#define STRLEN 304
#define SUBSTR 305
#define STRCAT 306
#define INDEX 307
#define MKLIST 308
#define SUBSCR 309
#define BNOT 310
#define LSHIFT 311
#define RSHIFT 312
#define BAND 313
#define BOR 314
#define ASC 315
#define CHR 316
#define ID 317
#define BLTIN 318
#define NUMBER 319
#define STRING 320
#define LOWER_THAN_ELSE 321




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 16 "d:\\source\\c\\pixie\\parse.y"
{
	Node *node;			/* node in parse tree */
	Symbol *sym;		/* symbol table pointer */
	int n;				/* token id */
}
/* Line 1489 of yacc.c.  */
#line 187 "y.tab.h"
YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

