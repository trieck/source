#pragma once
#include "NumEdit.h"

class SettingsPane : public CPaneDialog
{
protected:
DECLARE_MESSAGE_MAP()

    void DoDataExchange(CDataExchange* pDX) override; // DDX/DDV support
    afx_msg LRESULT HandleInitDialog(WPARAM wParam, LPARAM lParam);
    afx_msg void OnUpDownTempo(NMHDR* pNMHDR, LRESULT* pResult);

private:
    NumEdit m_tempo;
    CMFCSpinButtonCtrl m_spin;
    const short m_lowerLimit = 40;
    const short m_upperLimit = 300;
public:
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};
