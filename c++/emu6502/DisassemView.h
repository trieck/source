#pragma once

#include "MultirowView.h"
#include "Disassem.h"

// DisassemView view

class DisassemView : public MultirowView {
    DECLARE_DYNCREATE(DisassemView)

protected:
    DisassemView();           // protected constructor used by dynamic creation
    virtual ~DisassemView();

public:
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    DECLARE_MESSAGE_MAP()
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
    void DrawDisassem(CDC *pDC);
    CString GetLine(USHORT &addr);
    CFont m_Font;
    Disassembler disassembler;
};


