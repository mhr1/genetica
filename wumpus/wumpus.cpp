
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <conio.h>

using namespace std;

#define FALSE 0
#define TRUE !FALSE

#define q 0x71

int world[20][3] = {
{  2,  5, 6 },	//1
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
{ 14, 16, 19}};	//20

void auto_play(void);
void user_play(void);
void delay(int seconds);

void main (void)
{
	char console_ip[5];
	char ch;

	do
	{
		cout << "Auto play? (y or n)" << endl;
		cin >> console_ip;
		//cout << autoplay << endl;

		if(!strcmp(console_ip, "y"))
		{
			auto_play();
		}
		else
		{
			user_play();
		}

		cout <<  "q to quit any other to continue" << endl;
		//cin >> console_ip;
	}while((ch = getch()) != 'q');
}

void auto_play(void)
{
	int player, oldroom, arrow, arrows_left = 7;
	int wumpus, pit, bats;
	int i, dead = FALSE, correct_input;
	double temp;


	cout << "Autoplay engaged" << endl;

	srand((unsigned int)time(NULL));

	temp = rand();
	player = (int)fmod(temp,20) + 1;

	temp = rand();
	while ((wumpus = (int)fmod(temp,20) + 1) == player)
		temp = rand();

	temp = rand();
	while ((pit = (int)fmod(temp,20) + 1) == player)
		temp = rand();

	temp = rand();
	while ((bats = (int)fmod(temp,20) + 1) == player)
		temp = rand();

	cout << "Wumpus is in room " << wumpus << endl;
	cout << "Pit is in room " << pit << endl;
	cout << "Bats are in room " << bats << endl;


	cout << "You are in room " << player << endl;
	cout << "Connecting rooms are " << world[player - 1][0] \
			<< ", " << world[player - 1][1] \
			<< ", " << world[player - 1][2] << endl;

	while(!dead)
	{
		delay(4);
		// randomly choose one of three rooms to go to

		temp = rand();
		oldroom = player;
		player = world[oldroom - 1][(int)fmod(temp, 3)];

		if(player == wumpus )
		{
			cout << "The Wumpus got you!" << endl;
			dead = TRUE;
		}
		else if(player == pit)
		{
			cout << "You fell down the pit!" << endl;
			dead = TRUE;
		}
		else if(player == bats)
		{
			cout << "The bats have got you!!!" << endl;

			temp = rand();
			player = (int)fmod(temp,20) + 1;

			if(player == wumpus)
			{
				cout << "The bats dropped you on the wumpus - you're dead!" << endl;
				dead = TRUE;
			}

			else if(player == pit)
			{
				cout << "The bats dropped you down the pit - you're dead!" << endl;
				dead = TRUE;
			}
			else
			{

				cout << "You are in room " << player << endl;
				cout << "Connecting rooms are " << world[player - 1][0] \
				<< ", " << world[player - 1][1] \
				<< ", " << world[player - 1][2] << endl;
	
				for(i = 0; i < 3; i++)
				{
					if(world[player - 1][i] == wumpus)
						cout << "I smell a wumpus!" << endl;
					else if(world[player - 1][i] == pit)
						cout << "I feel a draft!" << endl;
					
				}

				bats = player;
			}

		}
		else
		{
			cout << "You are in room " << player << endl;
			cout << "Connecting rooms are " << world[player - 1][0] \
			<< ", " << world[player - 1][1] \
			<< ", " << world[player - 1][2] << endl;

	
			for(i = 0; i < 3; i++)
			{
				if(world[player - 1][i] == wumpus)
				{
					cout << "I smell a wumpus!" << endl;

					cout << "Try shooting the Wumpus" << endl;

					temp = rand();
					arrow = world[player - 1][(int)fmod(temp, 3)];

					if(arrows_left > 0)
					{
						if(arrow == wumpus )
						{
							cout << "Wumpus killed in room " << wumpus << endl;
							dead = TRUE;
							break;
						}
						else
						{
							cout << "Missed!" << endl;
							arrows_left--;
						}
					}
					else
					{
						cout << "Out of arrows - cannot shoot the Wumpus" << endl;
					}

				}
				else if(world[player - 1][i] == pit)
					cout << "I feel a draft!" << endl;
				else if(world[player - 1][i] == bats)
					cout << "I hear bats!" << endl;
			}
		}
	}


}

void user_play(void)
{
	char key_input [40];
	int player, oldroom, arrow;
	int wumpus, pit, bats;
	int i, dead = FALSE, correct_input;
	double temp;

	srand((unsigned int)time(NULL));

	temp = rand();
	player = (int)fmod(temp,20) + 1;

	temp = rand();
	while ((wumpus = (int)fmod(temp,20) + 1) == player)
		temp = rand();

	temp = rand();
	while ((pit = (int)fmod(temp,20) + 1) == player)
		temp = rand();

	temp = rand();
	while ((bats = (int)fmod(temp,20) + 1) == player)
		temp = rand();

/*	cout << "Wumpus is in room " << wumpus << endl;
	cout << "Pit is in room " << pit << endl;
	cout << "Bats are in room " << bats << endl;*/

	cout << "You are in room " << player << endl;
	cout << "Connecting rooms are " << world[player - 1][0] \
		<< ", " << world[player - 1][1] \
		<< ", " << world[player - 1][2] << endl;

	for(i = 0; i < 3; i++)
	{
		if(world[player - 1][i] == wumpus)
			cout << "I smell a wumpus!" << endl;
		else if(world[player - 1][i] == pit)
			cout << "I feel a draft!" << endl;
		else if(world[player - 1][i] == bats)
			cout << "I hear bats!" << endl;
	}

	char ch[2];

	while(!dead)
	{
		

		correct_input = FALSE;
		oldroom = player;

		while(!correct_input)
		{
			cin >> key_input;

			strncpy(ch, key_input, 1);

//cout << ch << endl;

			if(ch[0] == 0x73)
			{	
				cout << "Which room to shoot at?" << endl;
				cin >> key_input;
				arrow = (int)strtod(key_input, NULL);

				if(arrow == wumpus)
				{
					cout << "You got the Wumpus!" << endl;
					dead = TRUE;
					break;
				}
				else
				{
					cout << "You missed!" << endl;
				}

			}
			else if(ch[0] == 0x6D)
				cout << "Do you want to move?" << endl;
			else
			{
				player = (int)strtod(key_input, NULL);
			}

			if(player == world[oldroom - 1][0])
				correct_input = TRUE;
			else if(player == world[oldroom - 1][1])
				correct_input = TRUE;
			else if(player == world[oldroom - 1][2])
				correct_input = TRUE;
			else
			{
				cout << "You can't get to room " << player 
					<< " from here!" << endl;
				correct_input = FALSE;
			}

		}

		if(player == wumpus )
		{
			cout << "The Wumpus got you!" << endl;
			dead = TRUE;
		}
		else if(player == pit)
		{
			cout << "You fell down the pit!" << endl;
			dead = TRUE;
		}
		else if(player == bats)
		{
			cout << "The bats have got you!!!" << endl;

			temp = rand();
			player = (int)fmod(temp,20) + 1;

			if(player == wumpus)
			{
				cout << "The bats dropped you on the wumpus - you're dead!" << endl;
				dead = TRUE;
			}

			else if(player == pit)
			{
				cout << "The bats dropped you down the pit - you're dead!" << endl;
				dead = TRUE;
			}
			else
			{

				cout << "You are in room " << player << endl;
				cout << "Connecting rooms are " << world[player - 1][0] \
				<< ", " << world[player - 1][1] \
				<< ", " << world[player - 1][2] << endl;
	
				for(i = 0; i < 3; i++)
				{
					if(world[player - 1][i] == wumpus)
						cout << "I smell a wumpus!" << endl;
					else if(world[player - 1][i] == pit)
						cout << "I feel a draft!" << endl;
					
				}

				bats = player;
			}

		}
		else
		{
			cout << "You are in room " << player << endl;
			cout << "Connecting rooms are " << world[player - 1][0] \
			<< ", " << world[player - 1][1] \
			<< ", " << world[player - 1][2] << endl;

	
			for(i = 0; i < 3; i++)
			{
				if(world[player - 1][i] == wumpus)
					cout << "I smell a wumpus!" << endl;
				else if(world[player - 1][i] == pit)
					cout << "I feel a draft!" << endl;
				else if(world[player - 1][i] == bats)
					cout << "I hear bats!" << endl;
			}
		} 
	}
}

void delay(int seconds)
{
	long timenow;

	timenow = time(NULL);
	timenow += seconds;

	while(time(NULL) < timenow)
	{
			//cout << timenow << endl;
	}
}