/*-------------------------------------------

	Module	:	PlayDlg.H
	Purpose	:	Player Dialog Declarations
	Date	:	12/01/1997

-------------------------------------------*/

#ifndef __PLAYDLG_H__
#define __PLAYDLG_H__

#include "stdafx.h"
#include "resource.h"
#include "WaveDoc.h"
#include "DigitCtrlMgr.h"
#include "LEDMeter.h"

class CPlayDlg : public CDialog
{
    DECLARE_DYNCREATE (CPlayDlg)

// Construction
public:
    static CString TranslatePlayPosition(DWORD);
    CPlayDlg(CWnd* pParent = NULL);
    virtual ~CPlayDlg();

protected:
    // Overrides
    virtual BOOL OnInitDialog();
    virtual VOID OnCancel();
    virtual VOID PostNcDestroy();

    afx_msg void OnTimer(UINT nIDEvent);

    VOID			OnStopWave();
    VOID			OnPlayWave();
    VOID			OnPauseWave();
protected:
    CWaveDoc*		GetActiveDocument();
    CWaveDoc*		m_pDoc;
    CDigitCtrlMgr*	m_pDigitCtrlMgr;
    CLEDMeter*		m_pLeftChannel;
    CLEDMeter*		m_pRightChannel;
    BOOL			m_fPaused;

    static const UINT sm_nCtrlIDs[];
    static const RECT sm_rcDigitSizes[];

    DECLARE_MESSAGE_MAP()
};

#endif // __PLAYDLG_H__