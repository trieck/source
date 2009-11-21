// Dictionary.cpp: implementation of the Dictionary class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TorrentExplorer.h"
#include "Dictionary.h"
#include "String.h"
#include <algorithm>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Dictionary::Dictionary()
{
}

Dictionary::~Dictionary()
{
	CString key;
	LPTORRENTOBJECT val;

	POSITION pos = map.GetStartPosition();
	while (pos != NULL) {
		map.GetNextAssoc(pos, key, val);
		delete val;
	}
}

void Dictionary::Set(LPCSTR k, LPTORRENTOBJECT v)
{
	LPTORRENTOBJECT o;
	if (map.Lookup(k, o))
		delete o;

	map[k] = v;
}

LPTORRENTOBJECT Dictionary::Get(LPCSTR k) const
{
	LPTORRENTOBJECT v;
	if (map.Lookup(k, v))
		return v;

	return NULL;
}

LPCSTR Dictionary::GetString(LPCSTR k) const
{
	LPTORRENTOBJECT v = Get(k);
	if (v == NULL) return NULL;
	if (v->GetElementType() != ET_STRING)
		return NULL;
	return (LPCSTR)*(LPSTRING)v;
}

KeyVec Dictionary::GetKeys() const
{
	KeyVec keys;
	CString key;
	LPTORRENTOBJECT val;

	POSITION pos = map.GetStartPosition();
	while (pos != NULL) {
		map.GetNextAssoc(pos, key, val);
		keys.push_back(key);
	}

	return keys;
}

KeyVec Dictionary::GetKeysSorted() const
{
	KeyVec keys = GetKeys();

	std::sort(keys.begin(), keys.end(), StringPtrLess());

	return keys;
}
