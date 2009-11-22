#!/bin/bash

. ./exclude.sh

find . -regextype posix-egrep -regex ".+\.(${EXCLUDE})$" -print -exec rm -f {} \;









