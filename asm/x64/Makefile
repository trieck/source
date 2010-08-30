LINK = GoLink.exe
LFLAGS = /entry main 
NASM = nasm
NASMFLAGS = -ic:\nasmx\inc\ -f win64 

all : first.exe second.exe third.exe fourth.exe

first.exe :	first.obj
	$(LINK) $(LFLAGS) first.obj kernel32.dll user32.dll

second.exe : second.obj
	$(LINK) $(LFLAGS) /console second.obj kernel32.dll
	
third.exe :	third.obj
	$(LINK) $(LFLAGS) third.obj kernel32.dll user32.dll
	
fourth.exe : fourth.obj
	$(LINK) $(LFLAGS) /console fourth.obj kernel32.dll user32.dll

.asm.obj :
	$(NASM) $(NASMFLAGS) $< 
	 
clean:
	@erase *.obj 2>nul
	@erase *.exe 2>nul
	@erase *.pdb 2>nul
	@erase *.ilk 2>nul