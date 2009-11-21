///////////////////////////////////////////////////////////////////////
//
//	NOTE.CPP
//
//	Copyright © 1999 Rieck Enterprises
//

#include "stdafx.h"
#include "baseinc.h"
#include "resource.h"
#include "neptune.h"

static const int iconYOffset = 20;
static const int iconXSize = 12;
static const int iconYSize = 24;
static const int modifierXOffset = 6;
static const int modifierYOffset = 8;
static const int modifierXSize = 6;
static const int modifierYSize = 15;
static const int headXSize = 7;
static const int headYSize = 7;
static const int headYOffset = headYSize / 2;

// Durations structure
typedef struct {
	Duration d;
	UINT icon;
} Durations;

// Duration / Icon lookup table
static const Durations durationTable [] = {
	EmptyNote, 0,
	WholeNote, IDI_WHOLENOTE,
	HalfNote, IDI_HALFNOTE,
	QuarterNote, IDI_QUARTERNOTE,
	EigthNote, IDI_EIGTHNOTE,
	SixteenthNote, IDI_SIXTEENTHNOTE,
	ThirtySecondNote, IDI_THIRTYSECONDNOTE
};

// Modifiers structure
typedef struct {
	Modifier mod;
	UINT icon;
} Modifiers;

// Modifier / Icon lookup table
static const Modifiers modifierTable[] = {
	NATURAL, IDI_NATURAL,
	FLAT, IDI_FLAT,
	SHARP, IDI_SHARP
};

IMPLEMENT_SERIAL(Note, CObject, VERSIONABLE_SCHEMA)

// Helper functions
static HICON DurationToIcon(Duration d);

//
// Constructor
//
Note :: Note()
{
	mod = NATURAL;
	keyname = 0;
	m_data = 0;
	m_pos.x = 0;
	m_pos.y = 0;
	m_hIcon = NULL;
	m_hModifier = NULL;
	m_duration = EmptyNote;
}

//
// Copy Constructor
//
Note :: Note (const Note & note)
{
	mod = note.mod;
	keyname = note.keyname;
	m_data = note.m_data;
	m_pos = note.m_pos;
	m_hIcon = note.m_hIcon;
	m_hModifier = note.m_hModifier;
	m_duration = note.m_duration;
}

//
// Destructor
//
Note :: ~Note()
{
}

//
// operator =
//
Note & Note :: operator = (const Note & note)
{
	if (this != &note) {
		mod = note.mod;
		keyname = note.keyname;
		m_data = note.m_data;
		m_pos = note.m_pos;
		m_hIcon = note.m_hIcon;
		m_hModifier = note.m_hModifier;
		m_duration = note.m_duration;
	}

	return * this;
}

//
// Render
//
BOOL Note :: Render(CDC * pDC) const
{
	ASSERT_VALID(pDC);

	// Render the modifier icon
	if (m_hModifier != NULL)
		RenderModifier(pDC);

	if (m_hIcon == NULL)
		return FALSE; // Can't render

	return ::DrawIconEx(*pDC,
	                    m_pos.x,
	                    m_pos.y - iconYOffset,
	                    m_hIcon,
	                    0,
	                    0,
	                    0,
	                    NULL,
	                    DI_NORMAL);
}

//
// RenderModifier
//
BOOL Note :: RenderModifier(CDC * pDC) const
{
	ASSERT_VALID(pDC);
	ASSERT(m_hModifier != NULL);

	return ::DrawIconEx(*pDC,
	                    m_pos.x - modifierXOffset,
	                    m_pos.y - modifierYOffset,
	                    m_hModifier,
	                    0,
	                    0,
	                    0,
	                    NULL,
	                    DI_NORMAL);
}

//
// SetPos
//
void Note :: SetPos(const CPoint & pos)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
}

//
// GetNoteHead
//
void Note :: GetNoteHead(CRect & rc) const
{
	rc.left = m_pos.x;
	rc.top = m_pos.y - headYOffset;
	rc.right = rc.left + headXSize;
	rc.bottom = rc.top + headYSize;
}

//
// PtOnHead
//
BOOL Note :: PtOnHead(const CPoint & pt) const
{
	CRect rcHead;
	GetNoteHead(rcHead);

	CRgn region;
	if (!region.CreateEllipticRgnIndirect(rcHead))
		return FALSE;

	if (!region.PtInRegion(pt))
		return FALSE;

	return TRUE;
}

//
// GetRect
//
void Note :: GetRect(CRect & rc) const
{
	rc.left = m_pos.x;
	rc.top = m_pos.y - iconYOffset;
	rc.right = rc.left + iconXSize;
	rc.bottom = rc.top + iconYSize;
}

//
// GetModifierRect
//
void Note :: GetModifierRect(CRect & rc) const
{
	rc.left = m_pos.x - modifierXOffset;
	rc.top = m_pos.y - modifierYOffset;
	rc.right = m_pos.x + modifierXSize;
	rc.bottom = m_pos.y + modifierYSize;
}

//
// Serialize
//
void Note :: Serialize(CArchive & ar)
{
	// BUGBUG -- include modifiers

	if (ar.IsStoring()) {
		ar << m_data << (int)m_duration << m_pos.x << m_pos.y;
	}
	else {
		ar >> m_data >> (int &)m_duration >> m_pos.x >> m_pos.y;
		m_hIcon = DurationToIcon(m_duration);
	}
}

//
// SetModifier
//
void Note :: SetModifier(const Tool * pTool)
{
	if (pTool != NULL) {
		ASSERT(pTool->type == ModifierTool);

		mod = (Modifier)pTool->user;
		m_hModifier = (HICON)Neptune::LoadImage(pTool->icon, IMAGE_ICON);
		ASSERT(m_hModifier != NULL);
	}
	else {
		mod = NATURAL;
		m_hModifier = NULL;
	}
}

// Helper functions

//
// DurationToIcon
//
HICON DurationToIcon(Duration d)
{
	int Count = sizeof(durationTable) / sizeof(Durations);

	for (int i = 0; i < Count; i++) {
		if (durationTable[i].d == d)
			return (HICON)Neptune::LoadImage(durationTable[i].icon, IMAGE_ICON);
	}

	return NULL;
}

//
// ModifierToIcon
//
UINT ModifierToIcon(Modifier mod)
{
	int Count = sizeof(modifierTable) / sizeof(Modifiers);

	for (int i = 0; i < Count; i++) {
		if (modifierTable[i].mod == mod)
			return modifierTable[i].icon;
	}

	return 0;

}