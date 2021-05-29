#include "StdAfx.h"

#include "MidiBuffer.h"
#include "midimessage.h"
#include "miditime.h"

ANON_BEGIN
void tempo(LPSTR* stream, int bpm);
void noteOn(LPSTR* stream, BYTE data, BYTE velocity, Duration delta);
void noteOff(LPSTR* stream, BYTE data, Duration delta);
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
        * sizeof(MIDISHORTEVENT)
        + sizeof(MIDISHORTEVENT); // tempo

    if (size > m_header.dwBufferLength) {
        Alloc(size);
    }

    auto pdata = m_header.lpData;
    tempo(&pdata, 90);
    m_header.dwBytesRecorded = sizeof(MIDISHORTEVENT);

    for (auto i = 0; i < Sequence::NSUBS; i++) {
        auto delta = i == 0 ? EmptyNote: SixteenthNote;
        for (auto j = 0; j < Sequence::NINSTRUMENTS; j++) {
            const auto instrument = seq.GetInstrument(j);

            if (j > 0 && delta != EmptyNote) {
                delta = EmptyNote;
            }
            if (seq.GetBeat(i,j)) {
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

    void tempo(LPSTR* stream, int bpm)
    {
        const auto microseconds = MidiTime::BPMToMicroseconds(bpm);

        MIDISHORTEVENT event = {};
        event.event = TEMPO_CHANGE(microseconds);

        memcpy(*stream, &event, sizeof(MIDISHORTEVENT));
        *stream += sizeof(MIDISHORTEVENT);
    }

    void noteOn(LPSTR* stream, BYTE data, BYTE velocity, Duration delta)
    {
        MIDISHORTEVENT event = {};

        MidiMessage message;
        message.SetData(data);
        message.SetStatus(NOTEON(0));
        message.SetVelocity(velocity);

        event.delta = MidiTime::DurationToTicks(delta);
        event.event = message;

        memcpy(*stream, &event, sizeof(MIDISHORTEVENT));
        *stream += sizeof(MIDISHORTEVENT);
    }

    void noteOff(LPSTR* stream, BYTE data, Duration delta)
    {
        MIDISHORTEVENT event = {};

        MidiMessage message;
        message.SetData(data);
        message.SetStatus(NOTEOFF(0));
        message.SetVelocity(0);

        event.delta = MidiTime::DurationToTicks(delta);
        event.event = message;

        memcpy(*stream, &event, sizeof(MIDISHORTEVENT));
        *stream += sizeof(MIDISHORTEVENT);
    }

ANON_END
