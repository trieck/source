// wtlView.h : interface of the CWtlView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WTLVIEW_H__8721183E_C8AC_48B4_A7F2_0ED900FA46D3__INCLUDED_)
#define AFX_WTLVIEW_H__8721183E_C8AC_48B4_A7F2_0ED900FA46D3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CWtlView : public CWindowImpl<CWtlView, CTreeViewCtrl> {
public:
    DECLARE_WND_SUPERCLASS(NULL, CTreeViewCtrl::GetWndClassName())

    BOOL PreTranslateMessage(MSG* pMsg) {
        pMsg;
        return FALSE;
    }

    BEGIN_MSG_MAP(CWtlView)
    END_MSG_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WTLVIEW_H__8721183E_C8AC_48B4_A7F2_0ED900FA46D3__INCLUDED_)
