// FileView.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "WinADFDoc.h"
#include "FileView.h"

#include "volume.h"
#include "file.h"

// FileView

IMPLEMENT_DYNCREATE(FileView, CEditView)

FileView::FileView()
{

}

FileView::~FileView()
{
}

BEGIN_MESSAGE_MAP(FileView, CEditView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// FileView drawing

void FileView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// FileView diagnostics

#ifdef _DEBUG
void FileView::AssertValid() const
{
	CEditView::AssertValid();
}

#ifndef _WIN32_WCE
void FileView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

WinADFDoc* FileView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(WinADFDoc)));
	return (WinADFDoc*)m_pDocument;
}

#endif
#endif //_DEBUG

// FileView message handlers

void FileView::OnUpdate(CEditView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
}

void FileView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();
}

int FileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_Font.CreatePointFont(90, _T("Courier New"));	
	SetFont(&m_Font);	

	WinADFDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	Volume *pVol = pDoc->GetVolume();
	ASSERT(pVol != NULL);

	const Entry *pEntry = pDoc->GetEntry();
	ASSERT(pEntry != NULL);

	CString buffer;
	try {
		FilePtr file = pVol->openfile(*pEntry);

		LPSTR pbuf = buffer.GetBuffer(pEntry->size+1);
		file->read(pEntry->size, pbuf);
		pbuf[pEntry->size] = '\0';
		buffer.ReleaseBuffer();

	} catch (const ADFException &e) {
		AfxMessageBox(e.getDescription().c_str());
		return -1;
	}

	CEdit &edit = GetEditCtrl();
	edit.SetReadOnly();	
	edit.FmtLines(TRUE);
	edit.SetWindowText(buffer);	

	return 0;
}

BOOL FileView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping	

	return CEditView::PreCreateWindow(cs);
}
