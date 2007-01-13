// LeftView.cpp : implementation of the LeftView class
//

#include "stdafx.h"
#include "windump.h"

#include "windumpDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LeftView

IMPLEMENT_DYNCREATE(LeftView, CTreeView)

BEGIN_MESSAGE_MAP(LeftView, CTreeView)
	//{{AFX_MSG_MAP(LeftView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LeftView construction/destruction

LeftView::LeftView()
{
}

LeftView::~LeftView()
{
}

BOOL LeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// LeftView drawing

void LeftView::OnDraw(CDC* pDC)
{
	WindumpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}


void LeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
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

WindumpDoc* LeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(WindumpDoc)));
	return (WindumpDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// LeftView message handlers
