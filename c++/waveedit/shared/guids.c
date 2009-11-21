/*------------------------------
	Module	:	GUIDS.C
	Purpose	:	Define GUIDs
	Date	:	11/23/1997
------------------------------*/
#include <objbase.h>
#include <initguid.h>

typedef IID CLSID;

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

// {B806C9F5-636F-11d1-80C0-00207812120D}
	const CLSID CLSID_WaveLib =
	{0xb806c9f5, 0x636f, 0x11d1, {0x80, 0xc0, 0x0, 0x20, 0x78, 0x12, 0x12, 0xd}};

// {36BC7E80-631C-11d1-80C0-00207812120D}
	const IID IID_IWaveLib =
	    {0x36bc7e80, 0x631c, 0x11d1, {0x80, 0xc0, 0x0, 0x20, 0x78, 0x12, 0x12, 0xd}};

#ifdef __cplusplus
}
#endif // __cplusplus