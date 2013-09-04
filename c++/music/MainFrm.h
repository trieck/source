// MainFrm.h : interface of the MainFrame class

//

/////////////////////////////////////////////////////////////////////////////



#if !defined(AFX_MAINFRM_H__F7CFDC37_51AB_11D4_89F0_00E098787497__INCLUDED_)

#define AFX_MAINFRM_H__F7CFDC37_51AB_11D4_89F0_00E098787497__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000



class MainFrame : public CFrameWnd

{



protected: // create from serialization only

	MainFrame();

	DECLARE_DYNCREATE(MainFrame)



// Attributes

public:



// Operations

public:



// Overrides

	// ClassWizard generated virtual function overrides

	//{{AFX_VIRTUAL(MainFrame)

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//}}AFX_VIRTUAL



// Implementation

public:

	virtual ~MainFrame();

#ifdef _DEBUG

	virtual void AssertValid() const;

	virtual void Dump(CDumpContext& dc) const;

#endif



protected:  // control bar embedded members

	CStatusBar  m_wndStatusBar;

	CReBar      m_wndReBar;

	CDialogBar  m_wndDlgBar;



// Generated message map functions

protected:

	//{{AFX_MSG(MainFrame)

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};



/////////////////////////////////////////////////////////////////////////////



//{{AFX_INSERT_LOCATION}}

// Microsoft Visual C++ will insert additional declarations immediately before the previous line.



#endif // !defined(AFX_MAINFRM_H__F7CFDC37_51AB_11D4_89F0_00E098787497__INCLUDED_)

