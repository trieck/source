/*--------------------------------------
	Module:	CONNDLG.CPP
	Author:	Thomas A. Rieck
	Date:	06/22/97
----------------------------------------*/

#include "ConnDlg.h"
#include "WysApp.h"
#include "WysWnd.h"

BEGIN_MESSAGE_MAP(CConnDlg, CDialog)
	ON_COMMAND(ID_REFRESH, OnRefresh)
	ON_COMMAND(ID_TERMINATE, OnKillSocket)
END_MESSAGE_MAP()

CConnDlg :: CConnDlg(CWnd* pParentWnd) :
	CDialog(CConnDlg::IDD, pParentWnd)
{
}

CConnDlg :: ~CConnDlg()
{
}

BOOL CConnDlg :: OnInitDialog()
{
	// set active connections
	this->OnRefresh();

	// center the dialog
	this->CenterWindow();

	return (CDialog :: OnInitDialog());
}

void CConnDlg :: OnRefresh()
{
	CWysApp* pApp = (CWysApp*)AfxGetApp();

	// clear listbox
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LSTCONN);
	pListBox->ResetContent();

	// iterate through sockets
	// displaying connected items
	for (INT i = 0, j = 0; i < MAXCONN; i++) {
		if (pApp->pSockets[i]->State == CONNECTED) {
			// set IP address
			pListBox->AddString(pApp->pSockets[i]->IPAddress);

			// set socket descriptor value
			pListBox->SetItemData(j, pApp->pSockets[i]->m_hSocket);
			j++;
		}
	}
	return;
}

void CConnDlg :: OnKillSocket()
{
	CWysApp* pApp = (CWysApp*)AfxGetApp();
	INT iItem;
	CString szTemp;
	SCREENLINE sl;

	// get the current selection
	CWysWnd* pWnd = (CWysWnd*)pApp->m_pMainWnd;
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LSTCONN);

	iItem = pListBox->GetCurSel();

	if (iItem == LB_ERR) {
		szTemp.LoadString(IDS_NOSEL);
		this->MessageBox(szTemp, NULL, MB_ICONINFORMATION);
		return;
	}

	// get the socket value
	// for currently selected item
	SOCKET hSocket;
	hSocket = (SOCKET)pListBox->GetItemData(iItem);
	if (hSocket == LB_ERR) {
		szTemp.LoadString(IDS_SOCKERRLST);
		this->MessageBox(szTemp, NULL, MB_ICONINFORMATION);
		return;
	}

	szTemp.LoadString(IDS_KILLSOCK);
	if (this->MessageBox(szTemp, "Kill Connection", MB_ICONQUESTION |
	                     MB_YESNO | MB_DEFBUTTON2) == IDYES) {
		CWySock* pSock = (CWySock*)CAsyncSocket::FromHandle(hSocket);
		if (!pSock) {
			szTemp.LoadString(IDS_ERRNOSOCK);
			this->MessageBox(szTemp, NULL, MB_ICONINFORMATION);
			return;
		}

		// add item to screen list
		sl.uColor = COLOR_RED;
		szTemp.LoadString(IDS_SERVKILL);
		sl.szText.Format(szTemp, pSock->IPAddress);
		pWnd->AddListItem(&sl);

		// remove socket from array of connected sockets
		pSock->Close();
		pSock->m_hSocket	= INVALID_SOCKET;
		pSock->State		= FREE;

		//  refresh list
		OnRefresh();
	}
	return;
}