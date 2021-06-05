#include "stdafx.h"
#include "SettingsPane.h"
#include "resource.h"
#include "DrumSequencer.h"

BEGIN_MESSAGE_MAP(SettingsPane, CPaneDialog)
        ON_NOTIFY(UDN_DELTAPOS, IDC_SP_TEMPO, SettingsPane::OnUpDownTempo)
        ON_MESSAGE(WM_INITDIALOG, SettingsPane::HandleInitDialog)
        ON_WM_CHAR()
END_MESSAGE_MAP()

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

    auto bpm = theApp.Tempo();
    ASSERT(bpm >= m_lowerLimit && bpm <= m_upperLimit);

    m_tempo.SetLimitText(3);
    m_tempo.setRange(m_lowerLimit, m_upperLimit);

    m_spin.SetBuddy(&m_tempo);
    m_spin.SetRange(m_lowerLimit, m_upperLimit);

    m_spin.SetPos(bpm);
    m_tempo.setValue(bpm);

    return TRUE;
}

void SettingsPane::OnUpDownTempo(NMHDR* pNMHDR, LRESULT* pResult)
{
    const auto pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

    if (pNMHDR->hwndFrom != m_spin.m_hWnd) {
        *pResult = -1; // don't know you
        return;
    }

    auto newValue = pNMUpDown->iPos + pNMUpDown->iDelta;
    if (newValue < m_lowerLimit || newValue > m_upperLimit) {
        *pResult = 1; // invalid
        return;
    }

    m_tempo.setValue(newValue);
    theApp.SetTempo(newValue);

    *pResult = 0;
}

void SettingsPane::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (nChar == VK_RETURN) {
        // enter a new tempo
        auto newTempo = m_tempo.value();
        if (newTempo >= m_lowerLimit && newTempo <= m_upperLimit) {
            if (theApp.Tempo() != newTempo) {
                m_spin.SetPos(newTempo);
                theApp.SetTempo(newTempo);
            }
        }
    } else {
        CPaneDialog::OnChar(nChar, nRepCnt, nFlags);
    }
}
