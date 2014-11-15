// emu6502View.h : interface of the Emu6502View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMU6502VIEW_H__EB1C3E11_F7DF_4302_B6FF_B44B615C8194__INCLUDED_)
#define AFX_EMU6502VIEW_H__EB1C3E11_F7DF_4302_B6FF_B44B615C8194__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class Emu6502View : public CEditView {
protected: // create from serialization only
    Emu6502View();
    DECLARE_DYNCREATE(Emu6502View)

// Attributes
public:
    Emu6502Doc* GetDocument();

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(Emu6502View)
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnInitialUpdate();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~Emu6502View();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(Emu6502View)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    CFont m_Font;
};

#ifndef _DEBUG  // debug version in emu6502View.cpp
inline Emu6502Doc* Emu6502View::GetDocument()
{
    return (Emu6502Doc*)m_pDocument;
}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMU6502VIEW_H__EB1C3E11_F7DF_4302_B6FF_B44B615C8194__INCLUDED_)
