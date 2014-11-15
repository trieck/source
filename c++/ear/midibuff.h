///////////////////////////////////////////////////////////////////////
//
//	MIDIBUFF.H : midi data buffer
//
//	Copyright (c) 2000 Rieck Enterprises
//

#ifndef __MIDIBUFF_H__
#define __MIDIBUFF_H__

///////////////////////////////////////////////////////////////////////
class MidiBuffer {
public:
    // Construction / Destruction
    MidiBuffer();
    virtual ~MidiBuffer();

    // Interface
    void Transform (BYTE note1, BYTE note2);
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

///////////////////////////////////////////////////////////////////////

#endif // __MIDIBUFF_H__