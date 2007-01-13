///////////////////////////////////////////////////////////////////////
//
//	STAFF.CPP
//
//	Copyright © 1999 Rieck Enterprises
//

#include "stdafx.h"
#include "baseinc.h"
#include "Score.h"
#include "resource.h"

static const int numLines = 5;              // Number of lines
static const int numSpaces = numLines - 1;  // Number of spaces
static const int lineHeight = 8;            // Height of a line on the staff
static const int leeway = 2;                // Leeway for mouse position
static const int borderWidth = 5;           // Width of left border
static const int staffWidth = 519;          // Width of staff
static const BYTE base = 64;                // E above middle C

typedef struct {
	char note;
	BYTE interval;
} NoteInterval;

static const NoteInterval NoteIntervals [] = {
	'E', 1,
	'F', 2,
	'G', 2,
	'A', 2,
	'B', 1,
	'C', 2,
	'D', 2
};

IMPLEMENT_SERIAL(Staff, CObject, VERSIONABLE_SCHEMA)

//
// Constructor
//
Staff :: Staff()
{
    this->left = borderOffset;
    this->top = borderOffset;
    this->right = this->left + staffWidth;
    this->bottom = this->top + ((numLines - 1) * lineHeight);

    m_Measures.SetSize(3);

    SetSize(numLines + numSpaces);
    BuildAnchors();
    BuildMeasures();
}

//
// Destructor
//
Staff :: ~Staff()
{
    RemoveAnchors();
    RemoveMeasures();
}

//
// Clear
//
void Staff :: Clear()
{
    // Remove all the notes from the measures
    for (int i = 0; i < GetMeasureCount(); i++) {
        Measure * pMeasure = m_Measures.GetAt(i);
        ASSERT_VALID(pMeasure);

        pMeasure->Clear();
    }
}

//
// BuildAnchors
//
void Staff :: BuildAnchors()
{
    int Count = GetSize();
    int mx = sizeof(NoteIntervals) / sizeof(NoteInterval);

    int b = base;

    for (int i = 0; i < Count; i++) {
        PANCHOR pAnchor = new Anchor();
        ASSERT(pAnchor != NULL);

		pAnchor->name = NoteIntervals [i % mx].note;
        pAnchor->data = (BYTE)b;
        
        // Is this a ledger line?
        if (i % 2 == 0)
            pAnchor->cy = bottom - (i / 2) * lineHeight;
        else
            pAnchor->cy = bottom - lineHeight / 2 - (i - 1) / 2 * lineHeight;
        
        SetAt(i, pAnchor);

        b += NoteIntervals[i % mx].interval;
    }
}

//
// BuildMeasures
//
void Staff :: BuildMeasures() 
{
    int Measures = GetMeasureCount();
    ASSERT(Measures != 0);

    int measureWidth = this->Width() / Measures;

    CRect rc;
    rc.left = this->left;
    rc.right = this->left + measureWidth;
    rc.top = this->top;
    rc.bottom = this->bottom;

    for (int i = 0; i < Measures; i++) {
        Measure * pMeasure = new Measure(this, rc, i == 0 ? IDB_TREBLECLEF : 0);
        ASSERT(pMeasure != NULL);
        m_Measures.SetAt(i, pMeasure);

        rc.left = rc.right;
        rc.right = rc.left + measureWidth;
    }
}

//
// GetMeasure
//
Measure * Staff :: GetMeasure(const CPoint & pt) const
{
    int Count = GetMeasureCount();
    for (int i = 0; i < Count; i++) {
        Measure * pMeasure = m_Measures.GetAt(i);
        ASSERT(pMeasure != NULL);

        CRect rc = *pMeasure;
        rc.InflateRect(0, leeway);
        if (rc.PtInRect(pt))
            return pMeasure;
    }

    return NULL;
}

//
// Render
//
void Staff :: Render (CDC * pDC) const
{
    ASSERT_VALID(pDC);
    
    // Render the Measures
    RenderMeasures(pDC);

    CPen aPen(PS_SOLID, 1, penColor);
    CPen * pOldPen = pDC->SelectObject(&aPen);
    
    CPoint ptStart (this->left, this->top);
    CPoint ptEnd (this->right, this->top);
    pDC->MoveTo(ptStart);

    // Draw the staff lines
    for (int i = 0; i < numLines; i++) {
        pDC->LineTo(ptEnd);
        ptStart.y += lineHeight;
        ptEnd.y += lineHeight;
        pDC->MoveTo(ptStart);
    }
    
    pDC->SelectObject(pOldPen);
}

//
// RenderMeasures 
//
void Staff :: RenderMeasures(CDC * pDC) const
{
    ASSERT_VALID(pDC);

    int Count = GetMeasureCount();
    for (int i = 0; i < Count; i++) {
        Measure * pMeasure = m_Measures.GetAt(i);
        ASSERT(pMeasure != NULL);
        pMeasure->Render(pDC);
    }
}

//
// GetAnchor
//
PANCHOR Staff :: GetAnchor(const CPoint & pt) const
{
    // Does this point land on a ledger line
    int line = PtOnLedgerLine(pt);
    if (line != -1) {
        return GetAt((numLines - line - 1) * 2);
    }
    
    // Does this point land on a space
    int space = PtOnSpace(pt);
    if (space != -1) {
        return GetAt ((numSpaces - space - 1) * 2 + 1);
    }

    return NULL;
}

//
// PtOnLedgerLine
//
int Staff :: PtOnLedgerLine(const CPoint & pt) const
{
    for (int i = 0; i < numLines; i++) {
        if (pt.x >= this->left &&
            pt.x <= this->right &&
            (pt.y >= this->top + (i * lineHeight) - leeway &&
            pt.y <= this->top + (i * lineHeight) + leeway))
            return i;
    }

    return -1;
}

//
// PtOnSpace
//
int Staff :: PtOnSpace(const CPoint & pt) const
{
    for (int i = 0; i < numSpaces; i++) {
        if (pt.x >= this->left &&
            pt.x <= this->right &&
            (pt.y >= this->top + (i * lineHeight) + leeway &&
            pt.y <= this->top + ((i + 1) * lineHeight) - leeway))
            return i;
    }

    return -1;
}

//
// RemoveAnchors
//
void Staff :: RemoveAnchors()
{
    int Count = GetSize();
    
    for (int i = 0; i < Count; i++) {
        PANCHOR pAnchor = GetAt(i);
        if (pAnchor != NULL)
            delete pAnchor;
    }
    
    RemoveAll();
}

//
// RemoveMeasures
//
void Staff :: RemoveMeasures()
{
    int Count = GetMeasureCount();
    
    for (int i = 0; i < Count; i ++) {
        Measure * pMeasure = m_Measures.GetAt(i);
        if (pMeasure != NULL)
            delete pMeasure;
    }
    m_Measures.RemoveAll();
}

//
// DeselectAllMeasures
//
void Staff :: DeselectAllMeasures ()
{
    int Count = GetMeasureCount();
    for (int i = 0; i < Count; i++) {
        Measure * pMeasure = m_Measures.GetAt(i);
        ASSERT(pMeasure != NULL);
        pMeasure->Select(FALSE);
    }
}

//
// Serialize
//
void Staff :: Serialize(CArchive & ar)
{
    CObject::Serialize(ar);

    for (int i = 0; i < GetMeasureCount(); i++)
        m_Measures.GetAt(i)->Serialize(ar);
}