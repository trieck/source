/////////////////////////////////////////////////////////////////////////////
//
//	REGKEY.CPP
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "RegKey.h"

//
// Constructor
//
CRegKey::CRegKey()
{
    m_hKey = NULL;
}

//
// Destructor
//
CRegKey::~CRegKey()
{
    Close();
}

//
// Close
//
LONG CRegKey::Close()
{
    LONG lRtn = ERROR_SUCCESS;

    if (m_hKey != NULL) {
        lRtn = ::RegCloseKey(m_hKey);
        m_hKey = NULL;
    }

    return lRtn;
}

//
// Open
//
LONG CRegKey::Open(HKEY hKeyParent, LPCTSTR lpszKeyName, REGSAM samDesired)
{
    LONG lRtn = ERROR_SUCCESS;
    ASSERT(hKeyParent != NULL);

    HKEY hKey = NULL;
    lRtn = ::RegOpenKeyEx(hKeyParent, lpszKeyName, 0, samDesired, &hKey);
    if (lRtn == ERROR_SUCCESS) {
        lRtn = Close();
        ASSERT(lRtn == ERROR_SUCCESS);
        m_hKey = hKey;
    }

    return lRtn;
}

//
// GetValue
//
LONG CRegKey::GetValue(LPTSTR szValue, LPCTSTR lpszValueName, LPDWORD pdwCount)
{
    LONG lRtn = ERROR_SUCCESS;

    ASSERT(pdwCount != NULL);
    ASSERT(m_hKey != NULL);

    DWORD dwType = NULL;
    lRtn = RegQueryValueEx(m_hKey, (LPTSTR)lpszValueName, NULL, &dwType, (LPBYTE)szValue, pdwCount);

    ASSERT ((lRtn != ERROR_SUCCESS) || (dwType == REG_SZ) ||
            (dwType == REG_MULTI_SZ) || (dwType == REG_EXPAND_SZ));

    return lRtn;
}

//
// GetValue
//
LONG CRegKey::GetValue(LPBYTEARRAY pByteArray, LPCTSTR lpszValueName, LPDWORD pdwCount)
{
    LONG lRtn = ERROR_SUCCESS;

    ASSERT(pByteArray != NULL);
    ASSERT(pdwCount != NULL);
    ASSERT(m_hKey != NULL);

    // Remove all the elements
    pByteArray->RemoveAll();

    // First determine the size of the needed buffer
    DWORD dwType = REG_BINARY;
    lRtn = RegQueryValueEx(m_hKey, (LPTSTR)lpszValueName, NULL, &dwType, NULL, pdwCount);
    if (lRtn != ERROR_SUCCESS)
        return lRtn;

    // Grow the array
    pByteArray->SetSize(*pdwCount);

    LPBYTE pData = pByteArray->GetData();
    if (pData != NULL) {
        // Now get the data
        lRtn = RegQueryValueEx(m_hKey, (LPTSTR)lpszValueName, NULL, &dwType, pData, pdwCount);
    }

    return lRtn;
}

//
// GetValue
//
LONG CRegKey::GetValue (LPDWORD pdwValue, LPCTSTR lpszValueName)
{
    LONG lRtn = ERROR_SUCCESS;

    ASSERT(pdwValue != NULL);
    ASSERT(m_hKey != NULL);

    // Initialize 'out' parameter
    *pdwValue = 0;

    DWORD dwSize	= 0;
    DWORD dwType	= REG_DWORD;
    DWORD dwCount	= sizeof(DWORD);

    lRtn = RegQueryValueEx(m_hKey, (LPTSTR)lpszValueName, NULL, &dwType, (LPBYTE)pdwValue, &dwCount);

    return lRtn;
}

//
// SetValue
//
LONG CRegKey::SetValue(LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
    ASSERT(lpszValue != NULL);
    ASSERT(m_hKey != NULL);

    return RegSetValueEx(m_hKey, lpszValueName, NULL, REG_SZ, (LPBYTE)lpszValue, (_tcslen(lpszValue) + 1) * sizeof(TCHAR));
}

//
// SetValue
//
LONG CRegKey::SetValue(LPBYTE pData, DWORD dwSize, LPCTSTR lpszValueName)
{
    ASSERT(pData != NULL);
    ASSERT(m_hKey != NULL);

    return RegSetValueEx(m_hKey, lpszValueName, NULL, REG_BINARY, pData, dwSize);
}

//
// SetValue
//
LONG CRegKey::SetValue(DWORD dwValue, LPCTSTR lpszValueName)
{
    ASSERT(m_hKey != NULL);

    return RegSetValueEx(m_hKey, lpszValueName, NULL, REG_DWORD, (LPBYTE)&dwValue, sizeof(DWORD));
}

//
// EnumKeys
//
LONG CRegKey::EnumKeys(LPTSTR lpszKey, LONG lIndex, LPDWORD pdwCount)
{
    ASSERT(pdwCount != NULL);
    ASSERT(lpszKey != NULL);
    ASSERT(m_hKey != NULL);

    return RegEnumKeyEx(m_hKey, lIndex, lpszKey, pdwCount, 0, NULL, 0, NULL);
}

//
// EnumValues
//
LONG CRegKey::EnumValues(DWORD dwIndex, LPTSTR lpszValueName, LPDWORD pdwValSize, LPDWORD pdwTypeCode, LPBYTE pValueData, LPDWORD pdwDataSize)
{
    ASSERT(lpszValueName != NULL);
    ASSERT(m_hKey != NULL);

    return RegEnumValue(m_hKey, dwIndex, lpszValueName, pdwValSize, NULL, pdwTypeCode, pValueData, pdwDataSize);

}