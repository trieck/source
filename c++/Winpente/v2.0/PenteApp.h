/*---------------------------------------
	Module Name	:	PenteApp.h
	Author		:	Thomas A. Rieck
	Purpose		:	Pente Application
					declarations
	Date		:	08/21/1997
---------------------------------------*/

#ifndef __PENTEAPP_H__
#define __PENTEAPP_H__

#include <mmsystem.h>
#include "miscobj.h"
#include "OurTypes.h"

///////////////////////////////////////////////////////////////////
// The CPenteApp application class

class CPenteApp : public CWinApp
{
protected:
    HINSTANCE			m_hDllInst;
    BOOL				m_fInitialized;
    static LPCTSTR		m_lpszRegPath;
protected:
    BOOL		IsValidResolution();
    static VOID AddScore(const CString&, const CString&, UINT, const CString&);
public:
    CPenteApp();
    virtual ~CPenteApp();

    static	BOOL	GetRegistryInformation(LPCTSTR, LPCTSTR, PPBYTE, UINT);
    static	BOOL	UpdateRegistryInformation(LPCTSTR, LPCTSTR, LPBYTE, UINT, UINT nBytes = 0);
    static  CString	GetRegPath()
    {
        return m_lpszRegPath;
    }

    BOOL	PlayWave(LPTSTR, UINT);
    VOID	DoFinish();

    // Overrides
    virtual BOOL	InitInstance();
    virtual int		ExitInstance();
    virtual int		DoMessageBox(LPCTSTR, UINT nType, UINT nIDPrompt);

public:
    BOOL	m_fEnableDebug;
protected:
    afx_msg VOID OnExit ();
    afx_msg VOID OnFileNew();
    afx_msg VOID OnFileOpen();
    afx_msg VOID OnAbout();
    afx_msg VOID OnViewScores();
    afx_msg VOID OnSettings();
    afx_msg VOID OnHelp();

    DECLARE_DYNCREATE(CPenteApp)
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __PENTEAPP_H__
