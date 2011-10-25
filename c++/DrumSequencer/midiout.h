/////////////////////////////////////////////////////////////////////////////
//
//	MIDIOUT.H : MIDI Output device module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MIDIOUT_H__
#define __MIDIOUT_H__

#include "OutputDev.h"
#include "MidiMessage.h"

/////////////////////////////////////////////////////////////////////////////
class MidiOutput : public OutputDevice {
	friend class OutputDevices;

protected:
	// Construction / Destruction
	MidiOutput(LPMIDIOUTCAPS, UINT);
public:
	virtual ~MidiOutput();

	virtual MMRESULT Open();
	virtual MMRESULT Close();
	MMRESULT ShortMessage(const MidiMessage &);
	MMRESULT LongMessage(LPSTR, UINT);
	MMRESULT GetVolume(LPDWORD);
	MMRESULT SetVolume(DWORD);

	inline operator HMIDIOUT() const {
		return (HMIDIOUT) m_handle;
	}

protected:
	// Implementation

	static void CALLBACK MidiOutProc(
	    HMIDIOUT hMidiOut,
	    UINT wMsg,
	    DWORD dwInstance,
	    DWORD dwParam1,
	    DWORD dwParam2);
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MIDIOUT_H__