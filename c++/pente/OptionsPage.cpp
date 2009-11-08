// OptionsPage.cpp : implementation file
//

#include "stdafx.h"
#include "pente.h"
#include "OptionsPage.h"
#include "PenteDoc.h"

// OptionsPage dialog

IMPLEMENT_DYNAMIC(OptionsPage, CPropertyPage)

OptionsPage::OptionsPage()
	: CPropertyPage(OptionsPage::IDD)
{	
	PenteApp *pApp = (PenteApp*)AfxGetApp();
	m_TwoPlayerGame = pApp->isTwoPlayerGame() ? 0 : 1;
}

OptionsPage::~OptionsPage()
{
}

void OptionsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_PLAYERVSPLAYER, m_TwoPlayerGame);
}

BEGIN_MESSAGE_MAP(OptionsPage, CPropertyPage)
	ON_BN_CLICKED(IDC_PLAYERVSPLAYER, &OptionsPage::OnPlayerVsPlayer)
	ON_BN_CLICKED(IDC_PLAYERVSCOMPUTER, &OptionsPage::OnPlayerVsComputer)
END_MESSAGE_MAP()

// OptionsPage message handlers

BOOL OptionsPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	PenteDoc *pDoc = (PenteDoc*)GetParentFrame()->GetActiveDocument();
	PenteBoard *pBoard = pDoc->getGame()->getBoard();

	GetDlgItem(IDC_PLAYERVSPLAYER)->EnableWindow(pBoard->isEmpty());
	GetDlgItem(IDC_PLAYERVSCOMPUTER)->EnableWindow(pBoard->isEmpty());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void OptionsPage::OnPlayerVsPlayer()
{
	int twoPlayerGame = m_TwoPlayerGame;

	UpdateData();
	
	if (twoPlayerGame != m_TwoPlayerGame)
		SetModified();
}

void OptionsPage::OnPlayerVsComputer()
{
	int twoPlayerGame = m_TwoPlayerGame;

	UpdateData();

	if (twoPlayerGame != m_TwoPlayerGame)
		SetModified();
}

BOOL OptionsPage::OnApply()
{
	PenteDoc *pDoc = (PenteDoc*)GetParentFrame()->GetActiveDocument();
	PenteBoard *pBoard = pDoc->getGame()->getBoard();

	if (pBoard->isEmpty()) {
		PenteApp *pApp = (PenteApp*)AfxGetApp();
		pApp->setTwoPlayerGame(m_TwoPlayerGame == 0);
		pApp->OnFileNew();
	}

	return CPropertyPage::OnApply();
}
