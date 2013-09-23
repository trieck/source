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

index = XMLIndexer.new
index.load(ARGV[0], ARGV.slice(1))

printf("    elapsed time #{timer}\n")

