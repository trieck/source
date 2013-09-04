#/bin/bash

# run this with cygwin, not mingw
#
find . \( -name *.vcproj -o -name *.sln \) -exec ./vcupgrade.sh {} \;

