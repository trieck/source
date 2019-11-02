#pragma once

// gripbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GripperBar window

class GripperBar : public CToolBar
{
// Construction
public:
    GripperBar();

// Attributes
public:

// Operations
public:
    BOOL CreateEx(CWnd* pParentWnd, DWORD dwCtrlStyle = TBSTYLE_FLAT,
                  DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
                  CRect rcBorders = CRect(0, 0, 0, 0), UINT nID = AFX_IDW_TOOLBAR);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(GripperBar)
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual int Create(CWnd *parent, UINT style);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~GripperBar();

    // Generated message map functions
protected:
    //{{AFX_MSG(GripperBar)
    afx_msg void OnPaint();
    afx_msg void OnNcPaint();
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
private:
    void CalcInsideRect(CRect& rect, BOOL bHorz) const;
    void DoPaint(CDC *pDC);
    void EraseNonClient();
    void DrawGripper(CDC* pDC, const CRect& rect);
    CSize CalcLayout(DWORD dwMode, int nLength = -1);
    void _GetButton(int nIndex, TBBUTTON* pButton) const;
    void _SetButton(int nIndex, TBBUTTON* pButton);
    CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
    CSize CalcDynamicLayout(int nLength, DWORD dwMode);
};

/////////////////////////////////////////////////////////////////////////////
