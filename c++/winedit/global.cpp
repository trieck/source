/////////////////////////////////////////////////////////////////////////////
//
// GLOBAL.CPP : global helper functions
//
// Copyright (c) 1999 Rieck Enterprises, All Rights Reserved.
//

#include "stdafx.h"
#include "global.h"

// Helper functions
static CString GetProfilePath();

//
// GetProfileString
//
CString GetProfileString(LPCSTR section, LPCSTR entry)
{
	CHAR buffer[256];
	buffer[0] = '\0';

	GetPrivateProfileString(section, entry, "", buffer, sizeof(buffer), GetProfilePath());

	return buffer;
}

//
// GetProfileInt
//
int GetProfileInt(LPCSTR section, LPCSTR entry)
{
	return GetPrivateProfileInt(section, entry, -1, GetProfilePath());
}

//
// SetProfileString
//
BOOL SetProfileString(LPCSTR section, LPCSTR entry, LPCSTR value)
{
	return WritePrivateProfileString(section, entry, value, GetProfilePath());
}

//
// SetProfileInt
//
BOOL SetProfileInt(LPCSTR section, LPCSTR entry, int value)
{
	CString strValue;
	strValue.Format("%d", value);

	return SetProfileString(section, entry, strValue);
}

// Helper functions

//
// GetProfilePath
//
CString GetProfilePath()
{
	CHAR module[MAX_PATH + _MAX_FNAME + 1];
	GetModuleFileName(NULL, module, MAX_PATH + _MAX_FNAME);

	CString ininame = module;
	int nPosition = ininame.ReverseFind('.');
	ininame = ininame.Left(nPosition) + ".ini";

	DWORD attr = GetFileAttributes(ininame);
	if (attr & FILE_ATTRIBUTE_READONLY) {
		attr &= ~FILE_ATTRIBUTE_READONLY;
		SetFileAttributes(ininame, attr);
	}

	return ininame;
}

int GetTextWidth(CWnd *pWnd, LPCSTR str)
{
	ASSERT_VALID(pWnd);
	ASSERT(IsWindow(*pWnd));
	ASSERT(str != NULL);

	CDC * pDC = pWnd->GetDC();
	ASSERT_VALID(pDC);

	CFont * pFont = pWnd->GetFont();
	ASSERT_VALID(pFont);

	CFont * pOldFont = pDC->SelectObject(pFont);

	SIZE sz;
	::GetTextExtentPoint32(*pDC, str, strlen(str), &sz);

	pDC->SelectObject(pOldFont);

	pWnd->ReleaseDC(pDC);

	return sz.cx;
}

CString Comma(UINT i)
{
	CString input, output;
	input.Format("%ld", i);

	int n = input.GetLength();

	for (int j = n - 1, k = 1; j >= 0; j--, k++) {
		output += input[(int)j];
		if (k % 3 == 0 && j > 0 && j < n - 1)
			output += ',';
	}

	strrev(output.GetBuffer(output.GetLength()));
	output.ReleaseBuffer();

	return output;
}
