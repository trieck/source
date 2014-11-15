//////////////////////////////////////
// Module Name	:	DocViewDoc.cpp	//
// Author		:	Thomas A. Rieck //
// Purpose		:	Simple Document //
//					 - View Test	//
// Date			:	4/11/97			//
//////////////////////////////////////

#include "DocViewView.h"
#include "DocViewDoc.h"

IMPLEMENT_DYNCREATE(CDocViewDoc, CDocument)

///////////////////////////////////////////////////////////////////
// CDocViewDoc construction/destruction

CDocViewDoc::CDocViewDoc()
{
}

CDocViewDoc::~CDocViewDoc()
{
}

///////////////////////////////////////////////////////////////////
// CDocViewDoc::OnNewDocument()

BOOL CDocViewDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // SDI documents will reuse this document, initialize here...

    return TRUE;
}

///////////////////////////////////////////////////////////////////



