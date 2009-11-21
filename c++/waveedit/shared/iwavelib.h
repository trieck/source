/*---------------------------------------

	Module	:	IWAVELIB.H
	Purpose	:	Wave Library
				Interface Declarations
	Date	:	11/22/1997

---------------------------------------*/

#ifndef __IWAVELIB_H__
#define __IWAVELIB_H__

#include <objbase.h>
#include <oleauto.h>

#include <mmsystem.h>

#include "comtypes.h"
#include "commacs.h"

////////////////////
//
// IWaveLib
//
interface IWaveLib :
IUnknown {
	// IUnknown Methods
	virtual HRESULT __stdcall QueryInterface(REFIID, PPVOID)=0;
	virtual ULONG	__stdcall AddRef()=0;
	virtual ULONG	__stdcall Release()=0;

	// IWaveLib Methods
	virtual HRESULT __stdcall GetOutputDevices(PPSAFEARRAY)=0;
	virtual HRESULT __stdcall GetInputDevices(PPSAFEARRAY)=0;
	virtual HRESULT __stdcall GetDeviceInCaps(UINT, WAVEINCAPS **)=0;
	virtual HRESULT __stdcall GetDeviceOutCaps(UINT, WAVEOUTCAPS **)=0;
};

typedef IWaveLib* LPWAVELIB;

#endif // __IWAVELIB_H__