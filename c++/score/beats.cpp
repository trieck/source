///////////////////////////////////////////////////////////////////////
//
//	BEATS.CPP : list of note lists
//
//	Copyright © 1999 Rieck Enterprises
//

#include "stdafx.h"
#include "baseinc.h"

//
// SerializeElements
//
template <>
void AFXAPI SerializeElements <NoteList *> ( CArchive& ar, NoteList ** ppNoteList, int nCount)
{
	ASSERT(ppNoteList != NULL);

	if (ar.IsLoading()) {
		*ppNoteList = new NoteList;
	}

	ASSERT_VALID(*ppNoteList);
	(*ppNoteList)->Serialize(ar);
}

IMPLEMENT_SERIAL(Beats, CObject, VERSIONABLE_SCHEMA)

//
// Constructor
//
Beats :: Beats()
{
}

//
// Destructor
//
Beats :: ~Beats()
{
	clear();
}

//
// insert
//
void Beats :: insert(Note * pNote)
{
	ASSERT_VALID(pNote);

	NoteList * pNoteList = new NoteList;
	ASSERT_VALID(pNoteList);

	pNoteList->AddTail(pNote);
	AddTail(pNoteList);
}

//
// remove
//
BOOL Beats :: remove(NoteList * pNoteList)
{
	ASSERT_VALID(pNoteList);

	POSITION pos = Find(pNoteList);
	while (pos != NULL) {
		RemoveAt(pos);
		delete pNoteList;
		return TRUE;
	}

	return FALSE;
}

//
// clear
//
void Beats :: clear()
{
	POSITION pos = GetHeadPosition();
	while (pos != NULL) {
		NoteList * pList = GetNext(pos);
		ASSERT_VALID(pList);

		delete pList;
	}

	RemoveAll();
}

//
// find
//
NoteList * Beats :: find(const Note * pNote, POSITION & rpos)
{
	ASSERT_VALID(pNote);

	rpos = NULL;
	POSITION pos = GetHeadPosition();
	while (pos != NULL) {
		NoteList * pNoteList = GetNext(pos);
		ASSERT_VALID(pNoteList);

		POSITION notepos = pNoteList->GetHeadPosition();
		while (notepos != NULL) {
			Note * pNextNote = pNoteList->GetNext(notepos);
			ASSERT_VALID(pNextNote);

			if (pNextNote == pNote) {
				rpos = pos;
				return pNoteList;
			}
		}
	}

	return NULL;
}

//
// splice
// insert after a position
POSITION Beats :: splice(POSITION pos, Note * pNote)
{
	ASSERT_VALID(pNote);

	NoteList * pNoteList = new NoteList;
	ASSERT_VALID(pNoteList);

	pNoteList->AddTail(pNote);

	return InsertAfter(pos, pNoteList);
}

//
// Serialize
//
void Beats :: Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring()) {
		ar.WriteCount(m_nCount);
		for (CNode* pNode = m_pNodeHead; pNode != NULL; pNode = pNode->pNext) {
			ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
			SerializeElements<NoteList *>(ar, &pNode->data, 1);
		}
	}
	else {
		DWORD nNewCount = ar.ReadCount();
		while (nNewCount--) {
			NoteList * newData;
			SerializeElements<NoteList *>(ar, &newData, 1);
			AddTail(newData);
		}
	}
}


