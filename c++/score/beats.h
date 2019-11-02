/////////////////////////////////////////////////////////////////////////////
//
//	BEATS.H : list of note lists
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#ifndef __BEATS_H__
#define __BEATS_H__

/////////////////////////////////////////////////////////////////////////////
class Beats : public CList<NoteList *, NoteList *>
{
public:
    // Construction / Destruction
    Beats();
    virtual ~Beats();

    // Interface
    void insert(Note * pNote);
    BOOL remove(NoteList *);
    void clear();
    NoteList * find(const Note * pNote, POSITION &);
    POSITION splice(POSITION pos, Note * pNote);
    void Serialize(CArchive &);

    // Implementation
protected:
    DECLARE_SERIAL(Beats);
};
/////////////////////////////////////////////////////////////////////////////


#endif // __BEATS_H__