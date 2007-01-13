# Microsoft Developer Studio Project File - Name="score" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=score - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "score.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "score.mak" CFG="score - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "score - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "score - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/score", GQEAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "score - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386 /out:"bin\score.exe"

!ELSEIF  "$(CFG)" == "score - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"bin\score.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "score - Win32 Release"
# Name "score - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\beats.cpp
# End Source File
# Begin Source File

SOURCE=.\DataEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\dblebuff.cpp
# End Source File
# Begin Source File

SOURCE=.\inputdev.cpp
# End Source File
# Begin Source File

SOURCE=.\inputdevs.cpp
# End Source File
# Begin Source File

SOURCE=.\keysig.cpp
# End Source File
# Begin Source File

SOURCE=.\keysigdg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\measqueue.cpp
# End Source File
# Begin Source File

SOURCE=.\measure.cpp
# End Source File
# Begin Source File

SOURCE=.\mididev.cpp
# End Source File
# Begin Source File

SOURCE=.\mididevs.cpp
# End Source File
# Begin Source File

SOURCE=.\midimessage.cpp
# End Source File
# Begin Source File

SOURCE=.\midiout.cpp
# End Source File
# Begin Source File

SOURCE=.\midistream.cpp
# End Source File
# Begin Source File

SOURCE=.\miditime.cpp
# End Source File
# Begin Source File

SOURCE=.\neptune.cpp
# End Source File
# Begin Source File

SOURCE=.\note.cpp
# End Source File
# Begin Source File

SOURCE=.\notelist.cpp
# End Source File
# Begin Source File

SOURCE=.\outputdev.cpp
# End Source File
# Begin Source File

SOURCE=.\outputdevs.cpp
# End Source File
# Begin Source File

SOURCE=.\RegKey.cpp
# End Source File
# Begin Source File

SOURCE=.\score.cpp
# End Source File
# Begin Source File

SOURCE=.\ScoreDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ScoreView.cpp
# End Source File
# Begin Source File

SOURCE=.\sequence.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\staff.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TempoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\timesignature.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolboxDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\baseinc.h
# End Source File
# Begin Source File

SOURCE=.\beats.h
# End Source File
# Begin Source File

SOURCE=.\common.h
# End Source File
# Begin Source File

SOURCE=.\DataEngine.h
# End Source File
# Begin Source File

SOURCE=.\dblebuff.h
# End Source File
# Begin Source File

SOURCE=.\inputdev.h
# End Source File
# Begin Source File

SOURCE=.\inputdevs.h
# End Source File
# Begin Source File

SOURCE=.\keynotes.h
# End Source File
# Begin Source File

SOURCE=.\keysig.h
# End Source File
# Begin Source File

SOURCE=.\keysigdg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\measqueue.h
# End Source File
# Begin Source File

SOURCE=.\measure.h
# End Source File
# Begin Source File

SOURCE=.\midicommon.h
# End Source File
# Begin Source File

SOURCE=.\mididev.h
# End Source File
# Begin Source File

SOURCE=.\mididevs.h
# End Source File
# Begin Source File

SOURCE=.\midimessage.h
# End Source File
# Begin Source File

SOURCE=.\midiout.h
# End Source File
# Begin Source File

SOURCE=.\midistream.h
# End Source File
# Begin Source File

SOURCE=.\miditime.h
# End Source File
# Begin Source File

SOURCE=.\neptune.h
# End Source File
# Begin Source File

SOURCE=.\note.h
# End Source File
# Begin Source File

SOURCE=.\notelist.h
# End Source File
# Begin Source File

SOURCE=.\outputdev.h
# End Source File
# Begin Source File

SOURCE=.\outputdevs.h
# End Source File
# Begin Source File

SOURCE=.\RegKey.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\score.h
# End Source File
# Begin Source File

SOURCE=.\ScoreDoc.h
# End Source File
# Begin Source File

SOURCE=.\ScoreView.h
# End Source File
# Begin Source File

SOURCE=.\sequence.h
# End Source File
# Begin Source File

SOURCE=.\SettingsDlg.h
# End Source File
# Begin Source File

SOURCE=.\staff.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TempoDlg.h
# End Source File
# Begin Source File

SOURCE=.\timesignature.h
# End Source File
# Begin Source File

SOURCE=.\tool.h
# End Source File
# Begin Source File

SOURCE=.\ToolboxDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\16not.cur
# End Source File
# Begin Source File

SOURCE=.\res\16not.ico
# End Source File
# Begin Source File

SOURCE=.\res\32not.cur
# End Source File
# Begin Source File

SOURCE=.\res\32not.ico
# End Source File
# Begin Source File

SOURCE=.\res\8note.cur
# End Source File
# Begin Source File

SOURCE=.\res\8note.ico
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\default.ico
# End Source File
# Begin Source File

SOURCE=.\res\erasenot.cur
# End Source File
# Begin Source File

SOURCE=.\res\flat.cur
# End Source File
# Begin Source File

SOURCE=.\res\flat.ico
# End Source File
# Begin Source File

SOURCE=.\res\halfnote.cur
# End Source File
# Begin Source File

SOURCE=.\res\halfnote.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\instuments.txt
# End Source File
# Begin Source File

SOURCE=.\res\keya.bmp
# End Source File
# Begin Source File

SOURCE=.\res\keyaflat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\keybflat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\keycflat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\keycshar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\keycsharp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\keydflat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\keyeflat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\keyf.bmp
# End Source File
# Begin Source File

SOURCE=.\res\keyfsharp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\keygflat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\natural.cur
# End Source File
# Begin Source File

SOURCE=.\res\natural.ico
# End Source File
# Begin Source File

SOURCE=.\res\qnote.cur
# End Source File
# Begin Source File

SOURCE=.\res\qnote.ico
# End Source File
# Begin Source File

SOURCE=.\score.rc
# End Source File
# Begin Source File

SOURCE=.\res\score.rc2
# End Source File
# Begin Source File

SOURCE=.\res\score.reg
# End Source File
# Begin Source File

SOURCE=.\res\sharp.cur
# End Source File
# Begin Source File

SOURCE=.\res\sharp.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\trebleclef.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wholenot.cur
# End Source File
# Begin Source File

SOURCE=.\res\wholenot.ico
# End Source File
# End Group
# Begin Group "Documents"

# PROP Default_Filter "xls;doc"
# End Group
# End Target
# End Project
