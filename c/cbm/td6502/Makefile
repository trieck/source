#######################################################################
#
# Teeny-Tiny 6502 Disassembler 
#
CC = gcc
COMMONDIR = ../common
CFLAGS = -ansi -I${COMMONDIR} -Wall
OBJECTS = main.o code.o common.o opcodes.o
TARGETDIR = ${HOME}/local/bin
TARGET = ${TARGETDIR}/td6502
LINKFLAGS = -o ${TARGET}
# suffix rules
.SUFFIXES: .o .c
.c.o:
	${CC} ${CFLAGS} -c $<
td6502: ${OBJECTS}
	${CC} ${CFLAGS} ${LINKFLAGS} ${OBJECTS}
common.o:
	${CC} ${CFLAGS} -c ${COMMONDIR}/common.c
clean:
	@rm -rf *.o
	@rm -f ${TARGET}
	@rm -f ${TARGETDIR}/core
