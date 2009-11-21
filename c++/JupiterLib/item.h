/////////////////////////////////////////////////////////////////////////////
//
//	ITEM.H : item definitions
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ITEM_H__
#define __ITEM_H__

/////////////////////////////////////////////////////////////////////////////
typedef struct Item {

// Construction / Destruction
	Item();
	Item(const Item &i);
	Item(LPCSTR s);
	Item(void *p, uint32_t len);
	virtual ~Item();

// Interface
	virtual void Attach(void *p, uint32_t len);

	Item &operator =(const Item &i);
	bool operator < (const Item &rhs);

// Implementation
	uint32_t nlen;	// length of data
	LPSTR data;		// data for the item
} *PITEM;

typedef auto_ptr<Item> ItemPtr;

/////////////////////////////////////////////////////////////////////////////
typedef struct Entry {
	PITEM key;		// key for entry
	PITEM val;		// value for entry
} *PENTRY;

#endif // __ITEM_H__