#/bin/bash

# run this with cygwin, not mingw
#
find . -name *.sln -exec ./vcbuild.sh {} \;

