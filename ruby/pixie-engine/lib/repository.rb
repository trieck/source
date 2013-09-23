require 'pixie_config'

class Repository

  def initialize
    @config = PixieConfig.instance
  end

  def get_path
    @config.get 'content', 'repos'
  end

  def map_path(db)
    File.join(get_path, File::SEPARATOR, db)
  end
end