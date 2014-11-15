// Scores.cpp : implementation file
//

#include "stdafx.h"
#include "Scores.h"
#include "PenteApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScores

CScores::CScores()
{
    m_pScoresArray	= NULL;
    m_fInitialized	= FALSE;
}

CScores::~CScores()
{
    if (m_pScoresArray) {
        m_pScoresArray->RemoveAll();
        delete m_pScoresArray;
    }
}

BOOL CScores::Init()
{
    if (m_fInitialized) {
        return FALSE;
    }

    m_pScoresArray	= new CStringArray;
    ASSERT_VALID(m_pScoresArray);

    // Parse score items and build array
    BuildScoresArray();

    m_fInitialized = TRUE;

    return TRUE;
}

BOOL CScores::AddScore(const CString& strScore)
{
    BOOL fRtn = FALSE;

    if (!m_fInitialized) {
        return fRtn;
    }

    ASSERT(m_pScoresArray);
    m_pScoresArray->Add(strScore);

    fRtn = UpdateRegistry();

    return fRtn;
}

VOID CScores::BuildScoresArray()
{
    INT		nPos;
    LPBYTE	pData;

    ASSERT_VALID(m_pScoresArray);

    m_pScoresArray->RemoveAll();

    if (CPenteApp::GetRegistryInformation(_T("bin"), _T("Scores"), &pData, REG_BINARY)) {
        CString strScores((LPCTSTR)pData);

        delete pData;

        while ((nPos = strScores.Find('\n')) != -1) {
            CString strItem = strScores.Left(nPos);

            VERIFY(!strItem.IsEmpty());

            m_pScoresArray->Add(strItem);

            strScores = strScores.Mid(nPos + 1);
        }
    }
}

INT CScores::GetScoreCount()
{
    INT nItems = -1;

    if (!m_fInitialized) {
        return nItems;
    }

    if (m_pScoresArray) {
        nItems = m_pScoresArray->GetSize();
    }

    return nItems;
}

BOOL CScores::GetScoreItem(INT nIndex, INT nItem, CString& strItem)
{
    // Initialize out parameter
    strItem = _T("");

    if (!m_fInitialized) {
        return FALSE;
    }

    ASSERT(m_pScoresArray);

    if (nIndex < 0 || nIndex > m_pScoresArray->GetSize()) {
        return FALSE;
    }

    if (nItem < 0 || nItem > 4) {
        return FALSE;
    }

    CString strScoreString;

    strScoreString = m_pScoresArray->GetAt(nIndex);

    INT nPos;
    INT nCount = 0;

    while ((nPos = strScoreString.Find('\t')) != -1) {
        CString strTemp = strScoreString.Left(nPos);
        VERIFY(!strTemp.IsEmpty());

        if (nCount == nItem) {
            strItem = strTemp;
            break;
        }

        strScoreString = strScoreString.Mid(nPos + 1);
        nCount++;
    }

    return (!strItem.IsEmpty());
}

BOOL CScores::FlushScores()
{
    BOOL fRtn = FALSE;

    if (!m_fInitialized) {
        return fRtn;
    }

    m_pScoresArray->RemoveAll();

    UpdateRegistry();

    fRtn = TRUE;

    return fRtn;
}

BOOL CScores::UpdateRegistry()
{
    BOOL fRtn = FALSE;

    ASSERT(m_pScoresArray);

    CString strScores;

    for (INT i = 0; i < m_pScoresArray->GetSize(); i++) {
        strScores += m_pScoresArray->GetAt(i) + '\n';
    }

    // Update the scores in the registry
    UINT nLength = strScores.GetLength() == 0 ? 1 : strScores.GetLength();

    fRtn = CPenteApp::UpdateRegistryInformation(_T("bin"), _T("Scores"), (LPBYTE)(LPCTSTR)strScores, REG_BINARY, nLength);

    return fRtn;
}
