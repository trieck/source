#pragma once

#include "midicommon.h"

///////////////////////////////////////////////////////////////////////
class MidiBuffer {
public:
	// Construction / Destruction
	MidiBuffer();
	virtual ~MidiBuffer();

	// Interface
	operator MIDIHDR* () {
		return &m_header;
	}

	// Implementation
protected:
	void Alloc();
	void Free();

private:
	MIDIHDR m_header;
};

