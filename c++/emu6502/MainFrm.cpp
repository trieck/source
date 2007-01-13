// MainFrm.cpp : implementation of the MainFrame class
//

#include "stdafx.h"
#include "emu6502.h"

#include "MainFrm.h"
#include "RegisterDlg.h"
#include "StackFrame.h"
#include "MemoryFrame.h"
#include "DisassemFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MainFrame

IMPLEMENT_DYNCREATE(MainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(MainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_REGISTERS, OnRegisters)
	ON_COMMAND(IDM_MEMORY, OnMemory)	
	ON_COMMAND(IDM_STACK, OnStack)
	ON_WM_SYSCOLORCHANGE()
	ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, OnToolbarDropDown)
	ON_UPDATE_COMMAND_UI(IDM_REGISTERS, OnUpdateRegisters)
	ON_UPDATE_COMMAND_UI(IDM_STACK, OnUpdateStack)
	ON_UPDATE_COMMAND_UI(IDM_MEMORY, OnUpdateMemory)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDM_DISASSEMBLY, OnUpdateDisassembly)
	ON_COMMAND(IDM_DISASSEMBLY, OnDisassembly)
END_MESSAGE_MAP()

static UINT indicators[] = {
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// MainFrame construction/destruction

MainFrame::MainFrame() 
{
}

MainFrame::~MainFrame()
{
}

int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	UINT id, style; int image;
	m_wndToolBar.GetButtonInfo(10, id, style, image);
	m_wndToolBar.SetButtonInfo(10, id, style |= TBSTYLE_CHECK, image);
	m_wndToolBar.GetButtonInfo(11, id, style, image);
	m_wndToolBar.SetButtonInfo(11, id, style |= TBSTYLE_CHECK, image);
	m_wndToolBar.GetButtonInfo(12, id, style, image);
	m_wndToolBar.SetButtonInfo(12, id, style |= TBSTYLE_CHECK, image);
	m_wndToolBar.GetButtonInfo(13, id, style, image);
	m_wndToolBar.SetButtonInfo(13, id, style |= TBSTYLE_CHECK, image);

	m_wndToolBar.GetToolBarCtrl().SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);
	DWORD dwStyle = m_wndToolBar.GetButtonStyle(m_wndToolBar.CommandToIndex(ID_FILE_OPEN));
	dwStyle |= TBSTYLE_DROPDOWN;
	m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(ID_FILE_OPEN), dwStyle);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT))) {
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	
	CenterWindow();

	return 0;
}

void MainFrame::OnToolbarDropDown(NMHDR *pnmh, LRESULT *plr)
{
	CWnd *pWnd;
	UINT nID;

	NMTOOLBAR* pnmtb = (NMTOOLBAR*)pnmh;

	// Switch on button command id's.
	switch (pnmtb->iItem)
	{
	case ID_FILE_OPEN:
		pWnd = &m_wndToolBar;
		nID  = IDR_DROPMENU;
		break;
	default:
		return;
	}
	
	// load and display popup menu
	CMenu menu;
	menu.LoadMenu(nID);
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup);
	
	CRect rc;
	pWnd->SendMessage(TB_GETRECT, pnmtb->iItem, (LPARAM)&rc);
	pWnd->ClientToScreen(&rc);
	
	pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,
		rc.left, rc.bottom, this, &rc);
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cx = cs.cy = 500;

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// MainFrame diagnostics

#ifdef _DEBUG
void MainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void MainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MainFrame message handlers

void MainFrame::OnRegisters() 
{
	RegisterDlg *dlg;
	Emu6502App *pApp = (Emu6502App*)AfxGetApp();
	dlg = (RegisterDlg*)pApp->GetState(RegisterDlg::IDD);
	if (dlg == NULL) {
		dlg	= new RegisterDlg();
		dlg->ShowWindow(SW_SHOWNORMAL);
	} else {
		dlg->DestroyWindow();
	}
}

void MainFrame::OnSysColorChange() 
{
	CFrameWnd::OnSysColorChange();
	SendMessageToDescendants(WM_SYSCOLORCHANGE);
}

void MainFrame::OnStack() 
{
	ToggleFrameWnd(RUNTIME_CLASS(StackFrame), STACK_FRAME_ID);
}

void MainFrame::OnUpdateRegisters(CCmdUI* pCmdUI) 
{
	Emu6502App *pApp = (Emu6502App*)AfxGetApp();
	pCmdUI->SetCheck(pApp->GetState(RegisterDlg::IDD) ? 1 : 0);	
}

void MainFrame::OnUpdateStack(CCmdUI* pCmdUI) 
{
	Emu6502App *pApp = (Emu6502App*)AfxGetApp();
	pCmdUI->SetCheck(pApp->GetState(STACK_FRAME_ID) ? 1 : 0);		
}

void MainFrame::OnMemory()
{	
	ToggleFrameWnd(RUNTIME_CLASS(MemoryFrame), MEMORY_FRAME_ID);
}

void MainFrame::OnUpdateMemory(CCmdUI* pCmdUI) 
{
	Emu6502App *pApp = (Emu6502App*)AfxGetApp();
	pCmdUI->SetCheck(pApp->GetState(MEMORY_FRAME_ID) ? 1 : 0);		
}

void MainFrame::OnUpdateDisassembly(CCmdUI *pCmdUI)
{
	Emu6502App *pApp = (Emu6502App*)AfxGetApp();
	pCmdUI->SetCheck(pApp->GetState(DISASSEM_FRAME_ID) ? 1 : 0);		
}

void MainFrame::OnDisassembly()
{
	ToggleFrameWnd(RUNTIME_CLASS(DisassemFrame), DISASSEM_FRAME_ID);
}

void MainFrame::ToggleFrameWnd(CRuntimeClass *pClass, int id)
{
	CFrameWnd *pFrame;
	Emu6502App *pApp = (Emu6502App*)AfxGetApp();
	pFrame = (CFrameWnd*)pApp->GetState(id);
	if (pFrame == NULL) {
		pFrame = (CFrameWnd*)pClass->CreateObject();
		if (pFrame == NULL) {
			TRACE0("Failed to create frame window.\n");
			return;
		}
		pFrame->ShowWindow(SW_SHOW);
		pFrame->UpdateWindow();	
	} else {
		pFrame->DestroyWindow();
	}
}