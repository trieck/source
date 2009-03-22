CC = gcc
CFLAGS = -Wall -ansi
#DBGFLAGS = -g
OBJECTS = erf.o
TARGETDIR = bin
TARGET = $(TARGETDIR)/erf
LINKFLAGS = -o $(TARGET)

# suffix rules
.SUFFIXES: .o .c
.c.o:
	$(CC) $(CFLAGS) -c $<

erf:	$(OBJECTS)
	$(CC) $(CFLAGS) $(LINKFLAGS) $(OBJECTS)

erf.o:	erf.c \
	erf.h

clean:
	@rm -rf *.o
	@rm -f $(TARGET)
	@rm -f $(TARGET).exe
	@rm -f $(TARGETDIR)/core
	@rm -f core

