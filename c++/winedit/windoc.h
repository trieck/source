// windoc.h : interface of the WinEditDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOC_H__7AAF9E79_A9FA_11D3_8900_000000000000__INCLUDED_)
#define AFX_WINDOC_H__7AAF9E79_A9FA_11D3_8900_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class WinEditDoc : public CDocument {
protected: // create from serialization only
	WinEditDoc();
	DECLARE_DYNCREATE(WinEditDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WinEditDoc)
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~WinEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(WinEditDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDOC_H__7AAF9E79_A9FA_11D3_8900_000000000000__INCLUDED_)

