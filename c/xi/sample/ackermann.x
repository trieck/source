#!/usr/bin/xi

# compute Ackermann's function
[A 
	[m [? ^]] let						# m is head of list
	[n [? $]] let						# n is tail of list
		
	[	[m 0] eq [n 1]+					# A(0, n) = n + 1
		[n 0] eq [[m 1]- 1]<-A			# A(m - 1, 1)	
		[1] [[m 1]- [m [n 1]-]<-A]<-A	# A(m - 1, A(m, n - 1))
	] cond
] def