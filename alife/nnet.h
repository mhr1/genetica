// nnet.h
#include <math.h>

#define NET_OK					0
#define NET_OUT_OF_RANGE		1
#define CONNECTIONS_NOT_SET	2

class network
{
public:
	network(){};
	double learning_rate;
};

class neuron : public network
{
public:
	neuron()
	{	//connections = 0;
	};
	/*neuron(int var)
	{	connections = var;
	};*/
	~neuron(){};
	int set_connections(int con);
	int set_input(int input_index, double net_var);
	int set_weight(int weight_index, double net_var);
	double get_weight(int weight_index);
	double get_output(void);
	double get_back_prop_error(int input_index, double error);
	void update_weights(double error);


private:
	int connections;
	double input[10];
	double weight[10];
	double output;
	double neta;
};