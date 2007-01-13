#!/usr/bin/xi

# sieve of eratosthenes

[N 1000] let					# number of primes
[a [N 1]+] mkarray				# make an array of N+1 elements
[[a 1]@ 0] let					# a[1] = 0
[i 2] let						# i = 2

[i .. N	 						# i <= N
	[[a i]@ 1] let 				# a[i] = 1
] each

[i 2] let						# i = 2
[i .. [N 2]/					# i <= N/2
	[j 2] let					# j = 2
	[j .. [N i]/				# j <= N/i
		[[a [i j]*]@ 0] let		# a[i*j] = 0
	] each		
] each

[i 1] let						# i = 1
[i .. N							# i <= N

	[[a i]@ 
		[]						# prime
	] if	
] each
