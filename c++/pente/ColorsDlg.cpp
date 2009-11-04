// ColorsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pente.h"
#include "ColorsDlg.h"
#include "ColorChooserDlg.h"

// CColorsDlg dialog

IMPLEMENT_DYNAMIC(CColorsDlg, CDialog)

CColorsDlg::CColorsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorsDlg::IDD, pParent), m_ModFlags(0)
{

}

CColorsDlg::~CColorsDlg()
{
}

void CColorsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TABLE_COLOR, m_TableColor);
	DDX_Control(pDX, IDC_BOARD_COLOR, m_BoardColor);
	DDX_Control(pDX, IDC_GRID_COLOR, m_GridColor);
}


BEGIN_MESSAGE_MAP(CColorsDlg, CDialog)
	ON_BN_CLICKED(IDC_TABLE_COLOR, OnTableColor)
	ON_BN_CLICKED(IDC_BOARD_COLOR, OnBoardColor)
	ON_BN_CLICKED(IDC_GRID_COLOR, OnGridColor)
	ON_BN_CLICKED(IDOK, &CColorsDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CColorsDlg::OnTableColor() 
{
	CColorChooserDlg dlg(&m_TableColor);
	if (dlg.DoModal() == IDOK) {
		m_TableColor.SetFillColor(dlg.GetSelectedColor());
		m_ModFlags |= TABLE_COLOR;
	}
}

void CColorsDlg::OnBoardColor() 
{
	CColorChooserDlg dlg(&m_BoardColor);
	if (dlg.DoModal() == IDOK) {
		m_BoardColor.SetFillColor(dlg.GetSelectedColor());
		m_ModFlags |= BOARD_COLOR;
	}
}

void CColorsDlg::OnGridColor() 
{
	CColorChooserDlg dlg(&m_GridColor);
	if (dlg.DoModal() == IDOK) {
		m_GridColor.SetFillColor(dlg.GetSelectedColor());
		m_ModFlags |= GRID_COLOR;
	}
}


// CColorsDlg message handlers

BOOL CColorsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CWinApp *pApp = AfxGetApp();
	COLORREF tableColor = pApp->GetProfileInt(_T("Settings"), _T("TableColor"),
		GetSysColor(COLOR_APPWORKSPACE));
	m_TableColor.SetFillColor(tableColor);

	COLORREF boardColor = pApp->GetProfileInt(_T("Settings"), _T("BoardColor"),
		GetSysColor(COLOR_WINDOW));
	m_BoardColor.SetFillColor(boardColor);

	COLORREF gridColor = pApp->GetProfileInt(_T("Settings"), _T("GridColor"),
		GetSysColor(COLOR_WINDOWTEXT));
	m_GridColor.SetFillColor(gridColor);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CColorsDlg::OnBnClickedOk()
{
	CWinApp *pApp = AfxGetApp();
	if (m_ModFlags & TABLE_COLOR) {
		pApp->WriteProfileInt(_T("Settings"), _T("TableColor"), 
			m_TableColor.GetFillColor());
	}

	if (m_ModFlags & BOARD_COLOR) {
		pApp->WriteProfileInt(_T("Settings"), _T("BoardColor"), 
			m_BoardColor.GetFillColor());
	}

	if (m_ModFlags & GRID_COLOR) {
		pApp->WriteProfileInt(_T("Settings"), _T("GridColor"), 
			m_GridColor.GetFillColor());
	}

	if (m_ModFlags) {
		; // pApp->m_pMainWnd->SendMessage(WM_SETTING_CHANGE);
	}

	m_ModFlags = 0;

	/*
		TorrentExplorer *pApp = (TorrentExplorer*)AfxGetApp();
	if (m_ModFlags & BKGND_COLOR) {
		pApp->PutSetting("ui_bkgnd_color", m_BkgndColor.GetFillColor());
	}
	if (m_ModFlags & TEXT_COLOR) {
		pApp->PutSetting("ui_text_color", m_TextColor.GetFillColor());
	}
	if (m_ModFlags & GRID_COLOR) {
		pApp->PutSetting("ui_grid_color", m_GridColor.GetFillColor());
	}
	if (m_ModFlags & HILIGHT_COLOR) {
		pApp->PutSetting("ui_hilight_color", m_HilightColor.GetFillColor());
	}
	if (m_ModFlags & HILIGHT_BORDER_COLOR) {
		pApp->PutSetting("ui_hilight_border_color", m_HilightBorderColor.GetFillColor());
	}

	if (m_ModFlags)
		pApp->m_pMainWnd->SendMessage(WM_SETTING_CHANGE);

	m_ModFlags = 0;
	*/

	OnOK();
}
