@echo off
echo Making "common" library...
cd common\win32
nmake %1 -nologo "CFG=Debug"
if %errorlevel% GTR 0 goto err
cd ..\..
echo Making "Tiny 6502 Assembler (t6502)" program...
cd t6502\win32
nmake %1 -nologo "CFG=Debug"
if %errorlevel% GTR 0 goto err
cd ..\..
echo Making "Tiny 6502 Disassembler (td6502)" program...
cd td6502\win32
nmake %1 -nologo "CFG=Debug"
if %errorlevel% GTR 0 goto err
cd ..\..
echo Making "6502 Linker (65link)" program...
cd 65link\win32
nmake %1 -nologo "CFG=Debug"
if %errorlevel% GTR 0 goto err
cd ..\..
echo Making "Neptune64" program...
cd Neptune64\win32
nmake %1 -nologo "CFG=Debug"
if %errorlevel% GTR 0 goto err
cd ..\..
goto end
:err
cd ..\..
:end

