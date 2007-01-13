# Microsoft Developer Studio Generated NMAKE File, Based on torrent.dsp
!IF "$(CFG)" == ""
CFG=torrent - Win32 Debug
!MESSAGE No configuration specified. Defaulting to torrent - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "torrent - Win32 Release" && "$(CFG)" != "torrent - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "torrent.mak" CFG="torrent - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "torrent - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "torrent - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "torrent - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\torrent.exe"


CLEAN :
	-@erase "$(INTDIR)\bencode.obj"
	-@erase "$(INTDIR)\btdict.obj"
	-@erase "$(INTDIR)\lex.obj"
	-@erase "$(INTDIR)\torrent.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase ".\torrent.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\torrent.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\torrent.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\torrent.pdb" /machine:I386 /out:"torrent.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bencode.obj" \
	"$(INTDIR)\lex.obj" \
	"$(INTDIR)\torrent.obj" \
	"$(INTDIR)\btdict.obj"

".\torrent.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "torrent - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\torrent.exe"


CLEAN :
	-@erase "$(INTDIR)\bencode.obj"
	-@erase "$(INTDIR)\btdict.obj"
	-@erase "$(INTDIR)\lex.obj"
	-@erase "$(INTDIR)\torrent.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\torrent.pdb"
	-@erase ".\torrent.exe"
	-@erase ".\torrent.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\torrent.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\torrent.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\torrent.pdb" /debug /machine:I386 /out:"torrent.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\bencode.obj" \
	"$(INTDIR)\lex.obj" \
	"$(INTDIR)\torrent.obj" \
	"$(INTDIR)\btdict.obj"

".\torrent.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("torrent.dep")
!INCLUDE "torrent.dep"
!ELSE 
!MESSAGE Warning: cannot find "torrent.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "torrent - Win32 Release" || "$(CFG)" == "torrent - Win32 Debug"
SOURCE=.\bencode.c

"$(INTDIR)\bencode.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\btdict.c

"$(INTDIR)\btdict.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\lex.c

"$(INTDIR)\lex.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\torrent.c

"$(INTDIR)\torrent.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

