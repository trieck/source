///////////////////////////////////////////////////////////////////////
//
//	REGKEY.H
//
//	Copyright © 1999 Rieck Enterprises
//

#ifndef __REGKEY_H__
#define __REGKEY_H__

typedef CByteArray * LPBYTEARRAY;

class CRegKey {
public:
	CRegKey();
	virtual ~CRegKey();

	LONG Close();
	LONG Open(HKEY, LPCTSTR, REGSAM = KEY_ALL_ACCESS);
	LONG GetValue(LPTSTR, LPCTSTR, LPDWORD);												// Get a string value
	LONG GetValue(LPBYTEARRAY, LPCTSTR, LPDWORD);											// Get a binary value
	LONG GetValue(LPDWORD, LPCTSTR);														// Get a DWORD value
	LONG SetValue(LPCTSTR, LPCTSTR);														// Set a string value
	LONG SetValue(LPBYTE, DWORD, LPCTSTR);													// Set a binary value
	LONG SetValue(DWORD, LPCTSTR);															// Set a DWORD value
	LONG EnumKeys(LPTSTR, LONG, LPDWORD);													// Enumerate keys
	LONG EnumValues(DWORD, LPTSTR, LPDWORD, LPDWORD = NULL, LPBYTE = NULL, LPDWORD = NULL);	// Enumerate Values
protected:
	HKEY m_hKey;
};
#endif // __REGKEY_H__