/////////////////////////////////////////////////////////////////////////////
//
//	COMINIT.H : COM Libraries Initializer
//
//	Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved.
//

#ifndef __COMINIT_INCLUDE_H__
#define __COMINIT_INCLUDE_H__

#include <objbase.h>

/////////////////////////////////////////////////////////////////////////////
class COMInitializer
{
public:
	COMInitializer() {
		hr = CoInitialize(NULL);
	}
	~COMInitializer() {
		if (SUCCEEDED(hr))
			CoUninitialize();
	}

private:
	HRESULT hr;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __COMINIT_INCLUDE_H__