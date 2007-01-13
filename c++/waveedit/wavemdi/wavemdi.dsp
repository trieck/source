# Microsoft Developer Studio Project File - Name="wavemdi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=wavemdi - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wavemdi.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wavemdi.mak" CFG="wavemdi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wavemdi - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "wavemdi - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wavemdi - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\shared" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ole32.lib oleaut32.lib uuid.lib dsound.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"Release/waveedit.exe"

!ELSEIF  "$(CFG)" == "wavemdi - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\shared" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ole32.lib oleaut32.lib uuid.lib dsound.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/waveedit.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "wavemdi - Win32 Release"
# Name "wavemdi - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\DeviceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DigitCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DigitCtrlMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\LEDMeter.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveApp.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\DeviceDlg.h
# End Source File
# Begin Source File

SOURCE=.\DigitCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DigitCtrlMgr.h
# End Source File
# Begin Source File

SOURCE=.\LEDMeter.h
# End Source File
# Begin Source File

SOURCE=.\MainFrame.h
# End Source File
# Begin Source File

SOURCE=.\PlayDlg.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\WaveApp.h
# End Source File
# Begin Source File

SOURCE=.\WaveDoc.h
# End Source File
# Begin Source File

SOURCE=.\WaveView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ".rc; .ico; .bmp"
# Begin Source File

SOURCE=.\digit0.bmp
# End Source File
# Begin Source File

SOURCE=.\digit1.bmp
# End Source File
# Begin Source File

SOURCE=.\digit2.bmp
# End Source File
# Begin Source File

SOURCE=.\digit3.bmp
# End Source File
# Begin Source File

SOURCE=.\digit4.bmp
# End Source File
# Begin Source File

SOURCE=.\digit5.bmp
# End Source File
# Begin Source File

SOURCE=.\digit6.bmp
# End Source File
# Begin Source File

SOURCE=.\digit7.bmp
# End Source File
# Begin Source File

SOURCE=.\digit8.bmp
# End Source File
# Begin Source File

SOURCE=.\digit9.bmp
# End Source File
# Begin Source File

SOURCE=.\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\Music.ico
# End Source File
# Begin Source File

SOURCE=.\pausebtn.ico
# End Source File
# Begin Source File

SOURCE=.\playbtn.ico
# End Source File
# Begin Source File

SOURCE=.\stopbtn.ico
# End Source File
# Begin Source File

SOURCE=.\WaveMdi.rc
# End Source File
# End Group
# End Target
# End Project
