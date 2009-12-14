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
#include "FixUps.h"

/////////////////////////////////////////////////////////////////////////////
// Symbol type
enum SymbolType {
	ST_UNDEF = 0,		// undefined
	ST_REG,				// cpu register 
	ST_INSTRUCTION,		// machine instruction 
	ST_ID, 				// identifier 
	ST_CONST,			// numeric constant 
	ST_STRING			// string literal
};

/////////////////////////////////////////////////////////////////////////////
// Symbol struct
typedef struct Symbol {
	Symbol() : type(ST_UNDEF), ftype(FT_STD), sub(0), instr(0), 
		weak(false), ref(0) {}
	
	string name;			// symbol name
	SymbolType type;		// symbol type
	FixUpType ftype;		// fix-up type
	uint32_t sub;			// sub-type
	bool weak;				// can flush?
	Symbol *ref;			// symbol references another
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
	LPSYMBOL installw(const string &s, SymbolType type, 
		uint32_t sub, word value, LPSYMBOL ref = 0, 
		FixUpType ftype = FT_UNDEF);
	LPSYMBOL lookup(const string &s) const;

	void flush();

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
