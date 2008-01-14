/////////////////////////////////////////////////////////////////////////////
//
// CONTENT.H
//
// Copyright (c) 2008 Thomas A. Rieck, All Rights Reserved
//

#ifndef __CONTENT_H__
#define __CONTENT_H__

#include "lex.h"
#include "inverter.h"
#include "files.h"

/////////////////////////////////////////////////////////////////////////////
class Content
{
// Construction
public:
    Content();
    ~Content();

// Interface
public:
	void index(int nfiles, char **files, const char *outfile);
	
// Implementation
private:
	void parse();	
	Lex lexer;			// lexical analyzer	
	Inverter block;		// inverted term list in memory
	Files files;		// list of files
	string outname;		// output index name
};

/////////////////////////////////////////////////////////////////////////////

#endif // __CONTENT_H__
