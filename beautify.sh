#!/bin/bash

find . \( -name *.cpp -o -name *.c -o -name *.h \) -exec astyle --style=kr --indent=spaces {} \;
