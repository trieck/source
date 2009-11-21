/////////////////////////////////////////////////////////////////////////////
//
//	KEYSIG.CPP : defines a key signature
//
//	Copyright © 1999 Rieck Enterprises
//

#include "stdafx.h"
#include "keysig.h"
#include "resource.h"
#include "neptune.h"
#include "common.h"

// Helper functions
static BOOL operator == (const KeyNote & lhs, const KeyNote & rhs);
static BOOL operator == (const tagKeySignature & lhs, const tagKeySignature & rhs);

// bitmap table
static const UINT bitmaps [] = {
	0,
	IDB_KEYF,
	IDB_KEYBFLAT,
	IDB_KEYEFLAT,
	IDB_KEYAFLAT,
	IDB_KEYDFLAT,
	IDB_KEYGFLAT,
	IDB_KEYCFLAT,
	IDB_KEYG,
	IDB_KEYD,
	IDB_KEYA,
	IDB_KEYE,
	IDB_KEYB,
	IDB_KEYFSHARP,
	IDB_KEYCSHARP
};

//
// Constructor
//
KeySignature :: KeySignature(int index)
{
	m_pbm = NULL;
	assign(index);
}

//
// Destructor
//
KeySignature :: ~KeySignature()
{
	if (m_pbm != NULL)
		delete m_pbm;
}

//
// assign
//
void KeySignature :: assign(int index)
{
	int count = sizeof(KeySignatures) / sizeof(tagKeySignature);

	ASSERT(index >= 0);
	ASSERT(index < count);

	m_index = index;

	memcpy(static_cast<tagKeySignature *>(this),
	       &KeySignatures[m_index], sizeof(tagKeySignature));
	SetBitmap();
}

//
// SetBitmap
//
void KeySignature :: SetBitmap()
{
	if (m_pbm != NULL) {
		delete m_pbm;
		m_pbm = NULL;
	}

	UINT bm = bitmaps[m_index];
	if (bm != 0) {
		m_pbm = new CBitmap;
		m_pbm->LoadBitmap(bitmaps[m_index]);
		ASSERT(m_pbm->m_hObject != NULL);
	}
}

//
// ismodifier
//
BOOL KeySignature :: ismodifier(const KeyNote * note) const
{
	ASSERT(note != NULL);
	ASSERT(modifiers != NULL);

	const KeyNote * pmods = modifiers;
	for (; pmods <= modifiers + size; pmods++) {
		if (*note == *pmods)
			return TRUE;
	}

	return FALSE;
}

//
// getmodifier
//
Modifier KeySignature :: getmodifier(char keyname) const
{
	const KeyNote * pmods = modifiers;
	for (; pmods && pmods <= modifiers + size; pmods++) {
		if (pmods->keyname == keyname)
			return pmods->mod;
	}

	return NATURAL;
};

//
// Render
//
void KeySignature :: Render(CDC * pDC, int cx, int cy) const
{
	ASSERT_VALID(pDC);

	// Can't render a null bitmap
	if (m_pbm == NULL)
		return;

	Neptune::DrawTransparentBitmap(
	    (CBitmap*)m_pbm,
	    pDC,
	    cx,
	    cy,
	    COLOR_WHITE);
}

//
// GetSize
//
CSize KeySignature :: GetSize() const
{
	CSize size(0, 0);
	if (m_pbm != NULL) {
		BITMAP bm;
		m_pbm->GetObject(sizeof(BITMAP), &bm);
		size.cx = bm.bmWidth;
		size.cy = bm.bmHeight;
	}

	return size;
}

// Helper functions

//
// operator ==
//
BOOL operator == (const KeyNote & lhs, const KeyNote & rhs)
{
	if (lhs.keyname == rhs.keyname &&
	        lhs.mod == rhs.mod)
		return TRUE;

	return FALSE;
}

//
// operator ==
//
BOOL operator == (const tagKeySignature & lhs, const tagKeySignature & rhs)
{
	if (lhs.name.keyname == rhs.name.keyname &&
	        lhs.name.mod == rhs.name.mod)
		return TRUE;

	return FALSE;
}

