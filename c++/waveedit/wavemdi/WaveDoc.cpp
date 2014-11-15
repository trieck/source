//////////////////////////////////////
// Module Name	:	WaveDoc.cpp		//
// Author		:	Thomas A. Rieck //
// Purpose		:	Wave Document	//
//					Implementations	//
// Date			:	11/23/1997		//
//////////////////////////////////////

#include "WaveDoc.h"
#include "PlayDlg.h"
#include "resource.h"

IMPLEMENT_DYNCREATE(CWaveDoc, CDocument)

BEGIN_MESSAGE_MAP(CWaveDoc, CDocument)
    ON_COMMAND(ID_DEVICEPLAYER, OnDevicePlayer)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CWaveDoc construction/destruction

CWaveDoc :: CWaveDoc()
{
    m_pDSBuffer		= NULL;
    m_dwBytesPerSec	= NULL;
}

CWaveDoc :: ~CWaveDoc()
{
}

BOOL CWaveDoc :: OnNewDocument()
{
    Initialize();
    return CDocument :: OnNewDocument();
}

VOID CWaveDoc :: OnDevicePlayer()
{
    // Check if the device player is
    // already open; restore it if it is.
    CWnd* pWnd = CWnd::FindWindow(NULL, _T("Device Player"));
    if (pWnd) {
        pWnd->ShowWindow(SW_RESTORE);
        return;
    } else {
        CPlayDlg* pDlg = new CPlayDlg;
        ASSERT_VALID(pDlg);

        pDlg->Create(IDD_PLAYER);
    }
}

VOID CWaveDoc :: SetBuffer(LPDIRECTSOUNDBUFFER pDSBuffer)
{
    ReleaseInterface(m_pDSBuffer);

    m_pDSBuffer = pDSBuffer;

    m_pDSBuffer->AddRef();
}

BOOL CWaveDoc :: Play()
{
    if (!m_pDSBuffer)
        return FALSE;

    return SUCCEEDED(m_pDSBuffer->Play(0, 0, 0));
}

BOOL CWaveDoc :: Pause()
{
    return SUCCEEDED(m_pDSBuffer->Stop());
}

BOOL CWaveDoc::Restart()
{
    return Play();
}

BOOL CWaveDoc :: Stop()
{
    HRESULT hr;

    if (!m_pDSBuffer)
        return FALSE;

    hr = m_pDSBuffer->Stop();
    if (FAILED(hr))
        return FALSE;

    return SUCCEEDED(m_pDSBuffer->SetCurrentPosition(0L));
}

BOOL CWaveDoc :: GetCurrentPosition(LPDWORD lpdwPlayPosition, LPDWORD lpdwWritePosition)
{
    *lpdwPlayPosition	= 0;
    *lpdwWritePosition	= 0;

    if (!m_pDSBuffer)
        return FALSE;

    return SUCCEEDED(m_pDSBuffer->GetCurrentPosition(lpdwPlayPosition, lpdwWritePosition));
}

BOOL CWaveDoc :: IsPlaying()
{
    if (!m_pDSBuffer)
        return FALSE;

    DWORD	dwStatus;
    HRESULT hr = m_pDSBuffer->GetStatus(&dwStatus);
    if (FAILED(hr))
        return FALSE;

    if (dwStatus != DSBSTATUS_PLAYING)
        return FALSE;

    return TRUE;
}

void CWaveDoc :: DeleteContents()
{
    Initialize();
}

VOID CWaveDoc :: Initialize()
{
    ReleaseInterface(m_pDSBuffer);

    m_pDSBuffer		= NULL;
    m_dwBytesPerSec	= NULL;

}
