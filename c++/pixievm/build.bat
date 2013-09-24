@echo off
msbuild.exe pixievm\pixievm.sln /p:"VCBuildAdditionalOptions=/useenv" /p:Configuration=Release /t:Clean,Build