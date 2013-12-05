#include <afxwin.h>
//#include <math.h>
#include <time.h>
#include <conio.h>
#include "ctrnn.h"

//-------------------------------------------------------------
// DEFINES

// Define linrank for linear rank selection algorithm 
// else the simple GA will be used

#define linrank

#ifndef linrank
#define simple_ga
#endif

// show_op Displays the outputs fromthe four CTRNNs
//#define show_op

#define GENERATIONS 60000
#define PLOT_STEP GENERATIONS/600

//-------------------------------------------------------------

void mdelay(int seconds)
{
	long timenow;
	timenow = (long)time(NULL);
	timenow += seconds;

	while(time(NULL) < timenow){}
}

class CMainWindow: public CFrameWnd
{
	public:
		CMainWindow() // :CFrameWnd()
		{
			int xScreen = GetSystemMetrics(SM_CXSCREEN),
				yScreen = GetSystemMetrics(SM_CYSCREEN);

			RECT rect = {0, 0, xScreen, yScreen};

			Create(NULL,			//Use default window-class name
				"Windows test 1",	// Text for title bar
				WS_OVERLAPPEDWINDOW,// Window Style
				rect,				// Size & position of window
				NULL,				// no parent window
				NULL);				// no menu
		}

	// Declare functions for handling messages from Windows
		afx_msg void OnPaint();

		DECLARE_MESSAGE_MAP()

	private:
};

//---------------------------------------------------------------
// Define the "message map"

    BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
        ON_WM_PAINT()
	END_MESSAGE_MAP()

//---------------------------------------------------------------

void CMainWindow::OnPaint()
{

//-----------------------------------------------------------------
//
//		Adaptive Systems project starts here
//
//-----------------------------------------------------------------

	int init_footx[4] = {30, 70, 30, 70};
	int	init_footy[4] = {200, 200, 300, 300};
	int footx[4];
	int	footy[4];
	int old_footy[4];
	int leg_disp[4];
	int legs_moved;
	int steps[4] = { 1, 2, 3, 0};
	int centrex, centrey, old_centrey;
	int sumx, sumy;
	int a, c, f, g, p = 0, i, t, k[4] = {0, 0, 0, 0};
	int input = 0;
	double temp;

	CPaintDC dc(this);
	CPen *myPen;// = (CPen*) dc.SelectStockObject(BLACK_PEN);

	const generations = GENERATIONS;
	const child_num = 30;
	const alleles = 20;
	int gene_no;

	int run_time = 20;

	double parenta[alleles];
	double parentb[alleles];
	double parent[child_num][alleles];
	double child[child_num][alleles];
	double output[4];
	double fitness_score[child_num];
	double fittest[generations];
	int prob_rank[(child_num + 1) * child_num/2];

	char ch[40];

	// Init random number generator
	srand((unsigned int)time(NULL));

	// Make ANN using 4 ctrnns
	neuron ctrnn[4];

	for(i = 0; i < 4; i++)
	{
		ctrnn[i].set_connections(5);
		ctrnn[i].set_time_constant(4);
		output[i] = 0;
	}

#ifdef simple_ga

	// Make the first parents for simple GA
	for(a = 0; a < alleles; a++)
	{
		temp = rand();
		parenta[a] = (fmod(temp, 41) - 21)/100; // Range -2 to 2
	}

#endif

#ifdef linrank

	// Make first generation for Linear Rank Selection
	for(c = 0; c < child_num; c++)
	{
		for(a = 0; a < alleles; a++)
		{
			temp = rand();
			child[c][a] = (fmod(temp,21) - 10)/10;
		}
	}
#endif

// START GENERATIONS

	for(g = 0; g < generations; g++)
	{
		fittest[g] = 0;

#ifdef simple_ga

		// Create some kids
		for(c = 0; c < child_num; c++)
		{
			// Recombination with 50/50 crossover
			for(a = 0; a < alleles; a++)
			{
				
				child[c][a] = parenta[a];

				// Mutate each child
				temp = rand();
				child[c][a] += (fmod(temp,21) - 10)/900;
				// Range -0.1 to 0.1				
			}			
		}
#endif		

		// For each kid
		for(c = 0; c < child_num; c++)
		{
			fitness_score[c] = 0;

			// Create phenotype - set weights
			ctrnn[0].set_weight(0, child[c][0]);
			ctrnn[0].set_weight(1, child[c][1]);
			ctrnn[0].set_weight(2, child[c][2]);
			ctrnn[0].set_weight(3, child[c][3]);
			ctrnn[0].set_weight(4, child[c][4]);
			ctrnn[1].set_weight(0, child[c][5]);
			ctrnn[1].set_weight(1, child[c][6]);
			ctrnn[1].set_weight(2, child[c][7]);
			ctrnn[1].set_weight(3, child[c][8]);
			ctrnn[1].set_weight(4, child[c][9]);
			ctrnn[2].set_weight(0, child[c][10]);
			ctrnn[2].set_weight(1, child[c][11]);
			ctrnn[2].set_weight(2, child[c][12]);
			ctrnn[2].set_weight(3, child[c][13]);
			ctrnn[2].set_weight(4, child[c][14]);
			ctrnn[3].set_weight(0, child[c][15]);
			ctrnn[3].set_weight(1, child[c][16]);
			ctrnn[3].set_weight(2, child[c][17]);
			ctrnn[3].set_weight(3, child[c][18]);
			ctrnn[3].set_weight(4, child[c][19]);


			// TEST PHENOTYPE

			// Set the start position for the walker

			for(i=0; i < 4; i++)
			{
				footy[i] = init_footy[i];
				footx[i] = init_footx[i];
			}

			// Find the centre of the walker
			sumx = 0;
			sumy = 0;

			for(i=0; i < 4; i++)
			{
				sumx += footx[i];
				sumy += footy[i];
			}

			centrex = sumx/4;	
			centrey = sumy/4;

			for(t=0; t < run_time; t++)
			{

				int xg = 20, yg = 200;

				// Set inputs
				ctrnn[0].set_input(0, 10 * cos(t/(4 * 3.1419)));
				ctrnn[0].set_input(1, output[1]);
				ctrnn[0].set_input(2, output[2]);
				ctrnn[0].set_input(3, output[3]);
				ctrnn[0].set_input(4, leg_disp[0]);
				ctrnn[1].set_input(0, 1);
				ctrnn[1].set_input(1, output[0]);
				ctrnn[1].set_input(2, output[2]);
				ctrnn[1].set_input(3, output[3]);
				ctrnn[1].set_input(4, leg_disp[1]);
				ctrnn[2].set_input(0, 1);
				ctrnn[2].set_input(1, output[0]);
				ctrnn[2].set_input(2, output[1]);
				ctrnn[2].set_input(3, output[3]);
				ctrnn[2].set_input(4, leg_disp[2]);
				ctrnn[3].set_input(0, 1);
				ctrnn[3].set_input(1, output[0]);
				ctrnn[3].set_input(2, output[1]);
				ctrnn[3].set_input(3, output[2]);
				ctrnn[3].set_input(4, leg_disp[3]);

	
				// Get Outputs
				output[0] = ctrnn[0].get_output();
				output[1] = ctrnn[1].get_output();
				output[2] = ctrnn[2].get_output();
				output[3] = ctrnn[3].get_output();

	
#ifdef show_op				

				for(i = 0; i < 4; i++)
				{ 	
					dc.SetPixel(xg + t +(run_time * c), yg - (int)output[i] + (100 * i), RGB(255, 0, 0));
					sprintf(ch,"output = %f", float(output[i]));
					dc.TextOut(10,10 + (25 * i), ch, strlen(ch));
				}
#endif

				

				// New positions for feet
				for(i=0; i < 4; i++)
				{
					old_footy[i] = footy[i];
					footy[i] += (int)output[i];
				}


				// Find the centre of the walker
				sumx = 0;
				sumy = 0;

				for(i=0; i < 4; i++)
				{
					sumx += footx[i];
					sumy += footy[i];
				}

				centrex = sumx/4;
				old_centrey = centrey;
				centrey = sumy/4;

				// Calculate leg displacement
				leg_disp[0] = unsigned int(footy[0] - (centrey - 50));
				leg_disp[1] = unsigned int(footy[1] - (centrey - 50));
				leg_disp[2] = unsigned int(footy[2] - (centrey + 50));
				leg_disp[3] = unsigned int(footy[3] - (centrey + 50));

//----------------------------------------------------------------

// Fitness function

//----------------------------------------------------------------

			
				if(centrey > old_centrey)
					fitness_score[c] += 3;
				// Favours forward movement

				legs_moved = 0;

				for(i=0; i < 4; i++)
				{
					if((leg_disp[i] > 5) || (leg_disp[i] < -5))
						fitness_score[c] -= 3;					
					//else
					//	fitness_score[c] += 1;

					// Check how many legs moved
					if(footy[i] != old_footy[i])
						legs_moved++;
				}

				switch (legs_moved)
				{	case 0:fitness_score[c] -= 0;
						break;
					case 1:fitness_score[c] += 3; // Favour single leg
						break;
					case 2:fitness_score[c] += 0.5;
						break;
					case 3:fitness_score[c] -= 0;
						break;
					case 4:fitness_score[c] -= 0;
						break;
					default:
						break;
				}




				// Draw walker

				/*myPen = (CPen*) dc.SelectStockObject(BLACK_PEN);

				for(i = 0; i < 4; i++)
				{
					dc.MoveTo(centrex, centrey);
					dc.LineTo(footx[i], footy[i]);
				}

		
				// Display drawing for one second
				//mdelay(1);

				// Erase drawing
				myPen = (CPen*) dc.SelectStockObject(WHITE_PEN);

				for(i = 0; i < 4; i++)
				{
					dc.MoveTo(centrex, centrey);
					dc.LineTo(footx[i], footy[i]);
				}*/
				//mdelay(1);

			}// End of runtime

#ifdef simple_ga

			if(fitness_score[c] > fittest[g])
			{
				fittest[g] = fitness_score[c];

				for(a = 0; a < alleles; a++)
				{
					parenta[a] = child[c][a];
				}
			}
#endif

		}// End of each child

// Now each child has been tested and has a fitness score

//***************************************************************

// LINEAR RANK SELECTION

#ifdef linrank

		// Sort the order children according to fitness

		while(f > 0)
		{
			f = 0;

			for(c = 0; c < child_num - 1; c++)
			{
				if(fitness_score[c] > fitness_score[c + 1])
				{
					f++;
					temp = fitness_score[c];
					fitness_score[c] = fitness_score[c + 1];
					fitness_score[c + 1] = temp;

					for(a = 0; a < alleles; a++)
					{
						parentb[a] = child[c][a];
						child[c][a] = child[c + 1][a];
						child[c + 1][a] = parentb[a];
					}
				}
			}
		} // End of LRS while loop

		fittest[g] = fitness_score[child_num -1];

		for(a = 0; a < alleles; a++)
		{
			parenta[a] = child[child_num -1][a];
		}


		// Copy the sorted children to a parent array
		for(c = 0; c < child_num; c++)
		{
			for(a = 0; a < alleles; a++)
			{
				parent[c][a] = child[c][a];
			}
		}

		// Make an array of parent indexes - more entries for the fittest
		// therefore higher chance of selection

		c = 0;

		for(t = 0; t < child_num; t++)
		{
			for(f = 0; f <= t; f++)
			{
				prob_rank[c] = t;
				c++;
			}
		}

		// Create a new generation

		for(c = 0; c < child_num; c++)
		{
			// Pick two parents at random
			temp = rand();
			int rank_index_a = fmod(temp, (child_num + 1) * child_num/2);

			temp = rand();
			int rank_index_b = fmod(temp, (child_num + 1) * child_num/2);

			// Recombination with 50/50 crossover
			for(a = 0; a < alleles; a++)
			{
				if(a < (alleles/2))
					child[c][a] = parent[prob_rank[rank_index_a]][a];
				else
					child[c][a] = parent[prob_rank[rank_index_b]][a];
			}

			// Mutate a random allele in each child
			temp = rand();
			gene_no = (int)fmod(temp, 20);

			temp = rand();
			child[c][gene_no] += (fmod(temp,21) - 10)/100;
				// Range -0.1 to 0.1

		} // end of child gen

// END OF LINEAR RANK SELECTION
#endif
//*******************************************************************

		sprintf(ch,"fitness = %f", float(fittest[g]));
		dc.TextOut(10,10, ch, strlen(ch));

		sprintf(ch,"Generation = %d", g);
		dc.TextOut(200,10, ch, strlen(ch));
		//mdelay(1);

/*		// Run the winning walker

		// Create phenotype - set weights
			ctrnn[0].set_weight(0, parenta[0]);
			ctrnn[0].set_weight(1, parenta[1]);
			ctrnn[0].set_weight(2, parenta[2]);
			ctrnn[0].set_weight(3, parenta[3]);
			ctrnn[1].set_weight(0, parenta[4]);
			ctrnn[1].set_weight(1, parenta[5]);
			ctrnn[1].set_weight(2, parenta[6]);
			ctrnn[1].set_weight(3, parenta[7]);
			ctrnn[2].set_weight(0, parenta[8]);
			ctrnn[2].set_weight(1, parenta[9]);
			ctrnn[2].set_weight(2, parenta[10]);
			ctrnn[2].set_weight(3, parenta[11]);
			ctrnn[3].set_weight(0, parenta[12]);
			ctrnn[3].set_weight(1, parenta[13]);
			ctrnn[3].set_weight(2, parenta[14]);
			ctrnn[3].set_weight(3, parenta[15]);


		// Set the start position for the walker

			for(i=0; i < 4; i++)
			{
				footy[i] = init_footy[i];
				footx[i] = init_footx[i];
			}

			// Find the centre of the walker
			sumx = 0;
			sumy = 0;

			for(i=0; i < 4; i++)
			{
				sumx += footx[i];
				sumy += footy[i];
			}

			centrex = sumx/4;	
			centrey = sumy/4;

			for(t=0; t < run_time; t++)
			{

				int xg = 20, yg = 200;

				// Set inputs
				ctrnn[0].set_input(0, 1);
				ctrnn[0].set_input(1, output[1]);
				ctrnn[0].set_input(2, output[2]);
				ctrnn[0].set_input(3, output[3]);
				ctrnn[0].set_input(4, leg_disp[0]);
				ctrnn[1].set_input(0, 1);
				ctrnn[1].set_input(1, output[0]);
				ctrnn[1].set_input(2, output[2]);
				ctrnn[1].set_input(3, output[3]);
				ctrnn[1].set_input(4, leg_disp[1]);
				ctrnn[2].set_input(0, 1);
				ctrnn[2].set_input(1, output[0]);
				ctrnn[2].set_input(2, output[1]);
				ctrnn[2].set_input(3, output[3]);
				ctrnn[2].set_input(4, leg_disp[2]);
				ctrnn[3].set_input(0, 1);
				ctrnn[3].set_input(1, output[0]);
				ctrnn[3].set_input(2, output[1]);
				ctrnn[3].set_input(3, output[2]);
				ctrnn[3].set_input(4, leg_disp[3]);

	
				// Get Outputs
				output[0] = ctrnn[0].get_output() * 10;
				output[1] = ctrnn[1].get_output() * 10;
				output[2] = ctrnn[2].get_output() * 10;
				output[3] = ctrnn[3].get_output() * 10;

	
				/*

				for(i = 0; i < 4; i++)
				{ 	
					dc.SetPixel(xg + t +(run_time * c), yg - (int)output[i] + (100 * i), RGB(255, 0, 0));
					sprintf(ch,"output = %f", float(output[i]));
					dc.TextOut(10,10 + (25 * i), ch, strlen(ch));
				}

				

				// New positions for feet
				for(i=0; i < 4; i++)
				{
					footy[i] += (int)output[i] - 5;
				}


				// Find the centre of the walker
				sumx = 0;
				sumy = 0;

				for(i=0; i < 4; i++)
				{
					sumx += footx[i];
					sumy += footy[i];
				}

				centrex = sumx/4;
				centrey = sumy/4;

				// Draw walker

				myPen = (CPen*) dc.SelectStockObject(BLACK_PEN);

				for(i = 0; i < 4; i++)
				{
					dc.MoveTo(centrex, centrey);
					dc.LineTo(footx[i], footy[i]);
				}

		
				// Display drawing for one second
				//mdelay(1);

				// Erase drawing
				myPen = (CPen*) dc.SelectStockObject(WHITE_PEN);

				for(i = 0; i < 4; i++)
				{
					dc.MoveTo(centrex, centrey);
					dc.LineTo(footx[i], footy[i]);
				}
				//mdelay(1);

			}// End of runtime
			*/
		
	}// End of each generation

	// Draw Fitness graph

	myPen = (CPen*) dc.SelectStockObject(BLACK_PEN);

	dc.MoveTo(150, 500);
	dc.LineTo(750, 500);
	dc.MoveTo(150, 500);
	dc.LineTo(150, 100);

	sprintf(ch,"Fitness");
	dc.TextOut(90,300, ch, strlen(ch));

	sprintf(ch,"%d Generations", generations);
	dc.TextOut(400,505, ch, strlen(ch));

	dc.MoveTo(150, 500);


	i = 0;
	for(g = 0; g < generations; g += PLOT_STEP)
	{
		i++; // += (600/generations);
		dc.LineTo(150 + i, 500 - ((int)fittest[g])/2);
	}

	while(!getch()){};

	
// Run the winning walker

		// Create phenotype - set weights
			ctrnn[0].set_weight(0, parenta[0]);
			ctrnn[0].set_weight(1, parenta[1]);
			ctrnn[0].set_weight(2, parenta[2]);
			ctrnn[0].set_weight(3, parenta[3]);
			ctrnn[0].set_weight(4, parenta[4]);
			ctrnn[1].set_weight(0, parenta[5]);
			ctrnn[1].set_weight(1, parenta[6]);
			ctrnn[1].set_weight(2, parenta[7]);
			ctrnn[1].set_weight(3, parenta[8]);
			ctrnn[1].set_weight(4, parenta[9]);
			ctrnn[2].set_weight(0, parenta[10]);
			ctrnn[2].set_weight(1, parenta[11]);
			ctrnn[2].set_weight(2, parenta[12]);
			ctrnn[2].set_weight(3, parenta[13]);
			ctrnn[2].set_weight(4, parenta[14]);
			ctrnn[3].set_weight(0, parenta[15]);
			ctrnn[3].set_weight(1, parenta[16]);
			ctrnn[3].set_weight(2, parenta[17]);
			ctrnn[3].set_weight(3, parenta[18]);
			ctrnn[3].set_weight(4, parenta[19]);

		// Set the start position for the walker

			for(i=0; i < 4; i++)
			{
				footy[i] = init_footy[i];
				footx[i] = init_footx[i];
			}

			// Find the centre of the walker
			sumx = 0;
			sumy = 0;

			for(i=0; i < 4; i++)
			{
				sumx += footx[i];
				sumy += footy[i];
			}

			centrex = sumx/4;	
			centrey = sumy/4;

			for(t=0; t < run_time; t++)
			{

				int xg = 20, yg = 200;

				// Set inputs
				ctrnn[0].set_input(0, 10 * cos(t/(4 * 3.1419)));
				ctrnn[0].set_input(1, output[1]);
				ctrnn[0].set_input(2, output[2]);
				ctrnn[0].set_input(3, output[3]);
				ctrnn[0].set_input(4, leg_disp[0]);
				ctrnn[1].set_input(0, 1);
				ctrnn[1].set_input(1, output[0]);
				ctrnn[1].set_input(2, output[2]);
				ctrnn[1].set_input(3, output[3]);
				ctrnn[1].set_input(4, leg_disp[1]);
				ctrnn[2].set_input(0, 1);
				ctrnn[2].set_input(1, output[0]);
				ctrnn[2].set_input(2, output[1]);
				ctrnn[2].set_input(3, output[3]);
				ctrnn[2].set_input(4, leg_disp[2]);
				ctrnn[3].set_input(0, 1);
				ctrnn[3].set_input(1, output[0]);
				ctrnn[3].set_input(2, output[1]);
				ctrnn[3].set_input(3, output[2]);
				ctrnn[3].set_input(4, leg_disp[3]);

	
				// Get Outputs
				output[0] = ctrnn[0].get_output() * 10;
				output[1] = ctrnn[1].get_output() * 10;
				output[2] = ctrnn[2].get_output() * 10;
				output[3] = ctrnn[3].get_output() * 10;

	
				/*

				for(i = 0; i < 4; i++)
				{ 	
					dc.SetPixel(xg + t +(run_time * c), yg - (int)output[i] + (100 * i), RGB(255, 0, 0));
					sprintf(ch,"output = %f", float(output[i]));
					dc.TextOut(10,10 + (25 * i), ch, strlen(ch));
				}*/

				

				// New positions for feet
				for(i=0; i < 4; i++)
				{
					footy[i] += (int)output[i];
				}


				// Find the centre of the walker
				sumx = 0;
				sumy = 0;

				for(i=0; i < 4; i++)
				{
					sumx += footx[i];
					sumy += footy[i];
				}

				centrex = sumx/4;
				centrey = sumy/4;

				// Draw walker

				myPen = (CPen*) dc.SelectStockObject(BLACK_PEN);

				for(i = 0; i < 4; i++)
				{
					dc.MoveTo(centrex, centrey);
					dc.LineTo(footx[i], footy[i]);
				}

		
				// Display drawing for one second
				mdelay(1);

				// Erase drawing
				myPen = (CPen*) dc.SelectStockObject(WHITE_PEN);

				for(i = 0; i < 4; i++)
				{
					dc.MoveTo(centrex, centrey);
					dc.LineTo(footx[i], footy[i]);
				}
			} //End of runtime
	
}

class CApp: public CWinApp
{
public:
	BOOL InitInstance()
	{
		m_pMainWnd = new CMainWindow();
		m_pMainWnd -> ShowWindow(m_nCmdShow);
		m_pMainWnd -> UpdateWindow();
		return TRUE;
	}
};

CApp App;