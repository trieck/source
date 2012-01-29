/////////////////////////////////////////////////////////////////////////////
//
//	PLUTOLIB.H : Pluto library include
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#ifndef __PLUTOLIB_H__
#define __PLUTOLIB_H__

#include "targetver.h"

#include <Windows.h>
#include <WinNT.h>
#include <tchar.h>
#include <stdint.h>
#include <atlbase.h>
#include <comdef.h>

#include <iostream>
#include <string>

#ifdef UNICODE
#define tcin     std::wcin
#define tcout    std::wcout
#define tcerr    std::wcerr
#else
#define tcin     std::cin
#define tcout    std::cout
#define tcerr    std::cerr
#endif // UNICODE

using std::endl;

typedef std::basic_string<TCHAR> tstring;

#include "utility.h"
#include "exception.h"

#endif // __PLUTOLIB_H__
