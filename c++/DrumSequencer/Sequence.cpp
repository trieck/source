#include "StdAfx.h"
#include "Sequence.h"

IMPLEMENT_SERIAL(Sequence, CObject, VERSIONABLE_SCHEMA)

ANON_BEGIN

// sequence file marker
const BYTE SEQ_MARKER[3] = {
    'S',
    'E',
    'Q'
};

// MIDI instruments
const BYTE INSTRUMENTS[Sequence::NINSTRUMENTS] = {
    42,	// closed hi-hat
    44,	// pedal hi-hat
    46,	// open hi-hat
    49,	// crash cymbal
    51,	// ride cymbal
    38,	// acoustic snare
    50,	// hi tom
    48,	// hi-mid tom
    45,	// low tom
    36	// bass drum1
};

ANON_END

Sequence::Sequence(void)
{
    Clear();
}

Sequence::~Sequence(void)
{
}

void Sequence::ToggleSub(const CPoint& pt)
{
    const auto x = pt.x % NSUBS;
    const auto y = pt.y % NINSTRUMENTS;
    m_beats[x][y] = !m_beats[x][y];
}

bool Sequence::GetBeat(int sub, int instrument) const
{
    sub = sub % NSUBS;
    instrument = instrument % NINSTRUMENTS;

    return m_beats[sub][instrument];
}

BYTE Sequence::GetInstrument(int i) const
{
    if (i < 0 || i >= NINSTRUMENTS)
        return 0;

    return INSTRUMENTS[i];
}

void Sequence::Clear(void)
{
    memset(&m_beats, 0, sizeof(m_beats));
}

void Sequence::Serialize(CArchive& ar)
{
    BYTE buffer[3];

    if (ar.IsStoring()) {
        ar << SEQ_MARKER[0];   // 'S'
        ar << SEQ_MARKER[1];   // 'E'
        ar << SEQ_MARKER[2];   // 'Q'

        ar.Write(&m_beats, sizeof(m_beats));

    } else {
        // Is this a valid sequence archive
        ar.Read(buffer, 3);
        if (memcmp(buffer, SEQ_MARKER, 3) != 0)
            AfxThrowArchiveException(CArchiveException::badIndex);

        UINT nRead = ar.Read(&m_beats, sizeof(m_beats));
        if (nRead != sizeof(m_beats)) {
            AfxThrowArchiveException(CArchiveException::endOfFile);
        }
    }
}

