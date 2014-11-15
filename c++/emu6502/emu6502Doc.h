// emu6502Doc.h : interface of the Emu6502Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMU6502DOC_H__964DE314_96CB_4EAF_B6C2_AAA993AC0981__INCLUDED_)
#define AFX_EMU6502DOC_H__964DE314_96CB_4EAF_B6C2_AAA993AC0981__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class Emu6502Doc : public CDocument {
protected: // create from serialization only
    Emu6502Doc();
    DECLARE_DYNCREATE(Emu6502Doc)

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(Emu6502Doc)
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~Emu6502Doc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(Emu6502Doc)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMU6502DOC_H__964DE314_96CB_4EAF_B6C2_AAA993AC0981__INCLUDED_)
