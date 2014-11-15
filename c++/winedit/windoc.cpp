// windoc.cpp : implementation of the WinEditDoc class
//

#include "stdafx.h"
#include "winedit.h"

#include "windoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// WinEditDoc

IMPLEMENT_DYNCREATE(WinEditDoc, CDocument)

BEGIN_MESSAGE_MAP(WinEditDoc, CDocument)
    //{{AFX_MSG_MAP(WinEditDoc)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WinEditDoc construction/destruction

WinEditDoc::WinEditDoc()
{
}

WinEditDoc::~WinEditDoc()
{
}

BOOL WinEditDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    ((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

    return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// WinEditDoc serialization

void WinEditDoc::Serialize(CArchive& ar)
{
    ((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// WinEditDoc diagnostics

#ifdef _DEBUG
void WinEditDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void WinEditDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// WinEditDoc commands

