require 'index'
require 'index_fields'
require 'repository'

class XMLIndexer

  def initialize
    @repos = Repository.instance
    @index = Index.new
    @elements = []
  end

  def load(db, fields)
    @fields = IndexFields.from_fields(fields)
    dir = @repos.map_path(db)
    files = expand(dir)
    if files.length == 0
      raise IOError, "no content files found in #{dir}."
    end
    load_files(files)
    @index.write(db, @fields)
  end

  def load_files(files)

  end

  def expand(dir)
    Dir.glob("#{dir}/**/*.xml")
  end
end