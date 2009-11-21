/*-----------------------------------------
	Module	:	CLIENT.CPP
	Author	:	Thomas A. Rieck
	Date	:	10/25/1997
	Purpose	:	Client for Aggregation
				Components
------------------------------------------*/

#include <objbase.h>
#include "iface.h"

typedef void**		PPVOID;
typedef IUnknown*	LPUNKNOWN;

int main()
{
	HRESULT		hr;
	IX*			pIX;
	BOOL		fInitialize;

	fInitialize = SUCCEEDED(OleInitialize(NULL));

	hr = CoCreateInstance(CLSID_Component1,
	                      NULL,
	                      CLSCTX_INPROC_SERVER,
	                      IID_IX,
	                      (PPVOID)&pIX);

	if (SUCCEEDED(hr)) {
		pIX->Fx();
		pIX->Release();
	}

	if (fInitialize)
		OleUninitialize();

	return 1;
}