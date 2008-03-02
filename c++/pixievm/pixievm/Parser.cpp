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

/* Bison version.  */
#define YYBISON_VERSION "2.1"

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




/* Copy the first part of user declarations.  */
#line 1 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"

#include "Common.h"
#include "Modes.h"
#include "Instructions.h"
#include "SymbolTable.h"
#include "Code.h"
#include "Exception.h"

extern int yylex(void);
extern int yyterminate(void);
static int yyerror(const char *s);


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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 14 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
typedef union YYSTYPE {
	int n;				/* token id */
	LPSYMBOL sym;		/* symbol table pointer */
} YYSTYPE;
/* Line 196 of yacc.c.  */
#line 137 "Parser.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 219 of yacc.c.  */
#line 149 "Parser.cpp"

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if defined (__STDC__) || defined (__cplusplus)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     define YYINCLUDED_STDLIB_H
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
#  endif
#  ifdef __cplusplus
extern "C" {
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifdef __cplusplus
}
#  endif
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
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
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  38
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   90

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  21
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  5
/* YYNRULES -- Number of rules. */
#define YYNRULES  53
/* YYNRULES -- Number of states. */
#define YYNSTATES  91

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   272

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    18,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    19,     2,    20,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     8,    13,    18,    23,    28,    33,
      38,    43,    48,    53,    58,    63,    69,    75,    80,    85,
      90,    96,   102,   107,   110,   113,   117,   121,   125,   129,
     131,   134,   137,   140,   143,   146,   149,   152,   155,   159,
     163,   167,   171,   174,   177,   181,   185,   189,   193,   196,
     199,   203,   207,   211
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      22,     0,    -1,     5,    -1,    23,     5,    -1,     6,    13,
      18,    13,    -1,     6,    13,    18,    16,    -1,     6,    13,
      18,    24,    -1,     6,    13,    18,    25,    -1,     6,    14,
      18,    14,    -1,     6,    14,    18,    16,    -1,     6,    14,
      18,    17,    -1,     6,    14,    18,    24,    -1,     6,    14,
      18,    25,    -1,     6,    24,    18,    13,    -1,     6,    24,
      18,    14,    -1,     6,     3,    24,    18,    16,    -1,     6,
       4,    24,    18,    16,    -1,     6,    24,    18,    17,    -1,
       6,    25,    18,    13,    -1,     6,    25,    18,    14,    -1,
       6,     3,    25,    18,    16,    -1,     6,     4,    25,    18,
      16,    -1,     6,    25,    18,    17,    -1,     7,    13,    -1,
       7,    14,    -1,     7,     3,    24,    -1,     7,     4,    24,
      -1,     7,     3,    25,    -1,     7,     4,    25,    -1,     8,
      -1,     9,    14,    -1,     9,    24,    -1,     9,    25,    -1,
       9,    16,    -1,     9,    17,    -1,    10,    16,    -1,    11,
      13,    -1,    11,    14,    -1,    11,     3,    24,    -1,    11,
       4,    24,    -1,    11,     3,    25,    -1,    11,     4,    25,
      -1,    12,    13,    -1,    12,    14,    -1,    12,     3,    24,
      -1,    12,     4,    24,    -1,    12,     3,    25,    -1,    12,
       4,    25,    -1,    12,    16,    -1,    12,    17,    -1,    19,
      14,    20,    -1,    19,    15,    20,    -1,    19,    16,    20,
      -1,    19,    17,    20,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    27,    27,    28,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      79,    80,    83,    84
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BYTE", "WORD", "EOL", "I1", "I2", "I3",
  "I4", "I5", "I6", "I7", "R8", "R16", "RX16", "IM8", "IM16", "','", "'['",
  "']'", "$accept", "prog", "instr", "M16", "A16", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,    44,    91,
      93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    21,    22,    22,    23,    23,    23,    23,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    23,    23,
      24,    24,    25,    25
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     2,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     5,     5,     4,     4,     4,
       5,     5,     4,     2,     2,     3,     3,     3,     3,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     3,     3,
       3,     3,     2,     2,     3,     3,     3,     3,     2,     2,
       3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     2,     0,     0,    29,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      23,    24,    30,    33,    34,    31,    32,    35,     0,     0,
      36,    37,     0,     0,    42,    43,    48,    49,     1,     3,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    25,    27,    26,    28,    38,    40,    39,    41,
      44,    46,    45,    47,     0,     0,     0,     0,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    50,    51,    52,
      53,    13,    14,    17,    18,    19,    22,    15,    20,    16,
      21
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     9,    10,    16,    17
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -16
static const yysigned_char yypact[] =
{
      57,   -16,    18,    45,   -16,    38,   -15,    47,    30,     4,
      -2,   -14,   -14,    -8,    -7,     3,    -6,    17,   -14,   -14,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -14,   -14,
     -16,   -16,   -14,   -14,   -16,   -16,   -16,   -16,   -16,   -16,
      20,    27,    35,    68,    58,    56,    16,    36,    63,    69,
      65,    67,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16,   -16,   -16,   -16,    60,    71,    72,    74,   -16,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -16,   -16,   -16,    -5,    -3
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      25,    27,    26,    39,    38,    15,    40,    42,    41,    43,
      44,    45,    50,    52,    54,    53,    55,    46,    47,    48,
      49,    11,    12,    56,    58,    57,    59,    60,    62,    61,
      63,    13,    14,    32,    33,    51,    77,    15,    64,    70,
      75,    71,    76,    34,    35,    65,    36,    37,    18,    19,
      28,    29,    22,    66,    23,    24,    78,    15,    20,    21,
      30,    31,     1,     2,     3,     4,     5,     6,     7,     8,
      72,    68,    73,    74,    69,    15,    87,    15,    81,    82,
      84,    85,    83,    79,    86,     0,    67,    88,    89,    80,
      90
};

static const yysigned_char yycheck[] =
{
       5,    16,     5,     5,     0,    19,    11,    12,    11,    12,
      18,    18,    18,    18,    19,    18,    19,    14,    15,    16,
      17,     3,     4,    28,    29,    28,    29,    32,    33,    32,
      33,    13,    14,     3,     4,    18,    20,    19,    18,    44,
      45,    44,    45,    13,    14,    18,    16,    17,     3,     4,
       3,     4,    14,    18,    16,    17,    20,    19,    13,    14,
      13,    14,     5,     6,     7,     8,     9,    10,    11,    12,
      14,    13,    16,    17,    16,    19,    16,    19,    13,    14,
      13,    14,    17,    20,    17,    -1,    18,    16,    16,    20,
      16
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     5,     6,     7,     8,     9,    10,    11,    12,    22,
      23,     3,     4,    13,    14,    19,    24,    25,     3,     4,
      13,    14,    14,    16,    17,    24,    25,    16,     3,     4,
      13,    14,     3,     4,    13,    14,    16,    17,     0,     5,
      24,    25,    24,    25,    18,    18,    14,    15,    16,    17,
      18,    18,    24,    25,    24,    25,    24,    25,    24,    25,
      24,    25,    24,    25,    18,    18,    18,    18,    13,    16,
      24,    25,    14,    16,    17,    24,    25,    20,    20,    20,
      20,    13,    14,    17,    13,    14,    17,    16,    16,    16,
      16
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


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
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (0)
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
              (Loc).first_line, (Loc).first_column,	\
              (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr,					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
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
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
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
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

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
  const char *yys = yystr;

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
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* YYERROR_VERBOSE */



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
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
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
    ;
#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



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
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
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
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

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
        case 2:
#line 27 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { YYABORT; }
    break;

  case 3:
#line 28 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { YYACCEPT; }
    break;

  case 4:
#line 31 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_RR8, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 5:
#line 32 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_RI8, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 6:
#line 33 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_RM8, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 7:
#line 34 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_RA8, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 8:
#line 35 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_RR16, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 9:
#line 36 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_RI16, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 10:
#line 37 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_RI16, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 11:
#line 38 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_RM16, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 12:
#line 39 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_RA16, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 13:
#line 40 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_MR8, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 14:
#line 41 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_MR16, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 15:
#line 42 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_M8I8, (yyvsp[-4].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 16:
#line 43 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_M16I8, (yyvsp[-4].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 17:
#line 44 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_MI16, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 18:
#line 45 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_AR8, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 19:
#line 46 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_AR16, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 20:
#line 47 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_A8I8, (yyvsp[-4].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 21:
#line 48 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_A16I8, (yyvsp[-4].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 22:
#line 49 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code3(AM_AI16, (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 23:
#line 50 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_R8, (yyvsp[-1].sym), (yyvsp[0].sym)); }
    break;

  case 24:
#line 51 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_R16, (yyvsp[-1].sym), (yyvsp[0].sym)); }
    break;

  case 25:
#line 52 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_M8, (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 26:
#line 53 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_M16, (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 27:
#line 54 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_A8, (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 28:
#line 55 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_A16, (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 29:
#line 56 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code1(AM_IMPLIED, (yyvsp[0].sym)); }
    break;

  case 30:
#line 57 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_R16, (yyvsp[-1].sym), (yyvsp[0].sym)); }
    break;

  case 31:
#line 58 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_M16, (yyvsp[-1].sym), (yyvsp[0].sym)); }
    break;

  case 32:
#line 59 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_A16, (yyvsp[-1].sym), (yyvsp[0].sym)); }
    break;

  case 33:
#line 60 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_I16, (yyvsp[-1].sym), (yyvsp[0].sym)); }
    break;

  case 34:
#line 61 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_I16, (yyvsp[-1].sym), (yyvsp[0].sym)); }
    break;

  case 35:
#line 62 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_I8, (yyvsp[-1].sym), (yyvsp[0].sym)); }
    break;

  case 36:
#line 63 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_R8, (yyvsp[-1].sym), (yyvsp[0].sym)); }
    break;

  case 37:
#line 64 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_R16, (yyvsp[-1].sym), (yyvsp[0].sym)); }
    break;

  case 38:
#line 65 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_M8, (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 39:
#line 66 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_M16, (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 40:
#line 67 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_A8, (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 41:
#line 68 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_A16, (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 42:
#line 69 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_R8, (yyvsp[-1].sym), (yyvsp[0].sym)); }
    break;

  case 43:
#line 70 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_R16, (yyvsp[-1].sym), (yyvsp[0].sym)); }
    break;

  case 44:
#line 71 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_M8, (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 45:
#line 72 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_M16, (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 46:
#line 73 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_A8, (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 47:
#line 74 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_A16, (yyvsp[-2].sym), (yyvsp[0].sym)); }
    break;

  case 48:
#line 75 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_I8, (yyvsp[-1].sym), (yyvsp[0].sym)); }
    break;

  case 49:
#line 76 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { code2(AM_I16, (yyvsp[-1].sym), (yyvsp[0].sym)); }
    break;

  case 50:
#line 79 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { (yyval.sym) = (yyvsp[-1].sym); }
    break;

  case 51:
#line 80 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { (yyval.sym) = (yyvsp[-1].sym); }
    break;

  case 52:
#line 83 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { (yyval.sym) = (yyvsp[-1].sym); }
    break;

  case 53:
#line 84 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
    { (yyval.sym) = (yyvsp[-1].sym); }
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 1473 "Parser.cpp"

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
	  int yytype = YYTRANSLATE (yychar);
	  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
	  YYSIZE_T yysize = yysize0;
	  YYSIZE_T yysize1;
	  int yysize_overflow = 0;
	  char *yymsg = 0;
#	  define YYERROR_VERBOSE_ARGS_MAXIMUM 5
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;

#if 0
	  /* This is so xgettext sees the translatable formats that are
	     constructed on the fly.  */
	  YY_("syntax error, unexpected %s");
	  YY_("syntax error, unexpected %s, expecting %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
#endif
	  char *yyfmt;
	  char const *yyf;
	  static char const yyunexpected[] = "syntax error, unexpected %s";
	  static char const yyexpecting[] = ", expecting %s";
	  static char const yyor[] = " or %s";
	  char yyformat[sizeof yyunexpected
			+ sizeof yyexpecting - 1
			+ ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
			   * (sizeof yyor - 1))];
	  char const *yyprefix = yyexpecting;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 1;

	  yyarg[0] = yytname[yytype];
	  yyfmt = yystpcpy (yyformat, yyunexpected);

	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
		  {
		    yycount = 1;
		    yysize = yysize0;
		    yyformat[sizeof yyunexpected - 1] = '\0';
		    break;
		  }
		yyarg[yycount++] = yytname[yyx];
		yysize1 = yysize + yytnamerr (0, yytname[yyx]);
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + yystrlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
	    yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg)
	    {
	      /* Avoid sprintf, as that infringes on the user's name space.
		 Don't have undefined behavior even if the translation
		 produced a string with the wrong number of "%s"s.  */
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
		{
		  if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		    {
		      yyp += yytnamerr (yyp, yyarg[yyi++]);
		      yyf += 2;
		    }
		  else
		    {
		      yyp++;
		      yyf++;
		    }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      goto yyexhaustedlab;
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (0)
     goto yyerrorlab;

yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK;
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 87 "d:\\source\\c++\\pixievm\\pixievm\\grammar.y"
	/* end grammar */
    
int yyerror(const char *s)
{
	throw Exception(s);	
	return 0;
}

