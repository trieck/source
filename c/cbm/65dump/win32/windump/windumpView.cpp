// windumpView.cpp : implementation of the WindumpView class
//

#include "stdafx.h"
#include "windump.h"

#include "windumpDoc.h"
#include "windumpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// WindumpView

IMPLEMENT_DYNCREATE(WindumpView, CListView)

BEGIN_MESSAGE_MAP(WindumpView, CListView)
    //{{AFX_MSG_MAP(WindumpView)
    ON_WM_ERASEBKGND()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WindumpView construction/destruction

WindumpView::WindumpView()
{
}

WindumpView::~WindumpView()
{
}

BOOL WindumpView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// WindumpView drawing

void WindumpView::OnDraw(CDC* pDC)
{
    WindumpDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    CListCtrl& refCtrl = GetListCtrl();
}

void WindumpView::OnInitialUpdate()
{
    CListView::OnInitialUpdate();

}

/////////////////////////////////////////////////////////////////////////////
// WindumpView diagnostics

#ifdef _DEBUG
void WindumpView::AssertValid() const
{
    CListView::AssertValid();
}

void WindumpView::Dump(CDumpContext& dc) const
{
    CListView::Dump(dc);
}

WindumpDoc* WindumpView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(WindumpDoc)));
    return (WindumpDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// WindumpView message handlers
void WindumpView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
}

BOOL WindumpView::OnEraseBkgnd(CDC* pDC)
{
    CRect rc;
    pDC->GetClipBox(rc);

    pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);

    return TRUE;
    //return CListView::OnEraseBkgnd(pDC);
}
