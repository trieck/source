/////////////////////////////////////////////////////////////////////////////
//
// FSTRING.CPP : fast string class
//

#include <string.h>
#include <stdlib.h>
#include "fstring.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

String::String()
{
	AllocBuffer();
}

String::~String()
{
	delete [] buffer;
}

String::String(const String & str)
{
	AllocBuffer(max(str.nlen, BUFFSIZE));
	strcpy(buffer, str.buffer);
	nlen = str.nlen;
}

String::String(const char *pstr)
{
	size_t len = strlen(pstr);
	AllocBuffer(max(len, BUFFSIZE));
	strcpy(buffer, pstr);
	nlen = len;
}

String & String::operator = (const String & rhs)
{
	if (this != &rhs) {
		AllocBuffer(max(rhs.nlen, BUFFSIZE));
		strcpy(buffer, rhs.buffer);
		nlen = rhs.nlen;
	}

	return *this;
}

String & String::operator += (const String & rhs)
{
	if (size - nlen < rhs.nlen + 1)
		Realloc(size * 2);

	strcpy(buffer + nlen, rhs.buffer);
	nlen += rhs.nlen;

	return *this;
}

bool String::operator == (const String & rhs)
{
	return strcmp(buffer, rhs.buffer) == 0;
}

void String::AllocBuffer(size_t len)
{
	// room for null terminator
	buffer = new char[len + 1];
	buffer[0] = '\0';
	nlen = 0;
	size = len;
}

void String::Realloc(size_t nsize)
{
	String tmp = *this;
	delete [] buffer;
	AllocBuffer(nsize);
	strcpy(buffer, tmp.buffer);
	nlen = tmp.nlen;
}

// global operators
String operator +(const String & lhs, const String & rhs)
{
	String tmp = lhs;
	tmp += rhs;
	return tmp;
}