/////////////////////////////////////////////////////////////////////////////
//
//	INDEX.CPP : Generate index
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "index.h"
#include "filestream.h"

/////////////////////////////////////////////////////////////////////////////
Index::Index()
{
}

/////////////////////////////////////////////////////////////////////////////
Index::~Index()
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
void Index::close()
{
	stream.Release();
	btree.close();	 	
}

/////////////////////////////////////////////////////////////////////////////
void Index::index(LPCSTR filename)
{
	close();

	stream.Attach(FileStream::Create(filename, GENERIC_READ, FILE_SHARE_READ, 
		OPEN_EXISTING, FILE_ATTRIBUTE_READONLY));
	if (stream == NULL)
		throw Exception(lasterror());	// can't open

	char idxfile[MAX_PATH];
	sprintf(idxfile, "%s%s.idx",
		dirname(filename).c_str(),
		basename(filename).c_str());

	if (!btree.open(idxfile, OM_CREATE))
		throw Exception(lasterror());	// can't open

	index();
}

/////////////////////////////////////////////////////////////////////////////
void Index::index()
{
	Lexer lexer(stream);

	Token tok;
	while (!isempty(tok = lexer.gettok())) {
		insert(tok);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Index::insert(const Token &tok)
{	
	Entry entry;
	UINT64 loc = tok.getLocation();
	Item key(tok.val.c_str()), val(&loc, sizeof(UINT64));	
	entry.key = &key; entry.val = &val;

	if (btree.exists(&key)) {
		btree.append(&entry);
	} else {		
		btree.insert(&entry);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Index::writeStats(ostream &os)	const
{
	btree.writeStats(os);
}