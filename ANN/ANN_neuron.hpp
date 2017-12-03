/*  Copyright 2017 George Le

    This file contains the declarations for the base Neuron class and its
    derived InputLayerNeuron, HiddenLayerNeuron, and OutputLayerNeuron class.
*/
#ifndef ANN_NEURON_HPP
#define ANN_NEURON_HPP

#include <map> // std::map
#include <memory> // std::shared_ptr
#include <utility> // std::pair
#include <vector> // std::vector

// This enumerated type specifies to the neurons which transfer function to utilize
typedef enum Activation_Functions
{ 
    NO_ACTIVIATION_FUNCTION, 
    STEP, 
    SIGMOID, 
    RAMP, 
    LINEAR 
} ActivationFunctions;

/*---------------------------------------------------------------------------
	A neuron is a base component of an artificial neural network. This class 
    contains a pure virtual function that all inheriting classes must 
    implement. 
----------------------------------------------------------------------------*/
class Neuron
{
	public:
	Neuron() { }
	// this constructor should only be used for the input layer
	Neuron(double new_value) { m_neuron_value = new_value; }

	protected:
    /*
	    This neuron value is either the input layer's first input vectors or the output vector
	    of the hidden and output layer
	    for the output layer, this value will be evaluated on a range from values from 
        0 to 1 and be translated into the range's corresponding string value.
        for example if the ranges specified were:
        
            0 -> 0.5 is active low
            0.5 -> 1 is active high

        then if the neuron value is 0.6 then the output neuron will represent the value active high
        because it is in the range between 0.5 and 1 
	*/
    double m_neuron_value;
};

/*-----------------------------------------------------------------------------  
	Neurons in the hidden layer work as filters for the neural network being
	able to take in all of the input vectors of the previous layer (could be
	the input layer or another layer in the hidden layer) and output whether
	the inputs compared to a bias are significant enough for the neural net
	to factor into its decision. Neurons' outputs are simply a number, in this
	implementation, a double precision floating point number.
-----------------------------------------------------------------------------*/
class HiddenLayerNeuron : protected Neuron
{
public:
	HiddenLayerNeuron(std::vector<double> input_vectors, std::vector<double> input_weights, double bias) 
			: m_input_vectors(input_vectors), m_input_weight(input_weights), m_bias(bias), m_summation(0),
			summation_complete(false) { }

	// accessor functions for use by the neural network for backpropogation and gradient descent
	double get_input_vector(int index) { return m_input_vectors.at(index); }
	double get_input_weight(int index) { return m_input_weight.at(index); }
	double get_bias() { return m_bias; }

	void calculate_output(ActivationFunctions function_to_be_used);

private:
	/*------------------------------------------
	Calculates u = (summation of wi * xi + bias)
	-------------------------------------------*/
	double summation_weight_input_vector();

	// Transfer Functions

	/*--------------------------------------------------------------------
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

	// the default constructor of the hidden layer neuron is private to prevent the use of hidden layer neurons without
	// passing through the required parameters to create the neuron
	HiddenLayerNeuron() { }
};

/*
    The InputLayerNeuron takes in values that are contextually available to the neural 
    network to use in solving the problem posed to the neural network. These values must 
    be translated in some form to doubles if they are not 
*/
class InputLayerNeuron : protected Neuron
{
public:
	InputLayerNeuron::InputLayerNeuron(double value) : Neuron(value) { }

	// accessor function
	double get_value() const { return m_neuron_value; }

	// overloaded insertion and extraction operators
	friend std::ostream& operator<<(std::ostream& output, const InputLayerNeuron& neuron) { return output << neuron.get_value(); }
	friend std::istream& operator>>(std::istream& input, InputLayerNeuron& neuron) { return input >> neuron.m_neuron_value; }

	// overloaded assignment operator
	void operator=(const InputLayerNeuron& neuron) { m_neuron_value = neuron.m_neuron_value; }

private:
	// default constructor is private to prevent the use of the neuron in the input layer without providing a input value
	InputLayerNeuron() { }
};

class OutputLayerNeuron : public HiddenLayerNeuron
{
public:
	OutputLayerNeuron(std::vector<double> range_of_representations, std::vector<std::string> representations);
	OutputLayerNeuron(std::map<std::pair<double, double>, std::string> representation, 
					std::vector<double> input_vectors, std::vector<double> input_weights, double bias) 
		: HiddenLayerNeuron(input_vectors, input_weights, bias), representation_of_neuron(representation) { }

	// accessor function
	double get_value() const { return m_neuron_value; }
	std::string get_value_representation(std::pair<double, double> range_of_value) const { return representation_of_neuron.at(range_of_value); }

	// mutator function
	void set_value(double new_value) { m_neuron_value = new_value; }
	void set_representation(std::pair<double, double> range_of_representation, std::string);

	// overloaded insertion and extraction operator only accesses and modifies the double value and not the string value 
	// contained in the neuron
	friend std::ostream& operator<<(std::ostream& output, const OutputLayerNeuron& neuron) { return output << neuron.m_neuron_value; }
	friend std::istream& operator>>(std::istream& input, OutputLayerNeuron& neuron) { return input >> neuron.m_neuron_value; }

	// overloaded assignment operator modifies both values of the neuron
	void operator=(const OutputLayerNeuron& neuron) { m_neuron_value = neuron.m_neuron_value; representation_of_neuron = neuron.representation_of_neuron; }

private:
	// This member variable maps strings to the range of values that it represents, the range is specified as the values between
    // the first and second double in the pair.
	std::map<std::pair<double, double>, std::string> representation_of_neuron;
};


typedef enum ANN_Layer { UNSET_ANN_LAYER, INPUT_LAYER, HIDDEN_LAYER, OUTPUT_LAYER } ANN_layer;

class NeuronFactory
{
	public:
	// gain an s_instance of a static NeuronFactory (Version C++11) as a 
	// shared pointer to the NeuronFactory s_instance
	static std::shared_ptr<NeuronFactory> get_instance() {
		static std::shared_ptr<NeuronFactory> s_instance(new NeuronFactory);
		return s_instance;
	}

	// overloaded function for usage with pre C++11 or non-shared pointer
	// interfaces
	static NeuronFactory* get_instance_ptr() {
		static NeuronFactory* s_instance = new NeuronFactory();
		return s_instance;
	}

	private:
	// private default constructor because singleton
	// EMPTY default constructor
	NeuronFactory() { }

	std::vector<double> randomize_weights();

	double randomize_bias();
	
	/*---------------------------------------------------------------------------------------------------------------
	This function takes in a vector of doubles to be stored in the neuron layer and an enumerated type corresponding 
	to the layer of neurons that is being created. This function creates a vector of shared pointers to neurons (of
	the type specified by the enumerated type and of the size specified)
	----------------------------------------------------------------------------------------------------------------*/
	std::vector<std::shared_ptr<Neuron>> generate_layer(std::vector<double> input_vectors, ANN_layer chosen_layer, unsigned int size); 
};


#endif // ANN_NEURON_HPP