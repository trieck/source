// LeftView.cpp : implementation of the LeftView class
//

#include "stdafx.h"
#include "WinADF.h"

#include "WinADFDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// LeftView

IMPLEMENT_DYNCREATE(LeftView, CTreeView)

BEGIN_MESSAGE_MAP(LeftView, CTreeView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()


// LeftView construction/destruction

LeftView::LeftView()
{
	// TODO: add construction code here
}

LeftView::~LeftView()
{
}

BOOL LeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}


// LeftView printing

BOOL LeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void LeftView::OnDraw(CDC* /*pDC*/)
{
	WinADFDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void LeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void LeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void LeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}


// LeftView diagnostics

#ifdef _DEBUG
void LeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void LeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

WinADFDoc* LeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(WinADFDoc)));
	return (WinADFDoc*)m_pDocument;
}
#endif //_DEBUG


// LeftView message handlers
