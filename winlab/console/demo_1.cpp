// Demo 1: Output produced by a global variable definition

#include <iostream.h>

class test
{
	public:
	test(){cout << "Hello World\n";}
};

test t;

int main()
{
	return 0;
}