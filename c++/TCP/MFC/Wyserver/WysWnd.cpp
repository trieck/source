/*--------------------------------------
	Module:	WYSWND.CPP
	Author:	Thomas A. Rieck
	Date:	06/22/97
----------------------------------------*/

#include "resource.h"
#include "WysWnd.h"
#include "ConnDlg.h"
#include "PrefDlg.h"
#include <commdlg.h>

// message map for CWysWnd
BEGIN_MESSAGE_MAP(CWysWnd, CFrameWnd)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_WM_MENUSELECT()
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_COMMAND(IDM_ACTIVECONN, OnActiveConn)
	ON_COMMAND(IDM_PREFERENCE, OnPreferences)
	ON_COMMAND(IDM_FONT, OnFont)
END_MESSAGE_MAP()

BOOL CWysWnd :: PreCreateWindow(CREATESTRUCT& cs)
{
	// Get the icon handle from the resource data
	m_hIcon = (HICON)::LoadImage(cs.hInstance,
	                             MAKEINTRESOURCE(IDI_MAIN),
	                             IMAGE_ICON, 32, 32,
	                             LR_DEFAULTCOLOR);

	return (CFrameWnd :: PreCreateWindow(cs));
}

int CWysWnd :: OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// make the resource icon the default for the frame window
	if (m_hIcon)
		::SetClassLong(GetSafeHwnd(), GCL_HICON, (LONG)m_hIcon);

	return (0);
}
void CWysWnd :: OnSize(UINT nType, int cx, int cy)
{
	m_pListBox->MoveWindow(0, 0, cx, cy, TRUE);
}


CListBox* CWysWnd :: GetListBox()
{
	return (m_pListBox);
}

CWysWnd :: CWysWnd()
{
	// initialize class members
	m_pListBox	= NULL;
	m_pFont		= NULL;
}

void CWysWnd :: CreateListBox()
{
	CRect rc;

	GetClientRect(&rc);

	m_pListBox = new CListBox;
	ASSERT_VALID (m_pListBox);

	m_pListBox->Create(WS_VISIBLE | WS_CHILD | WS_VSCROLL |
	                   LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT |
	                   LBS_OWNERDRAWFIXED, rc,
	                   this, ID_LISTBOX);
}

BOOL CWysWnd :: CreateListFont(LPLOGFONT lpLogFont)
{
	CDC* pDC = GetDC();
	ASSERT_VALID(pDC);

	// create the font
	if (m_pFont) delete (m_pFont);

	m_pFont = new CFont;
	ASSERT_VALID(m_pFont);

	if (lpLogFont == NULL) {
		LOGFONT lf;
		INT cyPixels;

		cyPixels = pDC->GetDeviceCaps(LOGPIXELSY);
		lpLogFont = &lf;

		lf.lfHeight			= -MulDiv(DEFAULT_FONTSIZE, cyPixels, 72);
		lf.lfWidth			= 0;
		lf.lfEscapement		= 0;
		lf.lfOrientation	= 0;
		lf.lfWeight			= DEFAULT_WEIGHT;
		lf.lfItalic			= 0;
		lf.lfUnderline		= 0;
		lf.lfStrikeOut		= 0;
		lf.lfCharSet		= DEFAULT_CHARSET;
		lf.lfOutPrecision	= OUT_DEFAULT_PRECIS;
		lf.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
		lf.lfQuality		= DEFAULT_QUALITY;
		lf.lfPitchAndFamily	= DEFAULT_PITCH;
		strcpy(lf.lfFaceName, DEFAULT_FACENAME);
	}

	ReleaseDC(pDC);

	return (m_pFont->CreateFontIndirect(lpLogFont));
}

void CWysWnd :: AddListItem(LPSCREENLINE lpScreenLine)
{
	INT iCount;

	if (!m_pListBox)
		return;

	// add string to list
	m_pListBox->AddString(lpScreenLine->szText);

	// get count of items
	iCount = m_pListBox->GetCount() - 1;

	m_pListBox->SetItemData(iCount, lpScreenLine->uColor);
}

CWysWnd :: ~CWysWnd()
{
	// destroy list box
	if (m_pListBox) m_pListBox->DestroyWindow();

	// delete allocated data members
	if (m_pListBox)	delete m_pListBox;
	if (m_pFont) delete m_pFont;
}

BOOL CWysWnd :: OnEraseBkgnd(CDC* pDC)
{
	// call the inherited handler
	CFrameWnd :: OnEraseBkgnd(pDC);

	return (TRUE);
}

void CWysWnd :: OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC*		pDC;
	CFont*		pOldFont;
	TEXTMETRIC	tm;

	if (!m_pFont)
		return;

	pDC = m_pListBox->GetDC();
	ASSERT_VALID(pDC);

	pOldFont = pDC->SelectObject(m_pFont);

	pDC->GetTextMetrics(&tm);

	lpMeasureItemStruct->itemWidth	= tm.tmAveCharWidth;
	lpMeasureItemStruct->itemHeight	= tm.tmHeight + tm.tmExternalLeading;

	pDC->SelectObject(pOldFont);

	m_pListBox->ReleaseDC(pDC);
}

void CWysWnd :: OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CBrush aBrush, *pOldBrush;

	if (lpDrawItemStruct->itemID == -1)
		return;

	switch (lpDrawItemStruct->itemAction) {
		INT y;
		TCHAR tchBuffer[255];
		COLORREF uColor;
		CDC* pDC;
		TEXTMETRIC tm;

	case ODA_SELECT:
	case ODA_DRAWENTIRE:
		// get item text
		::SendMessage(lpDrawItemStruct->hwndItem, LB_GETTEXT,
		              lpDrawItemStruct->itemID, (LPARAM) tchBuffer);

		// get item color
		uColor = ::SendMessage(lpDrawItemStruct->hwndItem, LB_GETITEMDATA,
		                       lpDrawItemStruct->itemID, 0);

		// retrieve position
		pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
		pDC->GetTextMetrics(&tm);

		y = (lpDrawItemStruct->rcItem.bottom + lpDrawItemStruct->rcItem.top -
		     tm.tmHeight) / 2;

		// check if item is selected
		if (lpDrawItemStruct->itemState & ODS_SELECTED)
			// draw selected rectangle
			aBrush.CreateSolidBrush(COLOR_YELLOW);
		else	// draw default background
			aBrush.CreateSolidBrush(GetSysColor(COLOR_WINDOW));

		pOldBrush = (CBrush*)pDC->SelectObject(&aBrush);
		ASSERT_VALID(pOldBrush);

		pDC->FillRect(&(lpDrawItemStruct->rcItem), &aBrush);

		pDC->SelectObject(pOldBrush);
		aBrush.DeleteObject();

		// set background mode
		pDC->SetBkMode(TRANSPARENT);

		// set text item color
		pDC->SetTextColor(uColor);

		// display the text item
		pDC->TextOut(0, y, tchBuffer, strlen(tchBuffer));
		break;
	}
}

void CWysWnd :: OnAbout()
{
	CDialog dlg(MAKEINTRESOURCE(IDD_ABOUT), this);

	dlg.DoModal();
}

void CWysWnd :: OnActiveConn()
{
	CConnDlg dlg(this);

	dlg.DoModal();
}

void CWysWnd :: OnPreferences()
{
	CPrefDlg dlg(this);

	dlg.DoModal();
}

void CWysWnd :: OnFont()
{
	CHOOSEFONT cf;
	LOGFONT lf;

	// get logigical font structure
	m_pFont->GetLogFont(&lf);

	// fill in choosefont structure
	cf.lStructSize		= sizeof(cf);
	cf.hwndOwner		= GetSafeHwnd();
	cf.hDC				= 0;
	cf.lpLogFont		= &lf;
	cf.Flags			= CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;
	cf.rgbColors		= 0;
	cf.lCustData		= 0;
	cf.lpfnHook			= 0;
	cf.lpTemplateName	= 0;
	cf.hInstance		= 0;
	cf.lpszStyle		= 0;
	cf.nFontType		= 0;

	if (ChooseFont(&cf)) {
		// copy font returned from dialog
		CreateListFont(cf.lpLogFont);

		CDC* pDC		= m_pListBox->GetDC();
		CFont* pOldFont = pDC->SelectObject(m_pFont);

		// set the listbox item size and new font
		TEXTMETRIC tmList;
		INT cyItem;

		// set text height
		pDC->GetTextMetrics(&tmList);
		cyItem = tmList.tmHeight + tmList.tmExternalLeading;
		m_pListBox->SetItemHeight(0, cyItem);

		// set the font
		m_pListBox->SetFont(m_pFont, TRUE);

		// clean up
		pDC->SelectObject(pOldFont);
		m_pListBox->ReleaseDC(pDC);
	}
	return;
}