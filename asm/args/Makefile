#############################################################################
#
#	ARGS Project Makefile
#

OBJECTS = args.obj 
LIBS = msvcrt.lib
ASM = nasmw
ASMFLAGS = -f win32

args.exe :	$(OBJECTS)
	link.exe $(OBJECTS) $(LIBS) /out:$@
	
.asm.obj :
	$(ASM) $(ASMFLAGS) $< 
	 
clean:
	@erase *.obj 2>nul
	@erase *.exe 2>nul
	