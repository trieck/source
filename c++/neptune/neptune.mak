# Microsoft Developer Studio Generated NMAKE File, Based on neptune.dsp
!IF "$(CFG)" == ""
CFG=neptune - Win32 Debug
!MESSAGE No configuration specified. Defaulting to neptune - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "neptune - Win32 Release" && "$(CFG)" != "neptune - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "neptune.mak" CFG="neptune - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "neptune - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "neptune - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "neptune - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\neptune_i.c" ".\neptune.tlb" ".\neptune.h" ".\bin\neptune.dll" ".\Release\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\neptune.obj"
	-@erase "$(INTDIR)\neptune.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\neptune.exp"
	-@erase "$(OUTDIR)\neptune.lib"
	-@erase ".\bin\neptune.dll"
	-@erase ".\neptune.h"
	-@erase ".\neptune.tlb"
	-@erase ".\neptune_i.c"
	-@erase ".\Release\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "neptune_EXPORTS" /Fp"$(INTDIR)\neptune.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\neptune.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\neptune.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /dll /incremental:no /pdb:"$(OUTDIR)\neptune.pdb" /machine:I386 /def:".\neptune.def" /out:"bin\neptune.dll" /implib:"$(OUTDIR)\neptune.lib" 
DEF_FILE= \
	".\neptune.def"
LINK32_OBJS= \
	"$(INTDIR)\neptune.obj" \
	"$(INTDIR)\neptune.res"

".\bin\neptune.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Release
TargetPath=.\bin\neptune.dll
InputPath=.\bin\neptune.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "neptune - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\neptune_i.c" ".\neptune.tlb" ".\neptune.h" ".\bin\neptune.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\neptune.obj"
	-@erase "$(INTDIR)\neptune.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\neptune.exp"
	-@erase "$(OUTDIR)\neptune.lib"
	-@erase "$(OUTDIR)\neptune.pdb"
	-@erase ".\bin\neptune.dll"
	-@erase ".\bin\neptune.ilk"
	-@erase ".\Debug\regsvr32.trg"
	-@erase ".\neptune.h"
	-@erase ".\neptune.tlb"
	-@erase ".\neptune_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "neptune_EXPORTS" /Fp"$(INTDIR)\neptune.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\neptune.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\neptune.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /dll /incremental:yes /pdb:"$(OUTDIR)\neptune.pdb" /debug /machine:I386 /def:".\neptune.def" /out:"bin\neptune.dll" /implib:"$(OUTDIR)\neptune.lib" /pdbtype:sept 
DEF_FILE= \
	".\neptune.def"
LINK32_OBJS= \
	"$(INTDIR)\neptune.obj" \
	"$(INTDIR)\neptune.res"

".\bin\neptune.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\bin\neptune.dll
InputPath=.\bin\neptune.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
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
!IF EXISTS("neptune.dep")
!INCLUDE "neptune.dep"
!ELSE 
!MESSAGE Warning: cannot find "neptune.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "neptune - Win32 Release" || "$(CFG)" == "neptune - Win32 Debug"
SOURCE=.\neptune.cpp

"$(INTDIR)\neptune.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\neptune.idl

!IF  "$(CFG)" == "neptune - Win32 Release"

InputPath=.\neptune.idl

".\neptune.tlb"	".\neptune.h"	".\neptune_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "neptune.h" /iid "neptune_i.c" "neptune.idl"
<< 
	

!ELSEIF  "$(CFG)" == "neptune - Win32 Debug"

InputPath=.\neptune.idl

".\neptune.tlb"	".\neptune.h"	".\neptune_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "neptune.h" /iid "neptune_i.c" "neptune.idl"
<< 
	

!ENDIF 

SOURCE=.\neptune.rc

"$(INTDIR)\neptune.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

