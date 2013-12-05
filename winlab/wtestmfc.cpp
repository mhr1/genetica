// Wtestmfc.cpp : test windows programming using C++

#include <afxwin.h>

class CMyWindow: public CFrameWnd
{
	public:
		CMyWindow()
		{
			int xScreen = GetSystemMetrics(SM_CXSCREEN),
				yScreen = GetSystemMetrics(SM_CYSCREEN);

			RECT rect = {0, 0, xScreen, yScreen};

			Create(NULL,			//Use default window-class name
				"Windows test 1",	// Text for titile bar
				WS_OVERLAPPEDWINDOW,// WIndow Style
				rect,				// Size & position of window
				NULL,				// no parent window
				NULL);				// no menu
		}
};

class CApp: public CWinApp
{
public:
	BOOL InitInstance()
	{
		m_pMainWnd = new CMyWindow();
		m_pMainWnd -> ShowWindow(m_nCmdShow);
		m_pMainWnd -> UpdateWindow();
		return TRUE;
	}
};

CApp App;