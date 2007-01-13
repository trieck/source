// winview.cpp : implementation of the WinEditView class
//

#include "stdafx.h"
#include "winedit.h"
#include "windoc.h"
#include "winview.h"
#include "global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// WinEditView

IMPLEMENT_DYNCREATE(WinEditView, CEditView)

BEGIN_MESSAGE_MAP(WinEditView, CEditView)
	//{{AFX_MSG_MAP(WinEditView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WinEditView construction/destruction

WinEditView::WinEditView()
{
}

WinEditView::~WinEditView()
{
}

BOOL WinEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	
	cs.style |= WS_HSCROLL | WS_VSCROLL;

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// WinEditView drawing

void WinEditView::OnDraw(CDC* pDC)
{
	WinEditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// WinEditView diagnostics

#ifdef _DEBUG
void WinEditView::AssertValid() const
{
	CEditView::AssertValid();
}

void WinEditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

WinEditDoc* WinEditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(WinEditDoc)));
	return (WinEditDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// WinEditView message handlers

int WinEditView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);

	// Create the font
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	strcpy(lf.lfFaceName, GetProfileString("font", "FaceName"));
	lf.lfItalic = GetProfileInt("font", "Italic");
	lf.lfWeight = GetProfileInt("font", "Bold") == 1 ? FW_BOLD : FW_NORMAL;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfHeight = -MulDiv(GetProfileInt("font", "PointSize"), 
		dc.GetDeviceCaps(LOGPIXELSY), 72);

	if (!m_font.CreateFontIndirect(&lf))
		return -1;
			
	SetFont(&m_font);

	return 0;
}

void WinEditView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
}

void WinEditView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
}

