/*-----------------------------------
	Module	: 	WPTHK.C
	Purpose	:	Standard WinPente
				Thinking Module
	Author	: 	Thomas A. Rieck
	Date	:	01/18/1998
-----------------------------------*/

#include "wpthk.h"

HINSTANCE g_hModule = NULL;

BOOL APIENTRY DllMain(HANDLE hModule,
					DWORD dwReason,
					LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		g_hModule = hModule;

	return TRUE;
}
