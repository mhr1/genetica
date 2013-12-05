//---------------------------------------------------------------
// mod_net.cpp
//
// Modular Neural network with graphic output
//---------------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <afx.h>
#include <afxwin.h>
#include <time.h>
#include "nnet.h"

#define child_num 50

void delay(int seconds)
{
	long timenow;
	timenow = (long)time(NULL);
	timenow += seconds;

	while(time(NULL) < timenow){}
}


class CTestWnd : public CFrameWnd
{
public:
    /*CTestWnd() : CFrameWnd()
    {
        VERIFY(Create(NULL, "TestGen Graphics I/F", WS_OVERLAPPEDWINDOW, 
           rectDefault, NULL, NULL));

		// This also works without VERIFY	
    }*/

	// New window from windows wisdom book

	CTestWnd(): CFrameWnd()
	{	int xScreen = GetSystemMetrics(SM_CXSCREEN);
		int yScreen = GetSystemMetrics(SM_CYSCREEN);
		RECT rect = { 0, 0, xScreen, yScreen};
		Create(NULL,			//Use default window class name
			"Windows test 1",	//Text for title bar
			WS_OVERLAPPEDWINDOW,	// Window Style
			rect,				// Size and position oif window
			NULL,				// No parent window
			NULL);				// No menu
	}

// Declare functions for handling messages from Windows
    afx_msg void OnPaint();

    DECLARE_MESSAGE_MAP()

private:
	
	
};
//---------------------------------------------------------------
// Define the "message map"

    BEGIN_MESSAGE_MAP(CTestWnd, CFrameWnd)
        ON_WM_PAINT()
    END_MESSAGE_MAP()

//---------------------------------------------------------------

void CTestWnd::OnPaint()
{
	//double wi[2][2] = {{ 0.4, 0.9},{ 0.9, 0.4}};
	//double wj[2] = { 0.9, 0.4};

	double parent[6];
	double child[child_num][6];
	double delta_error[2];
	double yi[2];
	double yj[20];
	double yj_old[20];
	double xi[2];
	double fittest;
	double new_error, old_error;
	double temp;

	int i, c, p, n;
	int error_timeout = 0;

	network ga_net;

	ga_net.learning_rate = 0.1;

	neuron net[3]; // = new neuron();
	net[0].set_connections(2);
	//neuron net2; // = new neuron(2);
	net[1].set_connections(2);
	//neuron net3; // = new neuron(2);
	net[2].set_connections(2);

	double training_set[20][3] = {
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 1.0 },
		{ 1.0, 0.0, 1.0 },
		{ 1.0, 0.0, 1.0 },
		{ 1.0, 0.0, 1.0 },
		{ 0.0, 1.0, 1.0 },
		{ 0.0, 0.0, 0.0 },
		{ 1.0, 0.0, 1.0 },
		{ 0.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 1.0 },
		{ 0.0, 0.0, 0.0 },
		{ 1.0, 0.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 1.0 },
		{ 0.0, 0.0, 0.0 }};
	
// Set up device context (DC) for drawing
    CPaintDC dc(this);
	CPen *myPen = (CPen*) dc.SelectStockObject(BLACK_PEN);
		
	//int old_mapmode = dc.SetMapMode(MM_TWIPS);
    
    //CPoint points[3] = {CPoint(200,10), CPoint(300,200), CPoint(300,10)};
    //dc.Polygon(points, 3);
	//dc.SelectObject(myPen);
	//dc.TextOut(140,90, "Theta",5);
	dc.TextOut(15,70, "y(t)",4);
	dc.TextOut(10,100, "1",1);
	
	dc.TextOut(10,295, "0",1);
	//dc.TextOut(360,310, "large +ve values ->",19);

	dc.MoveTo(20,90);
	dc.LineTo(20,300);

	// tau axis
	//dc.MoveTo(20,300);
	//dc.LineTo(148,108);

	dc.MoveTo(20,300);
	dc.LineTo(20 + 15 +(20 * 15),300);

	int x = 20, y= 300; 
	double  neta = 0.5;

	// Scales the data to the graph
	int amplifier = 200;

	srand((unsigned int)time(NULL));

	// init parent values

	// This set has a solution - can the algorithm find it?
	//double wi[2][2] = {{ 0.4, 0.9},{ 0.9, 0.4}};
	//double wj[2] = { 0.9, 0.4};


	

	for(p = 0; p < 6; p++)
	{	
		temp = rand();
		parent[p] = (fmod(temp,40) - 19)/100; //values -19 to 20
	}

	fittest = 1000000;

	//set to initial values

	net[0].set_weight(0, parent[0]);
	net[0].set_weight(1, parent[1]);
	net[1].set_weight(0, parent[2]);
	net[1].set_weight(1, parent[3]);
	net[2].set_weight(0, parent[4]);
	net[2].set_weight(1, parent[5]);
	//p = 0;

	// For the number of iterations

	for(n = 0; n < 5000; n++)
	{
			// For all data in the training set
			for(i = 0; i < 20; i++)
			{
			// input layer
				net[0].set_input(0, training_set[i][0]); 
				net[0].set_input(1, training_set[i][1]);
				net[1].set_input(0, training_set[i][0]);
				net[1].set_input(1, training_set[i][1]);

			// Hidden layer
				net[2].set_input(0, net[0].get_output());
				net[2].set_input(1, net[1].get_output());

			// Output layer
				yj[i] = net[2].get_output();

			//New delta rule
				temp = training_set[i][2] - yj[i];

				//if(temp < 0)
				//	temp *= (-1);

				net[2].update_weights(temp);

				delta_error[0] = net[2].get_back_prop_error(0, temp);
				delta_error[1] = net[2].get_back_prop_error(1, temp);

			// Update weights

				net[0].update_weights(delta_error[0]);
				net[1].update_weights(delta_error[1]);
				



			/* Sum the error for the training set
				temp = yj[i] - training_set[i][2];

				if(temp < 0)
					temp *= (-1);

				new_error += temp;*/

			}	// end for training data

			
			parent[0] = net[0].get_weight(0);
			parent[1] = net[0].get_weight(1);
			parent[2] = net[1].get_weight(0);
			parent[3] = net[1].get_weight(1);
			parent[4] = net[2].get_weight(0);
			parent[5] = net[2].get_weight(1);

		
		//Draw graph

		int xg = x + 1;// + (n * 2);
		int yg = y + 1;// - (n * 2);

		dc.MoveTo(xg, yg );

		for(i = 0; i < 20; i++)
		{
			myPen = (CPen*) dc.SelectStockObject(WHITE_PEN);
			dc.LineTo(xg + (i * 15),yg - int(yj_old[i] * amplifier));
		}

		dc.MoveTo(xg, yg );
		//error = 0;

		for(i = 0; i < 20; i++)
		{
			myPen = (CPen*) dc.SelectStockObject(BLACK_PEN);
			dc.LineTo(xg + (i * 15),yg - int(yj[i] * amplifier));
			yj_old[i] = yj[i];

			dc.SetPixel(xg + (i * 15),yg+2 - int(training_set[i][2] * amplifier), RGB(255,0,0));
			dc.SetPixel(xg+1 + (i * 15),yg+2 - int(training_set[i][2] * amplifier), RGB(255,0,0));
			dc.SetPixel(xg + (i * 15),yg+1 - int(training_set[i][2] * amplifier), RGB(255,0,0));
			dc.SetPixel(xg+1 + (i * 15),yg+1 - int(training_set[i][2] * amplifier), RGB(255,0,0));

			
		}

	char ch[40];

	sprintf(ch,"Training iteration %d", n + 1);
	dc.TextOut(150,60, ch, strlen(ch));

	/*new_error = 100 * new_error/20;

	if(new_error < 0)
		new_error *= -1;*/

	sprintf(ch,"Fitness = %f", float(fittest) );
	dc.TextOut(340,80, ch, strlen(ch));


	sprintf(ch,"Error (%%) = %f", float(new_error) );
	dc.TextOut(340,100, ch, strlen(ch));

	sprintf(ch,"wi[0][0] = %f", float(parent[0]));
	dc.TextOut(340,140, ch, strlen(ch));

	sprintf(ch,"wi[1][0] = %f", float(parent[1]));
	dc.TextOut(340,160, ch, strlen(ch));

	sprintf(ch,"wi[0][1] = %f", float(parent[2]));
	dc.TextOut(340,180, ch, strlen(ch));

	sprintf(ch,"wi[1][1] = %f", float(parent[3]));
	dc.TextOut(340,200, ch, strlen(ch));

	sprintf(ch,"wj[0] = %f", float(parent[4]));
	dc.TextOut(340,220, ch, strlen(ch));

	sprintf(ch,"wj[1] = %f", float(parent[5]));
	dc.TextOut(340,240, ch, strlen(ch));

	sprintf(ch,"p = %f", float(p));
	dc.TextOut(340,260, ch, strlen(ch));

	dc.TextOut(x -18 + (5*15),305, "5", 1);
	dc.TextOut(x -20 + (10*15),305, "10", 2);
	dc.TextOut(x -20 + (15*15),305, "15", 2);
	dc.TextOut(x -20 + (20*15),305, "20", 2);

	dc.TextOut(150,325, "Training data", 13);
	}

}
//---------------------------------------------------------------
class CTestApp : public CWinApp
{
public:
    BOOL  InitInstance();
};
//---------------------------------------------------------------
BOOL CTestApp::InitInstance()
{
    Enable3dControls();

    m_pMainWnd = new CTestWnd();

    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();

    return TRUE;
}
//---------------------------------------------------------------

    CTestApp app;
