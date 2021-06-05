#pragma once
#include "NumEdit.h"

class SettingsPane : public CPaneDialog
{
public:
    BOOL Create(CWnd* pParentWnd);
    BOOL IsResizable() const override { return FALSE; }
    BOOL CanBeResized() const override { return FALSE; }
    BOOL CanFloat() const override { return FALSE; }

protected:
DECLARE_MESSAGE_MAP()
    void DoDataExchange(CDataExchange* pDX) override; // DDX/DDV support

private:
    NumEdit m_tempo;
    CMFCSpinButtonCtrl m_spin;
    const short m_lowerLimit = 40;
    const short m_upperLimit = 300;
protected:
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg LRESULT HandleInitDialog(WPARAM wParam, LPARAM lParam);
    afx_msg void OnUpDownTempo(NMHDR* pNMHDR, LRESULT* pResult);
};
