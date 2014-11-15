// DisassemFrame.cpp : implementation file
//

#include "stdafx.h"
#include "emu6502.h"
#include "DisassemFrame.h"
#include "DisassemView.h"

// DisassemFrame

IMPLEMENT_DYNCREATE(DisassemFrame, CMiniFrameWnd)

static UINT indicators[] = {
    ID_SEPARATOR	// status line indicator
};

DisassemFrame::DisassemFrame()
{
    Create(NULL, _T("Disassembly"), MFS_THICKFRAME | WS_OVERLAPPEDWINDOW,
           rectDefault, AfxGetMainWnd());

    Emu6502App *pApp = (Emu6502App*)AfxGetApp();
    pApp->RegisterConstruct(DISASSEM_FRAME_ID, this);
}

DisassemFrame::~DisassemFrame()
{
    Emu6502App *pApp = (Emu6502App*)AfxGetApp();
    pApp->RegisterDestruct(DISASSEM_FRAME_ID);
}


BEGIN_MESSAGE_MAP(DisassemFrame, CMiniFrameWnd)
    ON_WM_CREATE()
END_MESSAGE_MAP()

BOOL DisassemFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.cx = 400;
    cs.cy = 200;

    return CMiniFrameWnd::PreCreateWindow(cs);
}

BOOL DisassemFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
    CRuntimeClass* pRuntimeClass = RUNTIME_CLASS(DisassemView);
    DisassemView *pView = (DisassemView*)pRuntimeClass->CreateObject();

    if (!pView->CreateEx(WS_EX_CLIENTEDGE, NULL, _T(""),
                         WS_CHILD | WS_VISIBLE, rectDefault, this,
                         AFX_IDW_PANE_FIRST, NULL)) {
        TRACE0("Unable to create view.\n");
        return -1;
    }

    ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);

    return TRUE;
}

int DisassemFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
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


// DisassemFrame message handlers
