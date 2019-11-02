#pragma once


// CColorChooserWnd

class CColorChooserWnd : public CWnd
{
    DECLARE_DYNAMIC(CColorChooserWnd)

public:
    CColorChooserWnd();
    virtual ~CColorChooserWnd();

protected:
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

    COLORREF GetSelectedColor() const;
private:
    void PaintBitmap();
    CRgn m_Region;
    CDC m_MemDC;
    CBitmap m_Bitmap;
    COLORREF m_Shadow, m_Hilight, m_BtnFace;
    CPoint m_ptSelected;
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
    afx_msg void OnSysColorChange();
};


