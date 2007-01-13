// DDrawDoc.cpp : implementation of the DDrawDoc class
//

#include "stdafx.h"
#include "ddraw2.h"

#include "DDrawDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DDrawDoc

IMPLEMENT_DYNCREATE(DDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(DDrawDoc, CDocument)
	//{{AFX_MSG_MAP(DDrawDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DDrawDoc construction/destruction

DDrawDoc::DDrawDoc()
{
}

DDrawDoc::~DDrawDoc()
{
}

BOOL DDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// DDrawDoc serialization

void DDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// DDrawDoc diagnostics

#ifdef _DEBUG
void DDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void DDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

