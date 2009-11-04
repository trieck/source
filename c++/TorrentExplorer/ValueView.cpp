// ValueView.cpp : implementation file
//

#include "stdafx.h"
#include "TorrentExplorer.h"
#include "TorrentObject.h"
#include "Dictionary.h"
#include "List.h"
#include "String.h"
#include "Integer.h"
#include "ValueView.h"
#include "SHA1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR headers[] = { 
	"Value"
};

namespace {	// anonymous

CString FormatInt(LPINTEGER i, LONG lHint);
CString Comma(__int64 i);

}	// anonymous

/////////////////////////////////////////////////////////////////////////////
// ValueView

IMPLEMENT_DYNCREATE(ValueView, CListView)

ValueView::ValueView()
{
}

ValueView::~ValueView()
{
}


BEGIN_MESSAGE_MAP(ValueView, CListView)
	//{{AFX_MSG_MAP(ValueView)
	ON_WM_CREATE()
	ON_MESSAGE(WM_SETTING_CHANGE, OnSettingChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ValueView drawing

void ValueView::OnDraw(CDC* pDC)
{
}

/////////////////////////////////////////////////////////////////////////////
// ValueView diagnostics

#ifdef _DEBUG
void ValueView::AssertValid() const
{
	CListView::AssertValid();
}

void ValueView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ValueView message handlers

int ValueView::OnCreate(LPCREATESTRUCT lpcs) 
{
	if (CListView::OnCreate(lpcs) == -1)
		return -1;

	CListCtrl &list = GetListCtrl();		
	list.SetExtendedStyle(/*LVS_EX_GRIDLINES | */LVS_EX_FULLROWSELECT);

	// Add the columns
	int ncols = sizeof(headers) / sizeof(LPCSTR);
	int nwidth = (lpcs->cx / ncols);
	
	for (int i = 0; i < ncols; i++) {
		list.InsertColumn(i, headers[i], LVCFMT_CENTER, 
			nwidth);	
	}

	OnSettingChange(0, 0);

	return 0;
}

BOOL ValueView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style = cs.style | WS_CLIPSIBLINGS | LVS_REPORT
		| LVS_SHOWSELALWAYS | LVS_NOSORTHEADER;
	
	return CListView::PreCreateWindow(cs);
}

void ValueView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CListCtrl& list = GetListCtrl();
	list.DeleteAllItems();

	LPTORRENTOBJECT elem = (LPTORRENTOBJECT)pHint;
	if (elem == NULL) return;

	switch (elem->GetElementType()) {
	case ET_STRING:
		list.InsertItem(0, *(LPSTRING)elem);
		break;
	case ET_INTEGER:
		InsertInt((LPINTEGER)elem, lHint);
		break;
	}
}

void ValueView::InsertInt(LPINTEGER i, LONG lHint)
{
	CListCtrl& list = GetListCtrl();
	list.InsertItem(0, FormatInt(i, lHint));
}

LRESULT ValueView::OnSettingChange(WPARAM wParam, LPARAM lParam)
{
	TorrentExplorer *pApp = (TorrentExplorer*)AfxGetApp();
	CListCtrl &list = GetListCtrl();
	if (pApp->IsSetting("ui_bkgnd_color")) {
		COLORREF bkgndColor = pApp->GetIntSetting("ui_bkgnd_color");
		list.SetBkColor(bkgndColor);
	}

	if (pApp->IsSetting("ui_text_color")) {
		COLORREF textColor = pApp->GetIntSetting("ui_text_color");
		list.SetTextColor(textColor);
	}
	
	list.RedrawWindow();

	return 0;
}

namespace {	// anonymous

CString FormatInt(LPINTEGER i, LONG lHint)
{
	CString output;

	if (lHint) {
		CTime t(*i);
		output = t.Format("%m/%d/%Y %I:%M:%S %p");
	} else {
		output = Comma(*i);
	}

	return output;
}

CString Comma(__int64 i)
{
	CString input, output;
	input.Format("%I64d", i);
	
	int n = input.GetLength();

    for (int j = n - 1, k = 1; j >= 0; j--, k++) {
        output += input[(int)j];
        if (k % 3 == 0 && j > 0 && j < n - 1)
            output += ',';
    }
	
	strrev(output.GetBuffer(output.GetLength()));
	output.ReleaseBuffer();

	return output;
}

}	// anonymous