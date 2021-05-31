#include "StdAfx.h"

#include "MidiBuffer.h"
#include "midicommon.h"
#include "midimessage.h"
#include "miditime.h"

ANON_BEGIN
    void noteOn(PMIDISHORTEVENT* stream, BYTE data, BYTE velocity, Duration delta);
    void noteOff(PMIDISHORTEVENT* stream, BYTE data, Duration delta);
ANON_END

MidiBuffer::MidiBuffer() : m_header({})
{
}

MidiBuffer::~MidiBuffer()
{
    Free();
}

void MidiBuffer::Alloc(UINT nSize)
{
    Free();
    m_header.dwBufferLength = nSize;
    m_header.dwBytesRecorded = 0;
    m_header.lpData = new CHAR[nSize];
    if (m_header.lpData == nullptr)
        AfxThrowMemoryException();
}

void MidiBuffer::Free()
{
    delete [] m_header.lpData;
    memset(&m_header, 0, sizeof(MIDIHDR));
}

void MidiBuffer::Encode(const Sequence& seq)
{
    // Determine the size of the buffer needed
    const auto size = (Sequence::NINSTRUMENTS * Sequence::NSUBS) /* notes */
        * sizeof(MIDISHORTEVENT);

    if (size > m_header.dwBufferLength) {
        Alloc(size);
    }

    auto pdata = reinterpret_cast<PMIDISHORTEVENT>(m_header.lpData);

    m_header.dwBytesRecorded = 0;

    for (auto i = 0; i < Sequence::NSUBS; i++) {
        auto delta = i == 0 ? EmptyNote : SixteenthNote;
        for (auto j = 0; j < Sequence::NINSTRUMENTS; j++) {
            const auto instrument = seq.GetInstrument(j);

            if (j > 0 && delta != EmptyNote) {
                delta = EmptyNote;
            }
            if (seq.GetBeat(i, j)) {
                noteOn(&pdata, instrument, 127, delta);
            } else {
                noteOff(&pdata, instrument, delta);
            }
            m_header.dwBytesRecorded += sizeof(MIDISHORTEVENT);
        }
    }
}

// Helper functions

ANON_BEGIN

    void noteOn(PMIDISHORTEVENT* stream, BYTE data, BYTE velocity, Duration delta)
    {
        MIDISHORTEVENT event{};

        MidiMessage message;
        message.SetData(data);
        message.SetStatus(NOTEON(0));
        message.SetVelocity(velocity);

        event.delta = MidiTime::DurationToTicks(delta);
        event.event = std::move(message);

        *(*stream)++ = event;
    }

    void noteOff(PMIDISHORTEVENT* stream, BYTE data, Duration delta)
    {
        MIDISHORTEVENT event{};

        MidiMessage message;
        message.SetData(data);
        message.SetStatus(NOTEOFF(0));
        message.SetVelocity(0);

        event.delta = MidiTime::DurationToTicks(delta);
        event.event = std::move(message);

        *(*stream)++ = event;
    }

ANON_END
