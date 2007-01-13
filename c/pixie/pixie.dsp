# Microsoft Developer Studio Project File - Name="pixie" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=pixie - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pixie.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pixie.mak" CFG="pixie - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pixie - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "pixie - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Source/c/pixie", KKBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pixie - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386 /out:"pixie.exe"

!ELSEIF  "$(CFG)" == "pixie - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /out:"pixie.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "pixie - Win32 Release"
# Name "pixie - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\array.c
# End Source File
# Begin Source File

SOURCE=.\block.c
# End Source File
# Begin Source File

SOURCE=.\eval.c
# End Source File
# Begin Source File

SOURCE=.\global.c
# End Source File
# Begin Source File

SOURCE=.\lex.c
# End Source File
# Begin Source File

SOURCE=.\main.c
# End Source File
# Begin Source File

SOURCE=.\memcheck.c
# End Source File
# Begin Source File

SOURCE=.\parse.c
# End Source File
# Begin Source File

SOURCE=.\pixie.c
# End Source File
# Begin Source File

SOURCE=.\proctab.c
# End Source File
# Begin Source File

SOURCE=.\strutil.c
# End Source File
# Begin Source File

SOURCE=.\symbol.c
# End Source File
# Begin Source File

SOURCE=.\temp.c
# End Source File
# Begin Source File

SOURCE=.\tree.c
# End Source File
# Begin Source File

SOURCE=.\xmalloc.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\array.h
# End Source File
# Begin Source File

SOURCE=.\block.h
# End Source File
# Begin Source File

SOURCE=.\eval.h
# End Source File
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=.\memcheck.h
# End Source File
# Begin Source File

SOURCE=.\pixie.h
# End Source File
# Begin Source File

SOURCE=.\proctab.h
# End Source File
# Begin Source File

SOURCE=.\strutil.h
# End Source File
# Begin Source File

SOURCE=.\symbol.h
# End Source File
# Begin Source File

SOURCE=.\temp.h
# End Source File
# Begin Source File

SOURCE=.\tree.h
# End Source File
# Begin Source File

SOURCE=.\xmalloc.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Bison Grammar Files"

# PROP Default_Filter ".y"
# Begin Source File

SOURCE=.\parse.y

!IF  "$(CFG)" == "pixie - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Generating Parser from $(InputPath)...
InputPath=.\parse.y

BuildCmds= \
	if exist parse.c del parse.c \
	if exist parse.h del parse.h \
	bison -d  -y $(InputPath) \
	rename y.tab.c parse.c \
	rename y.tab.h parse.h \
	

"parse.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"parse.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "pixie - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Generating Parser from $(InputPath)...
InputPath=.\parse.y

BuildCmds= \
	if exist parse.c del parse.c \
	if exist parse.h del parse.h \
	bison -d  -y $(InputPath) \
	rename y.tab.c parse.c \
	rename y.tab.h parse.h \
	

"parse.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"parse.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Perl Source Files"

# PROP Default_Filter ".pl"
# Begin Source File

SOURCE=.\Configure.pl
# End Source File
# End Group
# Begin Group "Sample Source Files"

# PROP Default_Filter "*.pixie"
# End Group
# Begin Group "Flex Specification Files"

# PROP Default_Filter ".l"
# Begin Source File

SOURCE=.\lex.l

!IF  "$(CFG)" == "pixie - Win32 Release"

# Begin Custom Build - Generating Lexer from $(InputPath)...
InputPath=.\lex.l

"lex.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex -olex.c $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "pixie - Win32 Debug"

# Begin Custom Build - Generating Lexer from $(InputPath)...
InputPath=.\lex.l

"lex.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex -olex.c $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
