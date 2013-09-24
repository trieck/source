require 'pixie_config'
require 'singleton'

class Repository
  include Singleton

  def initialize
    @config = PixieConfig.instance
  end

  def get_path
    @config.get 'content', 'repos'
  end

  def map_path(db)
    File.join(get_path, File::SEPARATOR, db)
  end

  def get_index_path(db)
    out_path = map_path(db)
    File.join(out_path, "#{db}.idx")
  end
end