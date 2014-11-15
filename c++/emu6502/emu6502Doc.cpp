// emu6502Doc.cpp : implementation of the Emu6502Doc class
//

#include "stdafx.h"
#include "emu6502.h"

#include "emu6502Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Emu6502Doc

IMPLEMENT_DYNCREATE(Emu6502Doc, CDocument)

BEGIN_MESSAGE_MAP(Emu6502Doc, CDocument)
    //{{AFX_MSG_MAP(Emu6502Doc)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Emu6502Doc construction/destruction

Emu6502Doc::Emu6502Doc()
{
}

Emu6502Doc::~Emu6502Doc()
{
}

BOOL Emu6502Doc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    ((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

    return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// Emu6502Doc serialization

void Emu6502Doc::Serialize(CArchive& ar)
{
    ((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// Emu6502Doc diagnostics

#ifdef _DEBUG
void Emu6502Doc::AssertValid() const
{
    CDocument::AssertValid();
}

void Emu6502Doc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Emu6502Doc commands
