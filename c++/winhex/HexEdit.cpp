// HexEdit.cpp : implementation file
//

#include "stdafx.h"
#include "winhex.h"
#include "HexEdit.h"
#include "HexDoc.h"
#include "HexView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CHARLIMIT 2

/////////////////////////////////////////////////////////////////////////////
// HexEdit

HexEdit::HexEdit()
{
    m_clrText = 0L;
    m_clrBkgnd = 0L;
    m_brBkgnd.CreateSolidBrush(m_clrBkgnd);
    memset(&m_LastChar, 0, sizeof(charStruct));
}

HexEdit::~HexEdit()
{
}


BEGIN_MESSAGE_MAP(HexEdit, CEdit)
    //{{AFX_MSG_MAP(HexEdit)
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_CREATE()
    ON_WM_KEYDOWN()
    ON_WM_CHAR()
    ON_CONTROL_REFLECT(EN_MAXTEXT, OnMaxtext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HexEdit message handlers

void HexEdit::SetBkColor(COLORREF clrBkgnd)
{
    m_clrBkgnd = clrBkgnd;

    if (m_brBkgnd.m_hObject)
        m_brBkgnd.DeleteObject();
    m_brBkgnd.CreateSolidBrush(m_clrBkgnd);
}

void HexEdit::SetTextColor(COLORREF clrText)
{
    m_clrText = clrText;
}

HBRUSH HexEdit::CtlColor(CDC* pDC, UINT nCtlColor)
{
    ASSERT_VALID(pDC);

    pDC->SetBkColor(m_clrBkgnd);
    pDC->SetTextColor(m_clrText);

    return m_brBkgnd;
}

int HexEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CEdit::OnCreate(lpCreateStruct) == -1)
        return -1;

    SetLimitText(CHARLIMIT);

    return 0;
}

BOOL HexEdit::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_CHAR) {
        char c = pMsg->wParam;
        if (!isxdigit(c))
            return TRUE;	// don't dispatch
    }

    return CEdit::PreTranslateMessage(pMsg);
}

void HexEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar) {
    case VK_TAB:
    case VK_UP:
    case VK_DOWN:
    case VK_LEFT:
    case VK_RIGHT:
    case VK_HOME:
    case VK_END:
    case VK_PRIOR:
    case VK_NEXT:
        GetParent()->SendMessage(WM_KEYDOWN, nChar, 0);
        return;
    default:
        break;
    }

    CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void HexEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    m_LastChar.nChar = nChar;
    m_LastChar.nRepCnt = nRepCnt;
    m_LastChar.nFlags = nFlags;

    CEdit::OnChar(nChar, nRepCnt, nFlags);

    HexView * pView = (HexView*)GetParent();
    ASSERT_VALID(pView);

    pView->SendMessage(WM_CHAR, nChar, MAKELPARAM(nRepCnt, nFlags));
}

void HexEdit::OnMaxtext()
{
    HexView * pView = (HexView*)GetParent();
    ASSERT_VALID(pView);

    // move to the next cell
    if (pView->NavigateCell(VK_RIGHT)) {
        SendMessage(WM_CHAR, m_LastChar.nChar,
                    MAKELPARAM(m_LastChar.nRepCnt, m_LastChar.nFlags));
    }
}
