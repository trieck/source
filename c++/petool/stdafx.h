// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "PlutoLib.h"

#define MAKE_PTR(cast, ptr, addValue)   (cast)((DWORD)(ptr) + (DWORD)(addValue))
#define MAKE_PTR_OFFSET(hi, low)        (DWORD)((PBYTE)hi - (PBYTE)low)
