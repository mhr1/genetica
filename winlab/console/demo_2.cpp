// Demo 2: An Application of late binding

#include <iostream.h>

class base
{
	public:
		virtual void f(){}
		base();
} *p;

base::base()
{
	p = this;
}

//---------------------------------

class test: public base
{
	public:
	void f(){cout << "Hello World\n";}
};

test t; // stores the address of t in p

//------------------------------------


int main()
{
	p -> f(); // produces output
	return 0;
}