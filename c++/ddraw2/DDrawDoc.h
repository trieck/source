// DDrawDoc.h : interface of the DDrawDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDRAWDOC_H__A76F4DAA_E597_11D4_AE70_0008C7E97A92__INCLUDED_)
#define AFX_DDRAWDOC_H__A76F4DAA_E597_11D4_AE70_0008C7E97A92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class DDrawDoc : public CDocument {
protected: // create from serialization only
    DDrawDoc();
    DECLARE_DYNCREATE(DDrawDoc)

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(DDrawDoc)
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~DDrawDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(DDrawDoc)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDRAWDOC_H__A76F4DAA_E597_11D4_AE70_0008C7E97A92__INCLUDED_)
