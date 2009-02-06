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

	if (!m_wndStatusBar.Create(this)) {
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	return 0;
}

BOOL FileViewFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~FWS_ADDTOTITLE;

	return CMDIChildWnd::PreCreateWindow(cs);
}

BOOL FileViewFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle , CWnd* pParentWnd , CCreateContext* pContext)
{
	WinADFDoc *pDoc = (WinADFDoc*)pContext->m_pCurrentDoc;
	if (pDoc == NULL)
		return FALSE;

	ASSERT_VALID(pDoc);
	
	const Entry *pEntry = pDoc->GetEntry();
	if (pEntry == NULL)
		return FALSE;

	m_strTitle = pDoc->GetTitle();
	m_strTitle += ':';
	m_strTitle += pEntry->name.c_str();

	return CMDIChildWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
}

void FileViewFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	SetWindowText(m_strTitle);	
}
