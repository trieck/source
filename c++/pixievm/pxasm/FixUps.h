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
	FixUp() : name(NULL), location(0) {}
	FixUp(const FixUp &rhs) { *this = rhs; }
	FixUp & operator = (const FixUp &rhs) {
		if (this != &rhs) {
			name = rhs.name;	// shared
			location = rhs.location;
		}
		return *this;
	}

	const char *name;	// symbol name
	word location;		// code location
};

class FixUps;
typedef auto_ptr<FixUps> FixUpsPtr;

/////////////////////////////////////////////////////////////////////////////
class FixUps
{
// Construction / Destruction
private:
	FixUps();
public:
	~FixUps();

// Interface
	static FixUps *getInstance();

	void add(const char *name, word location);

// Implementation
private:
	static FixUpsPtr instance;	// singleton instance

	typedef vector<FixUp> FixUpVector;
	FixUpVector m_fixups;
};

#endif // __FIXUPS_H__