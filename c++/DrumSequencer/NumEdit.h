#pragma once
#include <afxwin.h>

///////////////////////////////////////////////////////////////////////
class NumEdit : public CEdit
{
public:
    NumEdit();
    virtual ~NumEdit() = default;

    virtual void range(int& min, int& max) const;
    virtual void setRange(int min, int max);

    virtual int value() const;
    virtual void setValue(int val);

private:
DECLARE_MESSAGE_MAP()

    //{{AFX_MSG(NumEdit)
    afx_msg LRESULT OnPaste(WPARAM, LPARAM);
    afx_msg LRESULT OnContextMenu(WPARAM, LPARAM);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg UINT OnGetDlgCode();
    //}}AFX_MSG

    void setValue();
    int m_minValue, m_maxValue;
public:
    afx_msg void OnKillFocus(CWnd* pNewWnd);
};
