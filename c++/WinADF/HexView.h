#pragma once
#include "bigscrollview.h"

class HexView :	public BigScrollView
{
    DECLARE_DYNCREATE(HexView)
public:
    HexView(void);
    ~HexView(void);

protected:
    CFont m_Font;
    CPen m_GridPen;

    uint8_t *m_pBuffer;
    LPSTR m_pLine;
    uint32_t m_nBufferLen;

    virtual void OnDraw(CDC* /*pDC*/);
    void Render(CDC* pDC);
    void DrawGridLine(CDC *pDC, uint32_t line, uint32_t cx);
    void DrawText(CDC *pDC, uint32_t line);
    uint32_t FormatLine(uint32_t line, uint8_t *pdata, uint32_t size);
    void SetSizes();
public:
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
