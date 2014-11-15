#!/bin/bash

if [ $# -eq 0 ]; then
	echo "usage: msbuild.sh solution"
	exit 1
fi

msbuild.exe /nologo /nocolor "$1" Release\|Win32



