#!/bin/bash

EXTENS=""
count=0

exec < ./remove-extensions
while read line
do
	if [ $count -gt 0 ]; then
		EXTENS="$EXTENS|";
	fi
	EXTENS="$EXTENS$line";	
	count=$[$count+1];
done

echo cleaning intermediate files...
find . -regextype posix-egrep -iregex ".+\.($EXTENS)" -exec ./clean-file.sh \{} \;



