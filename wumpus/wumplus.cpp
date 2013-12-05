
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

using namespace std;

#define FALSE 0
#define TRUE !FALSE

class wumpus_world
{
public:
	wumpus_world();
	//~wumpus_world();

	void delay(int seconds);

	int world[20][3];
};

// constructor for wumpus_world

wumpus_world::wumpus_world()
{
	world[19][3] = 3;
	/*{{  2,  5, 6 },	//1
{  1,  3, 10},	//2
{  2,  4, 9 },	//3
{  3,  5, 8 },	//4
{  1,  4, 7 },	//5
{  1, 11, 12},	//6
{  5, 12, 13},	//7
{  4, 13, 14},	//8
{  3, 14, 15},	//9
{  2, 11, 15},	//10
{  6, 10, 17},	//11
{  6,  7, 18},	//12
{  7,  8, 19},	//13
{  8,  9, 20},	//14
{  9, 10, 16},	//15
{ 15, 17, 20},	//16
{ 11, 16, 18},	//17
{ 12, 17, 19},	//18
{ 13, 18, 20},	//19
{ 14, 16, 19}};	//20*/

	//return(*world);
};

void wumpus_world::delay(int seconds)
{
	long timenow;

	timenow = time(NULL);
	timenow += seconds;

	while(time(NULL) < timenow)
	{
			//cout << timenow << endl;
	}
}

class player: public wumpus_world
{
public:
	//int locate(int);
	int loc;

};



int main(void)
{
	wumpus_world *game = new wumpus_world();
	double temp;
	player player, wumpus, pit, bats;

	cout << "Autoplay engaged" << endl;

	srand((unsigned int)time(NULL));

	temp = rand();
	player.loc = (int)fmod(temp,20) + 1;

	temp = rand();
	while ((wumpus.loc = (int)fmod(temp,20) + 1) == player.loc)
		temp = rand();

	temp = rand();
	while ((pit.loc = (int)fmod(temp,20) + 1) == player.loc)
		temp = rand();

	temp = rand();
	while ((bats.loc = (int)fmod(temp,20) + 1) == player.loc)
		temp = rand();

	cout << "Wumpus is in room " << wumpus.loc << endl;
	cout << "Pit is in room " << pit.loc << endl;
	cout << "Bats are in room " << bats.loc << endl;


	cout << "You are in room " << player.loc << endl;
	cout << "Connecting rooms are " << game->world[player.loc - 1][0] \
			<< ", " << game->world[player.loc - 1][1] \
			<< ", " << game->world[player.loc - 1][2] << endl;


	return 0;
}

