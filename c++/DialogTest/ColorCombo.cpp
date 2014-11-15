// COLORCOMBO.CPP

#include "ColorCombo.h"

void CColorCombo::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    // get a device context for the current item
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

    // get the RGB that's stored as item data
    COLORREF cr = (COLORREF)lpDrawItemStruct->itemData;

    if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) {
        // Paint the item in the color defined by cr
        CBrush br(cr);
        pDC->FillRect(&lpDrawItemStruct->rcItem, &br);
    }

    // See if this item is currently selected or not
    if (lpDrawItemStruct->itemState & ODS_SELECTED) {
        // The item is selected, so draw a highlighted border
        COLORREF crBorderColor;
        crBorderColor = RGB(255 - GetRValue(cr),
                            255 - GetGValue(cr),
                            255 - GetBValue(cr));

        // Create a brush for the highlighted border
        CBrush br(crBorderColor);
        pDC->FrameRect(&lpDrawItemStruct->rcItem, &br);
    }

    else {
        // item isn't selected, so draw a frame the same color as cr
        CBrush br(cr);
        pDC->FrameRect(&lpDrawItemStruct->rcItem, &br);
    }
}

void CColorCombo::MeasureItem(LPMEASUREITEMSTRUCT lpMeasure)
{
    lpMeasure->itemHeight = 15;  // set item height
}

void CColorCombo::FillList()
{
    // Add 16 progressively darker shades of purple
    for (int i = 255; i > 0; i-=16)
        AddColorToList(RGB(i, 0, i));
}

void CColorCombo::AddColorToList(COLORREF cr)
{
    // add an RGB color as a combo box string
    AddString((LPCTSTR) cr);
}