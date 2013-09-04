
// CWIZARD.CPP

#include "cwizard.h"
#include "cpagethree.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(CWizard, CPropertySheet)
	ON_WM_CREATE()
END_MESSAGE_MAP()

CWizard::CWizard(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CWizard::CWizard(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

int CWizard::OnCreate(LPCREATESTRUCT lpcs)
{
	return (0);
}

int CWizard::GetRegInfo()
{
	HKEY hkMain, hkServer, hkDatabase, hkReportPath;
	DWORD dwType, dwLength;

	// buffers for strings
	BYTE szServerBuff[255];
	BYTE szDbBuff[255];
	BYTE szReportBuff[255];

	// open main key
	CString str;
	str.LoadString(IDS_REGMAINKEY);

	if (RegOpenKey(HKEY_LOCAL_MACHINE,
	               (LPCTSTR)str, &hkMain) != ERROR_SUCCESS)
		return(-1);

	// get registry information
	for (int i = 0; i < 3; i++) {
		switch (i) {
		case 0:				// server

			dwLength = 255;
			str.LoadString(IDS_REGSERVERKEY);
			if (RegOpenKey(hkMain,
			               (LPCTSTR)str, &hkServer) != ERROR_SUCCESS)
				return (-1);

			str.LoadString(IDS_SERVERVALUE);
			if (RegQueryValueEx(hkServer,
			                    (LPCTSTR)str, 0, &dwType,
			                    &szServerBuff[0],
			                    &dwLength) != ERROR_SUCCESS)
				return (-1);
			break;
		case 1:				// database

			dwLength = 255;
			str.LoadString(IDS_REGDBKEY);
			if (RegOpenKey(hkMain,
			               (LPCTSTR)str, &hkDatabase) != ERROR_SUCCESS)
				return (-1);

			str.LoadString(IDS_DBVALUE);
			if (RegQueryValueEx(hkDatabase,
			                    (LPCTSTR)str, 0, &dwType,
			                    &szDbBuff[0],
			                    &dwLength) != ERROR_SUCCESS)
				return (-1);
			break;
		case 2:				// report path

			dwLength = 255;
			str.LoadString(IDS_REGREPORTKEY);
			if (RegOpenKey(hkMain,
			               (LPCTSTR)str, &hkReportPath) != ERROR_SUCCESS)
				return (-1);

			str.LoadString(IDS_REPORTVALUE);
			if (RegQueryValueEx(hkReportPath,
			                    (LPCTSTR)str, 0, &dwType,
			                    &szReportBuff[0],
			                    &dwLength) != ERROR_SUCCESS)
				return (-1);
			break;
		}
	}

	// copy data into member variables
	m_rgi.sServerName = szServerBuff;
	m_rgi.sDatabaseName = szDbBuff;
	m_rgi.sReportPath = szReportBuff;

	// close reg keys
	RegCloseKey(hkMain);
	RegCloseKey(hkServer);
	RegCloseKey(hkDatabase);
	RegCloseKey(hkReportPath);
	return (0);
}

int CWizard::SetRegInfo()
{
	HKEY hkMain, hkServer, hkDatabase, hkReportPath;

	// make sure active page is page three
	ASSERT(GetActivePage()->IsKindOf(RUNTIME_CLASS(CPageThree)));

	// get a pointer to page three
	CPageThree* pPageThree = (CPageThree*)GetActivePage();
	ASSERT_VALID (pPageThree);

	// set initial progress value
	pPageThree->m_pProgress->SetPos(0);

	// open main key
	CString str;
	str.LoadString(IDS_REGMAINKEY);

	if (RegCreateKey(HKEY_LOCAL_MACHINE,
	                 (LPCTSTR)str, &hkMain) != ERROR_SUCCESS)
		return (-1);

	// update progress
	pPageThree->m_pProgress->SetPos(10);

	// create subkeys and set values
	for (int i = 0; i < 3; i++) {
		switch (i) {
		case 0: {	// server
			str.LoadString(IDS_REGSERVERKEY);
			if (RegCreateKey(hkMain,
			                 (LPCTSTR)str, &hkServer) != ERROR_SUCCESS)
				return (-1);

			// update progress
			pPageThree->m_pProgress->SetPos(20);

			str.LoadString(IDS_SERVERVALUE);
			if (RegSetValueEx(hkServer, (LPCTSTR)str, 0, REG_SZ,
			                  (CONST BYTE*)(LPCTSTR)m_rgi.sServerName, m_rgi.sServerName.GetLength()) != ERROR_SUCCESS)
				return(-1);

			// update progress
			pPageThree->m_pProgress->SetPos(30);
			break;
		}
		case 1: {	// database
			str.LoadString(IDS_REGDBKEY);
			if (RegCreateKey(hkMain,
			                 (LPCTSTR)str, &hkDatabase) != ERROR_SUCCESS)
				return (-1);

			// update progress
			pPageThree->m_pProgress->SetPos(40);

			str.LoadString(IDS_DBVALUE);
			if (RegSetValueEx(hkDatabase, (LPCTSTR)str, 0, REG_SZ,
			                  (CONST BYTE*)(LPCTSTR)m_rgi.sDatabaseName, m_rgi.sDatabaseName.GetLength()) != ERROR_SUCCESS)
				return(-1);

			// update progress
			pPageThree->m_pProgress->SetPos(50);
			break;
		}
		case 2: {	// report path
			str.LoadString(IDS_REGREPORTKEY);
			if (RegCreateKey(hkMain,
			                 (LPCTSTR)str, &hkReportPath) != ERROR_SUCCESS)
				return (-1);

			// update progress
			pPageThree->m_pProgress->SetPos(60);

			str.LoadString(IDS_REPORTVALUE);
			if (RegSetValueEx(hkReportPath, (LPCTSTR)str, 0, REG_SZ,
			                  (CONST BYTE*)(LPCTSTR)m_rgi.sReportPath, m_rgi.sReportPath.GetLength()) != ERROR_SUCCESS)
				return(-1);

			// update progress
			pPageThree->m_pProgress->SetPos(70);
			break;
		}
		}
	}
	RegCloseKey(hkMain);
	RegCloseKey(hkServer);
	RegCloseKey(hkDatabase);
	RegCloseKey(hkReportPath);
	return (0);
}

CWizard::~CWizard()
{
}
