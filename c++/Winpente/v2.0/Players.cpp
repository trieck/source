// Players.cpp : implementation file
//

#include "stdafx.h"
#include "Players.h"
#include "PenteApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayers

CPlayers::CPlayers()
{
	m_fInitialized	= FALSE;
	m_pPlayersArray	= NULL;
}

CPlayers::~CPlayers()
{
	if (m_pPlayersArray)
	{
		m_pPlayersArray->RemoveAll();
		delete m_pPlayersArray;
	}
}

BOOL CPlayers::Init()
{
	if (m_fInitialized)
	{
		return FALSE;
	}

	m_pPlayersArray = new CStringArray;
	ASSERT_VALID(m_pPlayersArray);

	BuildPlayersArray();

	m_fInitialized = TRUE;

	return TRUE;
}

BOOL CPlayers::FlushPlayers()
{
	BOOL fRtn = FALSE;

	if (!m_fInitialized)
	{
		return fRtn;
	}

	m_pPlayersArray->RemoveAll();
		
	UpdateRegistry();

	fRtn = TRUE;

	return fRtn;
}

INT CPlayers::GetPlayerCount()
{
	INT nRtn = -1;

	if (!m_fInitialized)
	{
		return nRtn;
	}

	ASSERT(m_pPlayersArray);

	nRtn = m_pPlayersArray->GetSize();

	return nRtn;
}

BOOL CPlayers::UpdateRegistry()
{
	BOOL fRtn = FALSE;

	if (!m_fInitialized)
	{
		return fRtn;
	}

	// Build a long delimited string of players
	CString strPlayers;
	for(INT i = 0; i < m_pPlayersArray->GetSize(); i++)
	{
		strPlayers += m_pPlayersArray->GetAt(i) + '\n';
	}

	UINT nLength = strPlayers.GetLength() == 0 ? 1 : strPlayers.GetLength();

	fRtn = CPenteApp::UpdateRegistryInformation(_T("bin"), _T("Players"), (LPBYTE)(LPCTSTR)strPlayers, REG_BINARY, nLength);
	
	return fRtn;
}

VOID CPlayers::BuildPlayersArray()
{
	INT		nPos;
	LPBYTE	pData;

	ASSERT_VALID(m_pPlayersArray);

	m_pPlayersArray->RemoveAll();

	if (CPenteApp::GetRegistryInformation(_T("bin"), _T("Players"), &pData, REG_BINARY))
	{
		CString strPlayers((LPCTSTR)pData);

		delete pData;

		while((nPos = strPlayers.Find('\n')) != -1)
		{
			CString strItem = strPlayers.Left(nPos);

			VERIFY(!strItem.IsEmpty());

			m_pPlayersArray->Add(strItem);

			strPlayers = strPlayers.Mid(nPos + 1);
		}
	}
}

BOOL CPlayers::AddPlayer(const CString& strNewPlayer)
{
	BOOL fRtn = FALSE;

	if (!m_fInitialized)
	{
		return fRtn;
	}

	ASSERT(!strNewPlayer.IsEmpty());
	ASSERT(m_pPlayersArray);

	BOOL fFound = FALSE;

	// Only add the player if the don't yet exist
	for (INT i = 0; i < m_pPlayersArray->GetSize(); i++)
	{
		if (strNewPlayer == m_pPlayersArray->GetAt(i))
		{
			fFound = TRUE;
			break;
		}
	}

	if (!fFound)
	{
		m_pPlayersArray->Add(strNewPlayer);
		fRtn = UpdateRegistry();
	}

	return fRtn;
}

BOOL CPlayers::GetPlayer(INT nIndex, CString& strPlayer)
{
	BOOL fRtn = FALSE;

	// Initialize 'out' parameter
	strPlayer = _T("");

	if (!m_fInitialized)
	{
		return fRtn;
	}

	ASSERT(m_pPlayersArray);

	if (nIndex < 0 || nIndex > m_pPlayersArray->GetSize())
	{
		return fRtn;
	}

	strPlayer = m_pPlayersArray->GetAt(nIndex);

	fRtn = TRUE;

	return fRtn;
}
