
LINK = link.exe
LFLAGS = /nologo /machine:X64 /entry:main
NASM = nasm
NASMFLAGS = -f win64

all : first.exe second.exe

first.exe :	first.obj
	$(LINK) $(LFLAGS) /subsystem:windows /defaultlib:kernel32.lib /defaultlib:user32.lib first.obj /out:$@

second.exe : second.obj
	$(LINK) $(LFLAGS) /subsystem:console /defaultlib:kernel32.lib second.obj /out:$@
	
.asm.obj :
	$(NASM) $(NASMFLAGS) $< 
	 
clean:
	@erase *.obj 2>nul
	@erase *.exe 2>nul
	@erase *.pdb 2>nul
	@erase *.ilk 2>nul