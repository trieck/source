/////////////////////////////////////////////////////////////////////////////
//
//	LEXER.H : Lexical analyzer
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __LEXER_H__
#define __LEXER_H__

/////////////////////////////////////////////////////////////////////////////
typedef struct Token {
	Token() : pos(0), offset(0) {}
	Token(const Token &rhs) {
		*this = rhs;
	}
	Token &operator = (const Token &rhs) {
		if (this != &rhs) {
			pos = rhs.pos;
			offset = rhs.offset;
			val = rhs.val;
		}
		return *this;
	}

	UINT64 getLocation() const {
		return ((UINT64)pos << 32) | offset;
	}

	UINT pos;		// token position
	UINT offset;	// file offset
	string val;		// value of token
} *LPTOKEN;

/////////////////////////////////////////////////////////////////////////////
// Helper functions
inline bool isempty(const Token &t)
{
	return t.val == "";
}

/////////////////////////////////////////////////////////////////////////////
class Lexer {
// Construction / Destruction
public:
	Lexer(IPeekableStream *pstream);
	virtual ~Lexer();

// Interface
	Token gettok();

// Implementation
private:
	int getc();
	UINT pos;					// current word position
	UINT offset;				// current file offset
	IPeekableStream *stream;	// underlying stream
};
/////////////////////////////////////////////////////////////////////////////

typedef auto_ptr<Lexer> LexerPtr;

#endif // __LEXER_H__

