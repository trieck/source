
// TFingerView.cpp : implementation of the CTFingerView class
//

#include "stdafx.h"
#include "TFinger.h"
#include "TFingerDoc.h"
#include "TFingerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTFingerView

IMPLEMENT_DYNCREATE(CTFingerView, CScrollView)

BEGIN_MESSAGE_MAP(CTFingerView, CScrollView)
    ON_WM_CREATE()
END_MESSAGE_MAP()

#define COLOR_RED	RGB(192, 0, 0)
#define COLOR_GREEN	RGB(0, 192, 0)

// CTFingerView construction/destruction

CTFingerView::CTFingerView()
{
    m_endingPen.CreatePen(PS_SOLID, 1, COLOR_RED);
    m_bifurPen.CreatePen(PS_SOLID, 1, COLOR_GREEN);

    m_endingBrush.CreateSolidBrush(COLOR_RED);
    m_bifurBrush.CreateSolidBrush(COLOR_GREEN);
}

CTFingerView::~CTFingerView()
{
}

BOOL CTFingerView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CScrollView::PreCreateWindow(cs);
}

// CTFingerView drawing

void CTFingerView::OnDraw(CDC* pDC)
{
    CTFingerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    CImage* pImage = pDoc->GetBitmap();
    if (pImage == NULL)
        return;

    CRect rc;
    pDC->GetClipBox(rc);

    // draw the image
    pImage->BitBlt(pDC->GetSafeHdc(), rc.left, rc.top,
                   rc.Width(), rc.Height(), rc.left, rc.top);

    // draw the minutia
    const MinutiaVec *pMinutia;
    if ((pMinutia = pDoc->GetMinutia()) != NULL) {
        DrawMinutia(pDC, pMinutia);
    }
}

void CTFingerView::DrawMinutia(CDC *pDC, const MinutiaVec *pMinutia)
{
    CPen *pOldPen = pDC->SelectObject(&m_endingPen);
    CBrush *pOldBrush = pDC->SelectObject(&m_endingBrush);

    CRect rc;

    MinutiaVec::const_iterator it = pMinutia->begin();
    for ( ; it != pMinutia->end(); it++) {
        const Minutia &m = *it;
        if (m.type == MT_RIDGE_ENDING) {
            pDC->SelectObject(&m_endingPen);
            pDC->SelectObject(&m_endingBrush);
        } else if (m.type == MT_RIDGE_BIFUR) {
            pDC->SelectObject(&m_bifurPen);
            pDC->SelectObject(&m_bifurBrush);
        }

        rc.SetRect(m.x-2, m.y-2, m.x+2, m.y+2);
        if (pDC->RectVisible(&rc)) {
            pDC->Ellipse(rc);
        }
    }

    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}


// CTFingerView diagnostics

#ifdef _DEBUG
void CTFingerView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CTFingerView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CTFingerDoc* CTFingerView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTFingerDoc)));
    return (CTFingerDoc*)m_pDocument;
}
#endif //_DEBUG


// CTFingerView message handlers

void CTFingerView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();

    CSize sizeTotal;
    CTFingerDoc* pDoc = GetDocument();
    if (pDoc != NULL) {
        sizeTotal = pDoc->GetDocSize();
    }

    SetScrollSizes(MM_TEXT, sizeTotal);
}

int CTFingerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CScrollView::OnCreate(lpCreateStruct) == -1)
        return -1;

    SetScrollSizes(MM_TEXT, CSize(0,0));

    return 0;
}

