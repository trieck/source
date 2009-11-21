// windumpDoc.h : interface of the WindumpDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDUMPDOC_H__84539594_821B_485F_A6C1_EF750FFD970F__INCLUDED_)
#define AFX_WINDUMPDOC_H__84539594_821B_485F_A6C1_EF750FFD970F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class WindumpDoc : public CDocument {
protected: // create from serialization only
	WindumpDoc();
	DECLARE_DYNCREATE(WindumpDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WindumpDoc)
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~WindumpDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(WindumpDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDUMPDOC_H__84539594_821B_485F_A6C1_EF750FFD970F__INCLUDED_)
