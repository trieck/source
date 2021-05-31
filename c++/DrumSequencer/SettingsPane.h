#pragma once

class SettingsPane : public CPaneDialog
{
protected:
DECLARE_MESSAGE_MAP()

    void DoDataExchange(CDataExchange* pDX) override; // DDX/DDV support
    afx_msg LRESULT HandleInitDialog(WPARAM wParam, LPARAM lParam);
    afx_msg void OnUpDownTempo(NMHDR* pNMHDR, LRESULT* pResult);

private:
    CEdit m_tempo;
    CMFCSpinButtonCtrl m_spin;
    const short m_lowerLimit = 0;
    const short m_upperLimit = 300;
};
