///////////////////////////////////////
// Module Name	:	SplitterDoc.cpp	 //
// Author		:	Thomas A. Rieck  //
// Purpose		:	Splitter Example //
// Date			:	4/11/97			 //
///////////////////////////////////////

#include "SplitterView.h"
#include "SplitterDoc.h"

IMPLEMENT_DYNCREATE(CSplitterDoc, CDocument)

///////////////////////////////////////////////////////////////////
// CSplitterDoc construction/destruction

CSplitterDoc::CSplitterDoc()
{
}

CSplitterDoc::~CSplitterDoc()
{
}

///////////////////////////////////////////////////////////////////
// CSplitterDoc::OnNewDocument()

BOOL CSplitterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// SDI documents will reuse this document, initialize here...

	return TRUE;
}

///////////////////////////////////////////////////////////////////



