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
#include <memory>

#ifdef _MSC_VER
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#endif // _MSC_VER

#define ANON_BEGIN	namespace {
#define ANON_END	}

extern const POINT NIL_MOVE;
extern bool isNilMove(const POINT &pt);
extern bool isEqualPoint(const POINT &pt1, const POINT &pt2);

#endif // __COMMON_H__
