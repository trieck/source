/////////////////////////////////////////////////////////////////////////////
//
// ENTRY.H : Pente board entry
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ENTRY_H__
#define __ENTRY_H__

/////////////////////////////////////////////////////////////////////////////
// entry types
enum EntryType {
    ET_EMPTY = 0,
    ET_PLAYER_ONE,
    ET_PLAYER_TWO
};

/////////////////////////////////////////////////////////////////////////////
class Entry {
// Construction / Destruction
public:
	Entry();
	Entry(const Entry &rhs);
	Entry(const POINT &aPoint, uint32_t ntype);
	~Entry();

// Interface
	Entry & operator = (const Entry &rhs);
	POINT where() const;
	uint32_t getType() const;

// Implementation
private:
	POINT pt;
	uint32_t type;
};

/////////////////////////////////////////////////////////////////////////////
inline POINT Entry::where() const
{
	return pt;
}

/////////////////////////////////////////////////////////////////////////////
inline uint32_t Entry::getType() const
{
	return type;
}



#endif // __ENTRY_H__
