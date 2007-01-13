//
// Registry.cpp
//

#include "Registry.h"

////////////////////////////////////////////////////////
//
// Internal helper functions prototypes
//

// Set the given key and its value.
BOOL setKeyAndValue(LPCTSTR pszPath,
                    LPCTSTR szSubkey,
                    LPCTSTR szValue);

// Convert a GUID into a TCHAR string.
void GUIDtoChar(const GUID& clsid, 
                 LPTSTR szGUID,
                 int length);

// Determine if a particular subkey exists.
BOOL SubkeyExists(LPCTSTR pszPath,
                  LPCTSTR szSubkey);

// Delete szKeyChild and all of its descendents.
LONG recursiveDeleteKey(HKEY hKeyParent, LPCTSTR szKeyChild);

////////////////////////////////////////////////////////
//
// Constants
//

// Size of a GUID as a string
const int GUID_STRING_SIZE = 39 * sizeof (TCHAR);

/////////////////////////////////////////////////////////
//
// Public function implementation
//

//
// Register the component in the registry.
//
HRESULT RegisterServer(HMODULE hModule,				// DLL module handle
                       const CLSID& clsid,			// Class ID
                       LPCTSTR szFriendlyName,		// Friendly Name
                       LPCTSTR szVerIndProgID,		// Programmatic
                       LPCTSTR szProgID,			// IDs
					   const GUID& libid)
{
	// Get server location.
	TCHAR szModule[512];
	DWORD dwResult =
		::GetModuleFileName(hModule, 
		                    szModule,
		                    sizeof(szModule) / sizeof (TCHAR));
	assert(dwResult != 0);

	// Convert the CLSID into a TCHAR.
	TCHAR szCLSID[GUID_STRING_SIZE];
	GUIDtoChar(clsid, szCLSID, sizeof(szCLSID));

	// Build the key CLSID\\{...}
	TCHAR szKey[64];
#ifndef _UNICODE
	strcpy(szKey, _T("CLSID\\"));
	strcat(szKey, szCLSID);
#else
	wcscpy(szKey, _T("CLSID\\"));
	wcscat(szKey, szCLSID);
#endif // _UNICODE
  
	// Add the CLSID to the registry.
	setKeyAndValue(szKey, NULL, szFriendlyName);

	// Add the server filename subkey under the CLSID key.
#ifdef _OUTPROC_SERVER_
	setKeyAndValue(szKey, _T("LocalServer32"), szModule);
#else
	setKeyAndValue(szKey, _T("InprocServer32"), szModule);
#endif

	// Add the ProgID subkey under the CLSID key.
	setKeyAndValue(szKey, _T("ProgID"), szProgID);

	// Add the version-independent ProgID subkey under CLSID key.
	setKeyAndValue(szKey, _T("VersionIndependentProgID"),
	               szVerIndProgID);

	// Add the Type Library ID subkey under the CLSID key.
	TCHAR szLIBID[GUID_STRING_SIZE] ;
	GUIDtoChar(libid, szLIBID, sizeof(szLIBID)) ;
	setKeyAndValue(szKey, _T("TypeLib"), szLIBID) ;

	// Add the version-independent ProgID subkey under HKEY_CLASSES_ROOT.
	setKeyAndValue(szVerIndProgID, NULL, szFriendlyName); 
	setKeyAndValue(szVerIndProgID, _T("CLSID"), szCLSID);
	setKeyAndValue(szVerIndProgID, _T("CurVer"), szProgID);

	// Add the versioned ProgID subkey under HKEY_CLASSES_ROOT.
	setKeyAndValue(szProgID, NULL, szFriendlyName); 
	setKeyAndValue(szProgID, _T("CLSID"), szCLSID);

	return S_OK;
}

//
// Remove the component from the registry.
//
LONG UnregisterServer(const CLSID& clsid,         // Class ID
                      LPCTSTR szVerIndProgID, // Programmatic
                      LPCTSTR szProgID)       //   IDs
{
	// Convert the CLSID into a TCHAR.
	TCHAR szCLSID[GUID_STRING_SIZE];
	GUIDtoChar(clsid, szCLSID, sizeof(szCLSID));

	// Build the key CLSID\\{...}
	TCHAR szKey[80];
#ifndef _UNICODE
	strcpy(szKey, _T("CLSID\\"));
	strcat(szKey, szCLSID);
#else
	wcscpy(szKey, _T("CLSID\\"));
	wcscat(szKey, szCLSID);
#endif // _UNICODE

	// Check for a another server for this component.
#ifdef _OUTPROC_SERVER_
	if (SubkeyExists(szKey, _T("InprocServer32")))
#else
	if (SubkeyExists(szKey, _T("LocalServer32")))
#endif
	{
		// Delete only the path for this server.
#ifdef _OUTPROC_SERVER_
#ifndef _UNICODE 
		strcat(szKey, _T("\\LocalServer32"));
#else
		wcscat(szKey, _T("\\LocalServer32"));
#endif // _UNICODE
#else
#ifndef _UNICODE
		strcat(szKey, _T("\\InprocServer32"));
#else
		wcscat(szKey, _T("\\InprocServer32"));
#endif // _UNICODE
#endif // _OUTPROC_SERVER_

		LONG lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szKey);
		assert(lResult == ERROR_SUCCESS);
	}
	else
	{
		// Delete all related keys.
		// Delete the CLSID Key - CLSID\{...}
		LONG lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szKey);
		assert((lResult == ERROR_SUCCESS) ||
		       (lResult == ERROR_FILE_NOT_FOUND)); // Subkey may not exist.

		// Delete the version-independent ProgID Key.
		lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szVerIndProgID);
		assert((lResult == ERROR_SUCCESS) ||
		       (lResult == ERROR_FILE_NOT_FOUND)); // Subkey may not exist.

		// Delete the ProgID key.
		lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szProgID);
		assert((lResult == ERROR_SUCCESS) ||
		       (lResult == ERROR_FILE_NOT_FOUND)); // Subkey may not exist.
	}
	return S_OK;
}

///////////////////////////////////////////////////////////
//
// Internal helper functions
//

// Convert a GUID to a TCHAR string.
void GUIDtoChar(const GUID& guid,
                 LPTSTR szGUID,
                 int length)
{
	assert(length >= GUID_STRING_SIZE);
	
	// Get GUID
	LPOLESTR wszGUID = NULL;
	HRESULT hr = StringFromCLSID(guid, &wszGUID);
	assert(SUCCEEDED(hr));

#ifndef _UNICODE
	// Covert from wide characters to non-wide.
	wcstombs(szGUID, wszGUID, length);
#else
	wcscpy(szGUID, wszGUID);
#endif // _UNICODE

	// Free memory.
	CoTaskMemFree(wszGUID);
}

//
// Delete a key and all of its descendents.
//
LONG recursiveDeleteKey(HKEY hKeyParent,           // Parent of key to delete
                        LPCTSTR lpszKeyChild)  // Key to delete
{
	// Open the child.
	HKEY hKeyChild;
	LONG lRes = RegOpenKeyEx(hKeyParent, lpszKeyChild, 0,
	                         KEY_ALL_ACCESS, &hKeyChild);
	if (lRes != ERROR_SUCCESS)
	{
		return lRes;
	}

	// Enumerate all of the decendents of this child.
	FILETIME time;
	TCHAR szBuffer[256];
	DWORD dwSize = 256;
	while (RegEnumKeyEx(hKeyChild, 0, szBuffer, &dwSize, NULL,
	                    NULL, NULL, &time) == S_OK)
	{
		// Delete the decendents of this child.
		lRes = recursiveDeleteKey(hKeyChild, szBuffer);
		if (lRes != ERROR_SUCCESS)
		{
			// Cleanup before exiting.
			RegCloseKey(hKeyChild);
			return lRes;
		}
		dwSize = 256;
	}

	// Close the child.
	RegCloseKey(hKeyChild);

	// Delete this child.
	return RegDeleteKey(hKeyParent, lpszKeyChild);
}

//
// Determine if a particular subkey exists.
//
BOOL SubkeyExists(LPCTSTR pszPath,    // Path of key to check
                  LPCTSTR szSubkey)   // Key to check
{
	HKEY hKey;
	TCHAR szKeyBuf[80];

	// Copy keyname into buffer.
#ifndef _UNICODE
	strcpy(szKeyBuf, pszPath);
#else
	wcscpy(szKeyBuf, pszPath);
#endif // _UNICODE

	// Add subkey name to buffer.
	if (szSubkey != NULL)
	{
#ifndef _UNICODE
		strcat(szKeyBuf, _T("\\"));
		strcat(szKeyBuf, szSubkey);
#else
		wcscpy(szKeyBuf, _T("\\"));
		wcscat(szKeyBuf, szKeyBuf);
#endif // _UNICODE
	}

	// Determine if key exists by trying to open it.
	LONG lResult = ::RegOpenKeyEx(HKEY_CLASSES_ROOT, 
	                              szKeyBuf,
	                              0,
	                              KEY_ALL_ACCESS,
	                              &hKey);
	if (lResult == ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return TRUE;
	}
	return FALSE;
}

//
// Create a key and set its value.
//   - This helper function was borrowed and modifed from
//     Kraig Brockschmidt's book Inside OLE.
//
BOOL setKeyAndValue(LPCTSTR szKey,
                    LPCTSTR szSubkey,
                    LPCTSTR szValue)
{
	HKEY hKey;
	TCHAR szKeyBuf[1024];

	// Copy keyname into buffer.
#ifndef _UNICODE
	strcpy(szKeyBuf, szKey);
#else
	wcscpy(szKeyBuf, szKey);
#endif // _UNICODE

	// Add subkey name to buffer.
	if (szSubkey != NULL)
	{
#ifndef _UNICODE
		strcat(szKeyBuf, _T("\\"));
		strcat(szKeyBuf, szSubkey);
#else
		wcscat(szKeyBuf, _T("\\"));
		wcscat(szKeyBuf, szSubkey);
#endif // _UNICODE
	}

	// Create and open key and subkey.
	long lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT ,
	                              szKeyBuf, 
	                              0, NULL, REG_OPTION_NON_VOLATILE,
	                              KEY_ALL_ACCESS, NULL, 
	                              &hKey, NULL);
	if (lResult != ERROR_SUCCESS)
	{
		return FALSE;
	}

	// Set the Value.
	if (szValue != NULL)
	{
		RegSetValueEx(hKey, NULL, 0, REG_SZ, 
		              (LPBYTE)szValue, 
#ifndef _UNICODE
		              strlen(szValue) + 1
#else
					  wcslen(szValue) * sizeof (TCHAR) + 1
#endif // _UNICODE
					  );
	}

	RegCloseKey(hKey);
	return TRUE;
}
