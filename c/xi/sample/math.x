#!/usr/bin/xi

# the constant PI
[PI [[1]atan 4]*] let	
	
# convert radians to degrees
[rad2deg
	[[? PI]/ 180]*
] def

# convert degrees to radians
[deg2rad
	[[? 180]/ PI]*
] def

