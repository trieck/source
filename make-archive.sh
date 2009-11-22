#!/bin/bash

EXCLUDE_FILE=/tmp/exclude
ARCHIVE_FILE=./source.tar.gz

# generate exclusion list
. ./exclude.sh
if [ $? -ne 0 ]; then
	echo "error: failed to generate exclusion list."
	exit $?
fi

# generate exclusion file
find . -regextype posix-egrep -regex ".+\.(${EXCLUDE})$" -print > ${EXCLUDE_FILE}
if [ $? -ne 0 ]; then
	echo "error: failed to generate ${EXCLUDE_FILE}."
	exit $?
fi

# generate archive
tar cvzf ${ARCHIVE_FILE} --exclude-vcs --exclude-from=${EXCLUDE_FILE} .
