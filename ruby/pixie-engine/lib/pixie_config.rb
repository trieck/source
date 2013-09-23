require 'yaml'
require 'singleton'

class PixieConfig
  include Singleton

  def initialize
    @config = YAML::load(File.open('../config/content.yml'))
  end

  def get(section, key)
    return @config[section][key]
  end
end