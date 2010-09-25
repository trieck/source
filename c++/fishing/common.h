/////////////////////////////////////////////////////////////////////////////
//
//	COMMON.H : common include file
//

#ifndef __COMMON_H__
#define __COMMON_H__

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

typedef struct {
	TCHAR server[_MAX_FNAME];
	TCHAR uid[_MAX_FNAME];
	TCHAR pwd[_MAX_FNAME];
} DbInfo;

extern DbInfo dbinfo;	// database settings

#endif // __COMMON_H__