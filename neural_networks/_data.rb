# data.rb

require_relative 'instance'

class MyData
  attr_accessor :instances

  # Assume last attribute is class attribute
  def self.read_file(file)
    line = file.gets
    attributes_and_values = []
    raise 'Invalid format, expected "@attributes"' unless line.strip == "@attributes"
    while (line = file.gets.strip) != "@end_of_attributes"
      new_hash = {}
      new_hash[:name] = line
      new_hash[:type] = file.gets.strip
      if new_hash[:type] == "continuous"
        new_hash[:max] = file.gets.strip
        new_hash[:min] = file.gets.strip
      elsif new_hash[:type] == "discrete"
        new_hash[:values] = file.gets.strip.gsub(/[{}]/,'').split(',').map{|str| str.strip}
      end
      attributes_and_values << new_hash
    end

    until (line = file.gets.strip) == "@data" ; end

    instances = []

    while (line = file.gets.strip) != "@end_of_data"
      values = line.split(',').map{|str| str.strip}
      new_hash = {}
      for index in 0..attributes_and_values.size-1
        # Assert that the value is valid
        if attributes_and_values[index][:type] == "continous"
          raise "Invalid data: #{values[index]}, min #{attributes_and_values[index][:min]}, max #{attributes_and_values[index][:min]}" unless values[index] >= attributes_and_values[index][:min] and values[index] <= attributes_and_values[index][:max]
        elsif attributes_and_values[index][:type] == "discrete"
          raise "Invalid data: #{values[index]}, #{attributes_and_values[index][:values]}" unless attributes_and_values[index][:values].include?(values[index])
        end
        new_hash[attributes_and_values[index][:name].to_sym] = values[index]
      end
      instances << Instance.create(new_hash)
    end

    return self.create(instances, attributes_and_values)
  end

  def self.create(instances, attributes_and_values)
    new_data = self.new
    new_data.instances = instances
    new_data.attributes_and_values = attributes_and_values
    return new_data
  end

  def attributes
    attributes_and_values.keys
  end

  def values_for(attribute)
    return attributes_and_values[attribute.to_sym]
  end
end