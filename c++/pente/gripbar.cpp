// gripbar.cpp : implementation file
//
#include "stdafx.h"
#include "pente.h"
#include "gripbar.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CX_GRIPPER  3
#define CY_GRIPPER  3
#define CX_BORDER_GRIPPER 2
#define CY_BORDER_GRIPPER 2

#define CX_SEPARATOR	1
#define CY_SEPARATOR	1

#define CX_GRIPPER_SIZE (CX_BORDER_GRIPPER+CX_GRIPPER+CX_SEPARATOR+CX_GRIPPER)
#define CY_GRIPPER_SIZE (CY_BORDER_GRIPPER+CY_GRIPPER+CY_SEPARATOR+CY_GRIPPER)

struct AFX_DLLVERSIONINFO {
    DWORD cbSize;
    DWORD dwMajorVersion;                   // Major version
    DWORD dwMinorVersion;                   // Minor version
    DWORD dwBuildNumber;                    // Build number
    DWORD dwPlatformID;                     // DLLVER_PLATFORM_*
};

typedef HRESULT (CALLBACK* AFX_DLLGETVERSIONPROC)(AFX_DLLVERSIONINFO *);
#ifdef _AFXDLL
int _afxComCtlVersion = -1;
int _afxDropDownWidth = -1;

int AFXAPI _AfxGetDropDownWidth()
{
    // return cached version if already determined...
    if (_afxDropDownWidth != -1)
        return _afxDropDownWidth;
    // otherwise calculate it...
    HDC hDC = GetDC(NULL);
    ASSERT(hDC != NULL);
    HFONT hFont;
    if ((hFont = CreateFont(GetSystemMetrics(SM_CYMENUCHECK), 0, 0, 0,
                            FW_NORMAL, 0, 0, 0, SYMBOL_CHARSET, 0, 0, 0, 0, _T("Marlett"))) != NULL)
        hFont = (HFONT)SelectObject(hDC, hFont);
    VERIFY(GetCharWidth(hDC, '6', '6', &_afxDropDownWidth));
    if (hFont != NULL) {
        SelectObject(hDC, hFont);
        DeleteObject(hFont);
    }
    ReleaseDC(NULL, hDC);
    ASSERT(_afxDropDownWidth != -1);
    return _afxDropDownWidth;
}

DWORD AFXAPI _AfxGetComCtlVersion()
{
    // return cached version if already determined...
    if (_afxComCtlVersion != -1)
        return _afxComCtlVersion;
    // otherwise determine comctl32.dll version via DllGetVersion
    HINSTANCE hInst = ::GetModuleHandleA("COMCTL32.DLL");
    ASSERT(hInst != NULL);
    AFX_DLLGETVERSIONPROC pfn;
    pfn = (AFX_DLLGETVERSIONPROC)GetProcAddress(hInst, "DllGetVersion");
    DWORD dwVersion = VERSION_WIN4;
    if (pfn != NULL) {
        AFX_DLLVERSIONINFO dvi;
        memset(&dvi, 0, sizeof(dvi));
        dvi.cbSize = sizeof(dvi);
        HRESULT hr = (*pfn)(&dvi);
        if (SUCCEEDED(hr)) {
            ASSERT(dvi.dwMajorVersion <= 0xFFFF);
            ASSERT(dvi.dwMinorVersion <= 0xFFFF);
            dwVersion = MAKELONG(dvi.dwMinorVersion, dvi.dwMajorVersion);
        }
    }
    _afxComCtlVersion = dwVersion;
    return dwVersion;
}
#else
extern int _afxComCtlVersion;
extern int _afxDropDownWidth;
extern int AFXAPI _AfxGetDropDownWidth();
#endif // _AFXDLL

/////////////////////////////////////////////////////////////////////////////
// GripperBar

GripperBar::GripperBar()
{
}

GripperBar::~GripperBar()
{
}

BEGIN_MESSAGE_MAP(GripperBar, CToolBar)
    //{{AFX_MSG_MAP(GripperBar)
    ON_WM_PAINT()
    ON_WM_NCPAINT()
    ON_WM_NCCALCSIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// GripperBar message handlers

BOOL GripperBar::PreCreateWindow(CREATESTRUCT& cs)
{
    return CToolBar::PreCreateWindow(cs);
}
/////////////////////////////////////////////////////////////////////////////
int GripperBar::Create(CWnd *parent, UINT style)
{
    return CreateEx(parent, TBSTYLE_FLAT, style |= CBRS_GRIPPER);
}
/////////////////////////////////////////////////////////////////////////////
void GripperBar::CalcInsideRect(CRect& rect, BOOL bHorz) const
{
    ASSERT_VALID(this);
    DWORD dwStyle = m_dwStyle;
    if (dwStyle & CBRS_BORDER_LEFT)
        rect.left += afxData.cxBorder2;
    if (dwStyle & CBRS_BORDER_TOP)
        rect.top += afxData.cyBorder2;
    if (dwStyle & CBRS_BORDER_RIGHT)
        rect.right -= afxData.cxBorder2;
    if (dwStyle & CBRS_BORDER_BOTTOM)
        rect.bottom -= afxData.cyBorder2;
    // inset the top and bottom.
    if (bHorz) {
        rect.left += m_cxLeftBorder;
        rect.top += m_cyTopBorder;
        rect.right -= m_cxRightBorder;
        rect.bottom -= m_cyBottomBorder;
        if ((m_dwStyle & (CBRS_GRIPPER|CBRS_FLOATING)) == CBRS_GRIPPER)
            rect.left += CX_GRIPPER_SIZE;
    } else {
        rect.left += m_cyTopBorder;
        rect.top += m_cxLeftBorder;
        rect.right -= m_cyBottomBorder;
        rect.bottom -= m_cxRightBorder;
        if ((m_dwStyle & (CBRS_GRIPPER|CBRS_FLOATING)) == CBRS_GRIPPER)
            rect.top += CY_GRIPPER_SIZE;
    }
}
/////////////////////////////////////////////////////////////////////////////
void GripperBar::OnPaint()
{
    if (m_bDelayedButtonLayout)
        Layout();
    Default();
}
/////////////////////////////////////////////////////////////////////////////
void GripperBar::OnNcPaint()
{
    EraseNonClient();
}
/////////////////////////////////////////////////////////////////////////////
void GripperBar::DoPaint(CDC *pDC)
{
    ASSERT_VALID(this);
    ASSERT_VALID(pDC);
    // paint inside client area
    CRect rect;
    GetClientRect(rect);
    DrawBorders(pDC, rect);
    DrawGripper(pDC, rect);
}
/////////////////////////////////////////////////////////////////////////////
void GripperBar::EraseNonClient()
{
    // get window DC that is clipped to the non-client area
    CWindowDC dc(this);
    CRect rectClient;
    GetClientRect(rectClient);
    CRect rectWindow;
    GetWindowRect(rectWindow);
    ScreenToClient(rectWindow);
    rectClient.OffsetRect(-rectWindow.left, -rectWindow.top);
    dc.ExcludeClipRect(rectClient);
    // draw borders in non-client area
    rectWindow.OffsetRect(-rectWindow.left, -rectWindow.top);
    DrawBorders(&dc, rectWindow);
    // erase parts not drawn
    dc.IntersectClipRect(rectWindow);
    SendMessage(WM_ERASEBKGND, (WPARAM)dc.m_hDC);
    // draw gripper in non-client area
    DrawGripper(&dc, rectWindow);
}
/////////////////////////////////////////////////////////////////////////////
void GripperBar::DrawGripper(CDC* pDC, const CRect& rect)
{
    // only draw the gripper if not floating and gripper is specified
    if ((m_dwStyle & (CBRS_GRIPPER|CBRS_FLOATING)) == CBRS_GRIPPER) {
        // draw the gripper in the border
        if (m_dwStyle & CBRS_ORIENT_HORZ) {
            pDC->Draw3dRect(rect.left+CX_BORDER_GRIPPER,
                            rect.top+m_cyTopBorder + 1,
                            CX_GRIPPER, rect.Height()-m_cyTopBorder-m_cyBottomBorder - 2,
                            afxData.clrBtnHilite, afxData.clrBtnShadow);
            pDC->Draw3dRect(rect.left + CX_BORDER_GRIPPER + CX_GRIPPER + CX_SEPARATOR,
                            rect.top+m_cyTopBorder + 1,
                            CX_GRIPPER, rect.Height()-m_cyTopBorder-m_cyBottomBorder - 2,
                            afxData.clrBtnHilite, afxData.clrBtnShadow);
        } else {
            pDC->Draw3dRect(rect.left+m_cyTopBorder + 1,
                            rect.top+CY_BORDER_GRIPPER,
                            rect.Width()-m_cyTopBorder-m_cyBottomBorder - 2, CY_GRIPPER,
                            afxData.clrBtnHilite, afxData.clrBtnShadow);
            pDC->Draw3dRect(rect.left+m_cyTopBorder + 1,
                            rect.top+CY_BORDER_GRIPPER + CY_GRIPPER + CY_SEPARATOR,
                            rect.Width()-m_cyTopBorder-m_cyBottomBorder - 2, CY_GRIPPER,
                            afxData.clrBtnHilite, afxData.clrBtnShadow);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////
void GripperBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
    // calculate border space (will add to top/bottom, subtract from right/bottom)
    CRect rect;
    rect.SetRectEmpty();
    BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
    CalcInsideRect(rect, bHorz);
    ASSERT(_afxComCtlVersion != -1);
    ASSERT(_afxComCtlVersion >= VERSION_IE4 || rect.top >= 2);
    // adjust non-client area for border space
    lpncsp->rgrc[0].left += rect.left;
    lpncsp->rgrc[0].top += rect.top;
    // previous versions of COMCTL32.DLL had a built-in 2 pixel border
    if (_afxComCtlVersion < VERSION_IE4)
        lpncsp->rgrc[0].top -= 2;
    lpncsp->rgrc[0].right += rect.right;
    lpncsp->rgrc[0].bottom += rect.bottom;
}

struct _AFX_CONTROLPOS {
    int nIndex, nID;
    CRect rectOldPos;
};
/////////////////////////////////////////////////////////////////////////////
CSize GripperBar::CalcLayout(DWORD dwMode, int nLength)
{
    ASSERT_VALID(this);
    ASSERT(::IsWindow(m_hWnd));
    if (dwMode & LM_HORZDOCK)
        ASSERT(dwMode & LM_HORZ);
    int nCount;
    TBBUTTON* pData = NULL;
    CSize sizeResult(0,0);
    //BLOCK: Load Buttons
    {
        nCount = (int)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
        if (nCount != 0) {
            int i;
            pData = new TBBUTTON[nCount];
            for (i = 0; i < nCount; i++)
                _GetButton(i, &pData[i]);
        }
    }
    if (nCount > 0) {
        if (!(m_dwStyle & CBRS_SIZE_FIXED)) {
            BOOL bDynamic = m_dwStyle & CBRS_SIZE_DYNAMIC;
            if (bDynamic && (dwMode & LM_MRUWIDTH))
                SizeToolBar(pData, nCount, m_nMRUWidth);
            else if (bDynamic && (dwMode & LM_HORZDOCK))
                SizeToolBar(pData, nCount, 32767);
            else if (bDynamic && (dwMode & LM_VERTDOCK))
                SizeToolBar(pData, nCount, 0);
            else if (bDynamic && (nLength != -1)) {
                CRect rect;
                rect.SetRectEmpty();
                CalcInsideRect(rect, (dwMode & LM_HORZ));
                BOOL bVert = (dwMode & LM_LENGTHY);
                int nLen = nLength + (bVert ? rect.Height() : rect.Width());
                SizeToolBar(pData, nCount, nLen, bVert);
            } else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
                SizeToolBar(pData, nCount, m_nMRUWidth);
            else
                SizeToolBar(pData, nCount, (dwMode & LM_HORZ) ? 32767 : 0);
        }
        sizeResult = CalcSize(pData, nCount);
        if (dwMode & LM_COMMIT) {
            _AFX_CONTROLPOS* pControl = NULL;
            int nControlCount = 0;
            BOOL bIsDelayed = m_bDelayedButtonLayout;
            m_bDelayedButtonLayout = FALSE;
            int i;
            for (i = 0; i < nCount; i++)
                if ((pData[i].fsStyle & TBSTYLE_SEP) && (pData[i].idCommand != 0))
                    nControlCount++;
            if (nControlCount > 0) {
                pControl = new _AFX_CONTROLPOS[nControlCount];
                nControlCount = 0;
                for (int i = 0; i < nCount; i++) {
                    if ((pData[i].fsStyle & TBSTYLE_SEP) && (pData[i].idCommand != 0)) {
                        pControl[nControlCount].nIndex = i;
                        pControl[nControlCount].nID = pData[i].idCommand;
                        CRect rect;
                        GetItemRect(i, &rect);
                        ClientToScreen(&rect);
                        pControl[nControlCount].rectOldPos = rect;
                        nControlCount++;
                    }
                }
            }
            if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
                m_nMRUWidth = sizeResult.cx;
            for (i = 0; i < nCount; i++)
                _SetButton(i, &pData[i]);
            if (nControlCount > 0) {
                for (int i = 0; i < nControlCount; i++) {
                    CWnd* pWnd = GetDlgItem(pControl[i].nID);
                    if (pWnd != NULL) {
                        CRect rect;
                        pWnd->GetWindowRect(&rect);
                        CPoint pt = rect.TopLeft() - pControl[i].rectOldPos.TopLeft();
                        GetItemRect(pControl[i].nIndex, &rect);
                        pt = rect.TopLeft() + pt;
                        pWnd->SetWindowPos(NULL, pt.x, pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
                    }
                }
                delete[] pControl;
            }
            m_bDelayedButtonLayout = bIsDelayed;
        }
        delete[] pData;
    }
    //BLOCK: Adjust Margins
    {
        CRect rect;
        rect.SetRectEmpty();
        CalcInsideRect(rect, (dwMode & LM_HORZ));
        sizeResult.cy -= rect.Height();
        sizeResult.cx -= rect.Width();
        CSize size = CControlBar::CalcFixedLayout((dwMode & LM_STRETCH), (dwMode & LM_HORZ));
        sizeResult.cx = max(sizeResult.cx, size.cx);
        sizeResult.cy = max(sizeResult.cy, size.cy);
    }
    return sizeResult;
}
/////////////////////////////////////////////////////////////////////////////
void GripperBar::_GetButton(int nIndex, TBBUTTON* pButton) const
{
    GripperBar* pBar = (GripperBar*)this;
    VERIFY(pBar->DefWindowProc(TB_GETBUTTON, nIndex, (LPARAM)pButton));
    // TBSTATE_ENABLED == TBBS_DISABLED so invert it
    pButton->fsState ^= TBSTATE_ENABLED;
}
/////////////////////////////////////////////////////////////////////////////
void GripperBar::_SetButton(int nIndex, TBBUTTON* pButton)
{
    // get original button state
    TBBUTTON button;
    VERIFY(DefWindowProc(TB_GETBUTTON, nIndex, (LPARAM)&button));
    // prepare for old/new button comparsion
    button.bReserved[0] = 0;
    button.bReserved[1] = 0;
    // TBSTATE_ENABLED == TBBS_DISABLED so invert it
    pButton->fsState ^= TBSTATE_ENABLED;
    pButton->bReserved[0] = 0;
    pButton->bReserved[1] = 0;
    // nothing to do if they are the same
    if (memcmp(pButton, &button, sizeof(TBBUTTON)) != 0) {
        // don't redraw everything while setting the button
        DWORD dwStyle = GetStyle();
        ModifyStyle(WS_VISIBLE, 0);
        VERIFY(DefWindowProc(TB_DELETEBUTTON, nIndex, 0));
        VERIFY(DefWindowProc(TB_INSERTBUTTON, nIndex, (LPARAM)pButton));
        ModifyStyle(0, dwStyle & WS_VISIBLE);
        // invalidate appropriate parts
        if (((pButton->fsStyle ^ button.fsStyle) & TBSTYLE_SEP) ||
                ((pButton->fsStyle & TBSTYLE_SEP) && pButton->iBitmap != button.iBitmap)) {
            // changing a separator
            Invalidate();
        } else {
            // invalidate just the button
            CRect rect;
            if (DefWindowProc(TB_GETITEMRECT, nIndex, (LPARAM)&rect))
                InvalidateRect(rect);
        }
    }
}

CSize GripperBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
    DWORD dwMode = bStretch ? LM_STRETCH : 0;
    dwMode |= bHorz ? LM_HORZ : 0;
    return CalcLayout(dwMode);
}

CSize GripperBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
    if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
            ((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK))) {
        return CalcFixedLayout(dwMode & LM_STRETCH, dwMode & LM_HORZDOCK);
    }
    return CalcLayout(dwMode, nLength);
}

BOOL GripperBar::CreateEx(CWnd* pParentWnd, DWORD dwCtrlStyle, DWORD dwStyle, CRect rcBorders, UINT nID)
{
    // initialize common controls
    VERIFY(AfxDeferRegisterClass(AFX_WNDCOMMCTL_BAR_REG));
    _AfxGetComCtlVersion();
    ASSERT(_afxComCtlVersion != -1);
    _AfxGetDropDownWidth();
    ASSERT(_afxDropDownWidth != -1);
    return CToolBar::CreateEx(pParentWnd, dwCtrlStyle, dwStyle, rcBorders, nID);
}

