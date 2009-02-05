// FileViewFrame.cpp : implementation file
//

#include "stdafx.h"
#include "WinADF.h"
#include "FileViewFrame.h"
#include "WinADFDoc.h"

// FileViewFrame

IMPLEMENT_DYNCREATE(FileViewFrame, CMDIChildWnd)

FileViewFrame::FileViewFrame()
{

}

FileViewFrame::~FileViewFrame()
{
}


BEGIN_MESSAGE_MAP(FileViewFrame, CMDIChildWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// FileViewFrame message handlers

int FileViewFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

BOOL FileViewFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~FWS_ADDTOTITLE;

	return CMDIChildWnd::PreCreateWindow(cs);
}

void FileViewFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	WinADFDoc *pDoc = (WinADFDoc*)GetActiveDocument();
	ASSERT(pDoc != NULL);
	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(WinADFDoc)));

	CString title = pDoc->GetTitle();
	const Entry *pEntry = pDoc->GetEntry();
	if (pEntry != NULL) {
		title += ':';
		title += pEntry->name.c_str();
	}
	
	SetWindowText(title);	
}
