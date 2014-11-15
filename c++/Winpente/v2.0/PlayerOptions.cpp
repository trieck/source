/*------------------------------------------
	Module Name	:	PlayerOptions.cpp
	Author		:	Thomas A. Rieck
	Purpose		:	Player Options Dialog
					implementation
	Date		:	09/01/1997
------------------------------------------*/

#include "stdafx.h"
#include "PlayerOptions.h"
#include "PenteDoc.h"
#include "MainFrame.h"
#include "OurConstants.h"

IMPLEMENT_DYNCREATE(CPlayerOptionsDlg, CDialog);

BEGIN_MESSAGE_MAP(CPlayerOptionsDlg, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()

CPlayerOptionsDlg :: CPlayerOptionsDlg() : CDialog(CPlayerOptionsDlg::IDD)
{
}

CPlayerOptionsDlg :: ~CPlayerOptionsDlg()
{
}

BOOL CPlayerOptionsDlg :: OnInitDialog()
{
    CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->GetMainWnd());
    ASSERT_VALID (pFrame);

    CPenteDoc* pDoc = (CPenteDoc*)(pFrame->GetActiveDocument());
    ASSERT_VALID(pDoc);

    UINT nSelection = (pDoc->GetPlayMode() == PLAYER_VS_PLAYER ?
                       IDC_PLAYERVSPLAYER : IDC_PLAYERVSCOMPUTER);

    CheckDlgButton(nSelection, 1);

    return CDialog::OnInitDialog();
}

VOID CPlayerOptionsDlg :: OnOK()
{
    CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->GetMainWnd());
    ASSERT_VALID (pFrame);

    CPenteDoc* pDoc = (CPenteDoc*)(pFrame->GetActiveDocument());
    ASSERT_VALID(pDoc);

    if (IsDlgButtonChecked(IDC_PLAYERVSPLAYER))
        pDoc->SetPlayMode(PLAYER_VS_PLAYER);
    else
        pDoc->SetPlayMode(PLAYER_VS_COMPUTER);

    CDialog::OnOK();
}

VOID CPlayerOptionsDlg :: OnPaint()
{
    CDialog::OnPaint();
}

