#include <afx.h>
#include <afxwin.h>
#include <iostream>
#include <fstream>

using namespace std;

class CWindow : public CFrameWnd
{
	public:
		CWindow(const char *title);

	private:
		CEdit	myEdit;
		char buff[128];
		char c;
};

CWindow::CWindow(const char *title)
{
	Create(NULL, title);

	//Now create a CEdit box

	myEdit.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP |
					WS_VSCROLL | WS_BORDER, 
					CRect(CPoint(10,10), CSize(500, 200)),
					this,
					0xFFFF);

	// Send stuff to the CEdit box

	myEdit.SetWindowText("Starting...");

	ifstream fin;
	fin.open("test1.txt");

	if(!fin)
	{
		myEdit.SetWindowText("Cannot open test1.txt");
	}

	while(fin.get(buff, 128))
	{			
		//fin.get(c);
		myEdit.SetWindowText(buff); 
		// Now the previous "Starting..." gets overwritten
		// ListBox didn't do 
	}

	//myEdit.SetWindowText("End of file ");

	fin.close();
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