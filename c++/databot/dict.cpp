/////////////////////////////////////////////////////////////////////////////
// 
// DICT.CPP : Dictionary message object class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "mobject.h"
#include "dict.h"

/////////////////////////////////////////////////////////////////////////////
Dictionary::Dictionary()
{
}

/////////////////////////////////////////////////////////////////////////////
Dictionary::Dictionary(const Dictionary &rhs)
{
	*this = rhs;
}

/////////////////////////////////////////////////////////////////////////////
Dictionary::~Dictionary()
{
	clear();
}

/////////////////////////////////////////////////////////////////////////////
Dictionary &Dictionary::operator =(const Dictionary &rhs)
{
	if (this != &rhs) {
		clear();

		// deep copy
		ObjectMap::const_iterator it = rhs.map.begin();
		for ( ; it != rhs.map.end(); it++) {
			put((*it).first, (*it).second->copy());
		}
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
LPMOBJECT Dictionary::copy() const
{
	return new Dictionary(*this);
}

/////////////////////////////////////////////////////////////////////////////
string Dictionary::toString() const
{
	string output = "<dict>";

	ObjectMap::const_iterator it = map.begin();
	for ( ; it != map.end(); it++) {
		ObjectEntry &entry = *it;
		output += "<key>";
		output += entry.first;
		output += "</key>";
		output += entry.second->toString();
	}

	output += "</dict>";

	return output;
}

/////////////////////////////////////////////////////////////////////////////
void Dictionary::put(const string &key, LPMOBJECT val)
{
	LPMOBJECT pObject = get(key);
	if (pObject != NULL)
		delete pObject;
	map[key] = val;
}

/////////////////////////////////////////////////////////////////////////////
LPMOBJECT Dictionary::get(const string &key) const
{
	ObjectMap::const_iterator it = map.find(key);
	if (it == map.end())
		return NULL;
	return (*it).second;
}

/////////////////////////////////////////////////////////////////////////////
void Dictionary::clear()
{
	LPMOBJECT pObject;
	ObjectMap::iterator it = map.begin();
	for ( ; it != map.end(); it++) {
		pObject = (*it).second;
		if (pObject != NULL)
			delete pObject;
	}

	map.clear();
}
