/////////////////////////////////////////////////////////////////////////////
//
// SYMBOL.CPP
//
// Copyright (c) 1999 Thomas A. Rieck
//

#include "common.h"
#include "symbol.h"
#include "machine.h"
#include <iostream>

//
// Constructor
//
SymbolTable::SymbolTable()
{
	init();	// install built in functions and keywords
}

//
// Destructor
//
SymbolTable::~SymbolTable()
{
	map<string, const Symbol *>::const_iterator it = begin();
	for ( ; it != end(); it++) {
		const Symbol * sp = (*it).second;
		delete const_cast<Symbol *>(sp);
	}
}

//
// install
//
const Symbol * SymbolTable::install(const char* name,
                                    SymbolType type, double value)
{
	Symbol * sp = const_cast<Symbol *>(lookup(name));
	if (sp == NULL)
		sp = new Symbol;

	sp->type = type;
	sp->value = value;

	return (*this)[name] = sp;
}

//
// install
//
const Symbol * SymbolTable::install(const char* name,
                                    SymbolType type, Instr * defn)
{
	Symbol * sp = const_cast<Symbol *>(lookup(name));
	if (sp == NULL)
		sp = new Symbol;

	sp->type = type;
	sp->defn = defn;

	return (*this)[name] = sp;
}


//
// install
//
const Symbol * SymbolTable::install(const char* name, Instr i)
{
	Symbol * sp = const_cast<Symbol *>(lookup(name));
	if (sp == NULL)
		sp = new Symbol;

	sp->type = bltin;
	sp->instruction = i;

	return (*this)[name] = sp;
}

//
// install
//
const Symbol * SymbolTable::install(const char *name, const char *value)
{
	Symbol * sp = const_cast<Symbol *>(lookup(name));
	if (sp == NULL)
		sp = new Symbol;

	sp->type = str;
	strcpy(sp->str, value);

	return (*this)[name] = sp;
}

//
// install
//
const Symbol * SymbolTable::install(const char *name, const Keyword kword)
{
	Symbol * sp = const_cast<Symbol *>(lookup(name));
	if (sp == NULL)
		sp = new Symbol;

	sp->type = keyword;
	sp->keyword = kword;

	return (*this)[name] = sp;
}

//
// lookup
//
const Symbol* SymbolTable::lookup(const char* name) const
{
	map<string, const Symbol *>::const_iterator it = find(name);
	if (it != end())
		return (*it).second;

	return NULL;
}

//
// init
//
void SymbolTable::init()
{
	// install built in functions
	install("pow", &Machine::pow);
	install("log", &Machine::log);
	install("log10", &Machine::log10);
	install("fmod", &Machine::fmod);
	install("sin", &Machine::sin);
	install("asin", &Machine::asin);
	install("sinh", &Machine::sinh);
	install("cos", &Machine::cos);
	install("acos", &Machine::acos);
	install("cosh", &Machine::cosh);
	install("tan", &Machine::tan);
	install("atan", &Machine::atan);
	install("tanh", &Machine::tanh);
	install("sqrt", &Machine::sqrt);
	install("int", &Machine::iint);
	install("exp", &Machine::exp);
	install("ceil", &Machine::ceil);
	install("floor", &Machine::floor);
	install("abs", &Machine::abs);

	// install keywords
	install("proc", PROC);
	install("func", FUNC);
	install("return", RETURN);
	install("if", IF);
	install("else", ELSE);
	install("while", WHILE);
	install("printf", PRINTF);
}



