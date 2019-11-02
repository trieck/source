/*-------------------------------------------

	Module	:	WAVEMACS.H
	Purpose	:	Wave Library macros
	Date	:	11/22/1997

-------------------------------------------*/
#ifndef __WAVEMACS_H__
#define __WAVEMAC_H__

typedef IID CLSID;

#define DECLARE_MY_GUIDS							\
		extern "C" const CLSID	CLSID_WaveLib;		\
		extern "C" const IID	IID_IWaveLib;		\

#endif // __WAVEMACS_H__