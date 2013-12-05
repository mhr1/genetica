
#include <iostream>

using namespace std;

unsigned char world[20][3] = {
{  2,  5, 8 },
{  1,  3, 10},
{  2,  4, 12},
{  3,  5, 14},
{  1,  4, 6 },
{  5,  7, 15},
{  6,  8, 17},
{  1,  7, 9 },
{  8, 10, 18},
{  2,  9, 11},
{ 12, 19, 16},
{  3, 11, 13}, 
{ 12, 14, 20},
{  4, 13, 15},
{  6, 14, 16},
{ 15, 17, 20},
{  7, 16, 18},
{  9, 17, 19},
{ 11, 18, 20},
{ 13, 16, 20}};	

int main (void)
{
	int player = 5;
	int wumpus = 11;

	
	cout << "You are in room " << player << endl;
	cout << "Connecting rooms are " << world[player - 1][0] \
		 << ", " << world[player - 1][1] \
		 << ", " << world[player - 1][2]

}