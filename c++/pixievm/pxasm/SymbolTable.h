/////////////////////////////////////////////////////////////////////////////
//
// SYMBOLTABLE.H : Symbol table
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include "Modes.h"
#include "Instructions.h"

/////////////////////////////////////////////////////////////////////////////
// Symbol type
#define ST_UNDEF		(0)			// undefined
#define ST_REG			(1 << 0)	// cpu register 
#define ST_INSTRUCTION	(1 << 1)	// machine instruction 
#define ST_ID			(1 << 2)	// identifier 
#define ST_CONST		(1 << 3)	// constant 
#define ST_STRING		(1 << 4)	// string literal

/////////////////////////////////////////////////////////////////////////////
// Symbol struct
typedef struct Symbol {
	int type;				// symbol type 
	int sub;				// sub-type 
	string name;			// symbol name 
	union {
		const Instr *instr;	// instruction 
		word val16;			// word value 
		byte val8;			// byte value 
	};
} Symbol, *LPSYMBOL;

class SymbolTable;
typedef auto_ptr<SymbolTable> SymbolTablePtr;

/////////////////////////////////////////////////////////////////////////////
class SymbolTable {
// Construction / Destruction
private:
	SymbolTable();
public:
	~SymbolTable();

// Interface
	static SymbolTable *getInstance();
	LPSYMBOL install(const string &s);	// undefined
	LPSYMBOL installs(const string &s);	// string literal
	LPSYMBOL installw(const string &s, int type, int sub, word w);
	LPSYMBOL installb(const string &s, int type, int sub, byte b);
	LPSYMBOL lookup(const string &s) const;

// Implementation
private:
	void iinsert(const string &s, int t, const Instr *i);
	void rinsert(const string &s, int t, byte r);
	void idinsert(const string &s, int id);

	static SymbolTablePtr instance;	// singleton instance

	typedef map<string, LPSYMBOL, stringless> symmap;
	symmap table;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __SYMBOLTABLE_H__
