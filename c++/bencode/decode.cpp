/////////////////////////////////////////////////////////////////////////////
//
// DECODE.CPP : Decode Bencoded stream
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "BEObject.h"
#include "Integer.h"
#include "BEString.h"
#include "List.h"
#include "Dictionary.h"
#include "decode.h"

/////////////////////////////////////////////////////////////////////////////
BEDecoder::BEDecoder(IPeekableStream *pStream)
	: m_pStream(pStream)
{
	// Copied pointer so AddRef it
	m_pStream->AddRef();
}

/////////////////////////////////////////////////////////////////////////////
BEDecoder::~BEDecoder()
{
	m_pStream->Release();
}

/////////////////////////////////////////////////////////////////////////////
LPBEOBJECT BEDecoder::decode(IPeekableStream *pStream)
{
	BEDecoderPtr pDecoder(new BEDecoder(pStream));
	return pDecoder->LoadObject();
}

/////////////////////////////////////////////////////////////////////////////
LPBEOBJECT BEDecoder::LoadObject()
{
	int t = Gettok();

	switch (t) {
	case BEObject::BET_DICT:
		return LoadDictionary();
	case BEObject::BET_INTEGER:
		return LoadInteger();
	case BEObject::BET_LIST:
		return LoadList();
	case BEObject::BET_STRING:
		return LoadString();
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
int BEDecoder::Gettok()
{
	int c = Peek();

	switch (c) {
	case 'd':
		Getc();
		return BEObject::BET_DICT;
	case 'i':
		Getc();
		return BEObject::BET_INTEGER;
	case 'l':
		Getc();
		return BEObject::BET_LIST;
	default:
		if (isdigit(c) || c == '-')
			return BEObject::BET_STRING;
	}

	Getc();

	return c;
}

/////////////////////////////////////////////////////////////////////////////
LPINTEGER BEDecoder::LoadInteger()
{
	string output;

	int c;
	while ((c = Peek()) != 'e' && c != EOF) {
		output += (char)Getc();
	}

	Getc();	// 'e'

	INT64 value = _atoi64(output.c_str());

	return MakeInteger(value);
}

/////////////////////////////////////////////////////////////////////////////
LPSTRING BEDecoder::LoadString()
{
	int c;
	string slen;

	while ((c = Peek()) != ':' && c != EOF) {
		slen += (char)Getc();
	}

	DWORD length = atoi(slen.c_str());
	LPBYTE buf = new BYTE[length];

	Getc();	// ':'

	DWORD read;
	m_pStream->Read(buf, length, &read);

	LPSTRING s = MakeString(buf, min(read, length));

	delete [] buf;

	return s;
}

/////////////////////////////////////////////////////////////////////////////
LPLIST BEDecoder::LoadList()
{
	LPLIST list = MakeList();

	int c;
	while ((c = Peek()) != 'e' && c != EOF) {
		list->AddObject(LoadObject());
	}

	Getc();	// 'e'

	return list;
}

/////////////////////////////////////////////////////////////////////////////
LPDICTIONARY BEDecoder::LoadDictionary()
{
	LPDICTIONARY d = MakeDictionary();
	LPSTRING k;
	LPBEOBJECT v;

	int c;
	while ((c = Peek()) != 'e' && c != EOF) {
		k = LoadString();
		v = LoadObject();
		d->Set(k, v);
	}

	c = Getc();	// 'e'

	return d;
}

/////////////////////////////////////////////////////////////////////////////
// Get next character from the stream
int BEDecoder::Getc()
{
	unsigned char buf[1];

	DWORD read;
	HRESULT hr = m_pStream->Read(buf, 1, &read);
	if (FAILED(hr))
		return EOF;

	if (read == 0)
		return EOF;

	return buf[0];
}

/////////////////////////////////////////////////////////////////////////////
// Peek next character from the stream
int BEDecoder::Peek()
{
	unsigned char buf[1];

	DWORD read;
	HRESULT hr = m_pStream->Peek(buf, 1, &read);
	if (FAILED(hr))
		return EOF;

	if (read == 0)
		return EOF;

	return buf[0];
}