CC = gcc
CFLAGS = -Wall -ansi
#DBGFLAGS = -g
OBJECTS = gff.o
TARGETDIR = bin
TARGET = $(TARGETDIR)/gff
LINKFLAGS = -o $(TARGET)

# suffix rules
.SUFFIXES: .o .c
.c.o:
	$(CC) $(CFLAGS) -c $<

gff:	$(OBJECTS)
	$(CC) $(CFLAGS) $(LINKFLAGS) $(OBJECTS)

gff.o:	gff.c \
	gff.h

clean:
	@rm -rf *.o
	@rm -f $(TARGET)
	@rm -f $(TARGET).exe
	@rm -f $(TARGETDIR)/core
	@rm -f core

