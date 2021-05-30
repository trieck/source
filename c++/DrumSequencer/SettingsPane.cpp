#include "stdafx.h"
#include "SettingsPane.h"
#include "resource.h"
#include "DrumSequencer.h"

BEGIN_MESSAGE_MAP(SettingsPane, CPaneDialog)
        ON_NOTIFY(UDN_DELTAPOS, IDC_SP_TEMPO, SettingsPane::OnUpDownTempo)
        ON_MESSAGE(WM_INITDIALOG, SettingsPane::HandleInitDialog)
END_MESSAGE_MAP()

extern CDrumSequencerApp theApp;

void SettingsPane::DoDataExchange(CDataExchange* pDX)
{
    CPaneDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(SettingsPane)
    DDX_Control(pDX, IDC_E_TEMPO, m_tempo);
    DDX_Control(pDX, IDC_SP_TEMPO, m_spin);
    //}}AFX_DATA_MAP
}

LRESULT SettingsPane::HandleInitDialog(WPARAM wParam, LPARAM lParam)
{
    if (!CPaneDialog::HandleInitDialog(wParam, lParam)) {
        return FALSE;
    }

    ASSERT(IsWindow(m_tempo));
    ASSERT(IsWindow(m_spin));

    auto bpm = theApp.tempo();
    ASSERT(bpm >= m_lowerLimit && bpm <= m_upperLimit);

    m_spin.SetBuddy(&m_tempo);
    m_spin.SetRange(m_lowerLimit, m_upperLimit);
    m_spin.SetPos(bpm);

    CString strTempo;
    strTempo.Format(_T("%d"), bpm);
    m_tempo.SetWindowText(strTempo);

    return TRUE;
}

void SettingsPane::OnUpDownTempo(NMHDR* pNMHDR, LRESULT* pResult)
{
    const auto pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

    if (pNMHDR->hwndFrom == m_spin.m_hWnd) {
        auto newValue = pNMUpDown->iPos + pNMUpDown->iDelta;
        if (newValue < m_lowerLimit || newValue > m_upperLimit) {
            *pResult = 1; // invalid
            return;
        }

        theApp.setTempo(newValue);

        CString str;
        str.Format(_T("%d"), newValue);

        m_tempo.SetWindowText(str);

        *pResult = 0;
    } else {
        *pResult = -1; // don't know you
    }
}
