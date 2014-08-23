require_relative 'attribute'

class ContinuousAttribute < Attribute
  attr_accessor :max, :min

  def initialize(name, max_val, min_val)
    @max = max_val.to_i
    @min = min_val.to_i
    @name = name
  end

  def contains?(val)
    return (val.to_i <= @max) && (val.to_i >= @min)
  end

  # Normalize and translate
  def normalize(value)
    (value - self.min)/(self.max - self.min)
  end
end