// DigitCtrlMgr.cpp : implementation file
//

#include "DigitCtrlMgr.h"

/////////////////////////////////////////////////////////////////////////////
// CDigitCtrlMgr

CDigitCtrlMgr :: CDigitCtrlMgr(CDialog* pParent, const UINT CtrlIDs[], const RECT rcs[], UINT nCount)
	: m_pParent(pParent), m_nCount(nCount)
{
	ASSERT_VALID(m_pParent);

	m_pArray = new CObArray();
	ASSERT_VALID(m_pArray);

	// Allocate and create controls
	for (UINT i = 0; i < m_nCount; i ++) {
		CDigitCtrl* pCtrl= new CDigitCtrl();
		ASSERT_VALID(pCtrl);

		// Convert the dialog units to pixels
		CRect rcTemp(&rcs[i]);
		m_pParent->MapDialogRect(rcTemp);
		pCtrl->Create(NULL, NULL, WS_VISIBLE | WS_CHILD, rcTemp, m_pParent, CtrlIDs[i]);

		m_pArray->Add(pCtrl);
	}
}

CDigitCtrlMgr :: ~CDigitCtrlMgr()
{
	CDigitCtrl* pCtrl;

	if (m_pArray) {
		while ((pCtrl = (CDigitCtrl*)m_pArray->GetAt(0))) {
			m_pArray->RemoveAt(0);
			delete pCtrl;

			if (m_pArray->GetUpperBound() < 0)
				break;
		}

		delete m_pArray;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDigitCtrlMgr message handlers
BOOL CDigitCtrlMgr :: Advance(UINT nCtrl)
{
	if (nCtrl > m_nCount - 1)
		return FALSE;

	// We have to check if we are
	// currently on the digit nine.
	// if we are and there is a control
	// to the right, then we must increase that value.
	CDigitCtrl* pCtrl = (CDigitCtrl*)m_pArray->GetAt(nCtrl);
	ASSERT_VALID(pCtrl);

	if (pCtrl->GetCurrentDigit() == 9
	        && nCtrl < m_nCount - 1)
		Advance(nCtrl + 1);

	pCtrl->SetNextDigit();
	pCtrl->Invalidate();

	return TRUE;
}

BOOL CDigitCtrlMgr :: SetValue(CString& strValue)
{
	CDigitCtrl* pCtrl;

	if (strValue.GetLength() != (INT)m_nCount)
		return FALSE;

	for (UINT i = 0; i < m_nCount; i++) {
		CString strTemp = strValue.Mid(i, 1);
		if (strTemp != _T("")) {
			int nValue = atoi(strTemp);

			pCtrl = (CDigitCtrl*)m_pArray->GetAt(m_nCount - (i+1));
			ASSERT_VALID(pCtrl);

			pCtrl->SetValue(nValue);
			pCtrl->Invalidate();
		} else
			return FALSE;
	}

	return TRUE;
}

CDigitCtrl* CDigitCtrlMgr :: GetControl(UINT nControl)
{
	ASSERT_VALID(m_pArray);

	if (m_pArray->GetUpperBound() < (INT)nControl)
		return NULL;

	CDigitCtrl* pCtrl = (CDigitCtrl*)m_pArray->GetAt(nControl);

	return pCtrl;
}

UINT CDigitCtrlMgr :: GetCount()
{
	return m_nCount;
}
