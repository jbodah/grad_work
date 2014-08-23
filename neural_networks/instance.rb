# instance.rb

class Instance
  attr_accessor :attribute_values

  def self.create(attribute_values)
    @attribute_values = attribute_values
  end
end