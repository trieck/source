#############################################################################
#
#	File Read Utility
#

OBJECTS = file.obj 
LIBS = msvcrt.lib
ASM = nasm
ASMFLAGS = -f win32

file.exe :	$(OBJECTS)
	link.exe $(OBJECTS) $(LIBS) /out:$@
	
.asm.obj :
	$(ASM) $(ASMFLAGS) $< 
	 
clean:
	@erase *.obj 2>nul
	@erase *.exe 2>nul
	