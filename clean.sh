#!/bin/bash

# generate exclusion list
. ./exclude.sh
if [ $? -ne 0 ]; then
	echo "error: failed to generate exclusion list."
	exit $?
fi

# clean excluded files
find . -regextype posix-egrep -iregex ".+\.(${EXCLUDE})$" -print -exec rm -f {} \;
if [ $? -ne 0 ]; then
	echo "error: failed to clean files."
	exit $?
fi

# clean MSVC directories
find . -type d \( -iname "debug" -o -iname "release" -o -iname "*upgrade*" -o -iname "*backup*" \) -print -exec rm -rf {} \;









