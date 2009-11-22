#!/bin/bash

if [ $# -eq 0 ]; then
	echo "usage: vcbuild.sh solution"
	exit 1
fi

winpath=`cygpath -a -w "$1"`

vcbuild.exe /nologo /nocolor /errfile:./vcbuild.log /wrnfile:./vcbuild.log "${winpath}" Release\|Win32



