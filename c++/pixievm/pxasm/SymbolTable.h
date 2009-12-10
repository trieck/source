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
#define ST_UNDEF		(0)		// undefined
#define ST_REG			(1)		// cpu register 
#define ST_INSTRUCTION	(2)		// machine instruction 
#define ST_ID			(3)		// identifier 
#define ST_CONST		(4)		// numeric constant 
#define ST_STRING		(5)		// string literal

/////////////////////////////////////////////////////////////////////////////
// Symbol struct
typedef struct Symbol {
	uint32_t type;			// symbol type 
	uint32_t sub;			// sub-type 
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
	LPSYMBOL installw(const string &s, uint32_t type, uint32_t sub, word w);
	LPSYMBOL installb(const string &s, uint32_t type, uint32_t sub, byte b);
	LPSYMBOL lookup(const string &s) const;

// Implementation
private:
	void iinsert(const string &s, uint32_t t, const Instr *i);
	void rinsert(const string &s, uint32_t t, byte r);
	void idinsert(const string &s, uint32_t id);

	static SymbolTablePtr instance;	// singleton instance

	typedef map<string, LPSYMBOL, stringless> symmap;
	symmap table;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __SYMBOLTABLE_H__
