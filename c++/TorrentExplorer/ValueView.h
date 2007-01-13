#if !defined(AFX_VALUEVIEW_H__BE41C0B4_BA94_42A6_A5A6_3A6399B166C3__INCLUDED_)
#define AFX_VALUEVIEW_H__BE41C0B4_BA94_42A6_A5A6_3A6399B166C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ValueView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ValueView view

class ValueView : public CListView
{
protected:
	ValueView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(ValueView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ValueView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~ValueView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(ValueView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSettingChange(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void InsertInt(LPINTEGER i, LONG lHint);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VALUEVIEW_H__BE41C0B4_BA94_42A6_A5A6_3A6399B166C3__INCLUDED_)
