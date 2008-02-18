/////////////////////////////////////////////////////////////////////////////
// 
// COMMON.H : Common include
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#ifndef __COMMON_H__
#define __COMMON_H__

#pragma warning (disable:4786)

#include <stdint.h>

#include <string>
#include <memory>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>

using std::string;
using std::wstring;
using std::ostringstream;
using std::auto_ptr;
using std::map;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

typedef map<string, string> stringmap;

#define BUF_SIZE	(260)

#include "exception.h"

#endif // __COMMON_H__
