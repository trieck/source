#/bin/bash

find . -name *.sln -exec ./msbuild.sh {} \;

