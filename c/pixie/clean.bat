@echo off
nmake clean -f pixie.mak CFG="pixie - Win32 Release"
rm -rf Release
rm -rf Debug
rm -f *.ilk
