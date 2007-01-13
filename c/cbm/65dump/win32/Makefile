#############################################################################
#
#	WIN32 6502 Binary Dumper Makefile
#

!if "$(CFG)" != "Release" && "$(CFG)" != "Debug"
!message \tNo configuration was specified
!message \tValid configurations are "Debug" or "Release"
!message
!error
!endif

!if "$(CFG)" == "Debug"
CFLAGS = -nologo -I$(COMMONDIR) /W3 /Zi /MLd
INTDIR = Debug
!else
INTDIR = Release
CFLAGS = -nologo -I$(COMMONDIR) /W3
!endif

OBJECTS = $(INTDIR)\main.obj	\
		
SRCDIR = ..
COMMONDIR = ..\..\common
LIBDIR = $(COMMONDIR)\win32\$(INTDIR)
TARGETDIR = ..\..\bin
LIBS = common.lib
LINKFLAGS = -nologo /link $(LIBS) /$(CFG) /out:$(TARGETDIR)\$@ /libpath:$(LIBDIR)

65dump.exe:	$(INTDIR) $(OBJECTS)
	@$(CC) $(OBJECTS) $(LINKFLAGS)

"$(INTDIR)" :
	@if not exist "$(INTDIR)" mkdir "$(INTDIR)"
	
{$(SRCDIR)}.c{$(INTDIR)}.obj:
	@$(CC) $(CFLAGS) /c /Fo$@ $<

clean:
	-@erase $(TARGETDIR)\65dump.exe 2> nul
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
	
	

	
	