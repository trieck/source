///////////////////////////////////////////////////////////////////////
//
//	MEASURE.CPP
//
//	Copyright © 1999 Rieck Enterprises
//

#include "stdafx.h"
#include "baseinc.h"
#include "neptune.h"
#include <math.h>

static const int clefOffset = 5;                                // horizontal clef offset
static const int clefWidth = 23;								// width of the clef
static const int ksXOffset = 2;									// horizontal key signature offset
static const int ksYOffset = 11;								// vertical key signature offset
static const int defaultNoteAlign = 8;							// default note alignment
static const int endOffset = 5;									// end of measure offset
static const COLORREF selectedColor = RGB(0xFF, 0xFF, 0xC0);    // selected Color
static const int vicinity = 2;                                  // note vicinity

//
// Constructor
//
Measure :: Measure(const Staff * pStaff, const CRect & rc, UINT Clef)
		: m_ks(0),
		m_ts(4, Crotchet),
		m_pStaff(pStaff)
{
	ASSERT_VALID(m_pStaff);
	m_pClef = NULL;
	m_fSelected = FALSE;
	m_Tempo = DEFAULT_TEMPO;
	CopyRect(rc);

	if (Clef != 0) {
		m_pClef = new CBitmap();
		ASSERT_VALID(m_pClef);
		m_pClef->LoadBitmap(Clef);
	}

	SetNoteAlign();
}

//
// Destructor
//
Measure :: ~Measure()
{
	if (m_pClef != NULL)
		delete m_pClef;
}

//
// Clear
//
void Measure :: Clear()
{
	m_Beats.clear();
	m_ts.SetTimeSignature(4, Crotchet);
	m_ks.assign(0);
	SetTempo(DEFAULT_TEMPO);
	m_fSelected = FALSE;
}

//
// SetNoteAlign
//
void Measure :: SetNoteAlign()
{
	m_NoteAlign = defaultNoteAlign;

	if (m_pClef != NULL) {
		BITMAP bm;
		m_pClef->GetObject(sizeof(BITMAP), &bm);
		m_NoteAlign += bm.bmWidth;
	}

	m_NoteAlign += m_ks.GetSize().cx + ksXOffset;
}

//
// AddNote
//
BOOL Measure :: AddNote(Note * pNote)
{
	ASSERT_VALID(pNote);

	// Check whether this note is in the
	// vicinity of a note list and has the same
	// duration but not the same value (data).
	// If so add it to the measure at the same
	// horizontal position -- a chord
	NoteList * pList = GetVicinity(pNote);
	if (pList && !pList->ismember(pNote) &&
	        pList->GetDuration() == pNote->GetDuration()) {
		pList->AddTail(pNote);
		AdjustNotePositions();
		return TRUE;
	}

	// Is there enough room on this measure
	// to provide for this note
	if (!CanAddNote(pNote))
		return FALSE;

	// Check whether this note falls
	// between two other notes on the measure
	NoteList * pLeft = NULL;
	NoteList * pRight = NULL;
	if (IsBetween(pNote, &pLeft, &pRight)) {
		m_Beats.splice(m_Beats.Find(pLeft), pNote);
		AdjustNotePositions();
		return TRUE;
	}

	m_Beats.insert(pNote);
	AdjustNotePositions();

	return TRUE;
}

//
// RemoveNote
//
BOOL Measure :: RemoveNote(Note * pNote)
{
	ASSERT_VALID(pNote);

	POSITION pos;
	NoteList * pNoteList = m_Beats.find(pNote, pos);
	if (pNoteList != NULL) {
		pNoteList->Remove(pNote);
		if (pNoteList->IsEmpty()) {
			m_Beats.remove(pNoteList);
			AdjustNotePositions();
		}
		return TRUE;
	}

	return FALSE;
}

//
// ResetForward
//
Note * Measure :: ResetForward(Note * pNote)
{
	ASSERT_VALID(pNote);

	Modifier mod = m_ks.getmodifier(pNote->GetName());
	BYTE data = pNote->GetBaseData();

	POSITION pos = NULL;
	NoteList * pList = m_Beats.find(pNote, pos);
	ASSERT_VALID(pList);

	while (pos != NULL) {
		pList = m_Beats.GetNext(pos);
		ASSERT_VALID(pList);

		Note * pForward = pList->find(data);
		if (pForward != NULL) {
			Tool tool;
			tool.type = ModifierTool;
			tool.icon = ModifierToIcon(mod);
			tool.user = mod;
			pForward->SetModifier(&tool);
			return pForward;
		}
	}
	return NULL;
}

//
// CanAddNote
//
BOOL Measure :: CanAddNote(const Note * pNote) const
{
	ASSERT(pNote != NULL);

	float Total = m_ts.GetDuration();

	// Iterate through the existing notes
	float duration = float(1) / pNote->GetDuration();
	POSITION pos = m_Beats.GetHeadPosition();
	while (pos != NULL) {
		NoteList * pNoteList = m_Beats.GetNext(pos);
		ASSERT_VALID(pNoteList);

		duration += float(1) / pNoteList->GetDuration();
	}

	return duration <= Total;
}

//
// AdjustNotePositions
//
void Measure :: AdjustNotePositions()
{
	int cx = left + m_NoteAlign;

	POSITION pos = m_Beats.GetHeadPosition();
	while (pos != NULL) {
		NoteList * pNoteList = m_Beats.GetNext(pos);
		ASSERT_VALID(pNoteList);

		POSITION notepos = pNoteList->GetHeadPosition();
		while (notepos != NULL) {
			Note * pNote = pNoteList->GetNext(notepos);
			ASSERT_VALID(pNote);
			pNote->SetX(cx);
		}

		const Note * pHead = pNoteList->GetHead();
		ASSERT_VALID(pHead);

		cx += GetNoteWidth(pHead);
	}
}

//
// GetNoteSpanWidth
//
int Measure :: GetNoteSpanWidth() const
{
	return Width() - m_NoteAlign - endOffset;
}

//
// GetNoteWidth
//
int Measure :: GetNoteWidth(const Note * pNote) const
{
	ASSERT_VALID(pNote);

	float Total = m_ts.GetDuration();

	float duration = float(1) / pNote->GetDuration();
	float percentage = duration / Total;

	return int (GetNoteSpanWidth() * percentage);
}

//
// Render
//
void Measure :: Render(CDC * pDC) const
{
	ASSERT_VALID(pDC);

	int cookie = pDC->SaveDC();

	if (m_fSelected)
		RenderSelected(pDC);

	if (m_pClef != NULL)
		RenderClef(pDC);

	RenderKeySignature(pDC);

	CPen aPen(PS_SOLID, 1, penColor);
	CPen * pOldPen = pDC->SelectObject(&aPen);

	// Draw the measures borders
	pDC->MoveTo(left, top);
	pDC->LineTo(left, bottom);

	pDC->MoveTo(right, top);
	pDC->LineTo(right, bottom);

	pDC->SelectObject(pOldPen);

	// Render the notes
	RenderNotes(pDC);

	pDC->RestoreDC(cookie);
}

//
// RenderSelected
//
void Measure :: RenderSelected(CDC * pDC) const
{
	ASSERT(pDC != NULL);

	CRect rc = *this;

	pDC->FillSolidRect(rc, selectedColor);
}

//
// RenderClef
//
void Measure :: RenderClef(CDC * pDC) const
{
	ASSERT_VALID(pDC);
	ASSERT_VALID(m_pClef);

	Neptune::DrawTransparentBitmap(
	    (CBitmap*)m_pClef,
	    pDC,
	    left + clefOffset,
	    top,
	    COLOR_WHITE);
}

//
// RenderKeySignature
//
void Measure :: RenderKeySignature(CDC * pDC) const
{
	ASSERT_VALID(pDC);

	if (m_pClef != NULL)
		m_ks.Render(pDC, left + clefOffset + clefWidth, top - ksYOffset);
	else m_ks.Render(pDC, left + clefOffset, top - ksYOffset);
}

//
// RenderNotes
//
void Measure :: RenderNotes(CDC * pDC) const
{
	POSITION pos = m_Beats.GetHeadPosition();
	while (pos != NULL) {
		NoteList * pNoteList = m_Beats.GetNext(pos);
		ASSERT_VALID(pNoteList);

		POSITION notepos = pNoteList->GetHeadPosition();
		while (notepos != NULL) {
			Note * pNote = pNoteList->GetNext(notepos);
			ASSERT_VALID(pNote);
			pNote->Render(pDC);
		}
	}
}

//
// GetNote
//
Note * Measure :: GetNote(const CPoint & pt) const
{
	POSITION pos = m_Beats.GetHeadPosition();
	while (pos != NULL) {
		NoteList * pNoteList = m_Beats.GetNext(pos);
		ASSERT_VALID(pNoteList);

		POSITION notepos = pNoteList->GetHeadPosition();
		while (notepos != NULL) {
			Note * pNote = pNoteList->GetNext(notepos);
			ASSERT_VALID(pNote);
			if (pNote->PtOnHead(pt))
				return pNote;
		}
	}

	return NULL;
}

//
// IsBetween
//
BOOL Measure :: IsBetween(const Note * pNote, NoteList ** ppLeft, NoteList ** ppRight) const
{
	ASSERT_VALID(pNote);
	ASSERT(ppLeft != NULL);
	ASSERT(ppRight != NULL);

	*ppLeft = NULL;
	*ppRight = NULL;

	// Determine the note list adjacent to the left
	POSITION pos = m_Beats.GetHeadPosition();
	while (pos != NULL) {
		POSITION prev = pos;
		NoteList * pNoteList = m_Beats.GetNext(pos);
		ASSERT_VALID(pNoteList);

		if (pNoteList->GetX() >= pNote->GetX()) {
			pos = prev;
			break;
		}
		else *ppLeft = pNoteList;
	}

	// Determine the note list adjacent to the right
	if (pos != NULL && *ppLeft != NULL) {
		NoteList * pNoteList = m_Beats.GetAt(pos);
		ASSERT_VALID(pNoteList);

		if (pNoteList->GetX() > pNote->GetX()) {
			*ppRight = pNoteList;
			return TRUE;
		}
	}

	return FALSE;
}

//
// Serialize
//
void Measure :: Serialize(CArchive & ar)
{
	if (ar.IsStoring()) {
		ar << m_Tempo;
	}
	else {
		ar >> m_Tempo;
	}

	m_Beats.Serialize(ar);
}

//
// GetVicinity
//
NoteList * Measure :: GetVicinity(const Note * pNote) const
{
	ASSERT_VALID(pNote);

	POSITION pos = m_Beats.GetHeadPosition();
	while (pos != NULL) {
		NoteList * pNoteList = m_Beats.GetNext(pos);
		ASSERT_VALID(pNoteList);

		const Note * pHead = pNoteList->GetHead();
		ASSERT_VALID(pHead);

		int cx = abs(pHead->GetX() - pNote->GetX());
		if (cx <= vicinity)
			return pNoteList;
	}

	return NULL;
}

//
// GetNoteCount
//
int Measure :: GetNoteCount() const
{
	int count = 0;

	POSITION pos = m_Beats.GetHeadPosition();
	while (pos != NULL) {
		NoteList * pNoteList = m_Beats.GetNext(pos);
		ASSERT_VALID(pNoteList);

		count += pNoteList->GetCount();
	}

	return count;
}

//
// SetKeySignature
//
void Measure :: SetKeySignature(int index)
{
	m_ks.assign(index);
	SetNoteAlign();
	AdjustNotePositions();
}

