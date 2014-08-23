require_relative 'attribute'

class DiscreteAttribute < Attribute
  attr_accessor :values, :bit_size

  def initialize(name, values)
    @values = values
    @name = name
  end

  def contains?(val)
    return @values.include?(val)
  end
end