///////////////////////////////////////////////////////////////////////
//
//	INPUTDEVS.H
//
//	Copyright © 1999 Rieck Enterprises
//

#ifndef __INPUTDEVS_H__
#define __INPUTDEVS_H__

#include "mididevs.h"

///////////////////////////////////////////////////////////////////////
class InputDevices : public MidiDevices
{
public:
	// Construction / Destruction
	InputDevices();
	virtual ~InputDevices();

	// Interface
	UINT Count() const;
	MidiDevice * GetDevice(UINT) const;
protected:
	// Implementation
};
///////////////////////////////////////////////////////////////////////


#endif // __INPUTDEVS_H__