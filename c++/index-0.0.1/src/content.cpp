/////////////////////////////////////////////////////////////////////////////
//
// CONTENT.CPP
//
// Copyright (c) 2008 Thomas A. Rieck, All Rights Reserved
//

#include "global.h"
#include "content.h"

/////////////////////////////////////////////////////////////////////////////
Content::Content()
{
}

/////////////////////////////////////////////////////////////////////////////
Content::~Content()
{
}

/////////////////////////////////////////////////////////////////////////////
void Content::index(int nfiles, char **pfiles)
{
	for (int i = 0; i < nfiles; i++) {		
		if (!lexer.open(pfiles[i])) {
			error("unable to open file \"%s\".", pfiles[i]);
		}		
		
		files.insert(pfiles[i]);		
		parse();
		
		lexer.close();
	}
}

/////////////////////////////////////////////////////////////////////////////
// parse input stream 
void Content::parse(void)
{
	uint16_t filenum;
	const char *term;
	
	filenum = files.size();	
	while ((term = lexer.gettok()) != NULL) {
		block.insert(term, filenum);		
	}
}
