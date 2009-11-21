#!/bin/sh

find . \( -name '*.cpp' -o -name '*.h' \) -exec unmac --input={} --output=/d/tmp/{} \;
