// WinADFView.cpp : implementation of the WinADFView class
//

#include "stdafx.h"
#include "WinADF.h"

#include "WinADFDoc.h"
#include "WinADFView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// WinADFView

IMPLEMENT_DYNCREATE(WinADFView, CListView)

BEGIN_MESSAGE_MAP(WinADFView, CListView)
	ON_WM_STYLECHANGED()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

// WinADFView construction/destruction

WinADFView::WinADFView()
{
	// TODO: add construction code here

}

WinADFView::~WinADFView()
{
}

BOOL WinADFView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}


void WinADFView::OnDraw(CDC* /*pDC*/)
{
	WinADFDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


void WinADFView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}


// WinADFView printing

BOOL WinADFView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void WinADFView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void WinADFView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// WinADFView diagnostics

#ifdef _DEBUG
void WinADFView::AssertValid() const
{
	CListView::AssertValid();
}

void WinADFView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

WinADFDoc* WinADFView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(WinADFDoc)));
	return (WinADFDoc*)m_pDocument;
}
#endif //_DEBUG


// WinADFView message handlers
void WinADFView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window	
	CListView::OnStyleChanged(nStyleType,lpStyleStruct);	
}
