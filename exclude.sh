#!/bin/bash

EXCLUDE=""
count=0

exec < ./excluded
while read line
do
	len=${#line}

	if [ $len -gt 0 ]; then
		if [ $count -gt 0 ]; then
			EXCLUDE="$EXCLUDE|";
		fi
		
		EXCLUDE="${EXCLUDE}$line";	
		count=$[$count+1];
	fi
done


