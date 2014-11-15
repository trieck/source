#if !defined(AFX_DIGITCTRLMGR_H__EAAD64F2_6E47_11D1_80C7_00207812120D__INCLUDED_)
#define AFX_DIGITCTRLMGR_H__EAAD64F2_6E47_11D1_80C7_00207812120D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DigitCtrlMgr.h : header file
//
#include "DigitCtrl.h"
////////////////////////////////////////////////////////////////////////////
// CDigitCtrlMgr window
class CDigitCtrlMgr : public CObject {
// Construction
public:
    CDigitCtrlMgr(CDialog*, const UINT Ctrls[], const RECT rcs[], UINT nCount);

// Attributes
public:
protected:
// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDigitCtrlMgr)
    //}}AFX_VIRTUAL

// Implementation
public:
    UINT GetCount();
    CDigitCtrl* GetControl(UINT);
    BOOL	SetValue(CString&);
    BOOL	Advance(UINT);
    virtual ~CDigitCtrlMgr();

    // Generated message map functions
protected:
    //{{AFX_MSG(CDigitCtrlMgr)
    // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG

private:
    CDialog*	m_pParent;							// Parent dialog box
    const UINT	m_nCount;							// Number of controls
    CObArray*	m_pArray;							// Array to hold digit controls
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIGITCTRLMGR_H__EAAD64F2_6E47_11D1_80C7_00207812120D__INCLUDED_)
