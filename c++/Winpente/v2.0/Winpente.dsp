# Microsoft Developer Studio Project File - Name="Winpente" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Winpente - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Winpente.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Winpente.mak" CFG="Winpente - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Winpente - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Winpente - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Winpente - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_AFXDLL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib wpthk32.lib /nologo /subsystem:windows /machine:I386 /libpath:"Think\Release"

!ELSEIF  "$(CFG)" == "Winpente - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GX /ZI /Od /D "_DEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib wpthk32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"Think\Debug"

!ENDIF 

# Begin Target

# Name "Winpente - Win32 Release"
# Name "Winpente - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\BkgndBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\BkgndPage.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ColorPage.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\CustBmp.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\MainFrame.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\miscobj.cpp
# End Source File
# Begin Source File

SOURCE=.\MiscPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PenteApp.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\PenteDoc.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\PenteView.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\PiecePage.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\PlayerNamesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Players.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefDlg.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Scores.cpp
# End Source File
# Begin Source File

SOURCE=.\ScoresDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScoresPreviewFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\ScoresPreviewWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\BkgndBitmap.h
# End Source File
# Begin Source File

SOURCE=.\BkgndPage.h
# End Source File
# Begin Source File

SOURCE=.\ColorPage.h
# End Source File
# Begin Source File

SOURCE=.\CustBmp.h
# End Source File
# Begin Source File

SOURCE=.\MainFrame.h
# End Source File
# Begin Source File

SOURCE=.\miscobj.h
# End Source File
# Begin Source File

SOURCE=.\MiscPage.h
# End Source File
# Begin Source File

SOURCE=.\PenteApp.h
# End Source File
# Begin Source File

SOURCE=.\PenteDoc.h
# End Source File
# Begin Source File

SOURCE=.\PenteView.h
# End Source File
# Begin Source File

SOURCE=.\PiecePage.h
# End Source File
# Begin Source File

SOURCE=.\PlayerNamesDlg.h
# End Source File
# Begin Source File

SOURCE=.\Players.h
# End Source File
# Begin Source File

SOURCE=.\PrefDlg.h
# End Source File
# Begin Source File

SOURCE=.\ResDLL\resource.h
# End Source File
# Begin Source File

SOURCE=.\Scores.h
# End Source File
# Begin Source File

SOURCE=.\ScoresDlg.h
# End Source File
# Begin Source File

SOURCE=.\ScoresPreviewFrame.h
# End Source File
# Begin Source File

SOURCE=.\ScoresPreviewWnd.h
# End Source File
# Begin Source File

SOURCE=.\SettingsDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ".rc, .ico"
# Begin Source File

SOURCE=.\Pente.rc
# End Source File
# Begin Source File

SOURCE=.\winpente.ico
# End Source File
# End Group
# End Target
# End Project
