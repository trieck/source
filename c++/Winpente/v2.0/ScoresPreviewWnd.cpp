// ScoresPreviewWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ScoresPreviewWnd.h"
#include "ScoresPreviewFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScoresPreviewWnd

CScoresPreviewWnd::CScoresPreviewWnd()
{
}

CScoresPreviewWnd::~CScoresPreviewWnd()
{
	m_Font.DeleteObject();
}


BEGIN_MESSAGE_MAP(CScoresPreviewWnd, CWnd)
	//{{AFX_MSG_MAP(CScoresPreviewWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CScoresPreviewWnd message handlers

void CScoresPreviewWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CScoresPreviewFrame * pFrame= (CScoresPreviewFrame*)GetParentFrame();
	ASSERT_VALID(pFrame);

	CDC * pPrinterDC = pFrame->GetPrinterDC();
	ASSERT_VALID(pPrinterDC);

	INT cxPage, cyPage;

	CRect rc;
	GetClientRect(&rc);

	cxPage = rc.Width();
	cyPage = rc.Width();

	DrawPreview(&dc, cxPage, cyPage);
}

VOID CScoresPreviewWnd::DrawPreview(CDC * pDC, INT cxPage, INT cyPage)
{
	ASSERT_VALID(pDC);

	pDC->SetBkMode(TRANSPARENT);

	// Draw the page
	DrawPage(pDC, cxPage, cyPage);
}


VOID CScoresPreviewWnd::DrawPage(CDC * pDC, INT cxPage, INT cyPage)
{
	ASSERT_VALID(pDC);

	// Create a brush using window color
	CBrush aBrush(::GetSysColor(COLOR_WINDOW));
	CBrush * pOldBrush = pDC->SelectObject(&aBrush);

	pDC->Rectangle(0, 0, cxPage, cyPage);

	// Clean up
	pDC->SelectObject(pOldBrush);

	// Draw the data
	DrawData(pDC, cxPage, cyPage);
}

BOOL CScoresPreviewWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style		= WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_BORDER;
	cs.dwExStyle	= WS_EX_OVERLAPPEDWINDOW;

	cs.lpszClass = AfxRegisterWndClass(
	                   CS_HREDRAW | CS_VREDRAW |
	                   CS_SAVEBITS | CS_BYTEALIGNCLIENT | CS_BYTEALIGNWINDOW,		// Class Style
	                   NULL,														// No Cursor
	                   NULL,														// No background brush
	                   NULL);														// No Icon

	ASSERT(cs.lpszClass);

	return CWnd::PreCreateWindow(cs);
}

int CScoresPreviewWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create the font
	if (!(m_Font.CreatePointFont(80, _T("Tahoma")))) {
		return -1;
	}

	return 0;
}

VOID CScoresPreviewWnd::DrawData(CDC * pDC, INT cxPage, INT cyPage)
{
	CFont * pOldFont = pDC->SelectObject(&m_Font);

	pDC->SelectObject(pOldFont);
}
