// TorrentExplorer.h : main header file for the TORRENT application
//

#if !defined(AFX_TORRENT_H__B52E993E_9FA9_49D8_9099_8BE99E88B4B9__INCLUDED_)
#define AFX_TORRENT_H__B52E993E_9FA9_49D8_9099_8BE99E88B4B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "TorrentSettings.h"
#include "TorrentObject.h"	// Added by ClassView

typedef CMap<COLORREF, COLORREF, int, int> ColorMap;

/////////////////////////////////////////////////////////////////////////////
// TorrentExplorer:
// See TorrentExplorer.cpp for the implementation of this class
//

class TorrentExplorer : public CWinApp {
public:
    BOOL IsSetting(LPCSTR key);
    TorrentExplorer();

    __int64 GetIntSetting(LPCSTR key);
    BOOL GetBOOLSetting(LPCSTR key);
    LPTORRENTOBJECT GetSetting(LPCSTR key);
    void PutSetting(LPCSTR key, __int64 val);
    void PutSetting(LPCSTR key, LPCSTR val);
    RGBTRIPLE *GetPalette() const {
        return m_pPalette;
    }
    BOOL GetPaletteIndex(COLORREF c, int &i) const;

    enum { NUM_PALETTE_COLORS = 256 };

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(TorrentExplorer)
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    //}}AFX_VIRTUAL

// Implementation
    //{{AFX_MSG(TorrentExplorer)
    afx_msg void OnAppAbout();
    afx_msg void OnSettings();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    BOOL CheckInstance();
    BOOL LoadPalette();
    TorrentSettings *m_pSettings;
    RGBTRIPLE *m_pPalette;
    ColorMap m_ColorMap;
    HANDLE m_hMutex;
};


/////////////////////////////////////////////////////////////////////////////
// Global functions
void PumpMessages();
void ThrowUserException(UINT nFormatID, ...);
CDialog *GetTopmostDlgParent(CWnd *pWnd);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TORRENT_H__B52E993E_9FA9_49D8_9099_8BE99E88B4B9__INCLUDED_)
