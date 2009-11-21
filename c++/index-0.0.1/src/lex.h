/////////////////////////////////////////////////////////////////////////////
//
// LEX.H : Lexical Analyzer
//
// Copyright (c) 2008 Thomas A. Rieck, All Rights Reserved
//

#ifndef __LEX_H__
#define __LEX_H__

/////////////////////////////////////////////////////////////////////////////
class Lex {
// Construction / Destruction
public:
	Lex();
	~Lex();

// Interface
	bool open(const char *filename);
	void close();
	const char *gettok(void);

// Implementation
private:
	char buf[PATH_MAX];	// lexical buffer
	FILE *fp;			// input file ptr
};

/////////////////////////////////////////////////////////////////////////////
#endif // __LEX_H__
