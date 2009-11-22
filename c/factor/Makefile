CC = gcc
CFLAGS = -Wall -ansi -g -O2
OBJECTS = factor.o
TARGET = factor 
LINKFLAGS = -o $(TARGET)

# suffix rules
.SUFFIXES: .o .c
.c.o:
	$(CC) $(CFLAGS) -c $<

factor:	$(OBJECTS)
	$(CC) $(CFLAGS) $(LINKFLAGS) $(OBJECTS)

clean:
	@rm -rf *.o
	@rm -f $(TARGET)
	@rm -f $(TARGET).exe
	@rm -f core

