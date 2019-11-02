#pragma once

// TransparentBitmap command target

class TransparentBitmap : public CBitmap
{
public:
    TransparentBitmap(COLORREF transparent);
    virtual ~TransparentBitmap();

    void Repaint();
    void Draw(CDC *pDC, int x, int y);

private:
    void Cleanup();

    COLORREF m_Transparent;	// transparent color
    CDC m_MemDC;
    CDC m_AndDC;
    CDC m_XorDC;
    CBitmap *m_pOldBitmapAnd;
    CBitmap *m_pOldBitmapXor;
    CBitmap *m_pOldBitmapMem;
};


