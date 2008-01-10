@echo off
perl Configure-win32.pl > Makefile.win32
nmake /nologo -f Makefile.win32
