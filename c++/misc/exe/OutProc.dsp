# Microsoft Developer Studio Project File - Name="OutProc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=OutProc - Win32 Release ANSI
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OutProc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OutProc.mak" CFG="OutProc - Win32 Release ANSI"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OutProc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "OutProc - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "OutProc - Win32 Debug ANSI" (based on "Win32 (x86) Application")
!MESSAGE "OutProc - Win32 Release ANSI" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OutProc - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\proxy" /I "..\shared" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_OUTPROC_SERVER_" /D "UNICODE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib uuid.lib advapi32.lib ole32.lib comctl32.lib oleaut32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/miscobj.exe"

!ELSEIF  "$(CFG)" == "OutProc - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\proxy" /I "..\shared" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "UNICODE" /D "_OUTPROC_SERVER_" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib uuid.lib advapi32.lib ole32.lib comctl32.lib oleaut32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/miscobj.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "OutProc - Win32 Debug ANSI"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "OutProc_"
# PROP BASE Intermediate_Dir "OutProc_"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSI/debug"
# PROP Intermediate_Dir "ANSI/debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_OUTPROC_SERVER_" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\proxy" /I "..\shared" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_OUTPROC_SERVER_" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib uuid.lib advapi32.lib ole32.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib uuid.lib advapi32.lib ole32.lib comctl32.lib oleaut32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"ANSI/debug/miscobj.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "OutProc - Win32 Release ANSI"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "OutProc_"
# PROP BASE Intermediate_Dir "OutProc_"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ANSI/Release"
# PROP Intermediate_Dir "ANSI/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_OUTPROC_SERVER_" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /ML /W3 /GX /Zi /O2 /I "..\proxy" /I "..\shared" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_OUTPROC_SERVER_" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib uuid.lib advapi32.lib ole32.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib uuid.lib advapi32.lib ole32.lib comctl32.lib oleaut32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"ANSI/Release/miscobj.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "OutProc - Win32 Release"
# Name "OutProc - Win32 Debug"
# Name "OutProc - Win32 Debug ANSI"
# Name "OutProc - Win32 Release ANSI"
# Begin Source File

SOURCE=.\capp.h
# End Source File
# Begin Source File

SOURCE=.\emisc.cpp
# End Source File
# Begin Source File

SOURCE=..\proxy\guids.c
# End Source File
# Begin Source File

SOURCE=.\main.ico
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

SOURCE=.\outproc.rc
# End Source File
# Begin Source File

SOURCE=..\shared\REGISTRY.CPP
# End Source File
# Begin Source File

SOURCE=..\shared\REGISTRY.H
# End Source File
# End Target
# End Project
