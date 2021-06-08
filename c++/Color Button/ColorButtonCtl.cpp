// ColorButtonCtl.cpp : Implementation of the CColorButtonCtrl OLE control class.

#include "stdafx.h"
#include "ColorButtonApp.h"
#include "ColorButtonCtl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CColorButtonCtrl, COleControl)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CColorButtonCtrl, COleControl)
        //{{AFX_MSG_MAP(CColorButtonCtrl)
        ON_WM_LBUTTONDBLCLK()
        ON_WM_LBUTTONDOWN()
        ON_WM_LBUTTONUP()
        ON_WM_MOUSEMOVE()
        ON_WM_KILLFOCUS()
        ON_WM_SETFOCUS()
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CColorButtonCtrl, COleControl)
        //{{AFX_DISPATCH_MAP(CColorButtonCtrl)
        DISP_PROPERTY_EX(CColorButtonCtrl, "BevelWidth", GetBevelWidth, SetBevelWidth, VT_I2)
        DISP_STOCKPROP_FONT()
        DISP_STOCKPROP_ENABLED()
        DISP_PROPERTY_EX_ID(CColorButtonCtrl, "BackColor", DISPID_BACKCOLOR, GetBackColor, SetBackColor, VT_COLOR)
        DISP_PROPERTY_EX_ID(CColorButtonCtrl, "ForeColor", DISPID_FORECOLOR, GetForeColor, SetForeColor, VT_COLOR)
        DISP_PROPERTY_EX_ID(CColorButtonCtrl, "Caption", DISPID_CAPTION, GetCaption, SetCaption, VT_BSTR)
        //}}AFX_DISPATCH_MAP
        DISP_FUNCTION_ID(CColorButtonCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CColorButtonCtrl, COleControl)
        //{{AFX_EVENT_MAP(CColorButtonCtrl)
        EVENT_STOCK_CLICK()
        //}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages
/////////////////////////////////////////////////////////////////////////////


// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CColorButtonCtrl, "COLORBUTTON.ColorButtonCtrl.1",
                       0xa3afc616, 0xb347, 0x11d0, 0x97, 0xf7, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version
IMPLEMENT_OLETYPELIB(CColorButtonCtrl, _tlid, _wVerMajor, _wVerMinor)

/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DColorButton = { 0xa3afc614, 0xb347, 0x11d0, { 0x97, 0xf7, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DColorButtonEvents = {
    0xa3afc615, 0xb347, 0x11d0, { 0x97, 0xf7, 0x44, 0x45, 0x53, 0x54, 0, 0 }
};

/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwColorButtonOleMisc =
    OLEMISC_ACTIVATEWHENVISIBLE |
    OLEMISC_SETCLIENTSITEFIRST |
    OLEMISC_INSIDEOUT |
    OLEMISC_CANTLINKINSIDE |
    OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CColorButtonCtrl, IDS_COLORBUTTON, _dwColorButtonOleMisc)

/////////////////////////////////////////////////////////////////////////////
// CColorButtonCtrl::CColorButtonCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CColorButtonCtrl

BOOL CColorButtonCtrl::CColorButtonCtrlFactory::UpdateRegistry(BOOL bRegister)
{
    if (bRegister) {
        return AfxOleRegisterControlClass(
            AfxGetInstanceHandle(),
            m_clsid,
            m_lpszProgID,
            IDS_COLORBUTTON,
            IDB_COLORBUTTON,
            FALSE, //  Not insertable
            _dwColorButtonOleMisc,
            _tlid,
            _wVerMajor,
            _wVerMinor);
    }

    return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

/////////////////////////////////////////////////////////////////////////////
// CColorButtonCtrl::CColorButtonCtrl - Constructor

CColorButtonCtrl::CColorButtonCtrl()
{
    InitializeIIDs(&IID_DColorButton, &IID_DColorButtonEvents);

    // initialize data members
    m_bDown = FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CColorButtonCtrl::~CColorButtonCtrl - Destructor

/////////////////////////////////////////////////////////////////////////////
// CColorButtonCtrl::OnDraw - Drawing function

void CColorButtonCtrl::OnDraw(
    CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
    DrawControl(*pdc, (CRect&)rcBounds);
}

/////////////////////////////////////////////////////////////////////////////
// CColorButtonCtrl::DoPropExchange - Persistence support

void CColorButtonCtrl::DoPropExchange(CPropExchange* pPX)
{
    ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));

    COleControl::DoPropExchange(pPX);

    // Call PX_ functions for each persistent custom property.
    PX_Short(pPX, _T("BevelWidth"), m_BevelWidth, 2);
    PX_Color(pPX, _T("BackColor"), m_BackColor, ::GetSysColor(COLOR_BTNFACE));
    PX_Color(pPX, _T("ForeColor"), m_ForeColor, ::GetSysColor(COLOR_BTNTEXT));
    PX_String(pPX, _T("Caption"), m_sCaption, AmbientDisplayName());
}

/////////////////////////////////////////////////////////////////////////////
// CColorButtonCtrl::OnResetState - Reset control to default state

void CColorButtonCtrl::OnResetState()
{
    COleControl::OnResetState(); // Resets defaults found in DoPropExchange
}

/////////////////////////////////////////////////////////////////////////////
// CColorButtonCtrl::AboutBox - Display an "About" box to the user

void CColorButtonCtrl::AboutBox()
{
    CDialog dlgAbout(IDD_ABOUTBOX_COLORBUTTON);
    dlgAbout.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CColorButtonCtrl message handlers

void CColorButtonCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    OnLButtonDown(nFlags, point);
}

void CColorButtonCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    // call the base class handler
    COleControl::OnLButtonDown(nFlags, point);

    CRect rc;
    CDC* pDC = GetDC();

    // set down flag
    m_bDown = TRUE;

    // set mouse capture
    SetCapture();

    GetClientRect(&rc);

    DrawButtonDown(pDC, rc);

    ReleaseDC(pDC);
}

void CColorButtonCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
    CRect rc;
    CDC* pDC = GetDC();

    // set down flag
    m_bDown = FALSE;

    // release mouse capture
    ReleaseCapture();

    GetClientRect(&rc);

    DrawButtonUp(pDC, rc);

    ReleaseDC(pDC);

    // call the base class handler
    COleControl::OnLButtonUp(nFlags, point);
}

void CColorButtonCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
    static BOOL bHaveDrawnUp = FALSE;
    static BOOL bHaveDrawnDown = FALSE;

    CDC* pDC = GetDC();

    // get button rect
    CRect rc;
    GetClientRect(&rc);

    // check whether the button is down
    if (m_bDown) {
        // check whether mouse pointer is over button
        if (rc.PtInRect(point)) {
            bHaveDrawnUp = FALSE;
            if (!bHaveDrawnDown) {
                DrawButtonDown(pDC, rc);
                bHaveDrawnDown = TRUE;
            }
        } else {
            bHaveDrawnDown = FALSE;
            if (!bHaveDrawnUp) {
                DrawButtonUp(pDC, rc);
                bHaveDrawnUp = TRUE;
            }
        }
    } else {
        bHaveDrawnUp = FALSE;
        bHaveDrawnDown = FALSE;
    }
    ReleaseDC(pDC);
}

void CColorButtonCtrl::DrawControl(CDC& dc, const CRect& rc)
{
    // paint the button rect
    CBrush br(m_BackColor), *pbrOld;
    CRect rcClip;

    dc.GetClipBox(&rcClip);
    pbrOld = dc.SelectObject(&br);

    dc.PatBlt(rcClip.left, rcClip.top, (rcClip.right - rcClip.left),
              (rcClip.bottom - rcClip.top), PATCOPY);

    dc.SelectObject(pbrOld);

    // draw bevel
    DrawBevelRaised(&dc, rc);

    // draw caption
    DrawCaption(&dc, rc, GetEnabled() ? m_ForeColor : ::GetSysColor(COLOR_GRAYTEXT));

    // draw the frame
    if (this == GetFocus()) {
        CBrush br(::GetSysColor(COLOR_3DDKSHADOW));
        FrameButton(br);
    }
}

void CColorButtonCtrl::DrawBevelRaised(CDC* pDC, const CRect& rc)
{
    CPen penLight(PS_SOLID, 1, ::GetSysColor(COLOR_3DHILIGHT));

    CPen penShadow(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));

    DrawBevel(pDC, rc, penLight, penShadow);
}

void CColorButtonCtrl::DrawCaption(CDC* pDC, const CRect& rc, COLORREF lColor)
{
    int cx = 0;
    int cy = 0;
    CSize size;

    // set font
    CFont* pOldFont;
    pOldFont = SelectFontObject(pDC, InternalGetFont());

    // get the bounds of the caption text
    ::GetTextExtentPoint32(
        pDC->m_hDC, // handle of device context
        m_sCaption, // address of text string
        m_sCaption.GetLength(), // number of characters in string
        &size); // address of size structure

    cx = (rc.left + rc.right) / 2 - size.cx / 2;
    cy = (rc.top + rc.bottom) / 2 - size.cy / 2;

    // offset clipping region
    CRgn rgn;
    rgn.CreateRectRgn(rc.left + m_BevelWidth + 1, rc.top + m_BevelWidth + 1,
                      rc.right - m_BevelWidth - 1, rc.bottom - m_BevelWidth - 1);

    pDC->SelectClipRgn(&rgn);

    // make text background transparent
    pDC->SetBkMode(TRANSPARENT);

    // etch the caption if disabled
    if (!GetEnabled()) {
        pDC->SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
        pDC->TextOut(cx + 1, cy + 1, m_sCaption);
    }

    // set text color
    pDC->SetTextColor(lColor);

    // set panel caption
    pDC->TextOut(cx, cy, m_sCaption);

    // release font
    pDC->SelectObject(pOldFont);

    // delete region
    DeleteObject(&rgn);
}

void CColorButtonCtrl::DrawBevel(CDC* pDC, const CRect& rc, CPen& pen1, CPen& pen2)
{
    int i = 0;
    // draw bevel top and left

    // the top
    int cxLeft = rc.left;
    int cy = rc.top;
    int cxRight = rc.right + 1;

    // select new pen into DC for drawing; save old pen
    CPen* pPenOld = pDC->SelectObject(&pen1);

    // draw the bevel
    for (i = 0; i < m_BevelWidth; i++) {
        pDC->MoveTo(cxLeft++, cy);
        pDC->LineTo(cxRight--, cy++);
    }

    // the left
    int cx = rc.left;
    int cyTop = rc.top;
    int cyBottom = rc.bottom + 1;

    for (i = 0; i < m_BevelWidth; i++) {
        pDC->MoveTo(cx, cyTop++);
        pDC->LineTo(cx++, cyBottom--);
    }

    // draw the bottom and right

    // the bottom
    cxLeft = rc.left;
    cy = rc.bottom - 1;
    cxRight = rc.right;

    // select new pen into DC for drawing
    pDC->SelectObject(&pen2);

    // draw the bevel
    for (i = 0; i < m_BevelWidth; i++) {
        pDC->MoveTo(cxLeft++, cy);
        pDC->LineTo(cxRight--, cy--);
    }

    // the right
    cx = rc.right - 1;
    cyTop = rc.top;
    cyBottom = rc.bottom;

    for (i = 0; i < m_BevelWidth; i++) {
        pDC->MoveTo(cx, cyTop++);
        pDC->LineTo(cx--, cyBottom--);
    }

    // restore original pen
    pDC->SelectObject(pPenOld);
}

void CColorButtonCtrl::DrawButtonDown(CDC* pDC, const CRect& rc)
{
    // draw button down
    DrawBevelInset(pDC, rc);

    // erase caption
    DrawCaption(pDC, rc, m_BackColor);

    // move caption and redraw
    CRect rcTemp;
    CopyRect(rcTemp, rc);
    rcTemp.OffsetRect(1, 1);

    DrawCaption(pDC, rcTemp, m_ForeColor);
}

void CColorButtonCtrl::DrawBevelInset(CDC* pDC, const CRect& rc)
{
    CPen penLight(PS_SOLID, 1, ::GetSysColor(COLOR_3DHILIGHT));
    CPen penShadow(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));

    DrawBevel(pDC, rc, penShadow, penLight);
}

void CColorButtonCtrl::DrawButtonUp(CDC* pDC, const CRect& rc)
{
    // draw button up
    DrawBevelRaised(pDC, rc);

    // erase caption
    CRect rcTemp;
    CopyRect(rcTemp, rc);
    rcTemp.OffsetRect(1, 1);
    DrawCaption(pDC, rcTemp, m_BackColor);

    // redraw caption
    rcTemp.OffsetRect(-1, -1);
    DrawCaption(pDC, rcTemp, m_ForeColor);

    // draw the frame
    if (this == GetFocus()) {
        CBrush br(::GetSysColor(COLOR_3DDKSHADOW));
        FrameButton(br);
    }
}

OLE_COLOR CColorButtonCtrl::GetBackColor()
{
    return m_BackColor;
}

void CColorButtonCtrl::SetBackColor(OLE_COLOR nNewValue)
{
    m_BackColor = nNewValue;
    InvalidateControl();
    SetModifiedFlag();
}

OLE_COLOR CColorButtonCtrl::GetForeColor()
{
    return m_ForeColor;
}

void CColorButtonCtrl::SetForeColor(OLE_COLOR nNewValue)
{
    m_ForeColor = nNewValue;
    InvalidateControl();
    SetModifiedFlag();
}


BSTR CColorButtonCtrl::GetCaption()
{
    return m_sCaption.AllocSysString();
}

void CColorButtonCtrl::SetCaption(LPCTSTR lpszNewValue)
{
    m_sCaption = lpszNewValue;
    InvalidateControl();
    SetModifiedFlag();
}

void CColorButtonCtrl::OnKillFocus(CWnd* pNewWnd)
{
    COleControl::OnKillFocus(pNewWnd);

    InvalidateControl();
}

void CColorButtonCtrl::OnSetFocus(CWnd* pOldWnd)
{
    CBrush br(::GetSysColor(COLOR_3DDKSHADOW));

    FrameButton(br);

    COleControl::OnSetFocus(pOldWnd);
}

short CColorButtonCtrl::GetBevelWidth()
{
    return (m_BevelWidth);
}

void CColorButtonCtrl::SetBevelWidth(short nNewValue)
{
    if (nNewValue < 1 || nNewValue > 10) {
        CString str;
        str.LoadString(IDS_BEVELERROR);
        AfxMessageBox(str, MB_ICONINFORMATION);
        return;
    }
    m_BevelWidth = nNewValue;
    InvalidateControl();
    SetModifiedFlag();
}

void CColorButtonCtrl::FrameButton(CBrush& br)
{
    CDC* pDC = GetDC();

    CRect rc;

    GetClientRect(&rc);

    pDC->FrameRect(&rc, &br);

    ReleaseDC(pDC);
}
