# neural_net_individual.rb

require_relative 'individual'
require_relative 'discrete_attribute'

class NeuralNetIndividual < Individual
  attr_accessor :fitness

  @@data = nil
  @@number_of_nodes = nil
  @@class_attribute = nil
  @@bit_map = nil

  def initialize
    @fitness = 0
    super
  end

  # Test the net's accuracy on training data
  def calculate_fitness
    positive = 0
    negative = 0
    @@data.instances.each do |instance|
      # Calculate output
      classification = classify(instance) < 0 ? @@class_attribute.values[0] : @@class_attribute.values[1]
      if classification == instance[@@class_attribute.name.to_sym]
        positive +=1 
      else
        negative += 1
      end
    end

    @fitness = positive.to_f/(positive + negative)
    return @fitness
  end

  # Assumes binary classification
  def classify(instance)
    output = 0
    weight_index = 0
    # For each perceptron
    @@number_of_nodes.times do
      # For w_0 * x_0, note x_0 = 1
      sum = self.[](weight_index)
      weight_index += 1
      # Iterate through attributes
      @@data.attributes.each do |attribute|
        next if attribute == @@class_attribute
        # Sum up weighted product of instance value and weight
        sum += self.[](weight_index) * instance[attribute.name.to_sym]
        weight_index += 1
      end
      # Threshold
      output += (sum > 0) ? 1 : -1
    end
    return output
  end

  # Create a net with random values
  def self.create
    new_individual = self.new
    new_individual.randomly_initialize
    return new_individual
  end

  def randomly_initialize
    raise 'No data' if @@data.nil?
    raise 'How many nodes?' if @@number_of_nodes.nil?
    raise 'No class attribute' if @@class_attribute.nil?
    @@number_of_nodes.times do
      # For w_0
      self.<< NeuralNetIndividual.generate_weight
      @@data.attributes.each do |attribute|
        next if attribute == @@class_attribute
        self.<< NeuralNetIndividual.generate_weight
      end
    end
  end

  def self.generate_weight
    [-1,1].sample * rand() * 10000
  end

  # Overrides Invididual.new().mutate
  # Randomly choose an index to mutate and
  # generate a new weight
  def mutate
    index_to_mutate = rand(0..self.length-1)
    self[index_to_mutate] = NeuralNetIndividual.generate_weight
    return self
  end


  def self.class_attribute
    @@class_attribute
  end

  def self.number_of_nodes
    @@number_of_nodes
  end

private

  def self.data=(data)
    @@data = data
  end

  def self.number_of_nodes=(number_of_nodes)
    @@number_of_nodes = number_of_nodes
  end

  def self.class_attribute=(class_attribute)
    raise 'No data' if @@data.nil?
    raise 'Invalid class attribute' unless @@data.attributes.map{|attr| attr.name}.include?(class_attribute)
    for index in (0...@@data.attributes.size).to_a.each do
      if @@data.attributes[index].name == class_attribute
        @@class_attribute = @@data.attributes[index]
        return
      end
    end
  end
end