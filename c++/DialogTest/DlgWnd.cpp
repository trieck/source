// DLGWND.CPP

#include "DlgWnd.h"

// Message Map for CDlgWin
BEGIN_MESSAGE_MAP(CDlgWin, CFrameWnd)
    ON_WM_HSCROLL()
	ON_WM_ERASEBKGND()
	ON_LBN_SELCHANGE(ID_LISTBOX, OnLBSelChange)
	ON_LBN_DBLCLK(ID_LISTBOX, OnLBDblClick)
	ON_COMMAND(ID_OPENBTN, OnBtnOpenClick)
	ON_COMMAND(ID_EXITBTN, OnBtnExitClick)
END_MESSAGE_MAP()

CDlgWin::CDlgWin()
{
	// Initialize member variables
	m_pFont = NULL;
	m_pOpenBtn = NULL;
	m_pExitBtn = NULL;
	m_pRedSlider = NULL;
	m_pGreenSlider = NULL;
	m_pBlueSlider = NULL;
	m_pListBox = NULL;
	m_pEdit = NULL;
	m_pComboBox = NULL;
	m_pProgressCtrl = NULL;
}

CDlgWin::~CDlgWin()
{
	// Delete allocated memory
	if (m_pFont) delete m_pFont;
	if (m_pOpenBtn) delete m_pOpenBtn;
	if (m_pExitBtn) delete m_pExitBtn;
	if (m_pRedSlider) delete m_pRedSlider;
	if (m_pGreenSlider) delete m_pGreenSlider;
	if (m_pBlueSlider) delete m_pBlueSlider;
	if (m_pListBox) delete m_pListBox;
	if (m_pEdit) delete m_pEdit;
	if (m_pComboBox) delete m_pComboBox;
	if (m_pProgressCtrl) delete m_pProgressCtrl;
}

void CDlgWin::CreateControls()
{
	// Allocate memory for controls
	m_pOpenBtn = new CButton; ASSERT_VALID(m_pOpenBtn);
	m_pExitBtn = new CButton; ASSERT_VALID(m_pExitBtn);
    m_pRedSlider = new CSliderCtrl; ASSERT_VALID(m_pRedSlider);
	m_pGreenSlider = new CSliderCtrl; ASSERT_VALID(m_pGreenSlider);
	m_pBlueSlider = new CSliderCtrl; ASSERT_VALID(m_pBlueSlider);
	m_pListBox = new CListBox; ASSERT_VALID(m_pListBox);
	m_pEdit = new CEdit; ASSERT_VALID(m_pEdit);
	m_pComboBox = new CColorCombo; ASSERT_VALID(m_pComboBox);
	m_pProgressCtrl = new CProgressCtrl; ASSERT_VALID(m_pProgressCtrl);
	
	// Create them
	m_pOpenBtn->Create("&Open File", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
			CRect(350, 8, 513, 33), this, ID_OPENBTN);
	m_pExitBtn->Create("E&xit", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
            CRect(350, 40, 513, 65), this, ID_EXITBTN);
	m_pRedSlider->Create(WS_VISIBLE | WS_CHILD, CRect(0, 0, 250, 20), this, ID_REDSLIDER);
	m_pGreenSlider->Create(WS_VISIBLE | WS_CHILD, CRect(0, 20, 250, 40), this, ID_GREENSLIDER);
	m_pBlueSlider->Create(WS_VISIBLE | WS_CHILD, CRect(0, 40, 250, 60), this, ID_BLUESLIDER);
	m_pListBox->Create(LBS_STANDARD | WS_VISIBLE | WS_CHILD, CRect(0, 80, 250, 250), this, ID_LISTBOX);
	m_pEdit->Create(ES_MULTILINE | ES_READONLY | WS_VISIBLE | WS_VSCROLL | WS_CHILD | WS_BORDER, CRect (260, 80, 515, 240), this, ID_EDIT);
	m_pComboBox->Create(CBS_OWNERDRAWFIXED | CBS_NOINTEGRALHEIGHT | CBS_DROPDOWNLIST | WS_BORDER | WS_VISIBLE | WS_CHILD | WS_VSCROLL, CRect(260, 250, 515, 360), this, ID_COMBOBOX);
	m_pProgressCtrl->Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 275, 520, 295), this, ID_PROGRESSCTRL);
	
	// Set slider ranges and positions
	m_pRedSlider->SetRange(0,255, FALSE);
	m_pGreenSlider->SetRange(0,255, FALSE);
	m_pBlueSlider->SetRange(0,255, FALSE);
    
	m_pRedSlider->SetPos(128);
	m_pGreenSlider->SetPos(128);
	m_pBlueSlider->SetPos(128);

	// set current directory and fill list box
	SetCurrentDirectory("c:\\win95");
	m_pListBox->Dir(DDL_READONLY, (LPCTSTR)"*.ini");

	// fill combo box with colors
	m_pComboBox->FillList();
}

void CDlgWin::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;

	UpdateClientColor();

	CFrameWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgWin::OnBtnOpenClick()
{
	int nIndex;
	DWORD dwCount=0;
	CString szFile;
	BYTE* lpBuff = NULL;

	// initialize file member
	m_pFile = NULL;

	if ((nIndex = m_pListBox->GetCurSel())!=-1)
	{
		// extract string from list box
		m_pListBox->GetText(nIndex, _T(szFile));
		
		// create file
		m_pFile = new CStdioFile(_T(szFile), CFile::modeRead | CFile::typeBinary); ASSERT_VALID(m_pFile);
		
		// allocate memory
		lpBuff = new BYTE[m_pFile->GetLength()]; ASSERT_VALID(m_pFile);

		if (!(lpBuff))
		{
			AfxMessageBox("Error allocating memory.", MB_ICONINFORMATION);
			return;
		}

		// set progress control range
		m_pProgressCtrl->SetRange(0, m_pFile->GetLength());

		// read data
		while (dwCount < m_pFile->GetLength())
		{
			m_pFile->Read(lpBuff+dwCount, 10);
			dwCount +=10;
			m_pProgressCtrl->SetPos(dwCount);
		}

		// set text in edit control
		m_pEdit->SetWindowText((LPCTSTR)lpBuff);
		
		// close file
		m_pFile->Close();

		// release memory
		if (lpBuff) delete []lpBuff;
		if (m_pFile) delete m_pFile;
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

void CDlgWin::SetWndFont(CWnd* pWnd, CString szFont, LONG lSize)
{
	if (!m_pFont)
	{
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
	for (int i = nFirst; i<= nLast; i++)
	{
		CWnd* pWnd = GetDlgItem(i);

		if (pWnd) SetWndFont(pWnd, szFont, lSize);
	}
}

void CDlgWin::OnLBSelChange()
{
	m_pEdit->SetWindowText(NULL);
	m_pProgressCtrl->SetPos(0);
}

void CDlgWin::OnLBDblClick()
{
	this->OnBtnOpenClick();
}

