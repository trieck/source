//////////////////////////////////////
// Module Name	:	WaveDoc.h		//
// Author		:	Thomas A. Rieck //
// Purpose		:	Wave Document	//
//					Declarations	//
// Date			:	11/23/1997		//
//////////////////////////////////////


#ifndef __WAVEDOC_H__
#define __WAVEDOC_H__

#include "stdafx.h"

///////////////////////////////////////////////////////////////////
// The CWaveDoc document class

// Forward declarations
class CPlayDlg;

class CWaveDoc : public CDocument
{
	friend CPlayDlg;
protected: 
	VOID Initialize();
	virtual void DeleteContents();
	BOOL GetCurrentPosition(LPDWORD, LPDWORD);
	BOOL Stop();
	BOOL Restart();
	BOOL Pause();
	BOOL Play();
	DECLARE_DYNCREATE(CWaveDoc)
	DECLARE_MESSAGE_MAP()

	VOID	OnDevicePlayer();
public:
	BOOL IsPlaying();
	CWaveDoc();
	virtual ~CWaveDoc();

	VOID	SetBuffer(LPDIRECTSOUNDBUFFER);
	inline	VOID	SetRate(DWORD dwBytesPerSec){ m_dwBytesPerSec = dwBytesPerSec; }
	inline	DWORD	GetRate() { return m_dwBytesPerSec; }
	// Overrides
	virtual BOOL OnNewDocument();
private:
	LPDIRECTSOUNDBUFFER 	m_pDSBuffer;
	DWORD					m_dwBytesPerSec;
};

///////////////////////////////////////////////////////////////////

#endif	// __WAVEDOC_H__
