#!/bin/bash

make "INCLUDES"="`pkg-config --cflags glib-2.0`" \
	"LIBS"="`pkg-config --libs glib-2.0`"