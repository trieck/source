// DIALOGTEST.CPP

#include "DialogTest.h"

BOOL CDlgApp::InitInstance()
{
    CDlgWin* pDlg = new CDlgWin();

    m_pMainWnd = pDlg;

    pDlg->Create(0, _T("Dialog Test"),
                 WS_OVERLAPPED | WS_MINIMIZEBOX
                 | WS_SYSMENU | WS_DLGFRAME | WS_CLIPCHILDREN,
                 CRect(0,0,530,290));

    // Create controls
    pDlg->CreateControls();

    // Set child fonts
    pDlg->SetChildFonts(ID_EXEBTN, ID_LISTBOX,
                        "MS Sans Serif", 8);

    pDlg->CenterWindow();
    pDlg->ShowWindow(m_nCmdShow);
    pDlg->UpdateWindow();

    return (TRUE);
}

CDlgWin::CDlgWin()
{
    // Initialize member variables
    m_pFont = NULL;
    m_pExeBtn = NULL;
    m_pExitBtn = NULL;
    m_pRedSlider = NULL;
    m_pGreenSlider = NULL;
    m_pBlueSlider = NULL;

}

CDlgWin::~CDlgWin()
{
    // Delete allocated memory
    if (m_pFont) delete m_pFont;
    if (m_pExeBtn) delete m_pExeBtn;
    if (m_pExitBtn) delete m_pExitBtn;
    if (m_pRedSlider) delete m_pRedSlider;
    if (m_pGreenSlider) delete m_pGreenSlider;
    if (m_pBlueSlider) delete m_pBlueSlider;
    if (m_pListBox) delete m_pListBox;
}

void CDlgWin::CreateControls()
{
    // Allocate memory for controls
    m_pExeBtn = new CButton;
    ASSERT_VALID(m_pExeBtn);
    m_pExitBtn = new CButton;
    ASSERT_VALID(m_pExitBtn);
    m_pRedSlider = new CSliderCtrl;
    ASSERT_VALID(m_pRedSlider);
    m_pGreenSlider = new CSliderCtrl;
    ASSERT_VALID(m_pGreenSlider);
    m_pBlueSlider = new CSliderCtrl;
    ASSERT_VALID(m_pBlueSlider);
    m_pListBox = new CListBox;
    ASSERT_VALID(m_pListBox);

    // Create them
    m_pExeBtn->Create("Execute Program", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
                      CRect(350, 8, 513, 33), this, ID_EXEBTN);
    m_pExitBtn->Create("&Exit", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
                       CRect(350, 40, 513, 65), this, ID_EXITBTN);
    m_pRedSlider->Create(WS_VISIBLE | WS_CHILD, CRect(0, 0, 250, 20), this, ID_REDSLIDER);
    m_pGreenSlider->Create(WS_VISIBLE | WS_CHILD, CRect(0, 20, 250, 40), this, ID_GREENSLIDER);
    m_pBlueSlider->Create(WS_VISIBLE | WS_CHILD, CRect(0, 40, 250, 60), this, ID_BLUESLIDER);
    m_pListBox->Create(LBS_STANDARD | WS_VISIBLE | WS_CHILD, CRect(0, 80, 250, 250), this, ID_LISTBOX);

    // Set slider ranges and positions
    m_pRedSlider->SetRange(0,255, FALSE);
    m_pGreenSlider->SetRange(0,255, FALSE);
    m_pBlueSlider->SetRange(0,255, FALSE);

    m_pRedSlider->SetPos(128);
    m_pGreenSlider->SetPos(128);
    m_pBlueSlider->SetPos(128);

    // set current directory and fill list box
    SetCurrentDirectory("c:\\win95");
    m_pListBox->Dir(DDL_READONLY, (LPCTSTR)"*.exe");
}

void CDlgWin::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    UpdateClientColor();

    CFrameWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgWin::OnBtnExplorerClick()
{
    int nIndex;
    CString szText;

    if ((nIndex = m_pListBox->GetCurSel())!=-1) {
        // extract string from list box
        m_pListBox->GetText(nIndex, szText);
        // execute program
        ::WinExec(szText, SW_SHOWNORMAL);
    }
}

void CDlgWin::OnBtnExitClick()
{
    DestroyWindow();
};

BOOL CDlgWin::OnEraseBkgnd(CDC* pDC)
{
    // call the inherited handler
    CFrameWnd::OnEraseBkgnd(pDC);

    // paint the client area as needed
    UpdateClientColor();

    return (TRUE);
}

void CDlgWin::UpdateClientColor()
{
    BYTE nRed = m_pRedSlider->GetPos();
    BYTE nGreen = m_pGreenSlider->GetPos();
    BYTE nBlue = m_pBlueSlider->GetPos();

    // Set brush to desired background color
    CBrush br(RGB(nRed, nGreen, nBlue));

    // Save old brush
    CDC* pDC = GetDC();
    CBrush* pbrOld = pDC->SelectObject(&br);

    CRect rc;
    pDC->GetClipBox(&rc);  // Erase only the area needed
    pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);
    pDC->SelectObject(pbrOld);
}

CDlgApp TheApp;

void CDlgWin::SetWndFont(CWnd* pWnd, CString szFont, LONG lSize)
{
    if (!m_pFont) {
        m_pFont = new CFont;
        ASSERT_VALID(m_pFont);

        memset(&m_lf, 0, sizeof(LOGFONT));
        lstrcpy(m_lf.lfFaceName, _T(szFont));

        CWindowDC dcWnd(0);

        int cyPixels = dcWnd.GetDeviceCaps(LOGPIXELSY);
        m_lf.lfHeight = -MulDiv(lSize, cyPixels, 72);

        m_pFont->CreateFontIndirect(&m_lf);
    }
    pWnd->SetFont(m_pFont, TRUE);
}


void CDlgWin::SetChildFonts(int nFirst, int nLast, CString szFont, long lSize)
{
    for (int i = nFirst; i<= nLast; i++) {
        CWnd* pWnd = GetDlgItem(i);

        if (pWnd) SetWndFont(pWnd, szFont, lSize);
    }
}
