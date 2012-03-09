# Microsoft Developer Studio Generated NMAKE File, Based on RegWizard.dsp
!IF "$(CFG)" == ""
CFG=RegWizard - Win32 Release
!MESSAGE No configuration specified. Defaulting to RegWizard - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "RegWizard - Win32 Release" && "$(CFG)" != "RegWizard - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RegWizard.mak" CFG="RegWizard - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RegWizard - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "RegWizard - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "RegWizard - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\RegWizard.exe"


CLEAN :
	-@erase "$(INTDIR)\CPageThree.obj"
	-@erase "$(INTDIR)\CPageTwo.obj"
	-@erase "$(INTDIR)\CStartPage.obj"
	-@erase "$(INTDIR)\CWizard.obj"
	-@erase "$(INTDIR)\RegWizard.obj"
	-@erase "$(INTDIR)\RegWizard.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\RegWizard.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\RegWizard.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RegWizard.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RegWizard.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\RegWizard.pdb" /machine:I386 /out:"$(OUTDIR)\RegWizard.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CPageThree.obj" \
	"$(INTDIR)\CPageTwo.obj" \
	"$(INTDIR)\CStartPage.obj" \
	"$(INTDIR)\CWizard.obj" \
	"$(INTDIR)\RegWizard.obj" \
	"$(INTDIR)\RegWizard.res"

"$(OUTDIR)\RegWizard.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "RegWizard - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\RegWizard.exe"


CLEAN :
	-@erase "$(INTDIR)\CPageThree.obj"
	-@erase "$(INTDIR)\CPageTwo.obj"
	-@erase "$(INTDIR)\CStartPage.obj"
	-@erase "$(INTDIR)\CWizard.obj"
	-@erase "$(INTDIR)\RegWizard.obj"
	-@erase "$(INTDIR)\RegWizard.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\RegWizard.exe"
	-@erase "$(OUTDIR)\RegWizard.ilk"
	-@erase "$(OUTDIR)\RegWizard.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\RegWizard.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\RegWizard.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\RegWizard.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\RegWizard.pdb" /debug /machine:I386 /out:"$(OUTDIR)\RegWizard.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CPageThree.obj" \
	"$(INTDIR)\CPageTwo.obj" \
	"$(INTDIR)\CStartPage.obj" \
	"$(INTDIR)\CWizard.obj" \
	"$(INTDIR)\RegWizard.obj" \
	"$(INTDIR)\RegWizard.res"

"$(OUTDIR)\RegWizard.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("RegWizard.dep")
!INCLUDE "RegWizard.dep"
!ELSE 
!MESSAGE Warning: cannot find "RegWizard.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "RegWizard - Win32 Release" || "$(CFG)" == "RegWizard - Win32 Debug"
SOURCE=.\CPageThree.cpp

"$(INTDIR)\CPageThree.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CPageTwo.cpp

"$(INTDIR)\CPageTwo.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CStartPage.cpp

"$(INTDIR)\CStartPage.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CWizard.cpp

"$(INTDIR)\CWizard.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RegWizard.cpp

"$(INTDIR)\RegWizard.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\RegWizard.rc

"$(INTDIR)\RegWizard.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

