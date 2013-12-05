#include <afxwin.h>
//#include <math.h>
#include "fft.h"

//-------------------------------------------------------------
// DEFINES

#define NI 128
#define PI 3.1415926
#define FREQ 1

//-------------------------------------------------------------



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
	float signal[NI];


	CPaintDC dc(this);
	CPen *myPen = (CPen*) dc.SelectStockObject(BLACK_PEN);


	// Make a signal
	for(int n = 0; n < NI; n++)
	{
		signal[n] = 0 + 60 * sin(2 * PI * FREQ * n/NI);
	}


	// Graph of signal
	dc.MoveTo(20, 30);
	dc.LineTo(20, 200);
	dc.LineTo(532, 200);

	dc.MoveTo(20, 200);

	for(n = 0; n < NI; n++)
	{
		dc.LineTo(20 + (n * 2), 200 - signal[n]);
	}

	fft(signal, NI);

	// Graph of FFT
	dc.MoveTo(20, 30);
	dc.LineTo(20, 400);
	dc.LineTo(532, 400);

	dc.MoveTo(20, 400);

	for(n = 0; n < NI; n++)
	{
		dc.LineTo(20 + (n * 2), 400 - (signal[n]/ 10000));
	}

	
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