/////////////////////////////////////////////////////////////////////////////
//
// SYMBOLTABLE.CPP : Symbol table
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Modes.h"
#include "Instructions.h"
#include "SymbolTable.h"
#include "Parser.hpp"

SymbolTablePtr SymbolTable::instance(SymbolTable::getInstance());

/////////////////////////////////////////////////////////////////////////////
SymbolTable::SymbolTable()
{
	/* Group #1 instructions */
	iinsert("ADC", I1, &INS_ADC);
	iinsert("AND", I1, &INS_AND);
	iinsert("BIT", I1, &INS_BIT);
	iinsert("CMP", I1, &INS_CMP);
	iinsert("MOV", I1, &INS_MOV);
	iinsert("OR", I1, &INS_OR);
	iinsert("SBB", I1, &INS_SBB);
	iinsert("XOR", I1, &INS_XOR);

	/* Group #2 instructions */
	iinsert("DEC", I2, &INS_DEC);
	iinsert("INC", I2, &INS_INC);
	iinsert("ROL", I2, &INS_ROL);
	iinsert("ROR", I2, &INS_ROR);
	iinsert("SHL", I2, &INS_SHL);
	iinsert("SHR", I2, &INS_SHR);

	/* Group #3 instructions */
	iinsert("BRK", I3, &INS_BRK);
	iinsert("CLC", I3, &INS_CLC);
	iinsert("CLI", I3, &INS_CLI);
	iinsert("DEX", I3, &INS_DEX);
	iinsert("INX", I3, &INS_INX);
	iinsert("IRET", I3, &INS_IRET);
	iinsert("NOP", I3, &INS_NOP);
	iinsert("RET", I3, &INS_RET);
	iinsert("SEC", I3, &INS_SEC);
	iinsert("SEI", I3, &INS_SEI);
	iinsert("POPA", I3, &INS_POPA);
	iinsert("POPF", I3, &INS_POPF);
	iinsert("PUSHA", I3, &INS_PUSHA);
	iinsert("PUSHF", I3, &INS_PUSHF);

	/* Group #4 instructions */
	iinsert("CALL", I4, &INS_CALL);
	iinsert("JMP", I4, &INS_JMP);

	/* Group #5 instructions */
	iinsert("JCC", I5, &INS_JCC);
	iinsert("JCS", I5, &INS_JCS);
	iinsert("JMI", I5, &INS_JMI);
	iinsert("JNZ", I5, &INS_JNZ);
	iinsert("JPL", I5, &INS_JPL);
	iinsert("JVC", I5, &INS_JVC);
	iinsert("JVS", I5, &INS_JVS);
	iinsert("JZ", I5, &INS_JZ);

	/* Group #6 instructions */
	iinsert("POP", I6, &INS_POP);

	/* Group #7 instructions */
	iinsert("PUSH", I7, &INS_PUSH);

	// 8-bit registers */
	rinsert("AL", R8, 0x00);
	rinsert("AH", R8, 0x01);
	rinsert("BL", R8, 0x02);
	rinsert("BH", R8, 0x03);
	rinsert("CL", R8, 0x04);
	rinsert("CH", R8, 0x05);
	rinsert("DL", R8, 0x06);
	rinsert("DH", R8, 0x07);

	// 16-bit registers 
	rinsert("A", R16, 0x00);
	rinsert("B", R16, 0x01);
	rinsert("C", R16, 0x02);
	rinsert("D", R16, 0x03);
	rinsert("X", R16, 0x04);
	rinsert("SP", R16, 0x05);

	// Identifiers 
	idinsert("BYTE", BYTE);
	idinsert("WORD", WORD);

	/* pseudo operations */
	idinsert(".ORG", DECL_ORG);
	idinsert(".BYTE", DECL_BYTE);
	idinsert(".WORD", DECL_WORD);
	idinsert(".TEXT", DECL_TEXT);

}

/////////////////////////////////////////////////////////////////////////////
SymbolTable::~SymbolTable()
{
	symmap::const_iterator it = table.begin();
	for ( ; it != table.end(); it++) {
		LPSYMBOL sym = (*it).second;
		delete sym;
	}
}

/////////////////////////////////////////////////////////////////////////////
SymbolTable *SymbolTable::getInstance()
{
	if (instance.get() == NULL) {
		instance = SymbolTablePtr(new SymbolTable);
	}
	return instance.get();
}

/////////////////////////////////////////////////////////////////////////////
void SymbolTable::iinsert(const string &s, int t, const Instr *i)
{
	LPSYMBOL sym = new Symbol;
	sym->name = s;
	sym->type = ST_INSTRUCTION;
	sym->sub = t;
	sym->instr = i;
	table[s] = sym;
}

/////////////////////////////////////////////////////////////////////////////
void SymbolTable::rinsert(const string &s, int t, byte r)
{
	LPSYMBOL sym = new Symbol;
	sym->name = s;
	sym->type = ST_REG;
	sym->sub = t;
	sym->val8 = r;
	table[s] = sym;
}

/////////////////////////////////////////////////////////////////////////////
void SymbolTable::idinsert(const string &s, int id)
{
	LPSYMBOL sym = new Symbol;
	sym->name = s;
	sym->type = ST_ID;
	sym->sub = id;
	table[s] = sym;
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::install(const string &s)
{
	LPSYMBOL sym;
	if ((sym = lookup(s)) == NULL) {
		sym = new Symbol;
		sym->name = s;
		sym->type = ST_UNDEF;
		sym->sub = 0;
		table[s] = sym;
	}

	return sym;
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::installs(const string &s)
{
	LPSYMBOL sym;
	if ((sym = lookup(s)) == NULL) {
		sym = new Symbol;
		sym->name = s;
		sym->type = ST_STRING;
		sym->sub = 0;
		table[s] = sym;
	}

	return sym;
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::installw(const string &s, int type, int sub, word w)
{
	LPSYMBOL sym;
	if ((sym = lookup(s)) == NULL) {
		sym = new Symbol;
		sym->name = s;
		sym->type = type;
		sym->sub = sub;
		sym->val16 = w;
		table[s] = sym;
	}
	return sym;
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::installb(const string &s, int type, int sub, byte b)
{
	LPSYMBOL sym;
	if ((sym = lookup(s)) == NULL) {
		sym = new Symbol;
		sym->name = s;
		sym->type = type;
		sym->sub = sub;
		sym->val8 = b;
		table[s] = sym;
	}
	return sym;
}

/////////////////////////////////////////////////////////////////////////////
LPSYMBOL SymbolTable::lookup(const string &s) const
{
	symmap::const_iterator it = table.find(s);
	if (it == table.end())
		return NULL;

	return (*it).second;
}

