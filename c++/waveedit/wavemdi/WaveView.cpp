//////////////////////////////////////
// Module Name	:	WaveView.cpp	//
// Author		:	Thomas A. Rieck //
// Purpose		:	Wave View 		//
//					Implementations	//
// Date			:	11/23/1997		//
//////////////////////////////////////

#include "WaveView.h"
#include "MainFrame.h"

// Initialize static data
LPCTSTR	CWaveView::m_lpszHeaders[] = {_T("File Name"),
                                      _T("Size in Bytes"),
                                      _T("Format"),
                                      _T("Mono / Stereo"),
                                      _T("Bytes / Second"),
                                      _T("Bits / Sample")
                                     };

IMPLEMENT_DYNCREATE(CWaveView, CListView)

BEGIN_MESSAGE_MAP(CWaveView, CListView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()
///////////////////////////////////////////////////////////////////
// CWaveView construction/destruction

CWaveView::CWaveView()
{
}

CWaveView::~CWaveView()
{
}

BOOL CWaveView :: PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT | LVS_NOSORTHEADER;	// Report style view
	return CListView :: PreCreateWindow(cs);
}

void CWaveView::OnInitialUpdate()
{
}

INT	CWaveView :: OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CListView :: OnCreate(lpCreateStruct);

	// Set Column information
	LV_COLUMN	lvc;

	for (UINT i = 0; i < 6; i++) {
		lvc.mask		= LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvc.fmt			= LVCFMT_CENTER;
		lvc.cx			= 100;
		lvc.pszText		= (LPTSTR)m_lpszHeaders[i];
		lvc.cchTextMax	= 0;

		GetListCtrl().InsertColumn(i, &lvc);
	}

	return 0;
}

VOID CWaveView :: OnSize(UINT nType, int cx, int cy)
{
}

VOID CWaveView :: OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
}
