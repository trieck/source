
OBJECTS = util.o
util:	$(OBJECTS)
.asm.o:
	t6502 $<
	
clean:
	@-erase *.o 2>nul
	