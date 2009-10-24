#!/bin/bash

wc -l `find -regextype posix-egrep -iregex ".+\.(asm|c|cpp|h|m|cs|java|lua|ml|pas|pl|py|ms|rb|bas|frm|cls|)"`
