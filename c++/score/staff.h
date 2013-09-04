/////////////////////////////////////////////////////////////////////////////
//
//	STAFF.H
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#ifndef __STAFF_H__
#define __STAFF_H__

// Anchor struct
typedef struct {
	char name;	// note name
	BYTE data;  // MIDI data note
	int cy;     // vertical position
} Anchor, * PANCHOR;

typedef CArray<Measure *, Measure *> MEASUREARRAY;
typedef CArray<PANCHOR, PANCHOR> ANCHORARRAY;

/////////////////////////////////////////////////////////////////////////////
class Staff :
	public CRect,
	private ANCHORARRAY {
	friend class Measure;
public:
	// Construction / Destruction
	Staff();
	virtual ~Staff();

	// Interface
	void Clear();
	void Render (CDC * pDC) const;
	PANCHOR GetAnchor(const CPoint &) const;
	Measure * GetMeasure(const CPoint &) const;
	void DeselectAllMeasures();
	void Serialize(CArchive & ar);

	inline int GetMeasureCount() const {
		return m_Measures.GetSize();
	}
	inline const MEASUREARRAY* GetMeasures() const {
		return &m_Measures;
	}

protected:
	// Implementation
	int PtOnLedgerLine(const CPoint &) const;
	int PtOnSpace(const CPoint &) const;
	void RenderMeasures(CDC * pDC) const;
	void BuildAnchors();
	void BuildMeasures();
	void RemoveAnchors();
	void RemoveMeasures();

	MEASUREARRAY m_Measures;
	DECLARE_SERIAL(Staff)
};
/////////////////////////////////////////////////////////////////////////////

const COLORREF penColor = ::GetSysColor(COLOR_WINDOWTEXT);
const int borderOffset = 50;


#endif // __STAFF_H__