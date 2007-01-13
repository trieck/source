#ifndef __Registry_H__
#define __Registry_H__
//
// Registry.h
//   - Helper functions registering and unregistering a component.
//

#ifdef UNICODE
#define _UNICODE
#endif

#include <tchar.h>
#include <wchar.h>
#include <objbase.h>
#include <assert.h>

// This function will register a component in the Registry.
// The component calls this function from its DllRegisterServer function.
HRESULT RegisterServer(HMODULE hModule, 
                       const CLSID& clsid, 
                       LPCTSTR szFriendlyName,
                       LPCTSTR szVerIndProgID,
                       LPCTSTR szProgID,
					   const GUID& libid);

// This function will unregister a component.  Components
// call this function from their DllUnregisterServer function.
HRESULT UnregisterServer(const CLSID& clsid,
                         LPCTSTR szVerIndProgID,
                         LPCTSTR szProgID);

#endif