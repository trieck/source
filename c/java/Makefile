OBJECTS = $(OUTDIR)\$(PACKAGEDIR)\JDBLib.class
HEADERS = $(HEADERDIR)\com_knowx_kxtrieck_JDBLib.h

################################################################################

JC = javac.exe
JFLAGS = -d $(OUTDIR) -deprecation
PACKAGEDIR = com\knowx\kxtrieck
OUTDIR = classes
SOURCEDIR = source
HEADERDIR = jni

ALL : $(SOURCEDIR) $(OUTDIR) $(HEADERDIR) $(OBJECTS) $(HEADERS)

.SUFFIXES : .java

################################################################################

{$(SOURCEDIR)\$(PACKAGEDIR)}.java{$(OUTDIR)\$(PACKAGEDIR)}.class:
	$(JC) $(JFLAGS) $<

"$(OUTDIR)" :
	@if not exist "$(OUTDIR)" mkdir "$(OUTDIR)"
	
"$(HEADERDIR)" :
	@if not exist "$(HEADERDIR)" mkdir "$(HEADERDIR)"

"$(SOURCEDIR)" :
	@cd $(SOURCEDIR)

$(HEADERDIR)\com_knowx_kxtrieck_JDBLib.h :
	javah -jni -d $(HEADERDIR) com.knowx.kxtrieck.JDBLib
	
################################################################################
clean:
	-@erase $(HEADERS) 2>nul
	-@erase $(OBJECTS) 2>nul
	
	
