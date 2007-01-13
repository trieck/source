################################################################################
#
# QUEUE
#

#CC = gcc
CFLAGS = -Wall -ansi 
DBGFLAGS = -g
OBJECTS = main.o queue.o

TARGETDIR = $(HOME)/bin
TARGET = $(TARGETDIR)/queue
LINKFLAGS = -o $(TARGET)

# suffix rules
.SUFFIXES: .o .c
.c.o:
	$(CC) $(CFLAGS) -c $<

queue:	$(OBJECTS)
	$(CC) $(CFLAGS) $(LINKFLAGS) $(OBJECTS)

clean:
	@rm -rf *.o
	@rm -f $(TARGET)
	@rm -f $(TARGETDIR)/core
	@rm -f core

