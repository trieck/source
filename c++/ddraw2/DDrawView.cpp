// DDrawView.cpp : implementation of the DDrawView class
//

#include "stdafx.h"
#include "ddraw2.h"

#include "DDrawDoc.h"
#include "DDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COLOR_BLACK			RGB(0x00, 0x00, 0x00)
#define COLOR_WHITE			RGB(0xFF, 0xFF, 0xFF)
#define COLOR_RED			RGB(0xE0, 0x40, 0x40)
#define COLOR_TURQUOISE		RGB(0x60, 0xFF, 0xFF)
#define COLOR_PURPLE		RGB(0xE0, 0x60, 0xE0)
#define COLOR_GREEN			RGB(0x40, 0xE0, 0x40)
#define COLOR_BLUE			RGB(0x40, 0x40, 0xE0)
#define COLOR_YELLOW		RGB(0xFF, 0xFF, 0x40)
#define COLOR_ORANGE		RGB(0xE0, 0xA0, 0x40)
#define COLOR_BROWN			RGB(0x9C, 0x74, 0x48)
#define COLOR_LTRED			RGB(0xFF, 0xA0, 0xA0)
#define COLOR_LTGREY		RGB(0x54, 0x54, 0x54)
#define COLOR_GREY			RGB(0x88, 0x88, 0x88)
#define COLOR_LTGREEN		RGB(0xA0, 0xFF, 0xA0)
#define COLOR_LTBLUE		RGB(0xA0, 0xA0, 0xFF)
#define COLOR_DKGREY		RGB(0xC0, 0xC0, 0xC0)

#define COLORS 0x10

static COLORREF colors[COLORS] = {
	COLOR_BLACK, COLOR_WHITE, COLOR_RED, COLOR_TURQUOISE, COLOR_PURPLE,
	COLOR_GREEN, COLOR_BLUE, COLOR_YELLOW, COLOR_ORANGE, COLOR_BROWN,
	COLOR_LTRED, COLOR_LTGREY, COLOR_GREY, COLOR_LTGREEN, COLOR_LTBLUE,
	COLOR_DKGREY
};

/////////////////////////////////////////////////////////////////////////////
// DDrawView

IMPLEMENT_DYNCREATE(DDrawView, CView)

BEGIN_MESSAGE_MAP(DDrawView, CView)
	//{{AFX_MSG_MAP(DDrawView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DDrawView construction/destruction

DDrawView::DDrawView()
 : pdds(NULL)
{
}

DDrawView::~DDrawView()
{
}

BOOL DDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// DDrawView drawing

void DDrawView::OnDraw(CDC* pDC)
{
	DDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// DDrawView diagnostics

#ifdef _DEBUG
void DDrawView::AssertValid() const
{
	CView::AssertValid();
}

void DDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

DDrawDoc* DDrawView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(DDrawDoc)));
	return (DDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// DDrawView message handlers

int DDrawView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	DDrawApp *pApp = (DDrawApp*)AfxGetApp();
	ASSERT_VALID(pApp);

	LPDIRECTDRAW pdd = pApp->GetDirectDraw();
	pdd->AddRef();

	DDSURFACEDESC ddsd;

	ZeroMemory(&ddsd, sizeof(DDSURFACEDESC));
	ddsd.dwSize = sizeof(DDSURFACEDESC);
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	ddsd.dwBackBufferCount = 1;
	
	// Create the primary surface with one back buffer 
	HRESULT hr = pdd->CreateSurface(&ddsd, &pdds, NULL);
	if (hr != DD_OK) {
		TRACE0("failed while creating direct draw surface.\n");
		pdd->Release();
		return -1;
	}	

	pdd->Release();
	
	return 0;
}

void DDrawView::OnDestroy() 
{
	CView::OnDestroy();

	if (NULL != pdds) {
		ULONG result = pdds->Release();
		if (0 != result)
			TRACE1("DirectDraw surface non zero [%d] on Release()!\n", result);
	}
}

void DDrawView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
}

BOOL DDrawView::OnEraseBkgnd(CDC* pDC) 
{
	return CView::OnEraseBkgnd(pDC);
}
