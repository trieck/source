#!/bin/bash

if [ $# -eq 0 ]; then
	echo "usage: vcupgrade.sh project"
	exit 1
fi

winpath=`cygpath -a -w "$1"`

echo "Upgrading ${winpath}..."

devenv.exe /upgrade "${winpath}"


