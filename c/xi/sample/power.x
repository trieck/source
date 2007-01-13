#!/usr/bin/xi

[pow
	[x [? ^]] let	# x is head of list
	[y [? $]] let	# y is tail of list
		
	[ [y 0] eq [1];
	  [1] [x [x [y 1]-]<-pow ]*
	] cond	
] def
	