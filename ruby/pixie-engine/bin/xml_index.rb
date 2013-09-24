$:.unshift File.join(File.dirname(__FILE__),'..','lib')

require 'xml_indexer'
require 'timer'

def usage
  $stderr.puts("usage: #{File.basename($0)} database fields")
  exit(1)
end

if ARGV.length < 2
  usage()
end

timer = Timer.new

begin
  index = XMLIndexer.new
  index.load(ARGV[0], ARGV[1,ARGV.length])
rescue Exception => e
  puts e.message
  exit(1)
end

printf("    elapsed time #{timer}\n")

