/////////////////////////////////////////////////////////////////////////////
//
// FIXUPS.H : Forward reference fix-ups
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __FIXUPS_H__
#define __FIXUPS_H__

// fix-up types
enum FixUpType {
	FT_UNDEF = 0,	// undefined
	FT_STD,			// standard fix-up
	FT_REL,			// relative branch fix-up
	FT_HIBYTE,		// hi-byte of word
	FT_LOBYTE		// lo-byte of word
};

/////////////////////////////////////////////////////////////////////////////
struct FixUp {
	FixUp() : name(NULL), location(0), type(FT_UNDEF) {}
	FixUp(const FixUp &rhs) {
		*this = rhs;
	}
	FixUp & operator = (const FixUp &rhs) {
		if (this != &rhs) {
			name = rhs.name;	// shared
			location = rhs.location;
			type = rhs.type;
		}
		return *this;
	}

	const char *name;	// symbol name
	word location;		// code location
	FixUpType type;		// type of fixup
};

/////////////////////////////////////////////////////////////////////////////
class FixUps {
// Construction / Destruction
public:
	FixUps();
	~FixUps();

// Interface
	void add(const char *name, word location, FixUpType type);
	uint32_t size() const {
		return m_fixups.size();
	}

	FixUp & operator[](uint32_t index) {
		return m_fixups[index];
	}

// Implementation
private:
	typedef vector<FixUp> FixUpVector;
	FixUpVector m_fixups;
};

#endif // __FIXUPS_H__
