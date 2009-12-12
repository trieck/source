/////////////////////////////////////////////////////////////////////////////
//
// FIXUPS.H : Forward reference fix-ups
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __FIXUPS_H__
#define __FIXUPS_H__

/////////////////////////////////////////////////////////////////////////////
struct FixUp {
	FixUp() : name(NULL), location(0), isrel(false) {}
	FixUp(const FixUp &rhs) { *this = rhs; }
	FixUp & operator = (const FixUp &rhs) {
		if (this != &rhs) {
			name = rhs.name;	// shared
			location = rhs.location;
			isrel = rhs.isrel;
		}
		return *this;
	}

	const char *name;	// symbol name
	word location;		// code location
	bool isrel;			// is this a relative branch fix-up?
};

/////////////////////////////////////////////////////////////////////////////
class FixUps
{
// Construction / Destruction
public:
	FixUps();
	~FixUps();

// Interface
	void add(const char *name, word location, bool bRel);

// Implementation
private:
	typedef vector<FixUp> FixUpVector;
	FixUpVector m_fixups;
};

#endif // __FIXUPS_H__
