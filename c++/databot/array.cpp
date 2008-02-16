/////////////////////////////////////////////////////////////////////////////
// 
// ARRAY.CPP : Array message object class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "mobject.h"
#include "array.h"
#include "integer.h"
#include "float.h"
#include "mstring.h"

/////////////////////////////////////////////////////////////////////////////
Array::Array()
{
}

/////////////////////////////////////////////////////////////////////////////
Array::Array(const Array &rhs)
{
	*this = rhs;
}

/////////////////////////////////////////////////////////////////////////////
Array::~Array()
{
	clear();
}

/////////////////////////////////////////////////////////////////////////////
Array &Array::operator =(const Array &rhs)
{
	if (this != &rhs) {
		clear();

		// deep copy
		ObjectList::const_iterator it = rhs.list.begin();
		for ( ; it != rhs.list.end(); it++) {
			add((*it)->copy());
		}
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
LPMOBJECT Array::copy() const
{
	return new Array(*this);
}

/////////////////////////////////////////////////////////////////////////////
void Array::add(int64_t i)
{
	add(new Integer(i));
}

/////////////////////////////////////////////////////////////////////////////
void Array::add(double d)
{
	add(new Float(d));
}

/////////////////////////////////////////////////////////////////////////////
void Array::add(const string &s)
{
	add(new String(s));
}

/////////////////////////////////////////////////////////////////////////////
void Array::add(LPMOBJECT pObject)
{
	list.push_back(pObject);
}

/////////////////////////////////////////////////////////////////////////////
string Array::toString() const
{
	string output = "<array>";

	ObjectList::const_iterator it = list.begin();
	for ( ; it != list.end(); it++) {
		output += (*it)->toString();
	}

	output += "</array>";

	return output;
}


/////////////////////////////////////////////////////////////////////////////
void Array::clear()
{
	LPMOBJECT pObject;
	ObjectList::iterator it = list.begin();
	for ( ; it != list.end(); it++) {
		pObject = *it;
		if (pObject != NULL)
			delete pObject;
	}

	list.clear();
}
