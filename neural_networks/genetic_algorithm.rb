# genetic.rb

require 'timeout'

# Assumes individuals are in the form of an array
class GeneticAlgorithm
  attr_accessor :population, :mutation_rate

  def initialize(population, mutation_rate)
    @population     = population
    @mutation_rate  = mutation_rate
  end

  # Time-limited search
  def time_limited_search(threshold, time_limit_in_seconds)
    Timeout::timeout(time_limit_in_seconds) {
      self.search(threshold)
    }
  end

  # Return an individual whose fitness exceeds the threshold
  def search(threshold)
    until @population.contains_an_individual_with_fitness_as_good_as?(threshold)
      # DEBUG CODE
      puts "Reproducing... #{@population.size}"
      new_population = @population.class.new
      (@population.size/2).times do
        x = @population.random_selection
        y = @population.random_selection
        children = @population.first.class.reproduce(x, y)
        children.each do |child|
          child.mutate if rand() <= mutation_rate
        end
        children.each {|child| new_population.push(child)}
      end
      @population = new_population
    end
    return @population.best_individual
  end
end