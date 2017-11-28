/*  Copyright 2017 George Le

    Declaration of classes Neuron and ANN.
*/

#ifndef ANN_HPP
#define ANN_HPP

#include <map>
#include <vector>

/*  
    
*/
class HiddenLayerNeuron
{
public:
	HiddenLayerNeuron();

	// accessor functions
	double get_input_vector(int index) { return m_input_vectors.at(index); }
	double get_input_weight() { return m_input_weight; }
	double get_bias() { return m_bias; }

private:
	/*
	Calculates u = (summation of wi * xi + bias)
	*/
	double summation_weight_input_vector();

	// Transfer Functions
public:
	/*---------------------------------------------------------
	Perceptron Implementation

	Implements the piecewise function

	yk = { 1 if u >= 0, 0 if u < 0 }, where u = summation of wi * xi - bias

	Returns true if m_summation >= 0 and returns false if m_summation < 0
	----------------------------------------------------------*/
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
	double m_input_weight;
	// bias value of the neuron (optional), which has values less
	// than the bias ignored by the neural network
	double m_bias;

	// summation calculated in summation_weight_input_vector()
	double m_summation;
	// value stored by the neuron after calculating the neuron's 
	// selected activation function * summation
	// this value will be passed to the next layer of neurons as new inputs
	double m_value;

	// does not allow transfer functions to work until summation
	// has been calculated
	// reset after use in transfer functions
	bool summation_complete;
};

class InputLayerNeuron
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

private:
	double m_value;
};

class OutputLayerNeuron
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
	double m_value;
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

#endif // ANN_HPP