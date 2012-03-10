OBJECTS = first.o

.SUFFIXES: .lua .o
.lua.o:
	luac52 -o $@ $<

all: $(OBJECTS)

clean:
	@-del *.o > /nul 2>&1
