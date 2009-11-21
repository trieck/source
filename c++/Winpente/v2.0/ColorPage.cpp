/*---------------------------------------
	Module Name	:	ColorPage.cpp
	Author		:	Thomas A. Rieck
	Purpose		:	Color Preference
					Property Page
					implementation
	Date		:	08/24/1997
---------------------------------------*/

#include "stdafx.h"
#include "ColorPage.h"
#include "MainFrame.h"
#include "OurConstants.h"

IMPLEMENT_DYNCREATE(CColorPage, CPropertyPage)

BEGIN_MESSAGE_MAP(CColorPage, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_COMMAND(IDC_BACKCOLOR, OnBackColor)
	ON_COMMAND(IDC_GRIDCOLOR, OnGridColor)
	ON_COMMAND(IDC_USEBKGND, OnUseBkgnd)
	ON_COMMAND(IDC_USETHEME, OnUseTheme)
END_MESSAGE_MAP()

CColorPage::CColorPage() : CPropertyPage(CColorPage::IDD)
{
	m_pDoc			= NULL;
	m_lBackColor	= 0L;
	m_lGridColor	= 0L;
	m_fUseBackColor	= FALSE;
}

BOOL CColorPage::OnInitDialog()
{
	CMainFrame* pFrame;

	pFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();
	ASSERT_VALID(pFrame);

	m_pDoc = (CPenteDoc*)pFrame->GetActiveDocument();
	ASSERT_VALID(m_pDoc);

	m_lBackColor = m_pDoc->GetBackColor();
	m_lGridColor = m_pDoc->GetGridColor();

	m_fUseBackColor = m_pDoc->m_fUseBackColor;

	// Enable current option
	if (m_fUseBackColor)
		CheckDlgButton(IDC_USEBKGND, TRUE);
	else
		CheckDlgButton(IDC_USETHEME, TRUE);

	return CPropertyPage::OnInitDialog();
}

BOOL CColorPage::OnApply()
{
	return CPropertyPage::OnApply();
}

VOID CColorPage::OnOK()
{
	m_pDoc->m_fUseBackColor = m_fUseBackColor;

	if (m_pDoc->m_fUseBackColor)
		m_pDoc->SetBackColor(m_lBackColor);

	m_pDoc->SetGridColor(m_lGridColor);
	m_pDoc->UpdateAllViews(NULL);
}

VOID CColorPage::OnPaint()
{
	CRect		rcBack, rcGrid;

	CPaintDC	dc(this);
	CPaintDC	dcBack(&BackColor());
	CPaintDC	dcGrid(&GridColor());

	rcBack.CopyRect(&(dcBack.m_ps.rcPaint));
	rcGrid.CopyRect(&(dcGrid.m_ps.rcPaint));

	dcBack.FillSolidRect(&rcBack, m_lBackColor);
	dcGrid.FillSolidRect(&rcGrid, m_lGridColor);

	CPropertyPage::OnPaint();
}


INT CColorPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return CPropertyPage::OnCreate(lpCreateStruct);
}

VOID CColorPage::OnUseBkgnd()
{
	m_fUseBackColor = TRUE;
	SetModified();
}

VOID CColorPage::OnUseTheme()
{
	m_fUseBackColor = FALSE;
	SetModified();
}

VOID CColorPage::OnBackColor()
{
	CColorDialog dlgColor (m_lBackColor, CC_RGBINIT, this);

	if (IDOK == dlgColor.DoModal()) {
		m_lBackColor = dlgColor.GetColor();
		BackColor().InvalidateRect(NULL, TRUE);

		SetModified();
		RedrawWindow();
	}
}

VOID CColorPage::OnGridColor()
{
	CColorDialog dlgColor (m_lGridColor, CC_RGBINIT, this);

	if (IDOK == dlgColor.DoModal()) {
		m_lGridColor = dlgColor.GetColor();
		GridColor().InvalidateRect(NULL, TRUE);

		SetModified();
		RedrawWindow();
	}
}

CColorPage::~CColorPage()
{
}


