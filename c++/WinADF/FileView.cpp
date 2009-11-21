// FileView.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "WinADFDoc.h"
#include "FileView.h"

#include "volume.h"
#include "file.h"

// FileView

IMPLEMENT_DYNCREATE(FileView, TextView)

FileView::FileView()
{

}

FileView::~FileView()
{
}

BEGIN_MESSAGE_MAP(FileView, TextView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// FileView drawing

void FileView::OnDraw(CDC* pDC)
{
	TextView::OnDraw(pDC);
}


// FileView diagnostics

#ifdef _DEBUG
void FileView::AssertValid() const
{
	TextView::AssertValid();
}

#ifndef _WIN32_WCE
void FileView::Dump(CDumpContext& dc) const
{
	TextView::Dump(dc);
}

WinADFDoc* FileView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(WinADFDoc)));
	return (WinADFDoc*)m_pDocument;
}

#endif
#endif //_DEBUG

// FileView message handlers

void FileView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
}

void FileView::OnInitialUpdate()
{
	TextView::OnInitialUpdate();
}

int FileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	return RecalcLayout();
}

BOOL FileView::PreCreateWindow(CREATESTRUCT& cs)
{
	return TextView::PreCreateWindow(cs);
}


