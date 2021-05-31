#pragma once

#include "Sequence.h"

///////////////////////////////////////////////////////////////////////
class MidiBuffer
{
public:
    // Construction / Destruction
    MidiBuffer() = default;
    virtual ~MidiBuffer();

    // Not copyable, but movable
    MidiBuffer(const MidiBuffer&) = delete;
    MidiBuffer& operator = (const MidiBuffer&) = delete;

    MidiBuffer(MidiBuffer&& rhs) noexcept;
    MidiBuffer& operator = (MidiBuffer&& rhs) noexcept;

    // Interface
    void Encode(const Sequence& seq);

    operator PMIDIHDR ()
    {
        return &m_header;
    }

    // Implementation
protected:
    void Alloc(UINT nSize);
    void Free();

private:
    MIDIHDR m_header{};
};

