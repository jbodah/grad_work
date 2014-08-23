# main.rb

require_relative 'test_individual'
require_relative 'population'
require_relative 'genetic_algorithm'

require_relative 'my_data'
require_relative 'neural_net_individual'

require_relative 'parallel_genetic_algorithm'

#require 'debugger'
require 'ruby-debug'

=begin
  
individuals = []

10.times do
  individuals << TestIndividual.create(10)
end

#individuals.each {|individual| puts individual.join() << " #{individual.fitness}"}

puts

pop = Population.new(individuals)

#puts pop.best_individual.join() << " #{pop.best_individual.fitness}"

best = GeneticAlgorithm.new(pop, 0.1).search(2)

#puts best.join() << " #{best.fitness}"

mom = TestIndividual.convert("0000000001".split(//)) ; puts mom.join() + " #{mom.size}"
dad = TestIndividual.convert("1111111110".split(//)) ; puts dad.join() + " #{dad.size}"
Individual.reproduce(mom, dad).each {|child| puts child.join() + " #{child.size}"}

=end

#$stdout = File.new('console_longer_p.out', 'w')
#$stdout.sync = true

puts "Processing data..."

orig_file = File.new('spambase_fs.txt','r')
new_file = File.new('spambase_processed.txt','w')

until orig_file.eof?
  line = orig_file.gets
  new_file.write(line) unless line.include?('?')
end

orig_file.close
new_file.close

def verify_classifier(my_data, best, options = {})
  positive = 0
  my_data.instances.each do |instance|
    if options[:invert]
      classification = best.classify(instance) < 0 ? "0" : "1" 
    else
      classification = best.classify(instance) < 0 ? "1" : "0"
    end
    positive +=1 if classification == instance[@class_attribute.name.to_sym]
  end
  accuracy = positive.to_f/my_data.instances.size
  puts accuracy
  return accuracy
end

my_data = MyData.read_file(File.new('spambase_processed.txt','r'))

puts "Initializing network..."

num_nodes = 2
NeuralNetIndividual.data = my_data
NeuralNetIndividual.class_attribute = "is_spam"
NeuralNetIndividual.number_of_nodes = num_nodes
thresh = 0.87
population_size = 10000
search_time = 0
mutation_rate = 0.10

puts "Search on '#{NeuralNetIndividual.class_attribute}', #{num_nodes} nodes, #{thresh} thresh, #{population_size} pop size, #{search_time} search time, #{mutation_rate} mutation rate"

individuals = []
population_size.times do
  individuals << NeuralNetIndividual.create
end

pop = Population.new(individuals)

puts "Searching..."

start_time = Time.now

if search_time > 0
  best = ParallelGeneticAlgorithm.new(pop, mutation_rate).time_limited_search(thresh, search_time)
  #best = GeneticAlgorithm.new(pop, mutation_rate).time_limited_search(thresh, search_time)
else
  best = ParallelGeneticAlgorithm.new(pop, mutation_rate).search(thresh)
  #best = GeneticAlgorithm.new(pop, mutation_rate).time_limited_search(thresh)
end

delta_time = Time.now - start_time

puts "Time to search: #{delta_time}"

puts "Verifying the network..."

# Classify each of the instances
@class_attribute = NeuralNetIndividual.class_attribute

puts "Classifying on \"#{@class_attribute.name}\"..."

if verify_classifier(my_data, best) < thresh
  puts "Trying inversion..."
  verify_classifier(my_data, best, :invert => true)
end

weight_index = 0
for i in (0...NeuralNetIndividual.number_of_nodes)
  puts "===NODE #{i}==="
  my_data.attributes.each do |attribute|
    puts "\t#{attribute.name}: #{best[weight_index]}"
    weight_index += 1
  end
end
