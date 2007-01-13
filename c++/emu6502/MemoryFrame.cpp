// MemoryFrame.cpp : implementation file
//

#include "stdafx.h"
#include "emu6502.h"
#include "MemoryFrame.h"
#include "MemoryView.h"

// MemoryFrame

IMPLEMENT_DYNCREATE(MemoryFrame, CMiniFrameWnd)

static UINT indicators[] = {
	ID_SEPARATOR	// status line indicator
};

MemoryFrame::MemoryFrame()
{
	Create(NULL, _T("Memory"), MFS_THICKFRAME | WS_OVERLAPPEDWINDOW, 
		rectDefault, AfxGetMainWnd());

	Emu6502App *pApp = (Emu6502App*)AfxGetApp();
	pApp->RegisterConstruct(MEMORY_FRAME_ID, this);
}

MemoryFrame::~MemoryFrame()
{
	Emu6502App *pApp = (Emu6502App*)AfxGetApp();
	pApp->RegisterDestruct(MEMORY_FRAME_ID);
}

BEGIN_MESSAGE_MAP(MemoryFrame, CMiniFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// MemoryFrame message handlers

BOOL MemoryFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cx = 400;
	cs.cy = 200;

	return CMiniFrameWnd::PreCreateWindow(cs);
}

BOOL MemoryFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	CRuntimeClass* pRuntimeClass = RUNTIME_CLASS(MemoryView);
	MemoryView *pView = (MemoryView*)pRuntimeClass->CreateObject();

	if (!pView->CreateEx(WS_EX_CLIENTEDGE, NULL, _T(""), 
		WS_CHILD | WS_VISIBLE, rectDefault, this, 
		AFX_IDW_PANE_FIRST, NULL)) {
		TRACE0("Unable to create view.\n");
		return -1;
	}

	ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);

	return TRUE;
}

int MemoryFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMiniFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT))) {
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}
