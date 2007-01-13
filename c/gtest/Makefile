CC = gcc
LD = gcc
CFLAGS = -g -ansi -pedantic -Wall
TARGET = gtest
OBJECTS = \
	gtest.o

INCLUDES = 
LIBS =

# suffix rules
.SUFFIXES: .o .c
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

$(TARGET):	$(OBJECTS) $(DEPS)
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

gtest.o: \
	gtest.c

indent:
	@indent -kr -ts4 *.c *.h
	@rm -f *~

clean:
	@rm -f *.o
	@rm -f $(TARGET).exe
	@rm -f $(TARGET)
	@rm -f core



