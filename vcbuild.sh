#!/bin/bash

if [ $# -eq 0 ]; then
	echo "usage: vcbuild.sh solution"
	exit 1
fi

winpath=`cygpath -a -w "$1"`

vcbuild.exe /nologo /htmllog:BuildLog.htm "${winpath}" Release\|Win32


