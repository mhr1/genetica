
#include "nnet.h"


int neuron::set_connections(int con)
{
	if((con < 1) || (con > 10))
	{
		return NET_OUT_OF_RANGE;
	}
	else
	{
		connections = con;
		return NET_OK;
	}

	// returns zero if OK
}

int neuron::set_input(int input_index, double net_var)
{
	if((input_index < 0) || (input_index >= connections))
	{
		return NET_OUT_OF_RANGE;
	}
	else
	{
		input[input_index] = net_var;
		return NET_OK;
	}
}

int neuron::set_weight(int weight_index, double net_var)
{
	if((weight_index < 0) || (weight_index >= connections))
	{
		return NET_OUT_OF_RANGE;
	}
	else
	{
		weight[weight_index] = net_var;
		return NET_OK;
	}
}

double neuron::get_weight(int weight_index)
{
	return weight[weight_index];
}

double neuron::get_output(void)
{
	double temp = 0;

	for(int i = 0; i < connections; i++)
	{
		temp += (input[i] * weight[i]);
	}

	output = 1/(1 + exp(-temp));

	return output;
}

double neuron::get_back_prop_error(int input_index, double error)
{
	double delta;
	double back_prop_error;

	delta = output * (1 - output) * error;

	back_prop_error = delta * weight[input_index];

	return back_prop_error;
}

void neuron::update_weights(double error)
{
	double delta;

	delta = output * (1 - output) * error;

	for(int i = 0; i < connections; i++)
	{
		weight[i] += (0.5 * delta * input[i]);
	}

}

