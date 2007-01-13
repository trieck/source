/////////////////////////////////////////////////////////////////////////////
//
//	SYMBOL.H
//
//	Copyright (c) 1999 Thomas A. Rieck
//

#ifndef __SYMBOL_H__
#define __SYMBOL_H__

/////////////////////////////////////////////////////////////////////////////
class SymbolTable : protected map<string, const Symbol *>
{
public:
// Construction / Destruction
	SymbolTable();
	~SymbolTable();

// Interface
	const Symbol* install(const char *name, SymbolType type, double value);
	const Symbol* install(const char *name, Instr instruction);
	const Symbol* install(const char *name, const char *value);
	const Symbol* install(const char *name, const Keyword keyword);
	const Symbol* install(const char *name, SymbolType type, Instr * defn);
	const Symbol* lookup(const char *name) const;
protected:
// Implementation
	void init();
};
/////////////////////////////////////////////////////////////////////////////

#endif // __SYMBOL_H__

