# my_data.rb

require_relative 'instance'
require_relative 'continuous_attribute'
require_relative 'discrete_attribute'

class MyData
  attr_accessor :instances, :attributes

  # Assume last attribute is class attribute
  def self.read_file(file)
    line = file.gets
    attributes = []
    raise 'Invalid format, expected "@attributes"' unless line.strip == "@attributes"
    while (line = file.gets.strip) != "@end_of_attributes"
      name = line
      type = file.gets.strip
      if type == "continuous"
        new_attr = ContinuousAttribute.new(name, file.gets.strip.to_i, file.gets.strip.to_i)
      elsif type == "discrete"
        new_attr = DiscreteAttribute.new(name, file.gets.strip.gsub(/[{}]/,'').split(',').map{|str| str.strip})
      end
      attributes << new_attr
    end

    until (line = file.gets.strip) == "@data" ; end

    instances = []

    while (line = file.gets.strip) != "@end_of_data"
      values = line.split(',').map{|str| str.strip}
      new_hash = {}
      for index in 0..attributes.size-1
        # Assert that the value is valid
        raise "Invalid data: #{values[index]}, #{attributes[index].name}" unless attributes[index].contains?(values[index])
        # Normalize and translate
        new_hash[attributes[index].name.to_sym] = attributes[index].class == ContinuousAttribute ? attributes[index].normalize(values[index].to_i) : values[index]
      end
      instances << Instance.create(new_hash)
    end

    return self.create(instances, attributes)
  end

  def self.create(instances, attributes)
    new_data = self.new
    new_data.instances = instances
    new_data.attributes = attributes
    return new_data
  end
end