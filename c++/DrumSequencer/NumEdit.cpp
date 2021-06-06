#include "stdafx.h"
#include "NumEdit.h"

BEGIN_MESSAGE_MAP(NumEdit, CEdit)
        //{{AFX_MSG_MAP(NumEdit)
        ON_WM_CHAR()
        ON_WM_GETDLGCODE()
        ON_MESSAGE(WM_PASTE, OnPaste)
        ON_MESSAGE(WM_CONTEXTMENU, OnContextMenu)
        ON_WM_KILLFOCUS()
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

NumEdit::NumEdit() : m_minValue(0), m_maxValue(100)
{
}

void NumEdit::range(int& min, int& max) const
{
    min = m_minValue;
    max = m_maxValue;
}

void NumEdit::setRange(int min, int max)
{
    m_minValue = min;
    m_maxValue = max;
}


int NumEdit::value() const
{
    CString str;
    GetWindowText(str);
    return _ttoi(str);
}

void NumEdit::setValue(int val)
{
    if (val < m_minValue) {
        val = m_minValue;
    }

    if (val > m_maxValue) {
        val = m_maxValue;
    }

    CString str;
    str.Format(_T("%d"), val);

    SetWindowText(str);
}

LRESULT NumEdit::OnPaste(WPARAM, LPARAM)
{
    return 0;
}

LRESULT NumEdit::OnContextMenu(WPARAM, LPARAM)
{
    return 0;
}

void NumEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (nChar == VK_RETURN) {
        setValue();
        SetSel(0, -1, FALSE);
        GetParent()->SendMessage(WM_CHAR, nChar, MAKELPARAM(nRepCnt, nFlags));
    } else {
        CEdit::OnChar(nChar, nRepCnt, nFlags);
    }
}

UINT NumEdit::OnGetDlgCode()
{
    return CEdit::OnGetDlgCode() | DLGC_WANTALLKEYS;
}

void NumEdit::setValue()
{
    setValue(value());
}

void NumEdit::OnKillFocus(CWnd* pNewWnd)
{
    CEdit::OnKillFocus(pNewWnd);

    setValue();
    SetSel(0, -1, FALSE);
    (void)GetParent()->SendMessage(WM_CHAR, VK_RETURN, 0);
}
