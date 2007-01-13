/////////////////////////////////////////////////////////////////////////////
//
//	ITEM.H : Symbol table ADT
//	Adapted from Sedgewick 12.1
//
//	Copyright (c) 2004 KnowX.com, All Rights Reserved
//

#ifndef __ITEM_H__
#define __ITEM_H__

typedef unsigned __int64 Key;

/////////////////////////////////////////////////////////////////////////////
class Item {
// Construction / Destruction
public:
	Item() { keyval = MAXKEY; }
	Item(Key key, float f) 
		: keyval(key), info(f) {}
	
// Interface
	void setKey(Key key) { keyval = key; }
	void setInfo(unsigned __int64 i) { info = i; }

	Key key() { return keyval; }
	unsigned __int64 getInfo() { return info; }

	bool null() { return keyval == MAXKEY; }

// Implementation
private:
	enum { MAXKEY = -1i64 };
	Key keyval;
	unsigned __int64 info;
};
/////////////////////////////////////////////////////////////////////////////

const Item nullItem;

#endif // __ITEM_H__