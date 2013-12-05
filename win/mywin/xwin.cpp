#include <afx.h>
#include <afxwin.h>

class Fwin : public CFrameWnd
{
public:
	Fwin();
	~Fwin();

	afx_msg void mybutton(UINT nFlags, CPoint point);

private:
	int mx, my;
	CStatic myWindow;
	CStatic clickPos;
	char mousePos[16];

	DECLARE_MESSAGE_MAP()
};

// Define message map
BEGIN_MESSAGE_MAP(Fwin, CFrameWnd)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

Fwin::Fwin() : mx(0), my(0)
{
	Create(NULL, "Fwin");

	myWindow.Create("Mouse button down at: ",
					WS_CHILD | WS_VISIBLE | SS_LEFT,
					CRect(20, 20, 270, 44), this);

	wsprintf(mousePos, "(%d %d)", mx, my);

	clickPos.Create(mousePos,
		WS_CHILD | WS_VISIBLE | SS_CENTER,
		CRect(260, 20, 360, 44), this);
}

Fwin::~Fwin()
{
	myWindow.DestroyWindow();
	clickPos.DestroyWindow();
}

void Fwin::mybutton(UINT, CPoint point)
{
	mx = point.x;
	my = point.y;
	wsprintf(mousePos, "(%d, %d)", mx, my);
	clickPos.SetWindowText(mousePos);
}

class FwinApp : public CWinApp
{
public:
    BOOL  InitInstance();
};
//---------------------------------------------------------------
BOOL FwinApp::InitInstance()
{
    //Enable3dControls();

    m_pMainWnd = new Fwin();

    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();

    return TRUE;
}
//---------------------------------------------------------------

    Fwin app;


