#if !defined(AFX_DIGITWND_H__EAAD64F1_6E47_11D1_80C7_00207812120D__INCLUDED_)
#define AFX_DIGITWND_H__EAAD64F1_6E47_11D1_80C7_00207812120D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DigitCtrl.h : header file
//
#include "stdafx.h"
/////////////////////////////////////////////////////////////////////////////
// CDigitCtrl window

class CDigitCtrl : public CWnd {
// Construction
public:
    CDigitCtrl();

// Attributes
public:

    // Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDigitCtrl)
    //}}AFX_VIRTUAL

// Implementation
public:
    VOID SetBackColor(COLORREF lColor);
    BOOL			SetValue(UINT);
    inline	UINT	GetCurrentDigit() {
        return m_nCurrentDigit;
    }
    virtual VOID	DrawDigit(CDC*);
    VOID			SetNextDigit();
    virtual			~CDigitCtrl();

    // Generated message map functions
protected:
    COLORREF m_lBackColor;
    afx_msg	VOID	OnPaint();

    //{{AFX_MSG(CDigitCtrl)
    // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
private:
    UINT	m_nCurrentDigit;
    static	const UINT nBitmaps[10];

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIGITWND_H__EAAD64F1_6E47_11D1_80C7_00207812120D__INCLUDED_)
