/*-----------------------------------------
	Module Name	:	BkgndPage.cpp
	Author		:	Thomas A. Rieck
	Purpose		:	Background Preference
					Property Page
					implementation
	Date		:	08/30/1997
------------------------------------------*/

#include "stdafx.h"
#include "BkgndPage.h"
#include "PrefDlg.h"
#include "CustBmp.h"
#include "OurConstants.h"

IMPLEMENT_DYNCREATE(CBkgndPage, CPropertyPage)

BEGIN_MESSAGE_MAP(CBkgndPage, CPropertyPage)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
END_MESSAGE_MAP()

// Initialize static data members
const UINT CBkgndPage::ctlIDs[] = {IDC_PSYCHADELIC, IDC_ROPE, IDC_GREENROPE,
                                   IDC_GRAIN1, IDC_GRAIN2, IDC_GRAIN3
                                  };
const UINT CBkgndPage::resIDs[] = {IDB_PSYCHADELIC, IDB_ROPE, IDB_GREENROPE,
                                   IDB_GRAIN1, IDB_GRAIN2, IDB_GRAIN3
                                  };
const RECT CBkgndPage::rcs[] = {{9, 4, 74, 64}, {77, 4, 142, 64}, {145, 4, 210, 64},
	{9, 69, 74, 129}, {77, 69, 142, 129}, {145, 69, 210, 129}
};

CBkgndPage::CBkgndPage() : CPropertyPage(CBkgndPage::IDD)
{
	m_pView				= NULL;
	m_lpszClassName		= NULL;
	m_pCurrentBitmap	= NULL;

	for (int i = 0; i < 6; i++) {
		m_pBkgndBitmaps[i]	= NULL;
	}
}

CBkgndPage::~CBkgndPage()
{
	for (UINT i = 0; i < 6; i++) {
		if (m_pBkgndBitmaps[i]) delete m_pBkgndBitmaps[i];
	}

	if (m_lpszClassName) {
		::UnregisterClass(m_lpszClassName, AfxGetInstanceHandle());
	}
}

BOOL CBkgndPage::OnInitDialog()
{
	CPrefDlg*	pSheet = (CPrefDlg*)GetParent();
	ASSERT_VALID(pSheet);

	m_pView = (CPenteView*)GetParentFrame()->GetActiveView();
	ASSERT_VALID(m_pView);

	m_lpszClassName = AfxRegisterWndClass(CS_OWNDC);
	ASSERT(m_lpszClassName);

	for (UINT i = 0; i < 6; i++) {
		ASSERT(pSheet->m_hBitmaps[i]);
		ASSERT(pSheet->m_hPalettes[i]);

		m_pBkgndBitmaps[i] = new CBkgndBitmap(
		    pSheet->m_hBitmaps[i], pSheet->m_hPalettes[i], resIDs[i]);
		ASSERT_VALID(m_pBkgndBitmaps[i]);

		// Convert Dialog Units
		CRect rc(rcs[i]);
		MapDialogRect(&rc);

		m_pBkgndBitmaps[i]->CreateEx(WS_EX_CLIENTEDGE, m_lpszClassName,
		                             _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER, rc, this, ctlIDs[i]);
	}

	m_pCurrentBitmap = GetBkgndBitmapFromRes(m_pView->GetBackgroundRes());
	ASSERT_VALID(m_pCurrentBitmap);

	m_pCurrentBitmap->Frame(TRUE);

	RedrawBitmaps();

	return CPropertyPage::OnInitDialog();
}

VOID CBkgndPage::OnPaletteChanged(CWnd* pFocusWnd)
{
	OnQueryNewPalette();
}

BOOL CBkgndPage::OnQueryNewPalette()
{
	return CPropertyPage::OnQueryNewPalette();
}
VOID CBkgndPage::OnOK()
{
	ASSERT_VALID(m_pCurrentBitmap);

	UINT nID = m_pCurrentBitmap->GetResID();
	ASSERT(nID);

	m_pView->SetBackgroundBitmap(nID);
}

BOOL CBkgndPage::OnApply()
{
	return CPropertyPage::OnApply();
}

VOID CBkgndPage::RedrawBitmaps()
{
	for (UINT i = 0; i < 6; i++) {
		if (m_pBkgndBitmaps[i] != m_pCurrentBitmap) {
			m_pBkgndBitmaps[i]->Frame(FALSE);
		}

		m_pBkgndBitmaps[i]->Invalidate();
	}
}

CBkgndBitmap* CBkgndPage::GetBkgndBitmapFromRes(UINT nRes)
{
	for (UINT i = 0; i < 6; i++) {
		if (resIDs[i] == nRes) {
			return (CBkgndBitmap*)GetDlgItem(ctlIDs[i]);
		}
	}
	return NULL;
}

