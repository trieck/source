///////////////////////////////////////////////////////////////////////
//
//	NOTELIST.CPP : doubly linked list of notes
//
//  This class represents a vertical list of notes
//  represented as a musical chord
//
//	Copyright © 1999 Rieck Enterprises
//

#include "stdafx.h"
#include "baseinc.h"
#include "notelist.h"

//
// SerializeElements
//
template <>
void AFXAPI SerializeElements <Note *> ( CArchive& ar, Note ** ppNote, int nCount)
{
	ASSERT(ppNote != NULL);

	if (ar.IsLoading()) {
		*ppNote = new Note;
	}

	ASSERT_VALID(*ppNote);
	(*ppNote)->Serialize(ar);
}

IMPLEMENT_SERIAL(NoteList, CObject, VERSIONABLE_SCHEMA)

//
// Constructor
//
NoteList :: NoteList()
{
}

//
// Destructor
//
NoteList :: ~NoteList()
{
	Clear();
}

//
// Copy Constructor
//
NoteList :: NoteList(const NoteList & list)
{
	POSITION pos = list.GetHeadPosition();
	while (pos != NULL) {
		Note * pNote = list.GetNext(pos);
		ASSERT_VALID(pNote);

		Note * pNewNote = new Note(*pNote);
		ASSERT_VALID(pNewNote);

		AddTail(pNewNote);
	}
}

//
// operator =
//
NoteList & NoteList :: operator = (const NoteList & list)
{
	if (this != &list) {
		Clear();

		POSITION pos = list.GetHeadPosition();
		while (pos != NULL) {
			Note * pNote = list.GetNext(pos);
			ASSERT_VALID(pNote);

			Note * pNewNote = new Note(*pNote);
			ASSERT_VALID(pNewNote);

			AddTail(pNewNote);
		}
	}

	return * this;
}

//
// Clear
//
void NoteList :: Clear()
{
	POSITION pos = GetHeadPosition();
	while (pos != NULL) {
		Note * pNote = GetNext(pos);
		ASSERT_VALID(pNote);

		delete pNote;
	}

	RemoveAll();
}

//
// ismember
//
BOOL NoteList :: ismember(const Note * pNote) const
{
	ASSERT_VALID(pNote);

	// Do a comparison based on data

	POSITION pos = GetHeadPosition();
	while (pos != NULL) {
		Note * pNextNote = GetNext(pos);
		ASSERT_VALID(pNextNote);

		if (pNextNote->GetData() == pNote->GetData())
			return TRUE;
	}

	return FALSE;
}

//
// find
//
Note * NoteList :: find(BYTE data) const
{
	POSITION pos = GetHeadPosition();
	while (pos != NULL) {
		Note * pNote = GetNext(pos);
		ASSERT_VALID(pNote);

		// Do a comparison based on data

		if (pNote->GetData() == data)
			return pNote;
	}

	return NULL;
}

//
// GetDuration
//
Duration NoteList :: GetDuration() const
{
	ASSERT(!IsEmpty());

	return GetHead()->GetDuration();
}

//
// GetX
//
int NoteList :: GetX() const
{
	ASSERT(!IsEmpty());

	return GetHead()->GetX();
}

//
// Remove
//
BOOL NoteList :: Remove(Note * pNote)
{
	ASSERT_VALID(pNote);

	POSITION pos = Find(pNote);
	if (pos != NULL) {
		RemoveAt(pos);
		delete pNote;
		return TRUE;
	}

	return FALSE;
}

//
// Serialize
//
void NoteList :: Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring()) {
		ar.WriteCount(m_nCount);
		for (CNode* pNode = m_pNodeHead; pNode != NULL; pNode = pNode->pNext) {
			ASSERT(AfxIsValidAddress(pNode, sizeof(CNode)));
			SerializeElements<Note *>(ar, &pNode->data, 1);
		}
	}
	else {
		DWORD nNewCount = ar.ReadCount();
		while (nNewCount--) {
			Note * newData;
			SerializeElements<Note *>(ar, &newData, 1);
			AddTail(newData);
		}
	}
}



