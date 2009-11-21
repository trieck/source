///////////////////////////////////////
// Module Name	:	SplitterView.cpp //
// Author		:	Thomas A. Rieck  //
// Purpose		:	Splitter Example //
// Date			:	4/11/97			 //
///////////////////////////////////////

#include "SplitterFrame.h"
#include "SplitterView.h"

IMPLEMENT_DYNCREATE(CSplitterView, CListView)

BEGIN_MESSAGE_MAP(CSplitterView, CListView)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// Initialize static data members
LPCTSTR CSplitterView :: szHeaders[4] = {_T("Player One"), _T("Player Two"), _T("Winner"),
                                        _T("Date Time")
                                        };

///////////////////////////////////////////////////////////////////
// CSplitterView construction/destruction

CSplitterView::CSplitterView()
{
}

CSplitterView::~CSplitterView()
{
}

BOOL CSplitterView :: PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style = cs.style | WS_CLIPSIBLINGS | LVS_REPORT;
	return CListView :: PreCreateWindow(cs);
}


void CSplitterView::OnInitialUpdate()
{
}

INT	CSplitterView :: OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	INT nRtn, i;

	nRtn = CListView :: OnCreate(lpCreateStruct);

	// Set List View Backcolor
	GetListCtrl().SetBkColor(::GetSysColor(COLOR_WINDOW));

	// Add the columns
	for (i = 1; i < 5; i++)
		GetListCtrl().InsertColumn(i, szHeaders[i-1], LVCFMT_LEFT, 125);

	return nRtn;
}

