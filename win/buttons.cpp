//---------------------------------------------------------------
// File: buttons.cpp
//
// Sample program to illustrate the use of button, check box,
// radio buttons, and group box.
//---------------------------------------------------------------

#include <afx.h>
#include <afxwin.h>

const int ID_ORDER    = 1;
const int ID_BYE      = 2;

const int FWIDTH      = 150;
const int FHEIGHT     = 150;
const int TWIDTH      = 300;
const int THEIGHT     = 150;

static char* pressure_array[3] =
{
    "Low", "High", "Mean"
};

static char* aszToppingNames[3] =
{
    "Mute", "Reset", "Chocolate Chips"
};

class CButtonTestWindow : public CFrameWnd 
{
public:
    CButton m_aFlavors[3];
    CButton m_aToppings[3];
    CButton m_FlvrGrp;
    CButton m_TpngGrp;
    CButton m_Order;
    CButton m_Bye;

    CButtonTestWindow();
    ~CButtonTestWindow();

// Message handlers for the buttons

    afx_msg void  TakeOrder();
    afx_msg void  Quit()
    {
        DestroyWindow();
    }

    DECLARE_MESSAGE_MAP()
};

// Define the message map

BEGIN_MESSAGE_MAP(CButtonTestWindow, CFrameWnd)
      ON_COMMAND(ID_ORDER, TakeOrder)
      ON_COMMAND(ID_BYE, Quit)
END_MESSAGE_MAP()
//---------------------------------------------------------------
CButtonTestWindow::CButtonTestWindow() : CFrameWnd()
{
// Create the main frame window
    Create(NULL, "Michael's Simulator");

// Create the group boxes to display flavor and topping
// selections.
    m_FlvrGrp.Create("Pressure Display", WS_CHILD | WS_VISIBLE |
                      BS_GROUPBOX,
                      CRect(CPoint(30, 30), 
                            CSize(FWIDTH, FHEIGHT)),
                      this, 0xffff);

    m_TpngGrp.Create("Alarms", WS_CHILD | WS_VISIBLE |
                      BS_GROUPBOX,
                      CRect(CPoint(FWIDTH+60, 30), 
                            CSize(TWIDTH, THEIGHT)),
                      this, 0xffff);

// Set up the other buttons
    int i;
    DWORD style = WS_CHILD | WS_VISIBLE | WS_TABSTOP |
                  BS_AUTORADIOBUTTON;
    for(i = 0; i < 3; i++)
    {
        if(0 == i) style |= WS_GROUP;
        m_aFlavors[i].Create(pressure_array[i],
                             style,
                             CRect(CPoint(46, 30+34*(i+1)), 
                                   CSize(FWIDTH-30, 24)),
                             this, 0xffff);
        if(0 == i) style &= ~WS_GROUP;
    }
    style = WS_CHILD | WS_VISIBLE | WS_TABSTOP |
                  BS_AUTOCHECKBOX;
    for(i = 0; i < 3; i++)
    {
        if(0 == i) style |= WS_GROUP;
        m_aToppings[i].Create(aszToppingNames[i],
                              style,
                              CRect(CPoint(FWIDTH+76, 
                                          30+34*(i+1)), 
                                    CSize(TWIDTH-30, 24)),
                              this, 0xffff);
        if(0 == i) style &= ~WS_GROUP;
    }

    m_Order.Create("Test Cycle", WS_CHILD | WS_VISIBLE |
                     WS_TABSTOP | BS_DEFPUSHBUTTON,
                     CRect(CPoint(50, 200), CSize(80, 24)),
                     this, ID_ORDER);

    m_Bye.Create("Exit", WS_CHILD | WS_VISIBLE |
                     WS_TABSTOP,
                     CRect(CPoint(FWIDTH+90, 200), 
                           CSize(80, 24)),
                     this, ID_BYE);
}
//---------------------------------------------------------------
CButtonTestWindow::~CButtonTestWindow()
{
// Destroy all button windows
    m_FlvrGrp.DestroyWindow();
    m_TpngGrp.DestroyWindow();
        
    int i;
    for(i = 0; i < 3; i++)
    {
        m_aFlavors[i].DestroyWindow();
        m_aToppings[i].DestroyWindow();
    }
    m_Order.DestroyWindow();
    m_Bye.DestroyWindow();
}
//---------------------------------------------------------------
void CButtonTestWindow::TakeOrder()
{
    char buf[256];
// Check which flavor was ordered
    int i, n = 0;
    for(i = 0; i < 3; i++)
    {
        if(m_aFlavors[i].GetCheck() == 1)
        {
            n = wsprintf(buf, "%s  ",
                         pressure_array[i]);
            break;
        }
    }
    if(i >= 3)
    {
        MessageBeep(MB_ICONEXCLAMATION);
        return;
    }

// Now pick the selected toppings
    int with = 0;
    for(i = 0; i < 3; i++)
    {
        if(m_aToppings[i].GetCheck() == 1)
        {
            if(with == 0)
            {
                n += wsprintf(&buf[n], "with ");
                with = 1;
            }
            n += wsprintf(&buf[n], "%s, ",
                                   aszToppingNames[i]);
        }
    }
    wsprintf(&buf[n-2], ".");

// Display the order in a message box...
    MessageBox(buf, "Selected tests", MB_OK);
}
//---------------------------------------------------------------
class CButtonTestApp : public CWinApp 
{
public:
    CButtonTestApp() : CWinApp() {}
    BOOL  InitInstance();
};
//---------------------------------------------------------------
BOOL CButtonTestApp::InitInstance()
{
// Enable Microsoft's 3-D Controls
    Enable3dControls();
    m_pMainWnd = new CButtonTestWindow;
    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();
    return TRUE;
}
//---------------------------------------------------------------
// Create an instance of the application

    CButtonTestApp app;
