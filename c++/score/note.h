///////////////////////////////////////////////////////////////////////
//
//	NOTE.H
//
//	Copyright © 1999 Rieck Enterprises
//

#ifndef __NOTE_H__
#define __NOTE_H__

// Forward declarations
class Measure;

///////////////////////////////////////////////////////////////////////
// Note class
class Note : public CObject, protected KeyNote {
public:
	// Construction / Destruction
	Note();
	Note (const Note &);
	~Note();

	// Interface
	Note & operator = (const Note &);
	BOOL Render(CDC *) const;
	BOOL PtOnHead(const CPoint &) const;
	void GetRect(CRect &) const;
	void GetModifierRect(CRect &) const;
	void SetModifier(const Tool *);
	void Serialize(CArchive & ar);
	void SetData(BYTE b) {
		m_data = b;
	}
	BYTE GetData() const {
		return BYTE(m_data + mod);
	}
	BYTE GetBaseData() const {
		return BYTE(m_data);
	}
	void SetIcon(HICON hIcon) {
		m_hIcon = hIcon;
	}
	HICON GetIcon() const {
		return m_hIcon;
	}
	CPoint GetPos() const {
		return m_pos;
	}
	void SetPos(const CPoint & pos);
	void SetX(int x) {
		m_pos.x = x;
	}
	int GetX() const {
		return m_pos.x;
	}
	Duration GetDuration() const {
		return m_duration;
	}
	void SetDuration(Duration d) {
		m_duration = d;
	}
	void SetName(char c) {
		keyname = c;
	}
	char GetName() const {
		return keyname;
	}
	Modifier GetModifier() const {
		return mod;
	}

	// Implementation
protected:
	BOOL RenderModifier(CDC * pDC) const;
	void GetNoteHead(CRect &) const;

	BYTE m_data;				// midi data
	HICON m_hIcon;				// icon handle
	HICON m_hModifier;			// modifier icon handle
	CPoint m_pos;				// position
	Duration m_duration;		// note duration
	DECLARE_SERIAL(Note)
};

///////////////////////////////////////////////////////////////////////

// Global helpers
UINT ModifierToIcon(Modifier mod);

#endif // __NOTE_H__

