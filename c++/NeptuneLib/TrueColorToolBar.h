/***=========================================================================
====                                                                     ====
====                          D C U t i l i t y                          ====
====                                                                     ====
=============================================================================
====                                                                     ====
====    File name           :  TrueColorToolBar.h                        ====
====    Project name        :  Tester                                    ====
====    Project number      :  ---                                       ====
====    Creation date       :  13/1/2003                                 ====
====    Author(s)           :  Dany Cantin                               ====
====                                                                     ====
====                  Copyright � DCUtility  2003                        ====
====                                                                     ====
=============================================================================
===========================================================================*/

#pragma once

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CTrueColorToolBar

class CTrueColorToolBar : public CToolBar
{
// Construction
public:
    CTrueColorToolBar();

// Attributes
private:
    BOOL m_bDropDown;

    struct stDropDownInfo {
    public:
        UINT  uButtonID;
        UINT  uMenuID;
        CWnd* pParent;
    };

    CArray <stDropDownInfo, stDropDownInfo&> m_lstDropDownButton;

// Operations
public:
    BOOL LoadTrueColorToolBar(int  nBtnWidth,
                              UINT uToolBar,
                              UINT uToolBarHot		= 0,
                              UINT uToolBarDisabled = 0);

    void AddDropDownButton(CWnd* pParent, UINT uButtonID, UINT uMenuID);

private:
    BOOL SetTrueColorToolBar(UINT uToolBarType,
                             UINT uToolBar,
                             int  nBtnWidth);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTrueColorToolBar)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CTrueColorToolBar();

    // Generated message map functions
protected:
    //{{AFX_MSG(CTrueColorToolBar)
    afx_msg void OnToolbarDropDown(NMHDR* pnmh, LRESULT* plRes);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
