@echo off
msbuild.exe pixievm\pixievm.sln /p:Configuration=Release /t:Clean,Build