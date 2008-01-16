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
#include "noise.h"

/////////////////////////////////////////////////////////////////////////////
class Content
{
// Construction
public:
    Content();
    ~Content();

// Interface
public:
	void index(const stringvec &infiles, const char *outfile);
	void blocksave();

// Implementation
private:
	void parse();	
	Lex lexer;					// lexical analyzer	
	Inverter block;				// inverted term list in memory
	NoiseList noise;			// noise word list
	Files files;				// list of files indexed
	stringvec datfiles;			// temporary dat files
	string outname;				// output index name
	uint64_t estimatedcount;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __CONTENT_H__
