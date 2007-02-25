x = {}						-- auxillary exclusion table
math.randomseed(os.time())	-- seed random number generator

function rand(low,high)
	while true do
		local r = math.random(low,high)
		if x[r] ~= 1 then return r end
	end
end

function exch(v, l, r)
	local t = v[l]
	v[l] = v[r]
	v[r] = t
end

function scramble(v)
	local r
	local n = table.getn(v)
	for i=1,n do
		if not x[i] then
			x[i] = 1
			if table.getn(x) == n then break end
			r = rand(1, n)
			exch(v, i, r)
			x[r] = 1
		end
	end
end

a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
scramble(a)

print(unpack(a))

