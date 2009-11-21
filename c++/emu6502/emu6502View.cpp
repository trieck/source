// emu6502View.cpp : implementation of the Emu6502View class
//

#include "stdafx.h"
#include "emu6502.h"

#include "emu6502Doc.h"
#include "emu6502View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Emu6502View

IMPLEMENT_DYNCREATE(Emu6502View, CEditView)

BEGIN_MESSAGE_MAP(Emu6502View, CEditView)
	//{{AFX_MSG_MAP(Emu6502View)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Emu6502View construction/destruction

Emu6502View::Emu6502View()
{
}

Emu6502View::~Emu6502View()
{
}

BOOL Emu6502View::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// Emu6502View drawing

void Emu6502View::OnDraw(CDC* pDC)
{
	Emu6502Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// Emu6502View diagnostics

#ifdef _DEBUG
void Emu6502View::AssertValid() const
{
	CEditView::AssertValid();
}

void Emu6502View::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

Emu6502Doc* Emu6502View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Emu6502Doc)));
	return (Emu6502Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Emu6502View message handlers

void Emu6502View::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();
}

int Emu6502View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_Font.CreatePointFont(110, _T("Courier New"));
	SetFont(&m_Font);

	return 0;
}
