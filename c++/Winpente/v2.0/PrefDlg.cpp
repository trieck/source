/*---------------------------------------
	Module Name	:	PrefDlg.cpp
	Author		:	Thomas A. Rieck
	Purpose		:	Preferences Dialog
					implementations
	Date		:	08/24/1997
---------------------------------------*/

#include "stdafx.h"
#include "PrefDlg.h"
#include "CustBmp.h"
#include "OurMacros.h"

CPrefDlg::CPrefDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	: CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pColorPage	= NULL;
	m_pPiecePage	= NULL;
	m_pBkgndPage	= NULL;

	for (int i = 0; i < 6; i++) {
		m_hBitmaps[i]	= NULL;
		m_hPalettes[i]	= NULL;
	}
}

BOOL CPrefDlg::OnInitDialog()
{
	return CPropertySheet::OnInitDialog();
}

VOID CPrefDlg::Init()
{
	int nResIDs[6] = {IDB_PSYCHADELIC, IDB_ROPE, IDB_GREENROPE,
	                  IDB_GRAIN1, IDB_GRAIN2, IDB_GRAIN3
	                 };

	CCustomBitmap* pCustomBitmap = new CCustomBitmap();
	ASSERT_VALID(pCustomBitmap);

	// Load the bitmaps used
	// for the background page
	for (int i = 0; i < 6; i++) {
		m_hBitmaps[i] = pCustomBitmap->LoadResourceBitmap(nResIDs[i],
		                &m_hPalettes[i]);

		ASSERT(m_hBitmaps[i]);
		ASSERT(m_hPalettes[i]);
	}

	// Build the property pages
	// and add them to the dialog
	BuildPages();

	delete pCustomBitmap;
}

VOID CPrefDlg::BuildPages()
{
	// construct the property pages
	m_pColorPage = new CColorPage();
	ASSERT_VALID(m_pColorPage);

	m_pPiecePage = new CPiecePage();
	ASSERT_VALID(m_pPiecePage);

	m_pBkgndPage = new CBkgndPage();
	ASSERT_VALID(m_pBkgndPage);

	m_pColorPage->Construct(IDD_COLORPAGE, 0);
	m_pPiecePage->Construct(IDD_PIECEPAGE, 0);
	m_pBkgndPage->Construct(IDD_BKGNDPAGE, 0);

	// Add the property pages
	AddPage(m_pColorPage);
	AddPage(m_pPiecePage);
	AddPage(m_pBkgndPage);
}

CPrefDlg::~CPrefDlg()
{
	if (m_pColorPage)	delete m_pColorPage;
	if (m_pPiecePage)	delete m_pPiecePage;
	if (m_pBkgndPage)	delete m_pBkgndPage;

	for (int i = 0; i < 6; i++) {
		DELETEGDIOBJECT(m_hBitmaps[i]);
		DELETEGDIOBJECT(m_hPalettes[i]);
	}
}
