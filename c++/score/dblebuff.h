/////////////////////////////////////////////////////////////////////////////
//
//	DBLEBUFF.H : double buffer
//
//	This class implements a double buffer scheme
//	for streaming MIDI data
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#ifndef __DBLEBUFF_H__
#define __DBLEBUFF_H__

#define BUFFERS 2

/////////////////////////////////////////////////////////////////////////////
class DoubleBuffer {
public:
    // Construction / Destruction
    DoubleBuffer();
    virtual ~DoubleBuffer();

    // Interface
    BOOL SetFront(MIDIHDR*);
    BOOL SetBack(MIDIHDR*);

    inline MIDIHDR* GetFront() {
        return &m_Buffers[0];
    }
    inline MIDIHDR* GetBack() {
        return &m_Buffers[1];
    }

    // Implementation
protected:
    void AllocBuffers();
    void FreeBuffers();
    BOOL ReallocBuffer(MIDIHDR *) const;
    BOOL Set(MIDIHDR *, MIDIHDR *) const;

    MIDIHDR m_Buffers[BUFFERS];
};
/////////////////////////////////////////////////////////////////////////////


#endif // __DBLEBUFF_H__