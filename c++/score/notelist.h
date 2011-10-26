/////////////////////////////////////////////////////////////////////////////
//
//	NOTELIST.H : doubly linked list of notes
//
//  This class represents a vertical list of notes
//  represented as a musical chord
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#ifndef __NOTELIST_H__
#define __NOTELIST_H__

/////////////////////////////////////////////////////////////////////////////
class NoteList : public CList <Note *, Note *> {
public:
	// Construction / Destruction
	NoteList();
	NoteList(const NoteList &);
	virtual ~NoteList();

	// Interface
	NoteList & operator = (const NoteList &);
	void Clear();
	BOOL ismember(const Note *) const;
	Note * find(BYTE) const;
	Duration GetDuration() const;
	BOOL Remove(Note *);
	void Serialize(CArchive & ar);
	int GetX() const;

	// Implementation
protected:
	DECLARE_SERIAL(NoteList)
};
/////////////////////////////////////////////////////////////////////////////


#endif // __NOTELIST_H__