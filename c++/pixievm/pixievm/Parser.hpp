/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     BYTE = 258,
     WORD = 259,
     EOL = 260,
     I1 = 261,
     I2 = 262,
     I3 = 263,
     I4 = 264,
     I5 = 265,
     I6 = 266,
     I7 = 267,
     R8 = 268,
     R16 = 269,
     RX16 = 270,
     IM8 = 271,
     IM16 = 272
   };
#endif
/* Tokens.  */
#define BYTE 258
#define WORD 259
#define EOL 260
#define I1 261
#define I2 262
#define I3 263
#define I4 264
#define I5 265
#define I6 266
#define I7 267
#define R8 268
#define R16 269
#define RX16 270
#define IM8 271
#define IM16 272




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 14 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
typedef union YYSTYPE {
	int n;				/* token id */
	LPSYMBOL sym;		/* symbol table pointer */
} YYSTYPE;
/* Line 1447 of yacc.c.  */
#line 77 "Parser.hpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



