#include "StdAfx.h"
#include "Sequence.h"

IMPLEMENT_SERIAL(Sequence, CObject, VERSIONABLE_SCHEMA)

// sequence file marker
static const BYTE SEQ_MARKER[3] = {
	'S',
	'E',
	'Q'
}; 

Sequence::Sequence(void)
{
	Clear();
}

Sequence::~Sequence(void)
{
}

void Sequence::ToggleSub(const CPoint& pt)
{
	int x = pt.x % NSUBS;
	int y = pt.y % NINSTRUMENTS;
	m_beats[y][x] = !m_beats[y][x];
}

bool Sequence::GetBeat(int x, int y) const
{
	x = x % NSUBS;
	y = y % NINSTRUMENTS;
	return m_beats[y][x];
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
