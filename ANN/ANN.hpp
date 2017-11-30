/*  Copyright 2017 George Le

    Declaration of classes Neuron and ANN.
*/

#ifndef ANN_HPP
#define ANN_HPP

#include <map> // std::map
#include <memory> // std::shared_ptr
#include <vector> // std::vector

// This enumerated type specifies to the neurons which transfer function to utilize
typedef enum Activation_Functions { NO_ACTIVIATION_FUNCTION, STEP, SIGMOID } ActivationFunctions;

/*
	A neuron is a base component of an artificial neural network.
*/
class Neuron
{
	public:
	Neuron();
	Neuron(double new_value) { m_value = new_value; }

	protected:
	double m_value;
};

/*  
	Neurons in the hidden layer work as filters for the neural network being
	able to take in all of the input vectors of the previous layer (could be
	the input layer or another layer in the hidden layer) and output whether
	the inputs compared to a bias are significant enough for the neural net
	to factor into its decision. Neurons' outputs are simply a number, in this
	implementation, a double precision floating point number.
*/
class HiddenLayerNeuron : protected Neuron
{
public:
	HiddenLayerNeuron();

	// accessor functions
	double get_input_vector(int index) { return m_input_vectors.at(index); }
	double get_input_weight(int index) { return m_input_weight.at(index); }
	double get_bias() { return m_bias; }

private:
	/*------------------------------------------
	Calculates u = (summation of wi * xi + bias)
	------------------------------------------*/
	double summation_weight_input_vector();

	// Transfer Functions
public:
	/*---------------------------------------------------------------------
	Perceptron Implementation

	Implements the piecewise function

	yk = { 1 if u >= 0, 0 if u < 0 }, where u = summation of wi * xi - bias

	Returns true if m_summation >= 0 and returns false if m_summation < 0
	---------------------------------------------------------------------*/
	bool step_function();

	/*---------------------------------------------------------------------
	Sigmoid Implementation

	Function that implements the following function
	for the k'th neuron
	yk = phi * summation, where phi is the sigmoid function -> 1/(1-e^-x)
	and the summation = (summation of wi * xi - bias)

	And returns a double percision value yk between 1 and 0
	----------------------------------------------------------------------*/
	double sigmoid_function();

private:
	// a vector of all input vectors from either the inputs
	// or the outputs of the neurons of the previous layers
	std::vector<double> m_input_vectors;
	// should not be used if Neuron is in input layer
	std::vector<double> m_input_weight;
	// bias value of the neuron (optional-use with perceptron), which has values less
	// than the bias are ignored by the neural network
	double m_bias;

	// summation calculated in summation_weight_input_vector()
	double m_summation;

	// does not allow transfer functions to work until summation
	// has been calculated
	// reset after use in transfer functions
	bool summation_complete;
};

class InputLayerNeuron : protected Neuron
{
public:
	InputLayerNeuron();
	InputLayerNeuron(double value);

	// accessor function
	double get_value() const { return m_value; }

	// mutator function
	void set_value(double new_value) { m_value = new_value; }

	// overloaded insertion and extraction operators
	friend std::ostream& operator<<(std::ostream& output, const InputLayerNeuron& neuron) { return output << neuron.get_value(); }
	friend std::istream& operator>>(std::istream& input, InputLayerNeuron& neuron) { return input >> neuron.m_value; }

	// overloaded assignment operator
	void operator=(const InputLayerNeuron& neuron) { m_value = neuron.m_value; }
};

class OutputLayerNeuron : protected Neuron
{
public:
	OutputLayerNeuron();
	OutputLayerNeuron(std::string representation);

	// accessor function
	double get_value() const { return m_value; }
	std::string get_value_representation() const { return m_value_represents; }

	// mutator function
	void set_value(double new_value) { m_value = new_value; }
	void set_representation(std::string new_representation) { m_value_represents = new_representation; }

	// overloaded insertion and extraction operator only accesses and modifies the double value and not the string value 
	// contained in the neuron
	friend std::ostream& operator<<(std::ostream& output, const OutputLayerNeuron& neuron) { return output << neuron.m_value; }
	friend std::istream& operator>>(std::istream& input, OutputLayerNeuron& neuron) { return input >> neuron.m_value; }

	// overloaded assignment operator modifies both values of the neuron
	void operator=(const OutputLayerNeuron& neuron) { m_value = neuron.m_value; m_value_represents = neuron.m_value_represents; }

private:
	std::string m_value_represents;
};

/*
An artificial neural network
*/
class ANN
{
public:
	// default constructor
	ANN();

	// accessor functions
	unsigned int number_of_hidden_layers() const { return m_main_neural_network.size();  }
	unsigned int hidden_layer_size(int hidden_layer_location) const { return m_main_neural_network.at(hidden_layer_location).size(); }

	// mutator functions

	/*-------------------------------------------------------------------------
	This function adds a layer at either the input layer of the ANN
	It accepts a vector of neurons for the input layer of the neural net
	--------------------------------------------------------------------------*/
	bool push_back(std::vector<InputLayerNeuron> layer);
	/*-------------------------------------------------------------------------
	This function adds a layer at either the output layer of the ANN
	It accepts a vector of neurons for the output layer of the neural net
	--------------------------------------------------------------------------*/
	bool push_back(std::vector<OutputLayerNeuron> layer);
	/*-------------------------------------------------------------------
	This overloaded function adds a layer hidden layer of the ANN
	It accepts a vector of neurons and the index of the hidden layer
	--------------------------------------------------------------------*/
	bool push_back(std::vector<HiddenLayerNeuron> layer, unsigned int hidden_layer_location);

	/*--------------------------------------------------------------------------------
	This function evaluates the neural network and returns the result generated by the
	ANN.
	---------------------------------------------------------------------------------*/
	std::string evaluate_neural_net();

	// debug function


private:
	// holds hidden layers of the artificial neural network
	std::map<unsigned int, std::vector<HiddenLayerNeuron>> m_main_neural_network;

	// holds the neurons of the input layer
	std::vector<InputLayerNeuron> m_input_layer;

	// holds the neurons of the output layer
	std::vector<OutputLayerNeuron> m_output_layer;
};

typedef enum ANN_Layer { UNSET_ANN_LAYER, INPUT_LAYER, HIDDEN_LAYER, OUTPUT_LAYER } ANN_layer;

class NeuronFactory
{
	public:
	// gain an instance of a static NeuronFactory (Version C++11) as a 
	// shared pointer to the NeuronFactory instance
	static std::shared_ptr<NeuronFactory> get_instance() {
		static std::shared_ptr<NeuronFactory> instance(new NeuronFactory);
		return instance;
	}

	// overloaded function for usage with pre C++11 or non-shared pointer
	// interfaces
	static NeuronFactory* get_instance_ptr() {
		static NeuronFactory* instance = new NeuronFactory();
		return instance;
	}

	private:
	// private default constructor because singleton
	// EMPTY default constructor
	NeuronFactory() { }
	
	/*---------------------------------------------------------------------------------------------------------------
	This function takes in a vector of doubles to be stored in the neuron layer and an enumerated type corresponding 
	to the layer of neurons that is being created. This function creates a vector of shared pointers to neurons (of
	the type specified by the enumerated type)
	----------------------------------------------------------------------------------------------------------------*/
	std::vector<std::shared_ptr<Neuron>> generate_layer(std::vector<double> input_vectors, ANN_layer chosen_layer); 
};

#endif // ANN_HPP