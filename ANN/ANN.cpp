/*  Copyright 2017 George Le

Implementation of functions belonging to the ANN and Neuron class

*/
#include <cmath> // exp()

#include "ANN.hpp"

// default constructor
HiddenLayerNeuron::HiddenLayerNeuron()
{
	// EMPTY default constructor
}

double HiddenLayerNeuron::summation_weight_input_vector()
{
	m_summation = 0.0;

	if (m_input_vectors.size() == 0)
	{
		for (auto it = m_input_vectors.begin(); it != m_input_vectors.end(); ++it)
		{
			m_summation += (*it) * m_input_weight + m_bias;
		}
	}

	return m_summation;
}

bool HiddenLayerNeuron::step_function()
{
	if (summation_weight_input_vector() >= 0)
	{
		return true;
	}

	return false;
}

double HiddenLayerNeuron::sigmoid_function()
{
	return (1.0 / 1 - exp((-1) * summation_weight_input_vector()));
}

// default constructor
InputLayerNeuron::InputLayerNeuron()
{
	// EMPTY default constructor
}

InputLayerNeuron::InputLayerNeuron(double value) : m_value(value)
{

}

// default constructor
OutputLayerNeuron::OutputLayerNeuron()
{
	// EMPTY default constructor
}

OutputLayerNeuron::OutputLayerNeuron(std::string representation) : m_value_represents(representation)
{

}

// default constructor
ANN::ANN()
{
	// EMPTY default constructor
}

bool ANN::push_back(std::vector<InputLayerNeuron> layer)
{
	if (layer.size() == 0)
	{
		// if there is nothing in the layer then
		// don't put the layer in the neural net
		// ERROR
		return false;
	}
	else
	{
		m_input_layer = layer;
	}

	return true;
}

bool ANN::push_back(std::vector<OutputLayerNeuron> layer)
{
	if (layer.size() == 0)
	{
		// if there is nothing in the layer then
		// don't put the layer in the neural net
		// ERROR
		return false;
	}
	else
	{
		m_output_layer = layer;
	}

	return true;
}

bool ANN::push_back(std::vector<HiddenLayerNeuron> layer, unsigned int hidden_layer_location)
{
	if (layer.size() == 0)
	{
		// if there is nothing in the layer then
		// don't put the layer in the neural net
		// ERROR
		return false;
	}
	else
	{
		// create the space and insert the layer into the neural net at the
		// hidden_layer_location position
		m_main_neural_network.emplace(hidden_layer_location, layer);
	}
	return true;
}

std::string ANN::evaluate_neural_net()
{
	std::string temp;
	double value = 0.0;
	int index = 0, max_index = 0;


	return std::string();
}