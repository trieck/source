/////////////////////////////////////////////////////////////////////////////
//
// LIST.CPP : Bencoded list class
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "beobject.h"
#include "List.h"

/////////////////////////////////////////////////////////////////////////////
List::List() 
{
}

/////////////////////////////////////////////////////////////////////////////
List::List(const List &l) 
{
	*this = l;
}

/////////////////////////////////////////////////////////////////////////////
List::~List()
{
	vector<LPBEOBJECT>::const_iterator it = list.begin();
	for ( ; it != list.end(); it++) {
		delete *it;
	}
}

/////////////////////////////////////////////////////////////////////////////
List &List::operator =(const List &rhs) 
{
	if (this != &rhs) {
		list = rhs.list;
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
LPBEOBJECT List::Get(unsigned index) const
{
	if (index >= list.size())
		return NULL;

	return list[index];
}

/////////////////////////////////////////////////////////////////////////////
void List::AddObject(LPBEOBJECT o)
{
	list.push_back(o);
}

/////////////////////////////////////////////////////////////////////////////
LPBEOBJECT List::Copy() const
{
	return new List(*this);
}

/////////////////////////////////////////////////////////////////////////////
// Global helpers
LPLIST MakeList()
{
	return new List();
}
