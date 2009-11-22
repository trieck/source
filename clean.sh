#!/bin/bash

. ./exclude.sh

find . -regextype posix-egrep -iregex ".+\.(${EXCLUDE})$" -print -exec rm -f {} \;









