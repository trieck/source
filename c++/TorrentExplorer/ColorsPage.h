#if !defined(AFX_COLORSPAGE_H__37A986D2_5BDC_4D89_AAA0_E8925FA669AD__INCLUDED_)
#define AFX_COLORSPAGE_H__37A986D2_5BDC_4D89_AAA0_E8925FA669AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorsPage.h : header file
//

#include "ColorButton.h"

/////////////////////////////////////////////////////////////////////////////
// ColorsPage dialog

class ColorsPage : public CPropertyPage
{
    DECLARE_DYNCREATE(ColorsPage)

// Construction
public:
    ColorsPage();
    ~ColorsPage();

// Dialog Data
    //{{AFX_DATA(ColorsPage)
    enum { IDD = IDD_COLORS_PAGE };
    ColorButton	m_TextColor;
    ColorButton	m_GridColor;
    ColorButton	m_BkgndColor;
    ColorButton	m_HilightColor;
    ColorButton	m_HilightBorderColor;
    //}}AFX_DATA


// Overrides
    // ClassWizard generate virtual function overrides
    //{{AFX_VIRTUAL(ColorsPage)
public:
    virtual void OnOK();
    virtual BOOL OnApply();
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(ColorsPage)
    afx_msg void OnBkgndColor();
    afx_msg void OnGridColor();
    afx_msg void OnTextColor();
    virtual BOOL OnInitDialog();
    afx_msg void OnHilightColor();
    afx_msg void OnHilightBorder();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    enum {
        BKGND_COLOR = 1 << 0,
        TEXT_COLOR = 1 << 1,
        GRID_COLOR = 1 << 2,
        HILIGHT_COLOR = 1 << 3,
        HILIGHT_BORDER_COLOR = 1 << 4
    };
    DWORD m_ModFlags;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSPAGE_H__37A986D2_5BDC_4D89_AAA0_E8925FA669AD__INCLUDED_)
