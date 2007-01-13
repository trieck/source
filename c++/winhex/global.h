/////////////////////////////////////////////////////////////////////////////
//
// GLOBAL.H : global helper functions
//
// Copyright (c) 1999 Rieck Enterprises, All Rights Reserved.
//

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

/////////////////////////////////////////////////////////////////////////////
// Global helper functions

CString GetProfileString(LPCSTR section, LPCSTR entry);
int GetProfileInt(LPCSTR section, LPCSTR entry);
BOOL SetProfileString(LPCSTR section, LPCSTR entry, LPCSTR value);
BOOL SetProfileInt(LPCSTR section, LPCSTR entry, int value);
int GetTextWidth(CWnd *pWnd, LPCSTR str);
CString Comma(UINT);

/////////////////////////////////////////////////////////////////////////////

#endif // __GLOBAL_H__