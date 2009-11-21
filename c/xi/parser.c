#ifndef lint
static char const
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.28 2000/01/17 02:04:06 bde Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
static int yygrowstack();
#define YYPREFIX "yy"
#line 2 ".\parser.y"
#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"
#include "tree.h"
#include "x.h"

extern int yylex(void);
static int yyerror(const char *s);

extern int lineno;
extern Node *root;

#line 16 ".\parser.y"
typedef union {
	PNODE node;		/* node in parse tree */
	PSYMBOL sym;	/* symbol table pointer */
	int n;			/* token id */
} YYSTYPE;
#line 36 ".\parser.c"
#define YYERRCODE 256
#define FIRSTTOKEN 257
#define PLUS 258
#define SUB 259
#define MULT 260
#define DIV 261
#define MOD 262
#define RANGE 263
#define MKLIST 264
#define PRINT 265
#define PRINTLN 266
#define LET 267
#define LASTTOKEN 268
#define ARROW 269
#define CALL 270
#define NUMBER 271
#define ID 272
#define KEYWORD 273
const short yylhs[] = {                                        -1,
                      0,    0,    0,    1,    1,    2,    2,    2,    2,    2,
                      2,    2,    2,    3,    4,    4,    5,    5,    6,    6,
                      6,    7,    7,    8,
                      };
const short yylen[] = {                                         2,
                      0,    1,    2,    1,    2,    1,    2,    2,    2,    2,
                      2,    2,    3,    3,    0,    1,    1,    2,    1,    1,
                      1,    1,    1,    3,
                      };
const short yydefred[] = {                                      0,
                         0,    0,    0,    0,    6,   22,   23,    0,    0,   16,
                         0,    0,   21,    3,    0,    0,   12,    7,    8,    9,
                         10,   11,   14,   18,    0,   13,   24,
                         };
const short yydgoto[] = {                                       2,
                        3,    8,    5,    9,   10,   11,   12,   13,
                        };
const short yysindex[] = {                                    -73,
                         -77, -237,  -73,  -37,    0,    0,    0,  -37,  -72,    0,
                         -77, -243,    0,    0,  -37, -250,    0,    0,    0,    0,
                         0,    0,    0,    0, -255,    0,    0,
                         };
const short yyrindex[] = {                                      3,
                         -70,    0,    4,    1,    0,    0,    0,  -84,    0,    0,
                         -69,  -80,    0,    0,    2,    0,    0,    0,    0,    0,
                         0,    0,    0,    0,    0,    0,    0,
                         };
const short yygindex[] = {                                      0,
                         0,   12,    0,    0,   14,    0,    5,    0,
                         };
#define YYTABLESIZE 260
const short yytable[] = {                                      22,
                        4,    5,    1,    2,   20,   18,   19,   19,   19,   21,
                        20,    4,   20,    1,   15,    6,    7,    1,   14,   25,
                        23,   26,   15,   17,   24,    0,    0,    0,    0,   27,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    4,    5,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,   19,   19,    0,    0,
                        20,   20,    0,    6,    7,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,   16,    0,    0,    0,   17,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                        0,    0,    0,    0,    0,    0,    4,    5,    1,    2,
                        };
const short yycheck[] = {                                      37,
                        0,    0,    0,    0,   42,   43,   91,   45,   93,   47,
                        91,    0,   93,   91,    3,  271,  272,   91,  256,  263,
                        93,  272,   93,   93,   11,   -1,   -1,   -1,   -1,   25,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   91,   91,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,  271,  272,   -1,   -1,
                        271,  272,   -1,  271,  272,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,  269,   -1,   -1,   -1,  273,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                        -1,   -1,   -1,   -1,   -1,   -1,  256,  256,  256,  256,
                        };
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 273
#if YYDEBUG
const char * const yyname[] = {
	"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,"'%'",0,0,0,0,"'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	"FIRSTTOKEN","PLUS","SUB","MULT","DIV","MOD","RANGE","MKLIST","PRINT","PRINTLN",
	"LET","LASTTOKEN","ARROW","CALL","NUMBER","ID","KEYWORD",
};
const char * const yyrule[] = {
	"$accept : prog",
	"prog :",
	"prog : stmts",
	"prog : prog error",
	"stmts : expr",
	"stmts : stmts expr",
	"expr : list",
	"expr : expr '+'",
	"expr : expr '-'",
	"expr : expr '*'",
	"expr : expr '/'",
	"expr : expr '%'",
	"expr : expr KEYWORD",
	"expr : expr ARROW ID",
	"list : '[' items ']'",
	"items :",
	"items : item_list",
	"item_list : member",
	"item_list : member item_list",
	"member : expr",
	"member : primary",
	"member : range",
	"primary : NUMBER",
	"primary : ID",
	"range : primary RANGE primary",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 95 ".\parser.y"

/* end grammar */

/* parse error */
int yyerror(const char *s)
{
	error("%s near line no %d.", s, lineno);
	return 0;
}

#line 226 ".\parser.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
	int newsize, i;
	short *newss;
	YYSTYPE *newvs;

	if ((newsize = yystacksize) == 0)
		newsize = YYINITSTACKSIZE;
	else if (newsize >= YYMAXDEPTH)
		return -1;
	else if ((newsize *= 2) > YYMAXDEPTH)
		newsize = YYMAXDEPTH;
	i = yyssp - yyss;
	newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
	        (short *)malloc(newsize * sizeof *newss);
	if (newss == NULL)
		return -1;
	yyss = newss;
	yyssp = newss + i;
	newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
	        (YYSTYPE *)malloc(newsize * sizeof *newvs);
	if (newvs == NULL)
		return -1;
	yyvs = newvs;
	yyvsp = newvs + i;
	yystacksize = newsize;
	yysslim = yyss + newsize - 1;
	return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
YYPARSE_PARAM_DECL {
	register int yym, yyn, yystate;
#if YYDEBUG
	register const char *yys;

	if ((yys = getenv("YYDEBUG"))) {
		yyn = *yys;
		if (yyn >= '0' && yyn <= '9')
			yydebug = yyn - '0';
	}
#endif

	yynerrs = 0;
	yyerrflag = 0;
	yychar = (-1);

	if (yyss == NULL && yygrowstack()) goto yyoverflow;
	yyssp = yyss;
	yyvsp = yyvs;
	*yyssp = yystate = 0;

yyloop:
	if ((yyn = yydefred[yystate])) goto yyreduce;
	if (yychar < 0) {
		if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
		if (yydebug) {
			yys = 0;
			if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
			if (!yys) yys = "illegal-symbol";
			printf("%sdebug: state %d, reading %d (%s)\n",
			       YYPREFIX, yystate, yychar, yys);
		}
#endif
	}
	if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
	        yyn <= YYTABLESIZE && yycheck[yyn] == yychar) {
#if YYDEBUG
		if (yydebug)
			printf("%sdebug: state %d, shifting to state %d\n",
			       YYPREFIX, yystate, yytable[yyn]);
#endif
		if (yyssp >= yysslim && yygrowstack()) {
			goto yyoverflow;
		}
		*++yyssp = yystate = yytable[yyn];
		*++yyvsp = yylval;
		yychar = (-1);
		if (yyerrflag > 0)  --yyerrflag;
		goto yyloop;
	}
	if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
	        yyn <= YYTABLESIZE && yycheck[yyn] == yychar) {
		yyn = yytable[yyn];
		goto yyreduce;
	}
	if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
	goto yynewerror;
#endif
yynewerror:
	yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
	goto yyerrlab;
#endif
yyerrlab:
	++yynerrs;
yyinrecovery:
	if (yyerrflag < 3) {
		yyerrflag = 3;
		for (;;) {
			if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
			        yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE) {
#if YYDEBUG
				if (yydebug)
					printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
				if (yyssp >= yysslim && yygrowstack()) {
					goto yyoverflow;
				}
				*++yyssp = yystate = yytable[yyn];
				*++yyvsp = yylval;
				goto yyloop;
			} else {
#if YYDEBUG
				if (yydebug)
					printf("%sdebug: error recovery discarding state %d\n",
					       YYPREFIX, *yyssp);
#endif
				if (yyssp <= yyss) goto yyabort;
				--yyssp;
				--yyvsp;
			}
		}
	} else {
		if (yychar == 0) goto yyabort;
#if YYDEBUG
		if (yydebug) {
			yys = 0;
			if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
			if (!yys) yys = "illegal-symbol";
			printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
			       YYPREFIX, yystate, yychar, yys);
		}
#endif
		yychar = (-1);
		goto yyloop;
	}
yyreduce:
#if YYDEBUG
	if (yydebug)
		printf("%sdebug: state %d, reducing by rule %d (%s)\n",
		       YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
	yym = yylen[yyn];
	yyval = yyvsp[1-yym];
	switch (yyn) {
	case 2:
#line 39 ".\parser.y"
		{ root = mkstmt(MKLIST, yyvsp[0].node);
			return 1;
		}
		break;
	case 3:
#line 41 ".\parser.y"
		{ yyerrok;
		}
		break;
	case 5:
#line 46 ".\parser.y"
		{ yyval.node = lknodes(yyvsp[-1].node, yyvsp[0].node);
		}
		break;
	case 7:
#line 51 ".\parser.y"
		{ yyval.node = mkstmt(PLUS, yyvsp[-1].node);
		}
		break;
	case 8:
#line 53 ".\parser.y"
		{ yyval.node = mkstmt(SUB, yyvsp[-1].node);
		}
		break;
	case 9:
#line 55 ".\parser.y"
		{ yyval.node = mkstmt(MULT, yyvsp[-1].node);
		}
		break;
	case 10:
#line 57 ".\parser.y"
		{ yyval.node = mkstmt(DIV, yyvsp[-1].node);
		}
		break;
	case 11:
#line 59 ".\parser.y"
		{ yyval.node = mkstmt(MOD, yyvsp[-1].node);
		}
		break;
	case 12:
#line 61 ".\parser.y"
		{ yyval.node = mkstmt(yyvsp[0].sym->subtype, yyvsp[-1].node);
		}
		break;
	case 13:
#line 63 ".\parser.y"
		{ yyval.node = mkstmt2(CALL, yyvsp[-2].node, mkleaf(yyvsp[0].sym));
		}
		break;
	case 14:
#line 67 ".\parser.y"
		{ yyval.node = mkstmt(MKLIST, yyvsp[-1].node);
		}
		break;
	case 15:
#line 71 ".\parser.y"
		{ yyval.node = 0;
		}
		break;
	case 18:
#line 77 ".\parser.y"
		{ yyval.node = lknodes(yyvsp[-1].node, yyvsp[0].node);
		}
		break;
	case 22:
#line 86 ".\parser.y"
		{ yyval.node = mkleaf(yyvsp[0].sym);
		}
		break;
	case 23:
#line 88 ".\parser.y"
		{ yyval.node = mkleaf(yyvsp[0].sym);
		}
		break;
	case 24:
#line 92 ".\parser.y"
		{ yyval.node = mkstmt2(RANGE, yyvsp[-2].node, yyvsp[0].node);
		}
		break;
#line 485 ".\parser.c"
	}
	yyssp -= yym;
	yystate = *yyssp;
	yyvsp -= yym;
	yym = yylhs[yyn];
	if (yystate == 0 && yym == 0) {
#if YYDEBUG
		if (yydebug)
			printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
		yystate = YYFINAL;
		*++yyssp = YYFINAL;
		*++yyvsp = yyval;
		if (yychar < 0) {
			if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
			if (yydebug) {
				yys = 0;
				if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
				if (!yys) yys = "illegal-symbol";
				printf("%sdebug: state %d, reading %d (%s)\n",
				       YYPREFIX, YYFINAL, yychar, yys);
			}
#endif
		}
		if (yychar == 0) goto yyaccept;
		goto yyloop;
	}
	if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
	        yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
		yystate = yytable[yyn];
	else
		yystate = yydgoto[yym];
#if YYDEBUG
	if (yydebug)
		printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
	if (yyssp >= yysslim && yygrowstack()) {
		goto yyoverflow;
	}
	*++yyssp = yystate;
	*++yyvsp = yyval;
	goto yyloop;
yyoverflow:
	yyerror("yacc stack overflow");
yyabort:
	return (1);
yyaccept:
	return (0);
}
