/////////////////////////////////////////////////////////////////////////////
//
//	DATAENGINE.H
//
//	This class is responsible for converting
//	a high level abstract measure object
//	into raw MIDI data suitable for playback
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#ifndef __DATAENGINE_H__
#define __DATAENGINE_H__

/////////////////////////////////////////////////////////////////////////////
class DataEngine {
public:
	// Construction / Destruction
	DataEngine(const Measure *);
	virtual ~DataEngine();

	// Interface
	operator MIDIHDR* () const {
		return m_pData;
	}

	// Implementation
protected:
	BOOL xform(const Measure *);
	BOOL AllocBuffer(const Measure *);
	shortEvent * NoteOn(const Note *) const;
	shortEvent * NoteOff(const Note *, BOOL delay) const;
	void SetTempo(int bpm);

	MIDIHDR * m_pData;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __DATAENGINE_H__