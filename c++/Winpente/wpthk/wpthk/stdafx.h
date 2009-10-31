// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#define DllExport __declspec(dllexport)

// Set external linkage options
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif	// __cplusplus



