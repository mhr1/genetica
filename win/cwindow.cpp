// This makes a plain window 1/5/02
// The only problem is that it won't compile 19/9/03 - why?
// Actually, it compiles,but it wont link

// Worked OK when I compiled it first and then run 19/9/03

#include <afx.h>
#include <afxwin.h>
#include <iostream>
#include <fstream>

class CWindow : public CFrameWnd
{
	public:
		CWindow(const char *title);
};

CWindow::CWindow(const char *title)
{
	Create(NULL, title);
}

class CWindowApp : public CWinApp
{
public:
	BOOL InitInstance();
};

BOOL CWindowApp::InitInstance()
{
	m_pMainWnd = new CWindow("This is a window");
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

CWindowApp app;