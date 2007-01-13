/* A Bison parser, made by GNU Bison 1.875b.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 ".\\parse.y"

#include <stdlib.h>
#include <stdio.h>
#include "pixie.h"
#include "tree.h"

extern int yylex(void);
static int yyerror(const char *s);
static void defnonly(const char *s);
static void looponly(const char *s);

extern int lineno;
static int indef, inloop;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 16 ".\\parse.y"
typedef union YYSTYPE {
	Node *node;			/* node in parse tree */
	Symbol *sym;		/* symbol table pointer */
	int n;				/* token id */
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 229 "y.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 241 "y.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  82
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   918

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  24
/* YYNRULES -- Number of rules. */
#define YYNRULES  87
/* YYNRULES -- Number of states. */
#define YYNSTATES  181

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   321

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    72,     2,     2,
      78,    79,    70,    68,    80,    69,     2,    71,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    76,
       2,    67,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    74,     2,    81,    73,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    75,     2,    77,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     6,     9,    11,    14,    17,    18,
      23,    24,    31,    35,    41,    43,    45,    49,    50,    52,
      53,    55,    57,    60,    63,    66,    68,    70,    72,    74,
      76,    78,    80,    84,    88,    92,    96,   100,   104,   108,
     112,   115,   119,   123,   127,   131,   135,   139,   143,   147,
     151,   155,   160,   163,   166,   169,   172,   179,   186,   189,
     194,   203,   210,   217,   222,   227,   231,   233,   235,   237,
     241,   245,   248,   250,   254,   256,   258,   260,   264,   268,
     275,   280,   281,   286,   291,   292,   294,   296
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      83,     0,    -1,    -1,    84,    -1,    83,     1,    -1,    85,
      -1,    84,    85,    -1,    90,    76,    -1,    -1,    27,    93,
      86,    88,    -1,    -1,    47,    62,    48,    91,    87,    88,
      -1,    28,    93,    85,    -1,    28,    93,    85,    29,    85,
      -1,    88,    -1,   101,    -1,    75,    89,    77,    -1,    -1,
      84,    -1,    -1,    91,    -1,    94,    -1,    18,    97,    -1,
      19,    97,    -1,    44,    91,    -1,    45,    -1,    46,    -1,
      92,    -1,    98,    -1,    99,    -1,   100,    -1,   103,    -1,
      91,    56,    91,    -1,    91,    57,    91,    -1,    91,    68,
      91,    -1,    91,    69,    91,    -1,    91,    70,    91,    -1,
      91,    71,    91,    -1,    91,    72,    91,    -1,    91,    73,
      91,    -1,    69,    91,    -1,    91,    31,    91,    -1,    91,
      32,    91,    -1,    91,    33,    91,    -1,    91,    34,    91,
      -1,    91,    35,    91,    -1,    91,    36,    91,    -1,    91,
      37,    91,    -1,    91,    58,    91,    -1,    91,    38,    91,
      -1,    91,    59,    91,    -1,    63,    78,    91,    79,    -1,
      39,    91,    -1,    55,    91,    -1,    22,    62,    -1,    23,
      62,    -1,    24,    78,    62,    80,    91,    79,    -1,    25,
      78,    62,    80,    91,    79,    -1,    26,    62,    -1,    49,
      78,    91,    79,    -1,    50,    78,    91,    80,    91,    80,
      91,    79,    -1,    51,    78,    91,    80,    91,    79,    -1,
      52,    78,    91,    80,    91,    79,    -1,    60,    78,    91,
      79,    -1,    61,    78,    91,    79,    -1,    74,   104,    81,
      -1,    64,    -1,    65,    -1,    62,    -1,    78,    91,    79,
      -1,    78,    91,    79,    -1,    40,    95,    -1,    96,    -1,
      95,    80,    96,    -1,    62,    -1,    98,    -1,    91,    -1,
      97,    80,    91,    -1,    62,    67,    91,    -1,    62,    74,
      91,    81,    67,    91,    -1,    62,    74,    91,    81,    -1,
      -1,    42,    62,   102,    88,    -1,    62,    78,   104,    79,
      -1,    -1,   105,    -1,    91,    -1,    91,    80,   105,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    50,    50,    51,    52,    55,    56,    59,    60,    60,
      62,    62,    64,    65,    66,    67,    70,    73,    74,    77,
      78,    79,    80,    81,    82,    83,    84,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   128,   129,   130,   131,
     134,   137,   140,   141,   144,   145,   148,   149,   152,   155,
     158,   161,   161,   171,   178,   179,   182,   183
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FIRSTTOKEN", "PLUS", "SUB", "MULT", "DIV", 
  "MOD", "EXP", "SIN", "COS", "ATAN", "LOG", "LOG10", "SQRT", "INT", 
  "ABS", "PRINT", "PRINTLN", "ASGN", "SUBASGN", "LENGTH", "SHIFT", 
  "UNSHIFT", "PUSH", "POP", "WHILE", "IF", "ELSE", "UNARYMINUS", "GT", 
  "GE", "LT", "LE", "EQ", "NE", "AND", "OR", "NOT", "VAR", "BLOCK", "DEF", 
  "CALL", "RETURN", "BREAK", "CONTINUE", "FOREACH", "IN", "STRLEN", 
  "SUBSTR", "STRCAT", "INDEX", "MKLIST", "SUBSCR", "BNOT", "LSHIFT", 
  "RSHIFT", "BAND", "BOR", "ASC", "CHR", "ID", "BLTIN", "NUMBER", 
  "STRING", "LOWER_THAN_ELSE", "'='", "'+'", "'-'", "'*'", "'/'", "'%'", 
  "'^'", "'['", "'{'", "';'", "'}'", "'('", "')'", "','", "']'", 
  "$accept", "prog", "stmts", "stmt", "@1", "@2", "block", "stmt_list", 
  "expr_stmt", "expr", "prim", "cond", "decl", "decl_list", "declarator", 
  "prlist", "asgn", "subasgn", "subscr", "defn", "@3", "func", "args", 
  "arglist", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,    61,    43,    45,
      42,    47,    37,    94,    91,   123,    59,   125,    40,    41,
      44,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    82,    83,    83,    83,    84,    84,    85,    86,    85,
      87,    85,    85,    85,    85,    85,    88,    89,    89,    90,
      90,    90,    90,    90,    90,    90,    90,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    92,    92,    92,    92,
      93,    94,    95,    95,    96,    96,    97,    97,    98,    99,
     100,   102,   101,   103,   104,   104,   105,   105
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     1,     2,     1,     2,     2,     0,     4,
       0,     6,     3,     5,     1,     1,     3,     0,     1,     0,
       1,     1,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     2,     2,     2,     2,     6,     6,     2,     4,
       8,     6,     6,     4,     4,     3,     1,     1,     1,     3,
       3,     2,     1,     3,     1,     1,     1,     3,     3,     6,
       4,     0,     4,     4,     0,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    25,    26,     0,     0,     0,     0,
       0,     0,     0,     0,    68,     0,    66,    67,     0,    84,
      17,     0,     0,     3,     5,    14,     0,    20,    27,    21,
      28,    29,    30,    15,    31,    76,    22,    23,    54,    55,
       0,     0,    58,     0,     8,    19,    52,    74,    71,    72,
      75,    81,    24,     0,     0,     0,     0,     0,    53,     0,
       0,     0,     0,    84,     0,    40,    86,     0,    85,    18,
       0,     0,     1,     4,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    78,
       0,     0,     0,     0,    65,    16,    69,    41,    42,    43,
      44,    45,    46,    47,    49,    32,    33,    48,    50,    34,
      35,    36,    37,    38,    39,    77,     0,     0,    70,     9,
      19,    73,    82,    10,    59,     0,     0,     0,    63,    64,
      80,    83,    51,    87,     0,     0,    13,     0,     0,     0,
       0,     0,    56,    57,    11,     0,    61,    62,    79,     0,
      60
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    32,    33,    34,   108,   167,    35,    80,    36,    37,
      38,    54,    39,    58,    59,    46,    40,    41,    42,    43,
     111,    44,    77,    78
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -106
static const short yypact[] =
{
     139,   257,   257,   -52,   -49,   -64,   -55,   -37,   -47,   -47,
     257,   -36,   -33,   257,  -106,  -106,   -30,   -32,   -28,   -27,
     -25,   257,   -24,   -23,   -63,   -22,  -106,  -106,   257,   257,
     139,   257,     7,   139,  -106,  -106,   -19,   798,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,   798,   -21,   -21,  -106,  -106,
     -17,   -15,  -106,   257,  -106,   200,   -13,   -18,    -5,  -106,
    -106,  -106,   798,    10,   257,   257,   257,   257,   -13,   257,
     257,   257,   257,   257,   257,   -13,   334,   -20,  -106,   139,
     -10,   479,  -106,  -106,  -106,  -106,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,    -4,    -3,   508,     3,    45,
     -36,     3,   257,   537,   363,   392,   421,   566,   595,   798,
     305,     0,   624,   257,  -106,  -106,  -106,   -35,   -35,   -35,
     -35,   -35,   -35,   845,   827,   -29,   -29,   845,   827,   -54,
     -54,   -13,   -13,   -13,   -13,   798,   257,   257,  -106,  -106,
     200,  -106,  -106,   798,  -106,   257,   257,   257,  -106,  -106,
      13,  -106,  -106,  -106,   653,   682,  -106,     3,   450,   711,
     740,   257,  -106,  -106,  -106,   257,  -106,  -106,   798,   769,
    -106
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
    -106,  -106,    51,   -31,  -106,  -106,  -105,  -106,  -106,    -1,
    -106,    73,  -106,  -106,   -26,    81,    -6,  -106,  -106,  -106,
    -106,  -106,    32,   -16
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -20
static const short yytable[] =
{
      45,    45,    84,   149,    71,    60,   152,    82,    83,    56,
      48,    72,    62,    49,    50,    73,   100,   101,   102,   103,
      68,    94,    95,    51,   109,    52,    57,    75,    76,    61,
      81,    53,    63,    98,    99,   100,   101,   102,   103,    98,
      99,   100,   101,   102,   103,   105,    64,   106,    84,    71,
      65,    66,   107,    67,    69,    70,    74,    85,   112,   104,
     103,   124,   174,   113,   114,   115,   116,   125,   117,   118,
     119,   120,    76,   122,   150,   110,   146,   147,    30,   161,
     171,    79,    55,    47,   151,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,    60,   121,     0,   163,     0,     0,
       0,   153,     0,     0,     0,     0,     0,     0,     0,   166,
       0,     0,    76,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   164,   165,     0,     0,     0,
       0,     0,     0,     0,   168,   169,   170,     1,     2,     0,
       0,     3,     4,     5,     6,     7,     8,     9,     0,     0,
     178,     0,     0,     0,   179,     0,     0,     0,    10,    11,
       0,    12,     0,    13,    14,    15,    16,     0,    17,    18,
      19,    20,     0,     0,    21,     0,     0,     0,     0,    22,
      23,    24,    25,    26,    27,     0,     0,     0,    28,     0,
       0,     0,     0,    29,    30,   -19,     0,    31,     1,     2,
       0,     0,     3,     4,     5,     6,     7,     8,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    10,
      11,     0,    12,     0,    13,    14,    15,    16,     0,    17,
      18,    19,    20,     0,     0,    21,     0,     0,     0,     0,
      22,    23,    24,    25,    26,    27,     0,     0,     0,    28,
       0,     0,     0,     0,    29,    30,     0,     0,    31,     3,
       4,     5,     6,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    10,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    17,    18,    19,    20,
       0,     0,    21,     0,     0,     0,     0,    22,    23,    24,
      25,    26,    27,     0,     0,     0,    28,     0,     0,     0,
       0,    29,     0,     0,     0,    31,    86,    87,    88,    89,
      90,    91,    92,    93,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,    95,    96,    97,    86,    87,    88,    89,    90,
      91,    92,    93,    98,    99,   100,   101,   102,   103,     0,
       0,     0,     0,     0,     0,     0,   160,     0,     0,     0,
      94,    95,    96,    97,    86,    87,    88,    89,    90,    91,
      92,    93,    98,    99,   100,   101,   102,   103,     0,     0,
       0,     0,     0,     0,   123,     0,     0,     0,     0,    94,
      95,    96,    97,    86,    87,    88,    89,    90,    91,    92,
      93,    98,    99,   100,   101,   102,   103,     0,     0,     0,
       0,     0,     0,   155,     0,     0,     0,     0,    94,    95,
      96,    97,    86,    87,    88,    89,    90,    91,    92,    93,
      98,    99,   100,   101,   102,   103,     0,     0,     0,     0,
       0,     0,   156,     0,     0,     0,     0,    94,    95,    96,
      97,    86,    87,    88,    89,    90,    91,    92,    93,    98,
      99,   100,   101,   102,   103,     0,     0,     0,     0,     0,
       0,   157,     0,     0,     0,     0,    94,    95,    96,    97,
      86,    87,    88,    89,    90,    91,    92,    93,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,     0,     0,
     175,     0,     0,     0,     0,    94,    95,    96,    97,    86,
      87,    88,    89,    90,    91,    92,    93,    98,    99,   100,
     101,   102,   103,     0,     0,     0,     0,     0,   126,     0,
       0,     0,     0,     0,    94,    95,    96,    97,    86,    87,
      88,    89,    90,    91,    92,    93,    98,    99,   100,   101,
     102,   103,     0,     0,     0,     0,     0,   148,     0,     0,
       0,     0,     0,    94,    95,    96,    97,    86,    87,    88,
      89,    90,    91,    92,    93,    98,    99,   100,   101,   102,
     103,     0,     0,     0,     0,     0,   154,     0,     0,     0,
       0,     0,    94,    95,    96,    97,    86,    87,    88,    89,
      90,    91,    92,    93,    98,    99,   100,   101,   102,   103,
       0,     0,     0,     0,     0,   158,     0,     0,     0,     0,
       0,    94,    95,    96,    97,    86,    87,    88,    89,    90,
      91,    92,    93,    98,    99,   100,   101,   102,   103,     0,
       0,     0,     0,     0,   159,     0,     0,     0,     0,     0,
      94,    95,    96,    97,    86,    87,    88,    89,    90,    91,
      92,    93,    98,    99,   100,   101,   102,   103,     0,     0,
       0,     0,     0,   162,     0,     0,     0,     0,     0,    94,
      95,    96,    97,    86,    87,    88,    89,    90,    91,    92,
      93,    98,    99,   100,   101,   102,   103,     0,     0,     0,
       0,     0,   172,     0,     0,     0,     0,     0,    94,    95,
      96,    97,    86,    87,    88,    89,    90,    91,    92,    93,
      98,    99,   100,   101,   102,   103,     0,     0,     0,     0,
       0,   173,     0,     0,     0,     0,     0,    94,    95,    96,
      97,    86,    87,    88,    89,    90,    91,    92,    93,    98,
      99,   100,   101,   102,   103,     0,     0,     0,     0,     0,
     176,     0,     0,     0,     0,     0,    94,    95,    96,    97,
      86,    87,    88,    89,    90,    91,    92,    93,    98,    99,
     100,   101,   102,   103,     0,     0,     0,     0,     0,   177,
       0,     0,     0,     0,     0,    94,    95,    96,    97,    86,
      87,    88,    89,    90,    91,    92,    93,    98,    99,   100,
     101,   102,   103,     0,     0,     0,     0,     0,   180,     0,
       0,     0,     0,     0,    94,    95,    96,    97,    86,    87,
      88,    89,    90,    91,    92,     0,    98,    99,   100,   101,
     102,   103,     0,     0,     0,     0,    86,    87,    88,    89,
      90,    91,     0,    94,    95,    96,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    98,    99,   100,   101,   102,
     103,    94,    95,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    98,    99,   100,   101,   102,   103
};

static const short yycheck[] =
{
       1,     2,    33,   108,    67,    11,   111,     0,     1,    10,
      62,    74,    13,    62,    78,    78,    70,    71,    72,    73,
      21,    56,    57,    78,    55,    62,    62,    28,    29,    62,
      31,    78,    62,    68,    69,    70,    71,    72,    73,    68,
      69,    70,    71,    72,    73,    62,    78,    62,    79,    67,
      78,    78,    53,    78,    78,    78,    78,    76,    48,    80,
      73,    81,   167,    64,    65,    66,    67,    77,    69,    70,
      71,    72,    73,    74,    29,    80,    80,    80,    75,    79,
      67,    30,     9,     2,   110,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   110,    73,    -1,   123,    -1,    -1,
      -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,
      -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   146,   147,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   155,   156,   157,    18,    19,    -1,
      -1,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
     171,    -1,    -1,    -1,   175,    -1,    -1,    -1,    39,    40,
      -1,    42,    -1,    44,    45,    46,    47,    -1,    49,    50,
      51,    52,    -1,    -1,    55,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    -1,    -1,    -1,    69,    -1,
      -1,    -1,    -1,    74,    75,    76,    -1,    78,    18,    19,
      -1,    -1,    22,    23,    24,    25,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    -1,    42,    -1,    44,    45,    46,    47,    -1,    49,
      50,    51,    52,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    74,    75,    -1,    -1,    78,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    50,    51,    52,
      -1,    -1,    55,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,    -1,    -1,    -1,    69,    -1,    -1,    -1,
      -1,    74,    -1,    -1,    -1,    78,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    31,    32,    33,    34,    35,
      36,    37,    38,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      56,    57,    58,    59,    31,    32,    33,    34,    35,    36,
      37,    38,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    31,    32,    33,    34,    35,    36,    37,
      38,    68,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    31,    32,    33,    34,    35,    36,    37,    38,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    31,    32,    33,    34,    35,    36,    37,    38,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      31,    32,    33,    34,    35,    36,    37,    38,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    31,
      32,    33,    34,    35,    36,    37,    38,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    31,    32,
      33,    34,    35,    36,    37,    38,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,
      -1,    -1,    -1,    56,    57,    58,    59,    31,    32,    33,
      34,    35,    36,    37,    38,    68,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    31,    32,    33,    34,
      35,    36,    37,    38,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    31,    32,    33,    34,    35,
      36,    37,    38,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    31,    32,    33,    34,    35,    36,
      37,    38,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    31,    32,    33,    34,    35,    36,    37,
      38,    68,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    31,    32,    33,    34,    35,    36,    37,    38,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    31,    32,    33,    34,    35,    36,    37,    38,    68,
      69,    70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      31,    32,    33,    34,    35,    36,    37,    38,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    79,
      -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    31,
      32,    33,    34,    35,    36,    37,    38,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    31,    32,
      33,    34,    35,    36,    37,    -1,    68,    69,    70,    71,
      72,    73,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    -1,    56,    57,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    18,    19,    22,    23,    24,    25,    26,    27,    28,
      39,    40,    42,    44,    45,    46,    47,    49,    50,    51,
      52,    55,    60,    61,    62,    63,    64,    65,    69,    74,
      75,    78,    83,    84,    85,    88,    90,    91,    92,    94,
      98,    99,   100,   101,   103,    91,    97,    97,    62,    62,
      78,    78,    62,    78,    93,    93,    91,    62,    95,    96,
      98,    62,    91,    62,    78,    78,    78,    78,    91,    78,
      78,    67,    74,    78,    78,    91,    91,   104,   105,    84,
      89,    91,     0,     1,    85,    76,    31,    32,    33,    34,
      35,    36,    37,    38,    56,    57,    58,    59,    68,    69,
      70,    71,    72,    73,    80,    62,    62,    91,    86,    85,
      80,   102,    48,    91,    91,    91,    91,    91,    91,    91,
      91,   104,    91,    80,    81,    77,    79,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    80,    80,    79,    88,
      29,    96,    88,    91,    79,    80,    80,    80,    79,    79,
      81,    79,    79,   105,    91,    91,    85,    87,    91,    91,
      91,    67,    79,    79,    88,    80,    79,    79,    91,    91,
      79
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 51 ".\\parse.y"
    { root = stmt1(BLOCK, yyvsp[0].node); return 1; }
    break;

  case 4:
#line 52 ".\\parse.y"
    { yyclearin; yyerrok; }
    break;

  case 6:
#line 56 ".\\parse.y"
    { yyval.node = lknodes(yyvsp[-1].node, yyvsp[0].node); }
    break;

  case 8:
#line 60 ".\\parse.y"
    { inloop++; }
    break;

  case 9:
#line 61 ".\\parse.y"
    { yyval.node = stmt2(WHILE, yyvsp[-2].node, yyvsp[0].node); inloop--; }
    break;

  case 10:
#line 62 ".\\parse.y"
    { inloop++; }
    break;

  case 11:
#line 63 ".\\parse.y"
    { yyval.node = stmt3(FOREACH, symtonode(yyvsp[-4].sym), yyvsp[-2].node, yyvsp[0].node); inloop--;}
    break;

  case 12:
#line 64 ".\\parse.y"
    { yyval.node = stmt3(IF, yyvsp[-1].node, yyvsp[0].node, 0); }
    break;

  case 13:
#line 65 ".\\parse.y"
    { yyval.node = stmt3(IF, yyvsp[-3].node, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 16:
#line 70 ".\\parse.y"
    { yyval.node = stmt1(BLOCK, yyvsp[-1].node); }
    break;

  case 17:
#line 73 ".\\parse.y"
    { yyval.node = 0; }
    break;

  case 19:
#line 77 ".\\parse.y"
    { yyval.node = 0; }
    break;

  case 22:
#line 80 ".\\parse.y"
    { yyval.node = stmt1(PRINT, yyvsp[0].node); }
    break;

  case 23:
#line 81 ".\\parse.y"
    { yyval.node = stmt1(PRINTLN, yyvsp[0].node); }
    break;

  case 24:
#line 82 ".\\parse.y"
    { defnonly("return"); yyval.node = stmt1(RETURN, yyvsp[0].node); }
    break;

  case 25:
#line 83 ".\\parse.y"
    { looponly("break"); yyval.node = stmt0(BREAK); }
    break;

  case 26:
#line 84 ".\\parse.y"
    { looponly("continue"); yyval.node = stmt0(CONTINUE); }
    break;

  case 32:
#line 92 ".\\parse.y"
    { yyval.node = op2(LSHIFT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 33:
#line 93 ".\\parse.y"
    { yyval.node = op2(RSHIFT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 34:
#line 94 ".\\parse.y"
    { yyval.node = op2(PLUS, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 35:
#line 95 ".\\parse.y"
    { yyval.node = op2(SUB, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 36:
#line 96 ".\\parse.y"
    { yyval.node = op2(MULT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 37:
#line 97 ".\\parse.y"
    { yyval.node = op2(DIV, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 38:
#line 98 ".\\parse.y"
    { yyval.node = op2(MOD, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 39:
#line 99 ".\\parse.y"
    { yyval.node = op2(EXP, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 40:
#line 100 ".\\parse.y"
    { yyval.node = stmt1(UNARYMINUS, yyvsp[0].node); }
    break;

  case 41:
#line 101 ".\\parse.y"
    { yyval.node = op2(GT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 42:
#line 102 ".\\parse.y"
    { yyval.node = op2(GE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 43:
#line 103 ".\\parse.y"
    { yyval.node = op2(LT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 44:
#line 104 ".\\parse.y"
    { yyval.node = op2(LE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 45:
#line 105 ".\\parse.y"
    { yyval.node = op2(EQ, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 46:
#line 106 ".\\parse.y"
    { yyval.node = op2(NE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 47:
#line 107 ".\\parse.y"
    { yyval.node = op2(AND, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 48:
#line 108 ".\\parse.y"
    { yyval.node = op2(BAND, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 49:
#line 109 ".\\parse.y"
    { yyval.node = op2(OR, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 50:
#line 110 ".\\parse.y"
    { yyval.node = op2(BOR, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 51:
#line 111 ".\\parse.y"
    { yyval.node = stmt1(yyvsp[-3].sym->sub, yyvsp[-1].node); }
    break;

  case 52:
#line 112 ".\\parse.y"
    { yyval.node = op1(NOT, yyvsp[0].node); }
    break;

  case 53:
#line 113 ".\\parse.y"
    { yyval.node = op1(BNOT, yyvsp[0].node); }
    break;

  case 54:
#line 114 ".\\parse.y"
    { yyval.node = stmt1(LENGTH, symtonode(yyvsp[0].sym)); }
    break;

  case 55:
#line 115 ".\\parse.y"
    { yyval.node = stmt1(SHIFT, symtonode(yyvsp[0].sym)); }
    break;

  case 56:
#line 116 ".\\parse.y"
    { yyval.node = stmt2(UNSHIFT, symtonode(yyvsp[-3].sym), yyvsp[-1].node); }
    break;

  case 57:
#line 117 ".\\parse.y"
    { yyval.node = stmt2(PUSH, symtonode(yyvsp[-3].sym), yyvsp[-1].node); }
    break;

  case 58:
#line 118 ".\\parse.y"
    { yyval.node = stmt1(POP, symtonode(yyvsp[0].sym)); }
    break;

  case 59:
#line 119 ".\\parse.y"
    { yyval.node = stmt1(STRLEN, yyvsp[-1].node); }
    break;

  case 60:
#line 120 ".\\parse.y"
    { yyval.node = stmt3(SUBSTR, yyvsp[-5].node, yyvsp[-3].node, yyvsp[-1].node); }
    break;

  case 61:
#line 121 ".\\parse.y"
    { yyval.node = stmt2(STRCAT, yyvsp[-3].node, yyvsp[-1].node); }
    break;

  case 62:
#line 122 ".\\parse.y"
    { yyval.node = stmt2(INDEX, yyvsp[-3].node, yyvsp[-1].node); }
    break;

  case 63:
#line 123 ".\\parse.y"
    { yyval.node = stmt1(ASC, yyvsp[-1].node); }
    break;

  case 64:
#line 124 ".\\parse.y"
    { yyval.node = stmt1(CHR, yyvsp[-1].node); }
    break;

  case 65:
#line 125 ".\\parse.y"
    { yyval.node = stmt1(MKLIST, yyvsp[-1].node); }
    break;

  case 66:
#line 128 ".\\parse.y"
    { yyval.node = symtonode(yyvsp[0].sym); }
    break;

  case 67:
#line 129 ".\\parse.y"
    { yyval.node = symtonode(yyvsp[0].sym); }
    break;

  case 68:
#line 130 ".\\parse.y"
    { yyval.node = symtonode(yyvsp[0].sym); }
    break;

  case 69:
#line 131 ".\\parse.y"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 70:
#line 134 ".\\parse.y"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 71:
#line 137 ".\\parse.y"
    { yyval.node = stmt1(yyvsp[-1].n, yyvsp[0].node); }
    break;

  case 73:
#line 141 ".\\parse.y"
    { yyval.node = lknodes(yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 74:
#line 144 ".\\parse.y"
    { yyvsp[0].sym->type = SVAR; yyval.node = symtonode(yyvsp[0].sym); }
    break;

  case 77:
#line 149 ".\\parse.y"
    { yyval.node = lknodes(yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 78:
#line 152 ".\\parse.y"
    { yyvsp[-2].sym->type = SVAR; yyval.node = stmt2(ASGN, symtonode(yyvsp[-2].sym), yyvsp[0].node); }
    break;

  case 79:
#line 155 ".\\parse.y"
    { yyval.node = stmt3(SUBASGN, symtonode(yyvsp[-5].sym), yyvsp[-3].node, yyvsp[0].node); }
    break;

  case 80:
#line 158 ".\\parse.y"
    { yyval.node = stmt2(SUBSCR, symtonode(yyvsp[-3].sym), yyvsp[-1].node); }
    break;

  case 81:
#line 161 ".\\parse.y"
    {
			if (yyvsp[0].sym->type != SUNDEF) {
				error("%s already defined near line %d.",
				yyvsp[0].sym->name, lineno);
			}
			yyvsp[0].sym->type = SFUNC; indef++;
		}
    break;

  case 82:
#line 168 ".\\parse.y"
    { yyval.node = stmt2(DEF, symtonode(yyvsp[-2].sym), yyvsp[0].node); indef--; }
    break;

  case 83:
#line 171 ".\\parse.y"
    { 
			if (yyvsp[-3].sym->type != SFUNC) {
				error("%s not a function near line %d.", yyvsp[-3].sym->name, lineno);
			}
			yyval.node = stmt2(CALL, symtonode(yyvsp[-3].sym), yyvsp[-1].node); }
    break;

  case 84:
#line 178 ".\\parse.y"
    { yyval.node = 0; }
    break;

  case 87:
#line 183 ".\\parse.y"
    { yyval.node = lknodes(yyvsp[-2].node, yyvsp[0].node); }
    break;


    }

/* Line 999 of yacc.c.  */
#line 1780 "y.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 185 ".\\parse.y"
	
    /* end grammar */

void defnonly(const char *s)
{
	if (!indef)
		error("%s used outside definition near line %d.",
			s, lineno);
}

void looponly(const char *s)
{
	if (!inloop)
		error("%s used outside loop near line %d.",
			s, lineno);
}
    
/* error during parsing */
int yyerror(const char *s)
{
	error("%s near line number %d.", s, lineno);
	return 0;
}

