///////////////////////////////////////////////////////////////////////
//
//	MEASURE.H
//
//	Copyright © 1999 Rieck Enterprises
//

#ifndef __MEASURE_H__
#define __MEASURE_H__

///////////////////////////////////////////////////////////////////////
class Measure : public CRect, public CObject
{
    friend class Staff;
public:
	// Construction / Destruction
    Measure(const Staff *, const CRect & rc, UINT Clef = 0);
    virtual ~Measure();

	// Interface
    BOOL AddNote(Note *);
    BOOL RemoveNote(Note *);
	Note * ResetForward(Note *);
    void Render(CDC *) const;
    void RenderSelected(CDC *) const;
    Note * GetNote(const CPoint &) const;
    void Serialize(CArchive & ar);
    int GetNoteCount() const;
    const Staff * GetStaff() const { return m_pStaff; }
    BOOL IsSelected() const { return m_fSelected; }
    VOID Select(BOOL selected) { m_fSelected = selected; }
    INT GetTempo() const { return m_Tempo; }
    void SetTempo(int tempo) { m_Tempo = tempo; }
    BOOL HasData() const { return !m_Beats.IsEmpty(); }
    const Beats * GetBeats() const { return &m_Beats; }
	const TimeSignature & GetTimeSignature() const { return m_ts; }
	const KeySignature & GetKeySignature() const { return m_ks; }
	void SetKeySignature(int index);
protected:
	// Implementation
    void Clear();
    void RenderClef(CDC * pDC) const;
    void RenderNotes(CDC * pDC) const;
	void RenderKeySignature(CDC * pDC) const;
    BOOL CanAddNote (const Note *) const;
    void SetNoteAlign();
    int GetNoteSpanWidth() const;
    int GetNoteWidth(const Note *) const;
    void AdjustNotePositions();
    BOOL IsBetween(const Note *, NoteList **, NoteList **) const;
    NoteList * GetVicinity(const Note *) const;

    int m_NoteAlign;            // Leftmost note alignment
    int m_Tempo;                // Tempo for this measure
    const Staff * m_pStaff;     // Back pointer to the staff object
    CBitmap * m_pClef;          // Clef bitmap
    BOOL m_fSelected;           // Is the measure selected
    Beats m_Beats;              // Beat list
	TimeSignature m_ts;			// Time signature
	KeySignature m_ks;			// Key signature
};
///////////////////////////////////////////////////////////////////////

#endif // __MEASURE_H__