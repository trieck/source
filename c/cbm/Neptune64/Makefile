################################################################################
#
# Teeny-Tiny 6502 Monitor 
#
CC = gcc
COMMONDIR = ../common
CFLAGS = -Wall -ansi -I$(COMMONDIR)
DBGFLAGS = -g
OBJECTS = instr.o \
	symbol.o \
	assem.o \
	disassem.o \
	opcodes.o \
	machine.o \
	main.o \
	common.o \
	parser.o \
	code.o \
	video.o
 
TARGETDIR = $(HOME)/local/bin
TARGET = $(TARGETDIR)/mon
LINKFLAGS = -o $(TARGET)
# suffix rules
.SUFFIXES: .o .c
.c.o:
	$(CC) $(CFLAGS) -c $<
mon:	$(OBJECTS)
	$(CC) $(CFLAGS) $(LINKFLAGS) $(OBJECTS)
common.o:
	$(CC) $(CFLAGS) -c $(COMMONDIR)/common.c
clean:
	@rm -rf *.o
	@rm -f $(TARGET)
	@rm -f $(TARGETDIR)/core
	@rm -f core
