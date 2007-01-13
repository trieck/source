/////////////////////////////////////////////////////////////////////////////
//
//	LEXER.CPP : Lexical analzer
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "lexer.h"

/////////////////////////////////////////////////////////////////////////////
Lexer::Lexer(IPeekableStream *pstream)
 : stream(pstream), pos(0), offset(0)
{
	// pointer copied so AddRef
	stream->AddRef();
}

/////////////////////////////////////////////////////////////////////////////
Lexer::~Lexer()
{
	stream->Release();	
}

/////////////////////////////////////////////////////////////////////////////
Token Lexer::gettok()
{
	Token tok;

	int c;
	for ( ; (c = getc()) != EOF; offset++) {		
		if (isalnum(c)) {
			if (tok.val.length() == 0) {
				tok.pos = pos++; tok.offset = offset;
			}
			tok.val += (char)tolower(c);
		} else if (c == '_' || c == '\'' || c == '-') {
			if (tok.val.length()) tok.val += c;
		} else if (c == ',') {
			continue;
		} else {
			if (tok.val.length())
				break;
		}
	}

	return tok;
}

/////////////////////////////////////////////////////////////////////////////
int Lexer::getc()
{
	UCHAR buf[1];

	DWORD read;
	HRESULT hr = stream->Read(buf, sizeof(UCHAR), &read);
	if (FAILED(hr))
		return EOF;

	if (read == 0)
		return EOF;

	return buf[0];
}
