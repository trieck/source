#############################################################################
#
#	WIN32 Neptune64 Makefile
#
!if "$(CFG)" == "Debug"
CFLAGS = -nologo -I$(COMMONDIR) /W3 /Zi /MLd
INTDIR = Debug
!else
INTDIR = Release
CFLAGS = -nologo -I$(COMMONDIR) /W3
!endif
OBJECTS = $(INTDIR)\instr.obj 	\
	$(INTDIR)\symbol.obj 		\
	$(INTDIR)\assem.obj 		\
	$(INTDIR)\disassem.obj 		\
	$(INTDIR)\opcodes.obj 		\
	$(INTDIR)\machine.obj 		\
	$(INTDIR)\monitor.obj 		\
	$(INTDIR)\6510.obj 			\
	$(INTDIR)\mem.obj 			\
	$(INTDIR)\main.obj 			\
	$(INTDIR)\parser.obj 		\
	$(INTDIR)\code.obj 			\
	$(INTDIR)\video.obj 		\
	$(INTDIR)\sid.obj 			\
	$(INTDIR)\cart.obj 			\
	$(INTDIR)\cia.obj			\
	$(INTDIR)\interrupt.obj
	
SRCDIR = ..
COMMONDIR = ..\..\common
LIBDIR = $(COMMONDIR)\win32\$(INTDIR)
TARGETDIR = ..\..\bin
LIBS = common.lib
LINKFLAGS = -nologo /link $(LIBS) /$(CFG) /out:$(TARGETDIR)\$@ /libpath:$(LIBDIR)
nptune64.exe:	$(INTDIR) $(OBJECTS)
	@$(CC) $(OBJECTS) $(LINKFLAGS)
"$(INTDIR)" :
	@if not exist "$(INTDIR)" mkdir "$(INTDIR)"
{$(SRCDIR)}.c{$(INTDIR)}.obj:
	@$(CC) $(CFLAGS) /c /Fo$@ $<
clean:
	-@erase $(TARGETDIR)\nptune64.exe 2> nul
	-@erase $(TARGETDIR)\*.pdb 2> nul
	-@erase $(TARGETDIR)\*.ilk 2> nul
	-@erase *.pdb 2> nul
	-@erase *.plg 2> nul 
	-@erase *.ncb 2> nul 
	-@erase *.dsw 2> nul 
	-@erase *.opt 2> nul 	
	-@erase *.dep 2> nul
	-@rmdir /S /Q Debug 2> nul 
	-@rmdir /S /Q Release 2> nul	
	
	