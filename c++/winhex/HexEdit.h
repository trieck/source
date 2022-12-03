#if !defined(AFX_HEXEDIT_H__091BB775_A13E_11D3_88ED_000000000000__INCLUDED_)
#define AFX_HEXEDIT_H__091BB775_A13E_11D3_88ED_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HexEdit.h : header file
//

using charStruct = struct
{
    UINT nChar;
    UINT nRepCnt;
    UINT nFlags;
};

/////////////////////////////////////////////////////////////////////////////
// HexEdit window

class HexEdit : public CEdit
{
    // Construction
public:
    HexEdit();

    // Attributes
    // Operations
    void SetTextColor(COLORREF clrText);
    void SetBkColor(COLORREF clrBkgnd);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(HexEdit)
    BOOL PreTranslateMessage(MSG* pMsg) override;
    //}}AFX_VIRTUAL

    // Implementation
    ~HexEdit() override;

    // Generated message map functions
protected:
    //{{AFX_MSG(HexEdit)
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnMaxtext();
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

private:
    COLORREF m_clrText;
    COLORREF m_clrBkgnd;
    CBrush m_brBkgnd;
    charStruct m_LastChar{};
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXEDIT_H__091BB775_A13E_11D3_88ED_000000000000__INCLUDED_)
