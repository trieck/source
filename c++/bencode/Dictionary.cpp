/////////////////////////////////////////////////////////////////////////////
//
// DICTIONARY.CPP : Bencoded dictionary class
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "beobject.h"
#include "Dictionary.h"
#include "Integer.h"

/////////////////////////////////////////////////////////////////////////////
Dictionary::Dictionary()
{
}

/////////////////////////////////////////////////////////////////////////////
Dictionary::Dictionary(const Dictionary &d)
{
	*this = d;
}

/////////////////////////////////////////////////////////////////////////////
Dictionary::~Dictionary()
{
	ObjectMap::const_iterator it = m.begin();
	for ( ; it != m.end(); it++) {
		ObjectEntry e =  *it;
		delete e.first;
		delete e.second;
	}
}

/////////////////////////////////////////////////////////////////////////////
Dictionary &Dictionary::operator =(const Dictionary &rhs)
{
	if (this != &rhs) {
		m = rhs.m;
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
LPBEOBJECT Dictionary::Copy() const
{
	return new Dictionary(*this);
}

/////////////////////////////////////////////////////////////////////////////
DictIterator Dictionary::GetIterator() const
{
	return DictIterator(m.begin(), m.end());
}

/////////////////////////////////////////////////////////////////////////////
void Dictionary::Set(LPSTRING k, LPBEOBJECT v)
{
	LPBEOBJECT o;
	if ((o = Get(k)) != NULL)
		delete o;

	m[k] = v;
}

/////////////////////////////////////////////////////////////////////////////
void Dictionary::Set(LPCSTR k, LPBEOBJECT v)
{
	Set(MakeString(k), v);
}

/////////////////////////////////////////////////////////////////////////////
void Dictionary::Set(LPCSTR k, LPCSTR v)
{
	Set(MakeString(k), MakeString(v));
}

/////////////////////////////////////////////////////////////////////////////
void Dictionary::Set(LPCSTR k, const string &v)
{
	Set(MakeString(k), MakeString(v.c_str()));
}

/////////////////////////////////////////////////////////////////////////////
void Dictionary::Set(LPCSTR k, INT64 v)
{
	Set(MakeString(k), MakeInteger(v));
}

/////////////////////////////////////////////////////////////////////////////
LPBEOBJECT Dictionary::Get(LPSTRING k)
{
	ObjectMap::const_iterator it = m.find(k);
	if (it == m.end())
		return NULL;
	return (*it).second;
}

/////////////////////////////////////////////////////////////////////////////
LPBEOBJECT Dictionary::Get(LPCSTR k)
{
	/* make a temporary string object from a c-style string */
	LPSTRING s = MakeString(k);
	LPBEOBJECT v = Get(s);
	delete s;
	return v;
}

/////////////////////////////////////////////////////////////////////////////
// Global helpers
LPDICTIONARY MakeDictionary()
{
	return new Dictionary();
}
