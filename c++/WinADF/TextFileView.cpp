// TextFileView.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "WinADFDoc.h"
#include "TextFileView.h"

#include "volume.h"
#include "file.h"

// TextFileView

IMPLEMENT_DYNCREATE(TextFileView, TextView)

TextFileView::TextFileView()
{

}

TextFileView::~TextFileView()
{
}

BEGIN_MESSAGE_MAP(TextFileView, TextView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// TextFileView drawing

void TextFileView::OnDraw(CDC* pDC)
{
	TextView::OnDraw(pDC);
}


// TextFileView diagnostics

#ifdef _DEBUG
void TextFileView::AssertValid() const
{
	TextView::AssertValid();
}

#ifndef _WIN32_WCE
void TextFileView::Dump(CDumpContext& dc) const
{
	TextView::Dump(dc);
}

WinADFDoc* TextFileView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(WinADFDoc)));
	return (WinADFDoc*)m_pDocument;
}

#endif
#endif //_DEBUG

// TextFileView message handlers

void TextFileView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
}

void TextFileView::OnInitialUpdate()
{
	TextView::OnInitialUpdate();
}

int TextFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (TextView::OnCreate(lpCreateStruct) != 0)
		return -1;

	m_Font.CreatePointFont(90, _T("Courier New"));	

	WinADFDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	Volume *pVol = pDoc->GetVolume();
	ASSERT(pVol != NULL);

	const Entry *pEntry = pDoc->GetEntry();
	ASSERT(pEntry != NULL);

	try {
		FilePtr file = pVol->openfile(*pEntry);

		LPSTR pbuf = m_Text.GetBuffer(pEntry->size+1);
		file->read(pEntry->size, pbuf);
		pbuf[pEntry->size] = '\0';
		m_Text.ReleaseBuffer();
	} catch (const ADFException &e) {
		AfxMessageBox(e.getDescription().c_str());
		return -1;
	}

	RecalcLayout();

	return 0;
}

BOOL TextFileView::PreCreateWindow(CREATESTRUCT& cs)
{
	return TextView::PreCreateWindow(cs);
}


