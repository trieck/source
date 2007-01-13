#!/usr/bin/env ruby

(1..5).each do |i| 
	puts i
end
puts "\n\n"

3.upto(12) do |i|
	puts i
end
puts "\n\n"

puts Array(1..5)
puts String(self)
puts "\n\n"

puts global_variables
puts $LOAD_PATH

