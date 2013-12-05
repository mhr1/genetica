//---------------------------------------------------------------
// File: gamelife.cpp
// win32 application - using MFC 
// John Conway's Game of Life
//---------------------------------------------------------------
#include <math.h>
#include <afx.h>
#include <afxwin.h>
//#include <dos.h>
#include <stdio.h>

#define XGRIDSIZE 120
#define YGRIDSIZE 100

class CTestWnd : public CFrameWnd
{
public:
    CTestWnd() : CFrameWnd()
    {
        VERIFY(Create(NULL, "TestGen Graphics I/F", WS_OVERLAPPEDWINDOW, 
           rectDefault, NULL, NULL));

		// This also works without VERIFY	
    }

	CButton m_stop;

// Declare functions for handling messages from Windows
    afx_msg void OnPaint();

    DECLARE_MESSAGE_MAP()

private:
	
	
};
//---------------------------------------------------------------
// Define the "message map"

    BEGIN_MESSAGE_MAP(CTestWnd, CFrameWnd)
        ON_WM_PAINT()
		//ON_COMMAND(ID_STOP)
    END_MESSAGE_MAP()

//---------------------------------------------------------------
//const double pi = 3.142;
//double frequency = 2;
//unsigned char rt_output[600];
int i, j, iter = 0;
	int xgridsize = XGRIDSIZE;
	int ygridsize = YGRIDSIZE;
	int cellsize = 4;
	int xoffset = 2;
	int yoffset = 20;

unsigned char oldGrid[XGRIDSIZE][YGRIDSIZE];
unsigned char newGrid[XGRIDSIZE][YGRIDSIZE];
int neighbours = 0;
int ID_STOP = 1;

void CTestWnd::OnPaint()
{
// Set up device context (DC) for drawing
    CPaintDC dc(this);
	CPen *myPen = (CPen*) dc.SelectStockObject(BLACK_PEN);

	/*m_stop.Create("Stop",WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		CRect(2, 205, 82, 225),
		this, ID_STOP);*/

	// Draw grid 

	for(i = 0; i <= xgridsize; i++)
	{
		dc.MoveTo(xoffset + (i * cellsize), yoffset);
		dc.LineTo(xoffset + (i * cellsize), yoffset + (ygridsize) * cellsize);
	}

	for(i = 0; i <= ygridsize; i++)
	{
		dc.MoveTo(xoffset, yoffset + (i * cellsize));
		dc.LineTo(xoffset + (xgridsize) * cellsize, yoffset + (i * cellsize));
	}

	// Pick a square
	int x, xs;
	int y, ys;

	// Init grid

	for (x=0; x < xgridsize; x++)
	{
		for(y=0; y < ygridsize; y++)
		{
			oldGrid[x][y] = 0;
			newGrid[x][y] = 0;
		}
	}

	// A line @

	x = 70;
	y = 20;

	//newGrid[x][y + 1] = 1;
	//newGrid[x][y + 2] = 1;
	newGrid[x][y + 3] = 1;
	newGrid[x][y + 4] = 1;
	newGrid[x][y + 5] = 1;
	newGrid[x][y + 6] = 1;
	newGrid[x][y + 7] = 1;
	newGrid[x][y + 8] = 1;
	newGrid[x][y + 9] = 1;
	newGrid[x][y + 10] = 1;
	newGrid[x + 1][y + 10] = 1;
	newGrid[x + 2][y + 10] = 1;
	newGrid[x + 3][y + 10] = 1;
	newGrid[x + 4][y + 10] = 1;
	newGrid[x + 5][y + 10] = 1;
	//newGrid[x + 6][y + 10] = 1;
	//newGrid[x + 7][y + 10] = 1;

	// Zig Zag @
	x = 30;
	y = 30;

	newGrid[x + 1][y] = 1;
	newGrid[x][y + 1] = 1;
	newGrid[x + 2][y + 1] = 1;
	newGrid[x + 1][y + 2] = 1;
	newGrid[x + 3][y + 2] = 1;
	newGrid[x + 2][y + 3] = 1;
	newGrid[x + 4][y + 3] = 1;
	newGrid[x + 3][y + 4] = 1;
	newGrid[x + 5][y + 4] = 1;
	newGrid[x + 4][y + 5] = 1;
	



	/*newGrid[31][31] = 1;
	newGrid[31][32] = 1;
	newGrid[31][33] = 1;
	newGrid[31][34] = 1;
	newGrid[29][32] = 1;
	newGrid[30][32] = 1;
	newGrid[32][32] = 1;
	newGrid[33][32] = 1;
	newGrid[31][35] = 1;
	newGrid[34][32] = 1;*/

	//spaceship
	newGrid[2][10] = 1;
	newGrid[5][10] = 1;
	newGrid[6][11] = 1;
	newGrid[6][12] = 1;
	newGrid[6][13] = 1;
	newGrid[5][13] = 1;
	newGrid[4][13] = 1;
	newGrid[3][13] = 1;
	newGrid[2][12] = 1;


	// A glider @
	x = 35;
	y = 40;

	newGrid[x][y] = 1;
	newGrid[x+1][y] = 1;
	newGrid[x+2][y] = 1;
	newGrid[x+2][y+1] = 1;
	newGrid[x+1][y+2] = 1;
	//newGrid[20][6] = 1;



	while(iter < 500 )
	{
		// Print grid squares
		for (x=0; x < xgridsize; x++)
		{
			for(y=0; y < ygridsize; y++)
			{
				if(newGrid[x][y] != oldGrid[x][y])
				{
				
				if(newGrid[x][y] == 1)
				{
					CPen *myPen = (CPen*) dc.SelectStockObject(BLACK_PEN);
	
	// fill in square
					for(i=0;i < cellsize - 1;i++)
					{
						dc.MoveTo((cellsize * x) + xoffset +1, (cellsize * y) + yoffset +1 + i);
						dc.LineTo((cellsize * x) + (xoffset + cellsize), (cellsize * y) + yoffset +1 + i);
					}

				}
				else
				{
					CPen *myPen = (CPen*) dc.SelectStockObject(WHITE_PEN);
	
	// fill in square
					for(i=0;i < cellsize - 1;i++)
					{
						dc.MoveTo((cellsize * x) + xoffset +1, (cellsize * y) + yoffset +1 + i);
						dc.LineTo((cellsize * x) + (xoffset + cellsize), (cellsize * y) + yoffset +1 + i);
					}
				}
				}
			}
		}
		// end print

		//update grid

		for (x=0; x < xgridsize; x++)
		{
			for(y=0; y < ygridsize; y++)
			{
				oldGrid[x][y] = newGrid[x][y];

			}

		}


		for (x=1; x < xgridsize - 1; x++)
		{
			for(y=1; y < ygridsize - 1; y++)
			{
				neighbours = 0;

				for(xs = 0; xs < 3; xs ++)
				{
					for(ys = 0; ys < 3; ys ++)
					{
						if(oldGrid[x + (xs - 1)][y + (ys - 1)] == 1)
							neighbours++;
					}					
				}

				if(oldGrid[x][y] == 0)
				{
					if(neighbours == 3)
						newGrid[x][y] = 1;
					else
						newGrid[x][y] = 0;
				}
				else 
				{
					if(neighbours < 3 || neighbours > 4)
						newGrid[x][y] = 0;
					else
						newGrid[x][y] = 1;

				}

				

			}

		}

		//delay(500);
		//getchar();
		iter++;
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
    //Enable3dControls();

    m_pMainWnd = new CTestWnd();

    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();

    return TRUE;
}
//---------------------------------------------------------------

    CTestApp app;


/*	for (x=0; x < 30; x++)
	{
		for(y=0; y < 30; y++)
		{


		}

	}*/