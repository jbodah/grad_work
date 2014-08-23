require_relative 'individual'

class TestIndividual < Individual
  attr_accessor :fitness

  def initialize
    @fitness = 0
    super
  end

  def calculate_fitness
    @fitness = self.count(1).to_f / self.length
    return @fitness
  end

  def self.create(size)
    new_individual = self.new
    size.times { new_individual << rand(0..1) }
    return new_individual
  end
end