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
enum SymbolType {
	ST_UNDEF = 0,		// undefined
	ST_REG,				// cpu register 
	ST_INSTRUCTION,		// machine instruction 
	ST_ID, 				// identifier 
	ST_CONST,			// numeric constant 
	ST_STRING,			// string literal
	ST_OP				// operator
};

/////////////////////////////////////////////////////////////////////////////
// Symbol struct
typedef struct Symbol {
	Symbol() : type(ST_UNDEF), sub(0), instr(0), next(0) {}
	
	string name;			// symbol name
	SymbolType type;		// symbol type
	uint32_t sub;			// sub-type
	union {
		const Instr *instr;	// instruction
		uint32_t opcode;	// operator code
		word val16;			// word value
		byte val8;			// byte value
	};
	Symbol *next;			// next symbol in list
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
		uint32_t sub, word value);	// constant

	// operators
	LPSYMBOL installo(uint32_t op, uint32_t sub, Symbol *args); 

	LPSYMBOL lookup(const string &s) const;

	static LPSYMBOL link(LPSYMBOL s1, LPSYMBOL s2);

// Implementation
private:
	void iinsert(const string &s, uint32_t t, const Instr *i);
	void rinsert(const string &s, uint32_t t, byte r);
	void idinsert(const string &s, uint32_t id);

	void freeSym(LPSYMBOL s);

	static SymbolTablePtr instance;	// singleton instance

	typedef map<string, LPSYMBOL, stringless> symmap;
	symmap table;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __SYMBOLTABLE_H__
