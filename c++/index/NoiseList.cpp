/////////////////////////////////////////////////////////////////////////////
//
//	NOISELIST.CPP : Noise word list
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "noiselist.h"
#include "filestream.h"
#include "lexer.h"

/////////////////////////////////////////////////////////////////////////////
NoiseList::NoiseList()
{
	load();
}

/////////////////////////////////////////////////////////////////////////////
NoiseList::~NoiseList()
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
void NoiseList::close()
{
	stream.Release();	
}

/////////////////////////////////////////////////////////////////////////////
bool NoiseList::isnoise(const string &term)	const
{
	set<string>::const_iterator it = noise.find(term);
	return it != noise.end();
}

/////////////////////////////////////////////////////////////////////////////
void NoiseList::load()
{
	stream.Attach(FileStream::Create("noise.txt", GENERIC_READ, 
		FILE_SHARE_READ, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY));
	if (stream == NULL)
		throw Exception(lasterror());	// can't open
	
	LexerPtr lexer(new Lexer(stream));

	Token tok;
	while (!isempty(tok = lexer->gettok())) {
		noise.insert(tok.val);
	}
}
