/////////////////////////////////////////////////////////////////////////////
//
// ENCODE.CPP : Encode Bencoded Object
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "BEObject.h"
#include "Integer.h"
#include "String.h"
#include "List.h"
#include "Dictionary.h"
#include "encode.h"

static char BEGIN_DICT[1] =    { 'd' };
static char BEGIN_LIST[1] =    { 'l' };
static char BEGIN_INTEGER[1] = { 'i' };
static char END_OBJECT[1] =    { 'e' };

/////////////////////////////////////////////////////////////////////////////
BEEncoder::BEEncoder(ISequentialStream *pStream)
		: m_pStream(pStream)
{
	// Copied pointer so AddRef it
	m_pStream->AddRef();
}

/////////////////////////////////////////////////////////////////////////////
BEEncoder::~BEEncoder()
{
	m_pStream->Release();
}

/////////////////////////////////////////////////////////////////////////////
BOOL BEEncoder::encode(LPBEOBJECT pObject, ISequentialStream *pStream)
{
	BEEncoderPtr pEncoder(new BEEncoder(pStream));
	return pEncoder->EncodeObject(pObject);
}

/////////////////////////////////////////////////////////////////////////////
BOOL BEEncoder::EncodeObject(LPBEOBJECT pObject)
{
	switch (pObject->GetType()) {
	case BEObject::BET_DICT:
		return EncodeDict(static_cast<LPDICTIONARY>(pObject));
		break;
	case BEObject::BET_LIST:
		return EncodeList(static_cast<LPLIST>(pObject));
		break;
	case BEObject::BET_INTEGER:
		return EncodeInt(static_cast<LPINTEGER>(pObject));
		break;
	case BEObject::BET_STRING:
		return EncodeString(static_cast<LPSTRING>(pObject));
		break;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
BOOL BEEncoder::EncodeDict(LPDICTIONARY d)
{
	BeginDictionary();					// begin dictionary

	DictIterator it = d->GetIterator();
	while (it.HasNext()) {
		Dictionary::ObjectEntry entry = it.GetNext();
		EncodeString(entry.first);
		EncodeObject(entry.second);
	}

	EndObject();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
BOOL BEEncoder::EncodeList(LPLIST l)
{
	BeginList();

	for (unsigned i = 0; i < l->size(); i++) {
		EncodeObject(l->Get(i));
	}

	EndObject();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
BOOL BEEncoder::EncodeInt(LPINTEGER i)
{
	BeginInteger();
	WriteRawInt(*i);
	EndObject();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
BOOL BEEncoder::EncodeString(LPSTRING s)
{
	WriteRawInt(s->GetLength());
	WriteChar(':');
	WriteRawString(s);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
BOOL BEEncoder::BeginDictionary()
{
	return Write(BEGIN_DICT, sizeof(BEGIN_DICT));
}

//////////////////////////////////////////////////////////////////////
BOOL BEEncoder::BeginList()
{
	return Write(BEGIN_LIST, sizeof(BEGIN_LIST));
}

//////////////////////////////////////////////////////////////////////
BOOL BEEncoder::BeginInteger()
{
	return Write(BEGIN_INTEGER, sizeof(BEGIN_INTEGER));
}

//////////////////////////////////////////////////////////////////////
BOOL BEEncoder::EndObject()
{
	return Write(END_OBJECT, sizeof(END_OBJECT));
}

/////////////////////////////////////////////////////////////////////////////
BOOL BEEncoder::Write(void *pv, INT nlen)
{
	DWORD written;
	HRESULT hr = m_pStream->Write(pv, nlen, &written);
	if (FAILED(hr))
		return FALSE;

	return nlen == written;
}

//////////////////////////////////////////////////////////////////////
BOOL BEEncoder::WriteRawString(LPSTRING s)
{
	int nlength = s->GetLength();
	for (int i = 0; i < nlength; i++)
		WriteChar(s->GetAt(i));
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
BOOL BEEncoder::WriteRawInt(INT64 i)
{
	char buf[50];
	_i64toa(i, buf, 10);
	return Write(buf, strlen(buf));
}

//////////////////////////////////////////////////////////////////////
BOOL BEEncoder::WriteChar(char c)
{
	return Write(&c, sizeof(char));
}