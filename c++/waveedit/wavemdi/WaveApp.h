//////////////////////////////////////
// Module Name	:	WaveApp.h		//
// Author		:	Thomas A. Rieck //
// Purpose		:	Wave App		//
//					Declarations	//
// Date			:	11/23/1997		//
//////////////////////////////////////

#ifndef __WAVEAPP_H__
#define __WAVEAPP_H__

#include "stdafx.h"
#include "MainFrame.h"

///////////////////////////////////////////////////////////////////
// The CWaveApp application class

class CWaveApp : public CWinApp {
public:
    CWaveApp();
    virtual ~CWaveApp();

    // Overrides
    virtual BOOL	InitInstance();
    virtual INT		ExitInstance();

protected:

    afx_msg VOID	OnAppAbout();
    afx_msg VOID	OnFileOpen();

protected:
    LPDIRECTSOUND	m_pDSound;		// DirectSound object pointer
    CMainFrame*		m_pMainFrame;	// Main Frame Window
    CString			m_szDefPath;	// Default File Path

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __WAVEAPP_H__
