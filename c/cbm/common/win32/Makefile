#############################################################################
#
#	WIN32 Common Makefile
#
!if "$(CFG)" == "Debug"
CFLAGS = -nologo /W3 /Zi /MLd
INTDIR = Debug
!else
INTDIR = Release
CFLAGS = -nologo /W3
!endif
OBJECTS = $(INTDIR)\log.obj	\
		$(INTDIR)\util.obj
SRCDIR = ..
LIB32 = link.exe -lib -nologo
common.lib :	$(INTDIR) $(OBJECTS)
	@$(LIB32) $(OBJECTS) /out:$(INTDIR)\$@
	
"$(INTDIR)" :
	@if not exist "$(INTDIR)" mkdir "$(INTDIR)"
{$(SRCDIR)}.c{$(INTDIR)}.obj:
	@$(CC) $(CFLAGS) /c /Fo$@ $<
clean:
	-@erase *.pdb 2> nul
	-@erase *.plg 2> nul 
	-@erase *.ncb 2> nul 
	-@erase *.dsw 2> nul 
	-@erase *.opt 2> nul 	
	-@erase *.dep 2> nul
	-@rmdir /S /Q Debug 2> nul 
	-@rmdir /S /Q Release 2> nul	
	
	
	