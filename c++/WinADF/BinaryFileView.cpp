// BinaryFileView.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "WinADFDoc.h"
#include "BinaryFileView.h"

#include "volume.h"
#include "file.h"

// BinaryFileView

IMPLEMENT_DYNCREATE(BinaryFileView, HexView)

BinaryFileView::BinaryFileView()
{

}

BinaryFileView::~BinaryFileView()
{
}

BEGIN_MESSAGE_MAP(BinaryFileView, HexView)
    ON_WM_CREATE()
END_MESSAGE_MAP()


// BinaryFileView drawing

void BinaryFileView::OnDraw(CDC* pDC)
{
    HexView::OnDraw(pDC);
}


// BinaryFileView diagnostics

#ifdef _DEBUG
void BinaryFileView::AssertValid() const
{
    HexView::AssertValid();
}

#ifndef _WIN32_WCE
void BinaryFileView::Dump(CDumpContext& dc) const
{
    HexView::Dump(dc);
}
#endif

WinADFDoc* BinaryFileView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(WinADFDoc)));
    return (WinADFDoc*)m_pDocument;
}

#endif //_DEBUG


// BinaryFileView message handlers

int BinaryFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (HexView::OnCreate(lpCreateStruct) == -1)
        return -1;

    m_Font.CreatePointFont(90, _T("Courier New"));

    WinADFDoc *pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    Volume *pVol = pDoc->GetVolume();
    ASSERT(pVol != NULL);

    const Entry *pEntry = pDoc->GetEntry();
    ASSERT(pEntry != NULL);

    m_nBufferLen = pEntry->size;

    try {
        FilePtr file = pVol->openfile(*pEntry);
        m_pBuffer = new uint8_t[m_nBufferLen];
        file->read(m_nBufferLen, m_pBuffer);
    } catch (const ADFException &e) {
        AfxMessageBox(e.getDescription().c_str());
        return -1;
    }

    SetSizes();

    return 0;
}

