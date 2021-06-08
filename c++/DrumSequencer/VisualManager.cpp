#include "stdafx.h"
#include "VisualManager.h"

IMPLEMENT_DYNCREATE(VisualManager, CMFCVisualManager)

static constexpr auto CX_GRIPPER = 3;
static constexpr auto CX_OFFSET_LEFT = 2;
static constexpr auto CX_OFFSET_RIGHT = 4;
static constexpr auto CY_OFFSET_BOTTOM = 4;
static constexpr auto CY_OFFSET_TOP = 2;

void VisualManager::OnDrawBarGripper(CDC* pDC, CRect rc, BOOL bHorz, CBasePane* pBar)
{
    ASSERT_VALID(pDC);

    const auto clrHilite = pBar != nullptr && pBar->IsDialogControl()
                               ? GetGlobalData()->clrBtnHilite
                               : GetGlobalData()->clrBarHilite;
    const auto clrShadow = pBar != nullptr && pBar->IsDialogControl()
                               ? GetGlobalData()->clrBtnShadow
                               : GetGlobalData()->clrBarShadow;

    if (bHorz) {
        pDC->Draw3dRect(rc.left + CX_OFFSET_LEFT,
                        rc.top + CY_OFFSET_TOP,
                        CX_GRIPPER, rc.Height() - CY_OFFSET_BOTTOM,
                        clrHilite, clrShadow);

        pDC->Draw3dRect(rc.left + CX_OFFSET_LEFT + CX_GRIPPER + 1,
                        rc.top + CY_OFFSET_TOP,
                        CX_GRIPPER, rc.Height() - CY_OFFSET_BOTTOM,
                        clrHilite, clrShadow);
    } else {
        pDC->Draw3dRect(rc.left + CX_OFFSET_LEFT,
                        rc.top + CY_OFFSET_TOP,
                        rc.Width() - CX_OFFSET_RIGHT, CX_GRIPPER,
                        clrHilite, clrShadow);

        pDC->Draw3dRect(rc.left + CX_OFFSET_LEFT,
                        rc.top + CY_OFFSET_TOP + CX_GRIPPER + 1,
                        rc.Width() - CX_OFFSET_RIGHT, CX_GRIPPER,
                        clrHilite, clrShadow);
    }
}
