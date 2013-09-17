@echo off

set TARGET=%1
set MAINCLASS=%2
set CPATH=%3
set MANIFEST=Manifest.mf

echo Manifest-Version: 1.0> %MANIFEST%
echo Main-class: %MAINCLASS%>> %MANIFEST%

jar cvfm %TARGET% %MANIFEST% -C ..\classes %CPATH%

del %MANIFEST% 2>nul




