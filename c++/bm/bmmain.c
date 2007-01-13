//////////////////////////////////////////////////////	
//	Module	:	BMMAIN.C							//
//	Purpose	:	custom bitmap functions				//
//	Author	:	Thomas A. Rieck						//
//	Date	:	4/26/97								//
//////////////////////////////////////////////////////

#include "bmmain.h"

BOOL WINAPI DllMain	(HANDLE hInst, ULONG ul_reason_for_call,
                        LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			// set global instance handle
			hInstance = hInst;
	}

	return (TRUE);
}
