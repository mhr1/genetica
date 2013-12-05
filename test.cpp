//---------------------------------------------------------------
// File: test.cpp
//
// Sample program to test code fragments in Chapter 19
//---------------------------------------------------------------
#include <math.h>
#include <afx.h>
#include <afxwin.h>

class CTestWnd : public CFrameWnd
{
public:
    CTestWnd() : CFrameWnd()
    {
        VERIFY(Create(NULL, "TestGen Graphics I/F", WS_OVERLAPPEDWINDOW, 
           rectDefault, NULL, NULL));

		// This also works without VERIFY	
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
const double pi = 3.142;
double frequency = 2;
unsigned char rt_output[600];
unsigned char rt_input[600];
int delay = 35;

void CTestWnd::OnPaint()
{
// Set up device context (DC) for drawing
    CPaintDC dc(this);
	//CPen *myPen = (CPen*) dc.SelectStockObject(BLACK_PEN);
	
	//int old_mapmode = dc.SetMapMode(MM_TWIPS);
    
    CPoint points[3] = {CPoint(200,10), CPoint(300,200), CPoint(300,10)};
    //dc.Polygon(points, 3);
	//dc.SelectObject(myPen);
	//dc.TextOut(20,30, "Waves",5);
	//dc.TextOut(20,50, frequency);

	dc.MoveTo(20,50);
	dc.LineTo(20,300);

	dc.MoveTo(20,150);
	dc.LineTo(620,150);

	dc.MoveTo(20,300);
	dc.LineTo(620,300);

	// X axis event marker @ 300
	
	dc.MoveTo(20 + 305, 305);
	dc.LineTo(20 + 300, 300);
	dc.LineTo(20 + 294, 306);

	
	for(int i = 0; i < 600; i++)
	{
		rt_output[i] = 0;
		rt_input[i] = 0;
	}

	// Y axis

	for(i = 0; i < 26; i++)
	{
		dc.MoveTo(15, 50 + (i * 10));
		dc.LineTo(20, 50 + (i * 10));
	}

	rt_output[300] = 100;

	for(int j =0; j < 100; j++)
	{
		for(i = 50; i < 550; i++)
		{
			if(rt_input[i] > 0)
			{
				rt_output[i + 1] = 100;
			}		
		}

		for(i = 50; i < 550; i++)
		{
			if(rt_output[i] > 0)
			{
				rt_input[i - delay] = 2;
				rt_input[i + delay] = 10;
				rt_output[i] = 0;
			}			
		}
	}

	for(i = 0; i < 600; i++)
	{
		dc.MoveTo(20 + i, 150);
		dc.LineTo(20 + i, 150 - rt_output[i]);
		
		dc.MoveTo(20 + i, 300);
		dc.LineTo(20 + i, 300 - rt_input[i]);
	}



/*	for( i = 0; i < 360; i++)
	{
		double func = i * (2 * frequency * pi) / 360;
		dc.SetPixel(i + 20,200 + (int)(-cos(func) * 100), RGB(0,255,0));
	}

	for( i = 0; i < 360; i++)
	{
		double func = i * (2 * frequency * pi) / 360;
		dc.SetPixel(i + 20,200 + (int)(-sin(func) * 100), RGB(0,0,255));
	}

	for( i = 0; i < 360; i++)
	{
		double func = i * (2 * frequency * pi) / 360;
		dc.SetPixel(i + 20,200 + (int)(cos(func) * 100), RGB(255,0,0));
	}

	for( i = 0; i < 360; i++)
	{
		double func = i * (2 * frequency * pi) / 360;
		dc.SetPixel(i + 20,200 + (int)(sin(func) * 100), RGB(255,0,255));
	}*/
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
