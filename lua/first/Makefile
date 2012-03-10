OBJECTS = first.o

.SUFFIXES: .lua .o
.lua.o:
	luac52 -o $@ $<

all: ${OBJECTS}

clean:
	@-rm *.o > /dev/null 2>&1


	