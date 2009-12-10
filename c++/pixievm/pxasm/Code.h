/////////////////////////////////////////////////////////////////////////////
//
// CODE.H : Code generation
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __CODE_H__
#define __CODE_H__

#include "SymbolTable.h"

class Code;
typedef auto_ptr<Code> CodePtr;

/////////////////////////////////////////////////////////////////////////////
class Code
{
private:
	Code();
public:
	~Code();

	static Code *getInstance();

	void code1(uint32_t mode, LPSYMBOL s1);
	void code2(uint32_t mode, LPSYMBOL s1, LPSYMBOL s2);
	void code3(uint32_t mode, LPSYMBOL s1, LPSYMBOL s2, LPSYMBOL s3);
	
	bool isGenerated() const;

	word getOrigin() const;
	void setOrigin(word origin);
	bool isOriginSet() const;

	void putWord(word w);
	void putByte(byte b);
	void putString(const string &str);

	void setLabel(LPSYMBOL sym);

private:
	void rr8(const Instr *instr, byte dest, byte src);
	void ri8(const Instr *instr, byte r8, byte i8);
	void rm8(const Instr *instr, byte r8, byte m16);
	void ra8(const Instr *instr, byte r8, word a16);
	void rr16(const Instr *instr, byte dest, byte src);
	void ri16(const Instr *instr, byte r16, word i16);
	void rm16(const Instr *instr, byte r16, byte m16);
	void ra16(const Instr *instr, byte r16, word a16);
	void mr8(const Instr *instr, byte m16, byte r8);
	void mr16(const Instr *instr, byte m16, byte r16);
	void m8i8(const Instr *instr, byte m16, byte i8);
	void m16i8(const Instr *instr, byte m16, byte i8);
	void mi16(const Instr *instr, byte m16, word i16);
	void ar8(const Instr *instr, word a16, byte r8);
	void ar16(const Instr *instr, word a16, byte r16);
	void a8i8(const Instr *instr, word a16, byte i8);
	void a16i8(const Instr *instr, word a16, byte i8);
	void ai16(const Instr *instr, word a16, word i16);
	void r8(const Instr *instr, byte r8);
	void r16(const Instr *instr, byte r16);
	void m8(const Instr *instr, byte m16);
	void m16(const Instr *instr, byte m16);
	void a8(const Instr *instr, word a16);
	void a16(const Instr *instr, word a16);
	void implied(const Instr *instr);
	void i16(const Instr *instr, word i16);
	void i8(const Instr *instr, byte i8);

	static CodePtr instance;	// singleton instance

	enum { MEMSIZE = 4096 };	// maximum code size
	
	word m_origin;				// assembly origin
	bool m_bOrigin;				// origin has been declared
	byte m_memory[MEMSIZE];		// memory
	byte *m_pmem;				// current memory pointer
};

/////////////////////////////////////////////////////////////////////////////
inline word Code::getOrigin() const { 
	return m_origin; 
}
	
/////////////////////////////////////////////////////////////////////////////
inline void Code::setOrigin(word origin) { 
	m_origin = origin; 
	m_bOrigin = true;
}

/////////////////////////////////////////////////////////////////////////////
inline bool Code::isOriginSet() const {
	return m_bOrigin;
}

/////////////////////////////////////////////////////////////////////////////
inline bool Code::isGenerated() const {	// has code generation begun?
	return ((m_pmem - m_memory) > 0);
}

#endif // __CODE_H__
