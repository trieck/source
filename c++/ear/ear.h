// ear.h : main header file for the EAR application
//

#if !defined(AFX_EAR_H__5C739465_F614_11D3_895D_000000000000__INCLUDED_)
#define AFX_EAR_H__5C739465_F614_11D3_895D_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define INTERVAL_SECONDS	1
#define INTERVAL_THIRDS		2
#define INTERVAL_FOURTHS	4
#define INTERVAL_FIFTHS		8
#define INTERVAL_SIXTHS		16
#define INTERVAL_SEVENTHS	32
#define INTERVAL_OCTAVES	64
#define INTERVAL_ALL		INTERVAL_SECONDS	|	\
							INTERVAL_THIRDS		|	\
							INTERVAL_FOURTHS	|	\
							INTERVAL_FIFTHS		|	\
							INTERVAL_SIXTHS		|	\
							INTERVAL_SEVENTHS	|	\
							INTERVAL_OCTAVES

/////////////////////////////////////////////////////////////////////////////
// EarApp:
// See ear.cpp for the implementation of this class
//

class EarApp : public CWinApp
{
public:
    EarApp();
    ~EarApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(EarApp)
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    virtual int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt);
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(EarApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:
    BOOL Play(MidiBuffer *pbuff);
    BOOL Stop();
    BOOL SetInstrument(BYTE b);
    int GetIntervals() const;
    void SetIntervals(int i);
    int GetInstrument() const;
protected:
    BOOL InitializeStream();
private:
    MidiStream *m_pStream;
    int m_Intervals;
    BOOL m_instrument;
};

/////////////////////////////////////////////////////////////////////////////

inline int EarApp::GetIntervals() const
{
    return m_Intervals;
}

inline void EarApp::SetIntervals(int intervals)
{
    m_Intervals = intervals;
}

inline int EarApp::GetInstrument() const
{
    return m_instrument;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EAR_H__5C739465_F614_11D3_895D_000000000000__INCLUDED_)

