/*-----------------------------------
	Module	: 	WPTHK.H
	Purpose	:	Standard WinPente
				Thinking Header
	Author	: 	Thomas A. Rieck
	Date	:	08/28/1997
-----------------------------------*/

#ifndef _WPTHK_H_
#define _WPTHK_H_

#include <windows.h>
#include <assert.h>

#define DllExport __declspec(dllexport)

// Set external linkage options
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif	// __cplusplus

#define FREE_FOR_ALL	0
#define PLAYER_ONE		1
#define PLAYER_TWO		2

// Global Instance Handle
extern HINSTANCE g_hModule;

#endif // _WPTHK_H_