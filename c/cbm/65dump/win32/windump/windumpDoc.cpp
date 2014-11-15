// windumpDoc.cpp : implementation of the WindumpDoc class
//

#include "stdafx.h"
#include "windump.h"

#include "windumpDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// WindumpDoc

IMPLEMENT_DYNCREATE(WindumpDoc, CDocument)

BEGIN_MESSAGE_MAP(WindumpDoc, CDocument)
    //{{AFX_MSG_MAP(WindumpDoc)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WindumpDoc construction/destruction

WindumpDoc::WindumpDoc()
{
}

WindumpDoc::~WindumpDoc()
{
}

BOOL WindumpDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// WindumpDoc serialization

void WindumpDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
    } else {
    }
}

/////////////////////////////////////////////////////////////////////////////
// WindumpDoc diagnostics

#ifdef _DEBUG
void WindumpDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void WindumpDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// WindumpDoc commands
