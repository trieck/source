///////////////////////////////////////////////////////////////////////
//
// COMMON.H : common include
//
// Copyright (c) 1999 Rieck Enterprises
//

#ifndef __COMMON_H__
#define __COMMON_H__

#pragma warning(disable:4786) // disable truncation warning

#include <assert.h>
#include <windows.h>
#include <string>
#include <map>

using std::string;
using std::map;

#ifndef ASSERT
#define ASSERT assert
#endif // ASSERT

#include "winapp.h"		// application class
#include "window.h"		// window class
#include "framewnd.h"	// frame windows

/////////////////////////////////////////////////////////////////////////////
// global definitions

#endif // __COMMON_H__