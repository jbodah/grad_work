# parallel_genetic_algorithm.rb

require 'thread'

class ParallelGeneticAlgorithm < GeneticAlgorithm
  # Return an individual whose fitness exceeds the threshold
  def search(threshold)
    mutex = Mutex.new

    until @population.parallel_contains_an_individual_with_fitness_as_good_as?(threshold)
      # DEBUG CODE
      puts "Reproducing... #{@population.size}"
      new_population = @population.class.new
      threads = []
  
      for index in (0...(@population.size/2)) do
        threads << Thread.new { 
          x = @population.random_selection
          y = @population.random_selection
          children = @population.first.class.reproduce(x, y)
          children.each do |child|
            child.mutate if rand() <= mutation_rate
          end
          mutex.synchronize do
            children.each {|child| new_population.push(child)}
          end
        }
      end
      threads.each do |thread|
        thread.join
      end

      @population = new_population
    end
    return @population.best_individual
  end
end