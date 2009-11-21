// TorrentParser.cpp: implementation of the TorrentParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TorrentExplorer.h"
#include "Dictionary.h"
#include "List.h"
#include "Integer.h"
#include "String.h"
#include "TorrentParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace {	// anonymous

LPDICTIONARY LoadDictionary(CFile *fp);
LPTORRENTOBJECT LoadElement(CFile *fp);

int Peek(CFile *fp);
int Getch(CFile *fp);
int Gettok(CFile *fp);

LPDICTIONARY dictionary(CFile *fp);
LPINTEGER integer(CFile *fp);
LPLIST list(CFile *fp);
LPSTRING string(CFile *fp);

};	// anonymous

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TorrentParser::TorrentParser()
{

}

TorrentParser::~TorrentParser()
{
}

/////////////////////////////////////////////////////////////////////////////
LPDICTIONARY TorrentParser::Parse(CArchive &ar)
{
	if (!ar.IsLoading())
		return NULL;

	CFile *fp = ar.GetFile();
	if (fp == NULL)
		return NULL;

	return LoadDictionary(fp);
}

/////////////////////////////////////////////////////////////////////////////

namespace {	// anonymous

/////////////////////////////////////////////////////////////////////////////
LPDICTIONARY LoadDictionary(CFile *fp)
{
	LPTORRENTOBJECT element = LoadElement(fp);
	if (element->GetElementType() != ET_DICT)	// not a dictionary
		AfxThrowArchiveException(CArchiveException::badIndex);

	return (LPDICTIONARY)element;
}

/////////////////////////////////////////////////////////////////////////////
LPTORRENTOBJECT LoadElement(CFile *fp)
{
	int t = Gettok(fp);

	switch (t) {
	case ET_DICT:
		return dictionary(fp);
	case ET_INTEGER:
		return integer(fp);
	case ET_LIST:
		return list(fp);
	case ET_STRING:
		return string(fp);
	default:
		AfxThrowArchiveException(CArchiveException::badIndex);
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
int Peek(CFile *fp)
{
	int c = Getch(fp);
	if (c == EOF)
		return EOF;

	fp->Seek(-1, CFile::current);

	return c;
}

/////////////////////////////////////////////////////////////////////////////
int Getch(CFile *fp)
{
	unsigned char buf[1];
	if (!fp->Read(buf, 1))
		return EOF;

	return buf[0];
}

/////////////////////////////////////////////////////////////////////////////
int Gettok(CFile *fp)
{
	int c = Peek(fp);

	switch (c) {
	case 'd':
		Getch(fp);
		return ET_DICT;
	case 'i':
		Getch(fp);
		return ET_INTEGER;
	case 'l':
		Getch(fp);
		return ET_LIST;
	default:
		if (isdigit(c))
			return ET_STRING;
	}

	Getch(fp);

	return c;
}

/////////////////////////////////////////////////////////////////////////////
LPDICTIONARY dictionary(CFile *fp)
{
	LPDICTIONARY d = new Dictionary();
	LPSTRING k;
	LPTORRENTOBJECT v;

	int c;
	while ((c = Peek(fp)) != 'e' && c != EOF) {
		k = string(fp);
		v = LoadElement(fp);
		d->Set(*k, v);
		delete k;
	}

	c = Getch(fp);	// 'e'

	return d;
}

/////////////////////////////////////////////////////////////////////////////
LPINTEGER integer(CFile *fp)
{
	CString output;

	int c;
	while ((c = Peek(fp)) != 'e' && c != EOF) {
		output += (TCHAR)Getch(fp);
	}

	Getch(fp);	// 'e'

	return new Integer(_atoi64(output));
}

/////////////////////////////////////////////////////////////////////////////
LPLIST list(CFile *fp)
{
	LPLIST list = new List();

	int c;
	while ((c = Peek(fp)) != 'e' && c != EOF) {
		list->append(LoadElement(fp));
	}

	Getch(fp);	// 'e'

	return list;
}

/////////////////////////////////////////////////////////////////////////////
LPSTRING string(CFile *fp)
{
	int c;
	CString slen;

	while ((c = Peek(fp)) != ':' && c != EOF) {
		slen += (TCHAR)Getch(fp);
	}

	int length = atoi(slen);

	CString s;
	LPSTR buf = s.GetBufferSetLength(length);

	Getch(fp);	// ':'

	for (int i = 0; i < length; i++) {
		int c = Getch(fp);
		if (c == EOF)
			AfxThrowFileException(CFileException::endOfFile);
		*buf++ = (char)c;
	}


	return new String(s, length);
}

}	// anonymous
