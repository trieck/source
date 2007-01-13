# Microsoft Developer Studio Project File - Name="InProc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=InProc - Win32 Debug ANSI
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "InProc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "InProc.mak" CFG="InProc - Win32 Debug ANSI"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "InProc - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "InProc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "InProc - Win32 Debug ANSI" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "InProc - Win32 Release ANSI" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "InProc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\proxy" /I "..\shared" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_DLL_COMPONENT_" /D "UNICODE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 winspool.lib comdlg32.lib shell32.lib oleaut32.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib advapi32.lib ole32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386 /out:"Release/miscobj.dll"

!ELSEIF  "$(CFG)" == "InProc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\proxy" /I "..\shared" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_DLL_COMPONENT_" /D "UNICODE" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib ole32.lib uuid.lib oleaut32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/miscobj.dll" /pdbtype:sept

!ELSEIF  "$(CFG)" == "InProc - Win32 Debug ANSI"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "InProc__"
# PROP BASE Intermediate_Dir "InProc__"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSI/DEBUG"
# PROP Intermediate_Dir "ANSI/DEBUG"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_DLL_COMPONENT_" /D "UNICODE" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\proxy" /I "..\shared" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_DLL_COMPONENT_" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib ole32.lib advapi32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib ole32.lib uuid.lib oleaut32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"ANSI/DEBUG/miscobj.dll" /pdbtype:sept

!ELSEIF  "$(CFG)" == "InProc - Win32 Release ANSI"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "InProc_0"
# PROP BASE Intermediate_Dir "InProc_0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ANSI/RELEASE"
# PROP Intermediate_Dir "ANSI/RELEASE"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_DLL_COMPONENT_" /D "UNICODE" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\proxy" /I "..\shared" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_DLL_COMPONENT_" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 winspool.lib comdlg32.lib shell32.lib oleaut32.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib advapi32.lib ole32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386 /out:"ANSI/RELEASE/miscobj.dll"

!ENDIF 

# Begin Target

# Name "InProc - Win32 Release"
# Name "InProc - Win32 Debug"
# Name "InProc - Win32 Debug ANSI"
# Name "InProc - Win32 Release ANSI"
# Begin Source File

SOURCE=.\dmisc.cpp
# End Source File
# Begin Source File

SOURCE=..\proxy\guids.c
# End Source File
# Begin Source File

SOURCE=.\InProc.def
# End Source File
# Begin Source File

SOURCE=.\inproc.rc
# End Source File
# Begin Source File

SOURCE=..\shared\misc.cpp
# End Source File
# Begin Source File

SOURCE=..\shared\misc.h
# End Source File
# Begin Source File

SOURCE=.\misc.tlb
# End Source File
# Begin Source File

SOURCE=..\shared\REGISTRY.CPP
# End Source File
# Begin Source File

SOURCE=..\shared\REGISTRY.H
# End Source File
# End Target
# End Project
