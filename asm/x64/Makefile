
OBJECTS = first.obj 
LINK = link.exe
LIB64 = C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Lib\x64
LFLAGS = /nologo /machine:X64 /subsystem:windows /defaultlib:"$(LIB64)\kernel32.lib" /defaultlib:"$(LIB64)\user32.lib" /entry:main
NASM = nasm
NASMFLAGS = -f win64

first.exe :	$(OBJECTS)
	$(LINK) $(LFLAGS) $(OBJECTS) /out:$@
	
.asm.obj :
	$(NASM) $(NASMFLAGS) $< 
	 
clean:
	@erase *.obj 2>nul
	@erase *.exe 2>nul
	