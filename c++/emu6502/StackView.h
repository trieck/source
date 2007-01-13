#if !defined(AFX_STACKVIEW_H__9DEF6145_B418_4705_B81C_B75C08BF4026__INCLUDED_)
#define AFX_STACKVIEW_H__9DEF6145_B418_4705_B81C_B75C08BF4026__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StackView.h : header file
//

#include "MultirowView.h"

/////////////////////////////////////////////////////////////////////////////
// StackView view

class StackView : public MultirowView
{
protected:
	StackView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(StackView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StackView)
protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~StackView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(StackView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DrawStack(CDC *pDC);
	CString GetLine(USHORT i);
	CFont m_Font;					// text font	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STACKVIEW_H__9DEF6145_B418_4705_B81C_B75C08BF4026__INCLUDED_)
