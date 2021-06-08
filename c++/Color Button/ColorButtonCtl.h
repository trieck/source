// ColorButtonCtl.h : Declaration of the CColorButtonCtrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CColorButtonCtrl : See ColorButtonCtl.cpp for implementation.

class CColorButtonCtrl : public COleControl
{
DECLARE_DYNCREATE(CColorButtonCtrl)

    // Constructor
public:
    CColorButtonCtrl();

    // Overrides

    // Drawing function
    void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid) override;

    // Persistence
    void DoPropExchange(CPropExchange* pPX) override;

    // Reset control state
    void OnResetState() override;

    // Implementation
protected:
    void FrameButton(CBrush& br);
    void DrawButtonUp(CDC* pDC, const CRect& rc);
    void DrawBevelInset(CDC* pDC, const CRect& rc);
    void DrawButtonDown(CDC* pDC, const CRect& rc);
    void DrawBevel(CDC* pDC, const CRect& rc, CPen& pen1, CPen& pen2);
    void DrawCaption(CDC* pDC, const CRect& rc, COLORREF lColor);
    void DrawBevelRaised(CDC* pDC, const CRect& rc);
    void DrawControl(CDC& dc, const CRect& rc);
    ~CColorButtonCtrl() = default;

    BOOL m_bDown; // button down flag
    COLORREF m_BackColor{}; // button backcolor
    COLORREF m_ForeColor{}; // button forecolor
    CString m_sCaption; // button caption
    short m_BevelWidth{}; // bevel width

DECLARE_OLECREATE_EX(CColorButtonCtrl) // Class factory and guid
DECLARE_OLETYPELIB(CColorButtonCtrl) // GetTypeInfo
    DECLARE_OLECTLTYPE(CColorButtonCtrl) // Type name and misc status

    // Message maps
    //{{AFX_MSG(CColorButtonCtrl)
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()

    // Dispatch maps
    //{{AFX_DISPATCH(CColorButtonCtrl)
    afx_msg short GetBevelWidth();
    afx_msg void SetBevelWidth(short nNewValue);
    afx_msg OLE_COLOR GetBackColor();
    afx_msg void SetBackColor(OLE_COLOR nNewValue);
    afx_msg OLE_COLOR GetForeColor();
    afx_msg void SetForeColor(OLE_COLOR nNewValue);
    afx_msg BSTR GetCaption();
    afx_msg void SetCaption(LPCTSTR lpszNewValue);
    //}}AFX_DISPATCH
DECLARE_DISPATCH_MAP()

    afx_msg void AboutBox();

    // Event maps
    //{{AFX_EVENT(CColorButtonCtrl)
    //}}AFX_EVENT
DECLARE_EVENT_MAP()

    // Dispatch and event IDs
public:
    enum
    {
        //{{AFX_DISP_ID(CColorButtonCtrl)
        dispidBevelWidth = 1L,
        //}}AFX_DISP_ID
    };
};
