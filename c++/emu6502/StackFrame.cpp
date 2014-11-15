// StackFrame.cpp : implementation file
//

#include "stdafx.h"
#include "emu6502.h"
#include "StackFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StackFrame

IMPLEMENT_DYNCREATE(StackFrame, CMiniFrameWnd)

static UINT indicators[] = {
    ID_SEPARATOR	// status line indicator
};

StackFrame::StackFrame()
{
    Create(NULL, _T("Stack"), MFS_THICKFRAME | WS_OVERLAPPEDWINDOW,
           rectDefault, AfxGetMainWnd());

    Emu6502App *pApp = (Emu6502App*)AfxGetApp();
    pApp->RegisterConstruct(STACK_FRAME_ID, this);
}

StackFrame::~StackFrame()
{
    Emu6502App *pApp = (Emu6502App*)AfxGetApp();
    pApp->RegisterDestruct(STACK_FRAME_ID);
}

BEGIN_MESSAGE_MAP(StackFrame, CMiniFrameWnd)
    //{{AFX_MSG_MAP(StackFrame)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StackFrame message handlers

BOOL StackFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
    CRuntimeClass* pRuntimeClass = RUNTIME_CLASS(StackView);
    StackView *pView = (StackView*)pRuntimeClass->CreateObject();

    if (!pView->CreateEx(WS_EX_CLIENTEDGE, NULL, _T(""),
                         WS_CHILD | WS_VISIBLE, rectDefault, this,
                         AFX_IDW_PANE_FIRST, NULL)) {
        TRACE0("Unable to create view.\n");
        return -1;
    }

    ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);

    return TRUE;
}

BOOL StackFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.cx = 200;
    cs.cy = 300;
    return CMiniFrameWnd::PreCreateWindow(cs);
}

int StackFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
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



