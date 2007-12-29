#!/usr/bin/env lua5.1

-- Euclid's Algorithm
-- Given two positive integers m and n, find
-- their greatest common divisor, that is, the largest
-- positive integer that evenly divides both m and n.
function euclid(m, n)
	local r = m % n
	
	if r == 0 then return n end	
	return euclid(n, r)
end

--print (euclid(800,51))

-- Harmonic series
function harmonic(n)
	local t = 0; i = 1
	
	while i <= n do
		t = t + 1/i
		i = i + 1
	end
	
	return t
end

print (harmonic(10000000))
