///////////////////////////////////////////////////////////////////////
//
//	OUTPUTDEVS.H
//
//	Copyright © 1999 Rieck Enterprises
//

#ifndef __OUTPUTDEVS_H__
#define __OUTPUTDEVS_H__

#include "mididevs.h"

///////////////////////////////////////////////////////////////////////
class OutputDevices : public MidiDevices {
public:
	// Construction / Destruction
	OutputDevices();
	virtual ~OutputDevices();

	// Interface
	UINT Count() const;
	MidiDevice * GetDevice(UINT) const;
	MidiDevice * GetStream(UINT) const;

protected:
	// Implementation
};
///////////////////////////////////////////////////////////////////////

#endif // __OUTPUTDEVS_H__