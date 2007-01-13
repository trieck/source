# Microsoft Developer Studio Project File - Name="TorrentExplorer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TorrentExplorer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TorrentExplorer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TorrentExplorer.mak" CFG="TorrentExplorer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TorrentExplorer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TorrentExplorer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/source/c++/TorrentExplorer", RTEAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TorrentExplorer - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "TorrentExplorer - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TorrentExplorer - Win32 Release"
# Name "TorrentExplorer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BinaryView.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorButton.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorChooserDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorChooserWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Dictionary.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralPage.cpp
# End Source File
# Begin Source File

SOURCE=.\gripbar.cpp
# End Source File
# Begin Source File

SOURCE=.\Integer.cpp
# End Source File
# Begin Source File

SOURCE=.\List.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\sha1.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\String.cpp
# End Source File
# Begin Source File

SOURCE=.\StringTokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\TorrentDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TorrentDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\TorrentExplorer.cpp
# End Source File
# Begin Source File

SOURCE=.\TorrentExplorer.rc
# End Source File
# Begin Source File

SOURCE=.\TorrentMaker.cpp
# End Source File
# Begin Source File

SOURCE=.\TorrentObject.cpp
# End Source File
# Begin Source File

SOURCE=.\TorrentParser.cpp
# End Source File
# Begin Source File

SOURCE=.\TorrentSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\TorrentView.cpp
# End Source File
# Begin Source File

SOURCE=.\TorrentWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\ValueView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BinaryView.h
# End Source File
# Begin Source File

SOURCE=.\ColorButton.h
# End Source File
# Begin Source File

SOURCE=.\ColorChooserDlg.h
# End Source File
# Begin Source File

SOURCE=.\ColorChooserWnd.h
# End Source File
# Begin Source File

SOURCE=.\ColorsPage.h
# End Source File
# Begin Source File

SOURCE=.\Dictionary.h
# End Source File
# Begin Source File

SOURCE=.\GeneralPage.h
# End Source File
# Begin Source File

SOURCE=.\gripbar.h
# End Source File
# Begin Source File

SOURCE=.\Integer.h
# End Source File
# Begin Source File

SOURCE=.\List.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# PROP Ignore_Default_Tool 1
# End Source File
# Begin Source File

SOURCE=.\SettingsSheet.h
# End Source File
# Begin Source File

SOURCE=.\sha1.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\String.h
# End Source File
# Begin Source File

SOURCE=.\StringTokenizer.h
# End Source File
# Begin Source File

SOURCE=.\TorrentDlg.h
# End Source File
# Begin Source File

SOURCE=.\TorrentDoc.h
# End Source File
# Begin Source File

SOURCE=.\TorrentExplorer.h
# End Source File
# Begin Source File

SOURCE=.\TorrentMaker.h
# End Source File
# Begin Source File

SOURCE=.\TorrentObject.h
# End Source File
# Begin Source File

SOURCE=.\TorrentParser.h
# End Source File
# Begin Source File

SOURCE=.\TorrentSettings.h
# End Source File
# Begin Source File

SOURCE=.\TorrentView.h
# End Source File
# Begin Source File

SOURCE=.\TorrentWriter.h
# End Source File
# Begin Source File

SOURCE=.\ValueView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\default.pal
# End Source File
# Begin Source File

SOURCE=.\res\dict.ico
# End Source File
# Begin Source File

SOURCE=.\res\list.ico
# End Source File
# Begin Source File

SOURCE=.\res\number.ico
# End Source File
# Begin Source File

SOURCE=.\res\string.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TorrentExplorer.ico
# End Source File
# Begin Source File

SOURCE=.\res\TorrentExplorer.rc2
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "reg"
# Begin Source File

SOURCE=.\TorrentExplorer.reg
# End Source File
# End Group
# End Target
# End Project
