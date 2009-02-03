// WinADFDoc.cpp : implementation of the WinADFDoc class
//

#include "stdafx.h"
#include "WinADF.h"

#include "WinADFDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// WinADFDoc

IMPLEMENT_DYNCREATE(WinADFDoc, CDocument)

BEGIN_MESSAGE_MAP(WinADFDoc, CDocument)
END_MESSAGE_MAP()


// WinADFDoc construction/destruction

WinADFDoc::WinADFDoc()
{
	// TODO: add one-time construction code here

}

WinADFDoc::~WinADFDoc()
{
}

BOOL WinADFDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// WinADFDoc serialization

void WinADFDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// WinADFDoc diagnostics

#ifdef _DEBUG
void WinADFDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void WinADFDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// WinADFDoc commands
