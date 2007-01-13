#!/usr/bin/env ruby

require 'Win32API'

print "Type a character: "
getch = Win32API.new("crtdll", "_getch", [], 'L')
reply = getch.Call.chr
print reply

