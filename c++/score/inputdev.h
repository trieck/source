///////////////////////////////////////////////////////////////////////
//
//	INPUTDEV.H
//
//	Copyright © 1999 Rieck Enterprises
//

#ifndef __INPUTDEV_H__
#define __INPUTDEV_H__

#include "mididev.h"

///////////////////////////////////////////////////////////////////////
class InputDevice : public MidiDevice, private MIDIINCAPS {
	friend class InputDevices;

protected:
	// Construction / Destruction
	InputDevice(LPMIDIINCAPS, UINT);
public:
	virtual ~InputDevice();

	// Interface
	inline WORD GetMid() const {
		return wMid;
	}
	inline WORD GetPid() const {
		return wPid;
	}
	inline MMVERSION GetVersion() const {
		return vDriverVersion;
	}
	inline CString GetProduct () const {
		return szPname;
	}
	inline DWORD GetSupport() const {
		return dwSupport;
	}
	inline operator HMIDIIN() const {
		return (HMIDIIN)m_handle;
	}
	inline BOOL IsOpen() const {
		return m_handle != NULL;
	}

	static CString GetErrorText(MMRESULT);

	virtual MMRESULT Open();
	MMRESULT Close();
protected:
	// Implementation

	static void CALLBACK MidiInProc(
	    HMIDIIN hMidiIn,
	    UINT wMsg,
	    DWORD dwInstance,
	    DWORD dwParam1,
	    DWORD dwParam2);
};
///////////////////////////////////////////////////////////////////////


#endif // __INPUTDEV_H__