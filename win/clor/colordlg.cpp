//---------------------------------------------------------------
// File: colordlg.cpp
//
// Sample program that demonstrates how to use the 
// CColorDialog class.
//---------------------------------------------------------------
#include <afx.h>
#include <afxwin.h>
#include <afxdlgs.h>

#define CM_COLOR 101

class CColorDlgApp : public CWinApp
{
public:
    BOOL   InitInstance();
    virtual int ExitInstance();
    void   CmColor();

private:
    CButton   m_PickColor;
    DWORD     m_aCustomColors[16];

    DECLARE_MESSAGE_MAP()
};

// Define the message map
BEGIN_MESSAGE_MAP(CColorDlgApp, CWinApp)
  ON_COMMAND(CM_COLOR, CmColor)
END_MESSAGE_MAP()
//---------------------------------------------------------------
BOOL CColorDlgApp::InitInstance()
{
    Enable3dControls();

    CFrameWnd *Frame = new CFrameWnd;
    Frame->Create(NULL, "Pick a Color");
    m_pMainWnd = Frame;

// Create the button that the user can press to bring up the
// color selection dialog
    m_PickColor.Create("Pick Color...", WS_CHILD | WS_VISIBLE |
                       WS_TABSTOP,
                       CRect(CPoint(10, 20), CSize(100, 24)),
                       m_pMainWnd, CM_COLOR);
    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();

// Define the array of custom colors
    int i;
    for(i = 0; i < 16; i++)
        m_aCustomColors[i] = RGB(15*i, 15*i, 15*i);

    return TRUE;
}
//---------------------------------------------------------------
// CColorDlgApp:: E x i t I n s t a n c e
// Clean up before exiting application

int CColorDlgApp::ExitInstance()
{
    m_PickColor.DestroyWindow();
    return 0;
}
//---------------------------------------------------------------
// CColorDlgApp:: C m C o l o r
// Called when user presses the "Pick Color..." button

void CColorDlgApp::CmColor()
{
    CColorDialog ColorDlg(RGB(0,0,0), CC_FULLOPEN, m_pMainWnd);
    ColorDlg.m_cc.lpCustColors = m_aCustomColors;

    if(ColorDlg.DoModal() == IDOK)
    {
// Display information about selected color
        COLORREF ColorSel = ColorDlg.GetColor();
        char   msg[128];
        wsprintf(msg, "RGB intensities:\r\n\r\n Red: %d\r\n "
                      "Green: %d\r\n Blue: %d",
                       GetRValue(ColorSel), GetGValue(ColorSel),
                       GetBValue(ColorSel));
        m_pMainWnd->MessageBox(msg, m_pszAppName, MB_OK);
    }
}
//---------------------------------------------------------------
// Create an instance of this application

    CColorDlgApp app;

