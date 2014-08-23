# population.rb

class Population < Array
  attr_accessor :best_individual

  def self.create(individuals=nil)
    new_population = self.new
    individuals.each { |individual| new_population << individual }
    return new_population
  end

=begin
  # Return the fittest individual
  def best_individual
    self.max{|a,b| a.fitness <=> b.fitness}
  end
=end

  # Used to terminate search
  # Assumes threshold in [0,1] and assumes binary classification
  def parallel_contains_an_individual_with_fitness_as_good_as?(threshold)
    # Multithread
    threads = []
    self.each do |individual|
      threads << Thread.new(individual) do |indiv|
        indiv.calculate_fitness
      end
    end

    threads.each do |thread|
      thread.join
    end

    self.each do |individual|
      fitness = individual.fitness
      # DEBUG CODE
      puts fitness
      if fitness >= threshold
        @best_individual = individual
        return true
      end
    end
    false
  end

  def contains_an_individual_with_fitness_as_good_as?(threshold)
    # Single thread
    self.each do |individual|
      fitness = individual.calculate_fitness
      # DEBUG CODE
      puts fitness
      if fitness >= threshold
        @best_individual = individual
        return true
      end
    end
    false
  end

  # Randomly choose an individual based on fitnesses
  def random_selection
    fitness_sum = self.map{|x| x.fitness * x.fitness}.inject{|sum, x| sum + x}
    mapping = create_map_from_real_numbers_to_individuals(fitness_sum)
    random_number = rand()
    mapping.each do |individual_hash|
      return individual_hash[:individual] if random_number <= individual_hash[:upper_bound]
    end
    raise "Unexpected error"
  end

  private

  # Used to map probabilities to individuals
  def create_map_from_real_numbers_to_individuals(fitness_sum)
    mapping = []
    current = 0
    self.each do |individual|
      mapping << { :individual => individual, :upper_bound => current + individual.fitness/fitness_sum }
      current += (individual.fitness * individual.fitness)/fitness_sum
    end
    return mapping
  end
end