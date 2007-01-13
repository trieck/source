// backendsDoc.cpp : implementation of the BackendsDoc class
//

#include "stdafx.h"
#include "backends.h"
#include "backendsDoc.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace {
	const int MAX_SERVERLIST_SIZE = 4096;
	CString getProfilePath();

} // anonymous

/////////////////////////////////////////////////////////////////////////////
// BackendsDoc

IMPLEMENT_DYNCREATE(BackendsDoc, CDocument)

BEGIN_MESSAGE_MAP(BackendsDoc, CDocument)
	//{{AFX_MSG_MAP(BackendsDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BackendsDoc construction/destruction

BackendsDoc::BackendsDoc()
{
}

BackendsDoc::~BackendsDoc()
{
}

BOOL BackendsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	TCHAR servers[MAX_SERVERLIST_SIZE] = { 0 };

	GetPrivateProfileString(_T("machines"), NULL, _T(""), 
		servers, sizeof(servers) - 1, getProfilePath());

	LPCTSTR server = servers;
	for (int i = 0; *server; i++) {
		machines.push_back(server);
		server += _tcslen(server) + 1;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// BackendsDoc serialization

void BackendsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// BackendsDoc diagnostics

#ifdef _DEBUG
void BackendsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void BackendsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// BackendsDoc commands

void BackendsDoc::DeleteContents() 
{
	machines.clear();
	CDocument::DeleteContents();
}

/////////////////////////////////////////////////////////////////////////////
namespace {	// anonymous

/////////////////////////////////////////////////////////////////////////////
CString getProfilePath()
{
	TCHAR module[MAX_PATH + _MAX_FNAME + 1];
	GetModuleFileName(NULL, module, MAX_PATH + _MAX_FNAME);

	CString ininame = module;
	int nPosition = ininame.ReverseFind(_T('.'));
	ininame = ininame.Left(nPosition) + _T(".ini");

    if (_taccess(ininame, 0) != -1)
        return ininame;
    
	nPosition = ininame.ReverseFind('\\');
	ininame.Right(ininame.GetLength() - nPosition);

	return ininame;
}

} // anonymous
