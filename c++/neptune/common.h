/////////////////////////////////////////////////////////////////////////////
//
// COMMON.H : common include file
//

#ifndef __COMMON_H__
#define __COMMON_H__

#pragma warning(disable : 4786)

/////////////////////////////////////////////////////////////////////////////
#include <winsock2.h>
#include <tchar.h>
#include <sql.h>
#include <sqlext.h>
#include <crtdbg.h>
#include <malloc.h>

#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <strstream>
#include <vector>

using namespace std;
typedef basic_string<TCHAR> tstring;

extern HINSTANCE hInstance;
/////////////////////////////////////////////////////////////////////////////

#endif // __COMMON_H__