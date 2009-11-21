/*--------------------------------------
	Module:	WYSAPP.H
	Author:	Thomas A. Rieck
	Date:	06/22/97
----------------------------------------*/
#ifndef __WYSAPP_H__
#define __WYSAPP_H__

#include <afxwin.h>
#include "WySock.h"

// CWinApp derived class
class CWysApp : public CWinApp {
protected:
	BOOL	m_bIsLogging;
	CString	m_szLogPath;
public:
	CWySock* pSockets[MAXCONN];
	CWysApp();
	DWORD AsyncListen();
	INT GetSocket();
	BOOL IsLogging();
	void SetLogging(BOOL bLogging);
	INT SetLoggingPath(CString& szLogPath);
	INT GetLoggingPath(CString& szLogPath);
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};
#endif // __WYSAPP_H__