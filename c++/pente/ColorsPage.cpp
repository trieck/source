// ColorsPage.cpp : implementation file
//

#include "stdafx.h"
#include "pente.h"
#include "ColorsPage.h"
#include "ColorChooserDlg.h"
#include "PenteBoard.h"
#include "PenteDoc.h"

// CColorsPage dialog

IMPLEMENT_DYNAMIC(CColorsPage, CPropertyPage)

BEGIN_MESSAGE_MAP(CColorsPage, CPropertyPage)
	ON_BN_CLICKED(IDC_TABLE_COLOR, OnTableColor)
	ON_BN_CLICKED(IDC_BOARD_COLOR, OnBoardColor)
	ON_BN_CLICKED(IDC_GRID_COLOR, OnGridColor)
	ON_BN_CLICKED(IDC_PLAYER_ONE_COLOR, OnPlayerOneColor)
	ON_BN_CLICKED(IDC_PLAYER_TWO_COLOR, OnPlayerTwoColor)
	ON_BN_CLICKED(IDDEFAULT, &CColorsPage::OnBnClickedDefault)
END_MESSAGE_MAP()

CColorsPage::CColorsPage()
	: CPropertyPage(CColorsPage::IDD), m_ModFlags(0)
{
}

CColorsPage::~CColorsPage()
{
}

void CColorsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TABLE_COLOR, m_TableColor);
	DDX_Control(pDX, IDC_BOARD_COLOR, m_BoardColor);
	DDX_Control(pDX, IDC_GRID_COLOR, m_GridColor);
	DDX_Control(pDX, IDC_PLAYER_ONE_COLOR, m_PlayerOneColor);
	DDX_Control(pDX, IDC_PLAYER_TWO_COLOR, m_PlayerTwoColor);
	DDX_Control(pDX, IDDEFAULT, m_Default);
}

// CColorsPage message handlers

void CColorsPage::OnTableColor() 
{
	CColorChooserDlg dlg(&m_TableColor);
	if (dlg.DoModal() == IDOK) {
		m_TableColor.SetFillColor(dlg.GetSelectedColor());
		m_ModFlags |= TABLE_COLOR;
		SetModified();
	}
}

void CColorsPage::OnBoardColor() 
{
	CColorChooserDlg dlg(&m_BoardColor);
	if (dlg.DoModal() == IDOK) {
		m_BoardColor.SetFillColor(dlg.GetSelectedColor());
		m_ModFlags |= BOARD_COLOR;
		SetModified();
	}
}

void CColorsPage::OnGridColor() 
{
	CColorChooserDlg dlg(&m_GridColor);
	if (dlg.DoModal() == IDOK) {
		m_GridColor.SetFillColor(dlg.GetSelectedColor());
		m_ModFlags |= GRID_COLOR;
		SetModified();
	}
}

void CColorsPage::OnPlayerOneColor() 
{
	CColorChooserDlg dlg(&m_PlayerOneColor);
	if (dlg.DoModal() == IDOK) {
		m_PlayerOneColor.SetFillColor(dlg.GetSelectedColor());
		m_ModFlags |= PLAYER_ONE_COLOR;
		SetModified();
	}
}

void CColorsPage::OnPlayerTwoColor() 
{
	CColorChooserDlg dlg(&m_PlayerTwoColor);
	if (dlg.DoModal() == IDOK) {
		m_PlayerTwoColor.SetFillColor(dlg.GetSelectedColor());
		m_ModFlags |= PLAYER_TWO_COLOR;
		SetModified();
	}
}

BOOL CColorsPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	CWinApp *pApp = AfxGetApp();
	COLORREF tableColor = pApp->GetProfileInt(_T("Settings"), _T("TableColor"),
		PenteBoard::DEFAULT_TABLE_COLOR);
	m_TableColor.SetFillColor(tableColor);

	COLORREF boardColor = pApp->GetProfileInt(_T("Settings"), _T("BoardColor"),
		PenteBoard::DEFAULT_BOARD_COLOR);
	m_BoardColor.SetFillColor(boardColor);

	COLORREF gridColor = pApp->GetProfileInt(_T("Settings"), _T("GridColor"),
		PenteBoard::DEFAULT_GRID_COLOR);
	m_GridColor.SetFillColor(gridColor);

	COLORREF playerOneColor = pApp->GetProfileInt(_T("Settings"), 
		_T("PlayerOneColor"), PenteBoard::DEFAULT_PLAYER_ONE_COLOR);
	m_PlayerOneColor.SetFillColor(playerOneColor);

	COLORREF playerTwoColor = pApp->GetProfileInt(_T("Settings"), 
		_T("PlayerTwoColor"),
		PenteBoard::DEFAULT_PLAYER_TWO_COLOR);
	m_PlayerTwoColor.SetFillColor(playerTwoColor);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CColorsPage::OnApply()
{
	CWinApp *pApp = AfxGetApp();
	PenteDoc *doc = (PenteDoc*)GetParentFrame()->GetActiveDocument();
	PenteBoard *board = doc->getGame()->getBoard();

	if (m_ModFlags & TABLE_COLOR) {
		pApp->WriteProfileInt(_T("Settings"), _T("TableColor"), 
			m_TableColor.GetFillColor());
	}

	if (m_ModFlags & BOARD_COLOR) {
		pApp->WriteProfileInt(_T("Settings"), _T("BoardColor"), 
			m_BoardColor.GetFillColor());
		board->setBackgroundColor(m_BoardColor.GetFillColor());
	}

	if (m_ModFlags & GRID_COLOR) {
		pApp->WriteProfileInt(_T("Settings"), _T("GridColor"), 
			m_GridColor.GetFillColor());
		board->setGridColor(m_GridColor.GetFillColor());
	}

	if (m_ModFlags & PLAYER_ONE_COLOR) {
		pApp->WriteProfileInt(_T("Settings"), _T("PlayerOneColor"), 
			m_PlayerOneColor.GetFillColor());
		board->setPlayerOneColor(m_PlayerOneColor.GetFillColor());
	}

	if (m_ModFlags & PLAYER_TWO_COLOR) {
		pApp->WriteProfileInt(_T("Settings"), _T("PlayerTwoColor"), 
			m_PlayerTwoColor.GetFillColor());
		board->setPlayerTwoColor(m_PlayerTwoColor.GetFillColor());
	}

	if (m_ModFlags) {
		pApp->m_pMainWnd->SendMessage(WM_APPSETTING_CHANGE);
		doc->UpdateAllViews(NULL);
	}

	m_ModFlags = 0;

	return CPropertyPage::OnApply();
}

void CColorsPage::OnBnClickedDefault()
{
	m_TableColor.SetFillColor(PenteBoard::DEFAULT_TABLE_COLOR);
	m_BoardColor.SetFillColor(PenteBoard::DEFAULT_BOARD_COLOR);
	m_GridColor.SetFillColor(PenteBoard::DEFAULT_GRID_COLOR);
	m_PlayerOneColor.SetFillColor(PenteBoard::DEFAULT_PLAYER_ONE_COLOR);
	m_PlayerTwoColor.SetFillColor(PenteBoard::DEFAULT_PLAYER_TWO_COLOR);
	
	m_ModFlags |= TABLE_COLOR | BOARD_COLOR | GRID_COLOR | 
		PLAYER_ONE_COLOR | PLAYER_TWO_COLOR;
	SetModified();
}
