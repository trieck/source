#!/bin/bash

. ./exclude.sh

find . -regextype posix-egrep -regex ".+\.(${EXCLUDE})$" -exec rm -f {} \;









