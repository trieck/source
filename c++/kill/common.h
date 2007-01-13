
#ifndef __COMMON_H__
#define __COMMON_H__

/////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef basic_string<TCHAR> tstring;
#include "xcept.h"

#ifndef _UNICODE
#define _TPROCNAME(p) #p"A"
#else
#define _TPROCNAME(p) #pL"W"
#endif // _UNICODE

/////////////////////////////////////////////////////////////////////////////

#endif // __COMMON_H__

