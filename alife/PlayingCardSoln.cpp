#include <fstream>
#include <iostream>
#include <string.h>
#include <conio.h>

using namespace std;

void main(void)
{
	int ParentGenotype[11] = {0,0,0,0,0,0,0,0,0,0,0};
	int gene = 0;
	int mask = 1;
	int pile0 = 0;
	int pile1 = 1;
	int n;
	int handle;

	ofstream fout("CPres.txt");

	fout << "Hello file" << endl;

	while(gene < 1024)
	{
		pile0 = 0;
		pile1 = 1;	

		cout << "Pile0: ";
		fout << "Pile0: ";

		for(n = 0; n < 10; n++)
		{
			if((gene >> n) & mask)
			{
				cout << n+1 << " ";
				fout << n+1 << " ";
				pile0 += (n+1);
			}
		}

		fout << " = " << pile0;

		cout << "Pile1: ";
		fout << "Pile1: ";

		for(n = 0; n < 10; n++)
		{
			if(!((gene >> n) & mask))
			{
				cout << n+1 << " ";
				fout << n+1 << " ";
				pile1 *= (n+1);
			}
		}

		fout << " = " << pile1;


		cout << endl;
		fout << endl;

		gene++;
	}

	fout.close();
}