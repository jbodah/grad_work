# individual.rb

class Individual < Array
  def self.convert(array)
    new_individual = self.new
    array.each { |el| new_individual << el }
    return new_individual
  end

  # Produces a pair of children
  def self.reproduce(mother, father)
    crossover_point = rand(2..mother.length)
    children = []
    children << self.crossbreed(crossover_point, mother, father)
    children << self.crossbreed(crossover_point, father, mother)
    return children
  end

  def fitness
    raise 'No method implemented'
  end

  # Assume binary representation
  def mutate
    index_to_mutate = rand(0..self.length-1)
    self[index_to_mutate] = self[index_to_mutate] == 0 ? 1 : 0
    return self
  end

  private

  def self.crossbreed(crossover_point, a, b)
    self.convert(a[0, crossover_point-1] + b[crossover_point-1, b.length])
  end
end