BUILT_SOURCES = parser.h
AM_YFLAGS = -d
AM_CFLAGS = -Wall -Wstrict-prototypes
bin_PROGRAMS = xi
xi_SOURCES =		\
	block.c		\
	block.h		\
	eval.c 		\
	eval.h		\
	global.c	\
	global.h	\
	lexer.l		\
	list.c		\
	list.h		\
	main.c		\
	parser.y	\
	proctab.c	\
	proctab.h	\
	symbol.c	\
	symbol.h	\
	temp.c		\
	temp.h		\
	tree.c		\
	tree.h		\
	x.c		\
	x.h		\
	xmalloc.c	\
	xmalloc.h

xi_LDADD = @LEXLIB@ -lm

