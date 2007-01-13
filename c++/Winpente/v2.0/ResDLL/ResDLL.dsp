# Microsoft Developer Studio Project File - Name="ResDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ResDLL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ResDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ResDLL.mak" CFG="ResDLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ResDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ResDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ResDLL - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "UNICODE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"Release/wpres32.dll" /noentry
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ResDLL - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /YX /FD /noentry /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/wpres32.dll" /pdbtype:sept /noentry
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "ResDLL - Win32 Release"
# Name "ResDLL - Win32 Debug"
# Begin Group "Bitmap Files"

# PROP Default_Filter ".bmp"
# Begin Source File

SOURCE=.\1c.bmp
# End Source File
# Begin Source File

SOURCE=.\1u.bmp
# End Source File
# Begin Source File

SOURCE=.\1ulg.bmp
# End Source File
# Begin Source File

SOURCE=.\af.bmp
# End Source File
# Begin Source File

SOURCE=.\aj.bmp
# End Source File
# Begin Source File

SOURCE=.\aw.bmp
# End Source File
# Begin Source File

SOURCE=.\ax.bmp
# End Source File
# Begin Source File

SOURCE=.\tbarmain.bmp
# End Source File
# Begin Source File

SOURCE=.\TOOLBAR.BMP
# End Source File
# End Group
# Begin Group "Wave Files"

# PROP Default_Filter ".wav"
# Begin Source File

SOURCE=.\blip.wav
# End Source File
# Begin Source File

SOURCE=.\piece.wav
# End Source File
# Begin Source File

SOURCE=.\theme.wav
# End Source File
# Begin Source File

SOURCE=.\Winner.wav
# End Source File
# End Group
# Begin Group "Icon Files"

# PROP Default_Filter ".ico"
# Begin Source File

SOURCE=.\blueball.ico
# End Source File
# Begin Source File

SOURCE=.\greenbal.ico
# End Source File
# Begin Source File

SOURCE=.\ico00ste.ico
# End Source File
# Begin Source File

SOURCE=.\ltblueba.ico
# End Source File
# Begin Source File

SOURCE=.\mainicon.ico
# End Source File
# Begin Source File

SOURCE=.\purpleba.ico
# End Source File
# Begin Source File

SOURCE=.\redball.ico
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Cursor Files"

# PROP Default_Filter ".cur"
# Begin Source File

SOURCE=.\idr_main.cur
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ".rc, .bin"
# Begin Source File

SOURCE=.\resdll.rc
# End Source File
# Begin Source File

SOURCE=.\scores.bin
# End Source File
# End Group
# Begin Source File

SOURCE=.\players.bin
# End Source File
# End Target
# End Project
