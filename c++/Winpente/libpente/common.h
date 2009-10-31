/////////////////////////////////////////////////////////////////////////////
//
// COMMON.H : Common include
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <map>
#include <vector>

#ifdef _MSC_VER
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#endif // _MSC_VER

class Entry;
typedef std::vector<Entry> EntryVec;

#endif // __COMMON_H__
