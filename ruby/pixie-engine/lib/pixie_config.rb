require 'yaml'
require 'singleton'

class PixieConfig
  include Singleton

  def initialize
    path = File.join(File.dirname(__FILE__),'..','config', 'content.yml')
    @config = YAML::load(File.open(path))
  end

  def get(section, key)
    return @config[section][key]
  end
end