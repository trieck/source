INCLUDE = 
LINK = GoLink.exe
LFLAGS = /entry _MAIN__ 
ASM = GoAsm
AFLAGS = /x64 /l

all : fifth.exe sixth.exe

fifth.exe : fifth.obj
	$(LINK) $(LFLAGS) /console fifth.obj kernel32.dll

sixth.exe : sixth.obj
	$(LINK) $(LFLAGS) sixth.obj kernel32.dll user32.dll gdi32.dll

.asm.obj :
	$(ASM) $(AFLAGS) $< 
	 
clean:
	@erase *.obj 2>nul
	@erase *.exe 2>nul
	@erase *.pdb 2>nul
	@erase *.ilk 2>nul