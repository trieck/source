@echo off

if "%1" == "" goto usage
if "%2" == "" goto usage

set TIDYPATH=d:\bin
set TIDY=%TIDYPATH%\tidy.exe
set TIDYCONFIG=%TIDYPATH%\config.txt

set FILEPATT=%1
set INPATH=%~d1%~p1
set OUTPATH=%2

mkdir %2 2>NUL

for /f "tokens=*" %%G in ('dir /b %FILEPATT%') do (
	%TIDY% -config "%TIDYCONFIG%" "%INPATH%%%G" > "%OUTPATH%\%%G"
	IF %ERRORLEVEL% EQU 2 goto err
)

goto done

:usage
echo usage: tidy-xml-files filepattern outpath
goto done

:err
echo ERROR! An error has occurred and processing has halted.

:done
