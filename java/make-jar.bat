@echo off

set TARGET=%1
set CPATH=%2

jar cvfm %TARGET% manifest.mf -C classes %CPATH%

