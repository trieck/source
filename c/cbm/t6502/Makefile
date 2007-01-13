#######################################################################
#
# Teeny-Tiny 6502 Assembler
#
CC = gcc
COMMONDIR = ../common
CFLAGS = -ansi -I${COMMONDIR} -Wall
OBJECTS = main.o 	\
	code.o 			\
	label.o 		\
	opcodes.o 		\
	symbol.o 		\
	assem.o 		\
	common.o		\
	extern.o

TARGETDIR = ../bin
TARGET = ${TARGETDIR}/t6502
LINKFLAGS = -o ${TARGET}

# suffix rules
.SUFFIXES: .o .c
.c.o:
	${CC} ${CFLAGS} -c $<
	
t6502: ${OBJECTS}
	${CC} ${CFLAGS} ${LINKFLAGS} ${OBJECTS}
	
common.o:
	${CC} ${CFLAGS} -c ${COMMONDIR}/common.c
	
indent:
	@indent -kr --use-tabs --tab-size4 *.c *.h 
	@rm -f *~

clean:
	@rm -rf *.o
	@rm -f ${TARGET}
	@rm -f ${TARGETDIR}/*.out
	@rm -f ${TARGETDIR}/core
