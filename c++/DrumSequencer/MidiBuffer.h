#pragma once

#include "Sequence.h"

///////////////////////////////////////////////////////////////////////
class MidiBuffer
{
public:
    // Construction / Destruction
    MidiBuffer();
    virtual ~MidiBuffer();

    // Interface
    operator MIDIHDR* ()
    {
        return &m_header;
    }

    // Implementation
protected:
    void Alloc(UINT nSize);
    void Free();

private:
    MIDIHDR m_header;
public:
    void Encode(const Sequence & seq);
};

