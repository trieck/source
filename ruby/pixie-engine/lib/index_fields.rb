require 'index_header'

class IndexFields

  include Enumerable

  class << self
    private :new, :allocate
  end

  def self.from_db (db)
    @fields = []
    repos = Repository.instance
    index = repos.get_index_path(db)

    File.open(index, 'rb') do |io|
      header = IndexHeader.read(io)
      (0..header.num_fields-1).each do |i|
        @fields << header.fields[i].name
      end
    end
  end

  def self.from_fields (fields)
    @fields = fields.sort
  end

  def size
    @fields.size
  end

  def top_level?(field)
    @fields.include? field
  end

  def each(&block)
    @fields.each do |member|
      block.call(member)
    end
  end

end