#pragma once
#include <afxvisualmanager.h>

class VisualManager : public CMFCVisualManager
{
    DECLARE_DYNCREATE(VisualManager)

    void OnDrawBarGripper(CDC* pDC, CRect rc, BOOL bHorz, CBasePane* pBar) override;
};

