require 'index'
require 'index_fields'
require 'repository'

class XMLIndexer

  def initialize
    @repos = Repository.new
    @index = Index.new
    @fields = IndexFields.new
    @elements = []
  end

  def load(db, fields)
      puts @repos.map_path db
  end
end