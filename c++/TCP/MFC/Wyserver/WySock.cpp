/*--------------------------------------
	Module:	WYSOCK.CPP
	Author:	Thomas A. Rieck
	Date:	06/22/97
----------------------------------------*/

#include "WySock.h"
#include "WysApp.h"
#include "WysWnd.h"
#include "resource.h"

CWySock :: CWySock()
{
	m_hSocket	= INVALID_SOCKET;
	State		= FREE;
	strcpy(IPAddress, "\0");
}

CWySock :: ~CWySock()
{
	m_hSocket	= INVALID_SOCKET;
	State		= FREE;
	strcpy(IPAddress, "\0");
}

void CWySock :: OnAccept(int nErrorCode)
{
	CWysApp* pApp = (CWysApp*)AfxGetApp();
	CWysWnd* pWnd = (CWysWnd*)pApp->m_pMainWnd;
	SCREENLINE sl;
	INT i;

	// make sure socket is listening
	if (this->State != LISTENING)
		return;

	if (nErrorCode == WSAENETDOWN) {
		sl.uColor = COLOR_RED;
		sl.szText.LoadString(GetLastError());
		pWnd->AddListItem(&sl);
		return;
	}

	// find a free socket
	if ((i = pApp->GetSocket()) == NOTFOUND) {
		// no space to accept this connection. however will accept
		// just using simple socket variable and close. Otherwise
		// client program will think it is connected.
		CAsyncSocket sdTemp;
		Accept(sdTemp, NULL,NULL);
		sdTemp.Close();
		sl.uColor = COLOR_RED;
		sl.szText.LoadString(IDS_NOMORESOCKETS);
		pWnd->AddListItem(&sl);
		return;
	}

	// accept the incoming connection
	SOCKADDR_IN		acc_sin;
	INT				acc_sin_len;
	CWySock* pSock	= pApp->pSockets[i];
	acc_sin_len		= sizeof(acc_sin);

	this->Accept(*pSock, (LPSOCKADDR)&acc_sin,
	             (LPINT)&acc_sin_len);

	if (pSock->m_hSocket == INVALID_SOCKET) {
		sl.uColor = COLOR_RED;
		sl.szText.LoadString(IDS_ACCEPTERR);
		pWnd->AddListItem(&sl);
		return;
	}

	CString szTemp;

	sl.uColor = COLOR_BLUE;
	szTemp.LoadString(IDS_ACCEPTCONNECT);
	strcpy(pSock->IPAddress, inet_ntoa(acc_sin.sin_addr));
	pSock->State = CONNECTED;
	sl.szText.Format(szTemp, pSock->IPAddress);
	pWnd->AddListItem(&sl);

	return;
}

void CWySock :: OnClose (int nErrorCode)
{
	CWysWnd* pWnd = (CWysWnd*)AfxGetApp()->m_pMainWnd;
	SCREENLINE sl;
	CString szTemp;

	sl.uColor = COLOR_RED;
	szTemp.LoadString(IDS_CONNDROP);
	sl.szText.Format(szTemp, this->IPAddress);
	pWnd->AddListItem(&sl);

	// remove socket from array of connected sockets
	this->Close();
	this->m_hSocket = INVALID_SOCKET;
	this->State	= FREE;

	return;
}

void CWySock :: OnReceive(int nErrorCode)
{
	CWysWnd* pWnd = (CWysWnd*)AfxGetApp()->m_pMainWnd;

	if (this->State != CONNECTED)
		return;

	// turn off FD_READ event until
	// receive algorithm completes
	this->AsyncSelect(FD_CLOSE);

	INT iRc;
	SCREENLINE sl;
	CString szTemp;

	iRc = this->Receive((LPVOID)&Request, sizeof(REQUEST), 0);

	if (iRc == SOCKET_ERROR) {
		if ((iRc = GetLastError()) != WSAEWOULDBLOCK) {
			sl.uColor	= COLOR_RED;
			szTemp.LoadString(IDS_RCVERR);
			sl.szText.Format(szTemp, this->IPAddress);
			pWnd->AddListItem(&sl);
			return;
		}
	}

	// check for segmented command
	if (iRc != sizeof(REQUEST)) {
		sl.uColor = COLOR_RED;
		szTemp.LoadString(IDS_SEGMENTERR);
		sl.szText.Format(szTemp, this->IPAddress);
		pWnd->AddListItem(&sl);
		return;
	}

	// turn notification back on
	this->AsyncSelect(FD_ACCEPT | FD_READ | FD_CLOSE);

	// set response message
	RESPONSE rsp;
	rsp.cType		= RSP;
	rsp.cSubType	= this->Request.cSubType;
	rsp.cDetails	= this->Request.cDetails;
	rsp.cError		= SUCCESS;

	// parse the message request
	switch (this->Request.cType) {
		DWORD	dwRtn;
		DWORD	nSecPerClust, nBytesPerSec,
		nNumFreeClust, nTotalNumClust;

	case GET:
		if (this->Request.cSubType == DISK) {	// disk info
			switch (this->Request.cDetails) {
			case ENUMDRIVES:
				// get drive information
				dwRtn = GetLogicalDriveStrings(MAXMSGSPEC, rsp.cMsgSpec);

				if (dwRtn > MAXMSGSPEC) {
					rsp.iMsgLen = htons(0);
					rsp.cError = ERROREXEC;
				} else {
					rsp.iMsgLen	= htons(LOWORD(dwRtn));
					sl.uColor = COLOR_GREEN;
				}

				break;
			case DISKINFO:
				// find the disk free space information

				// expecting message specific
				// data to include null terminated
				// root path in format "C:\".
				// if length of message specific
				// data is not (3) then an error
				// occcured.
				DISKINFOSTRUCT dis;

				if (strlen(this->Request.cMsgSpec) != 3)
					break;

				if (!(GetDiskFreeSpace(this->Request.cMsgSpec,
				                       &nSecPerClust,
				                       &nBytesPerSec,
				                       &nNumFreeClust,
				                       &nTotalNumClust))) {
					rsp.iMsgLen = htons(0);
					rsp.cError	= ERROREXEC;
				} else {
					// calculate total bytes
					// and total free bytes
					dis.lTotalBytes	= htonl(nTotalNumClust * nSecPerClust * nBytesPerSec);
					dis.lFreeBytes	= htonl(nNumFreeClust * nSecPerClust * nBytesPerSec);

					rsp.iMsgLen	= htons(sizeof(DISKINFOSTRUCT));
					memcpy((LPDISKINFOSTRUCT)rsp.cMsgSpec, &dis, sizeof(DISKINFOSTRUCT));
					rsp.cError	= SUCCESS;
				}
				break;
			}
		}
		break;
	case PUT:
		break;
	default:
		rsp.cError	= ERRORBADCMD;
		break;
	}

	// show message notification
	if (rsp.cError != SUCCESS) {
		sl.uColor	= COLOR_RED;
		szTemp.LoadString(IDS_REQEXECERR);
	} else {
		sl.uColor	= COLOR_GREEN;
		szTemp.LoadString(IDS_REQSUCCESS);
	}

	sl.szText.Format(szTemp, this->IPAddress);
	pWnd->AddListItem(&sl);

	// send the response message

	iRc = this->Send((LPVOID)&rsp, sizeof(RESPONSE), 0);
	if (iRc == SOCKET_ERROR || iRc < sizeof(RESPONSE)) {
		sl.uColor = COLOR_RED;
		szTemp.LoadString(IDS_SENDERR);
		sl.szText.Format(szTemp, this->IPAddress);
		pWnd->AddListItem(&sl);
	}

	return;
}