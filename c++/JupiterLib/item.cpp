/////////////////////////////////////////////////////////////////////////////
//
//	ITEM.CPP : item definitions
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "stdint.h"
#include "item.h"

/////////////////////////////////////////////////////////////////////////////
Item::Item()
		: nlen(0), data(0)
{
}

/////////////////////////////////////////////////////////////////////////////
Item::Item(const Item &i)
{
	*this = i;
}

/////////////////////////////////////////////////////////////////////////////
Item::Item(LPCSTR s)
{
	nlen = strlen(s);
	data = new char[nlen];
	memcpy(data, s, nlen);
}

/////////////////////////////////////////////////////////////////////////////
Item::Item(void *p, uint32_t len)
{
	data = new char[nlen = len];
	memcpy(data, p, len);
}

/////////////////////////////////////////////////////////////////////////////
Item::~Item()
{
	delete []data;
}

/////////////////////////////////////////////////////////////////////////////
void Item::Attach(void *p, uint32_t len)
{
	delete []data;
	data = static_cast<LPSTR>(p);
	nlen = len;
}

/////////////////////////////////////////////////////////////////////////////
Item &Item::operator =(const Item &i)
{
	if (this != &i) {
		delete []data;
		data = new char[nlen = i.nlen];
		memcpy(data, i.data, nlen);
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
bool Item::operator < (const Item &rhs)
{
	if (nlen == rhs.nlen)
		return memcmp(data, rhs.data, nlen) < 0;
	else {
		int n = min(nlen, rhs.nlen);
		char *p1 = (char*)data;
		char *p2 = (char*)rhs.data;
		while (n--) {
			if (*p1 != *p2)
				return (*p1 - *p2) < 0;
			p1++;
			p2++;
		}
	}

	return (nlen - rhs.nlen) < 0;
}
