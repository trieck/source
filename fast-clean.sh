#!/bin/bash

FILTER=""
count=0

exec < ./remove-extensions
while read line
do
	if [ $count -gt 0 ]; then
		FILTER="$FILTER -o ";
	fi
	FILTER="$FILTER -name *.$line";	
	count=$[$count+1];
done

find . \( $FILTER \) -print -exec rm -rf \{} \;




