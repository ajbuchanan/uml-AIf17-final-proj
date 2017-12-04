/* Copyright 2017 George Le

    Definitions for member functions declared in ANN_neuron.hpp
*/
#include "ANN_neuron.hpp"

double HiddenLayerNeuron::summation_weight_input_vector()
{
	m_summation = 0.0;

	if ((m_input_vectors.size() == m_input_weight.size()) && (m_input_vectors.size() > 0 && m_input_weight.size() > 0))
	{
		for(unsigned int i = 0; i < m_input_vectors.size(); ++i)
		{
			m_summation += (m_input_vectors.at(i) * m_input_weight.at(i) + m_bias);
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
	return (1.0 / 1.0 - exp((-1) * summation_weight_input_vector()));
}

std::vector<std::shared_ptr<Neuron>> NeuronFactory::generate_layer(std::vector<double> input_vectors, ANN_layer chosen_layer, unsigned int size)
{
	std::vector<std::shared_ptr<Neuron>> temp;

	switch(chosen_layer)
	{
		case INPUT_LAYER:
		for(unsigned int i = 0; i < size; ++i)
		{
			InputLayerNeuron* temp = new InputLayerNeuron(input_vectors.at(i));
			temp.push_back(temp);
		}
		break;
		case HIDDEN_LAYER:
		
		break;
		case OUTPUT_LAYER:

		break;
	}
}