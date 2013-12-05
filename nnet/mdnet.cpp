
#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

void main(void)
{
	double weight[2] = { 0.1, 0.1};
	double x[2];
	double y, error, op, neta = 0.1;
	int i;
	char *ch;

	double training_set[10][3] = {
		{ 0.1, 0.2, 0.0 },
		{ 0.3, 0.4, 0.0 },
		{ 0.5, 0.6, 0.0 },
		{ 0.7, 0.8, 1.0 },
		{ 0.9, 1.0, 1.0 },
		{ 0.2, 0.9, 0.0 },
		{ 0.4, 0.7, 0.0 },
		{ 0.6, 0.6, 1.0 },
		{ 0.8, 0.5, 1.0 },
		{ 0.0, 0.4, 0.0 }};
		

	//net o/p
	while(getch())
	{
	for(i = 0; i < 10; i++)
	{
		x[0] = training_set[i][0];
		x[1] = training_set[i][1];

		y = x[0]*weight[0] + x[1]*weight[1];

		// Step function
		/*if(y > 0.5)
			op = 1.0;
		else
			op = 0.0;

		//error = training_set[i][2] - y;

		// Basic learning rule

		if(op != training_set[i][2])
		{
			if(op == 0.0)
			{
				weight[0] += neta * x[0];
				weight[1] += neta * x[1];
			}
			else
			{
				weight[0] -= neta * x[0];
				weight[1] -= neta * x[1];
			}
		}

		// end basic learning rule*/

		// Widrow-Hoff delta learning rule

		weight[0] += neta * (training_set[i][2] - y) * x[0];
		weight[1] += neta * (training_set[i][2] - y) * x[1];

		// End Widrow-Hoff

		cout << y << " req " << training_set[i][2]
			<< " " << weight[0] << " " << weight[1] << endl;
	}
	//*ch = (char)getch();

	}

}