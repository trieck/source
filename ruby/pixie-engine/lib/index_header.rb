require 'bindata'

class UTF8String < BinData::String
  def snapshot
    super.force_encoding('UTF-8')
  end
end

class IndexField < BinData::Record
  endian :big
  uint16 :len, :value => lambda { name.length }
  utf8_string :name, :read_length => :len
end

class IndexHeader < BinData::Record
  endian :big
  uint32 :magic_num, :asserted_value => 0xc001d00d
  uint32 :num_fields
  array :fields, :type => :index_field, :initial_length => :num_fields
end
