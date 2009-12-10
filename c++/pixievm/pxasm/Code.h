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
	
	word getOrigin() const;
	void setOrigin(word origin);
	bool isOriginSet() const;

	void putWord(word w);
	void putByte(byte b);
	void putString(const string &str);

private:
	void RR8(const Instr *instr, byte dest, byte src);
	void RI8(const Instr *instr, byte r8, byte i8);
	void RM8(const Instr *instr, byte r8, byte m16);
	void RA8(const Instr *instr, byte r8, word a16);
	void RR16(const Instr *instr, byte dest, byte src);
	void RI16(const Instr *instr, byte r16, word i16);
	void RM16(const Instr *instr, byte r16, byte m16);
	void RA16(const Instr *instr, byte r16, word a16);
	void MR8(const Instr *instr, byte m16, byte r8);
	void MR16(const Instr *instr, byte m16, byte r16);
	void M8I8(const Instr *instr, byte m16, byte i8);
	void M16I8(const Instr *instr, byte m16, byte i8);
	void MI16(const Instr *instr, byte m16, word i16);
	void AR8(const Instr *instr, word a16, byte r8);
	void AR16(const Instr *instr, word a16, byte r16);
	void A8I8(const Instr *instr, word a16, byte i8);
	void A16I8(const Instr *instr, word a16, byte i8);
	void AI16(const Instr *instr, word a16, word i16);
	void R8(const Instr *instr, byte r8);
	void R16(const Instr *instr, byte r16);
	void M8(const Instr *instr, byte m16);
	void M16(const Instr *instr, byte m16);
	void A8(const Instr *instr, word a16);
	void A16(const Instr *instr, word a16);
	void IMPLIED(const Instr *instr);
	void I16(const Instr *instr, word i16);
	void I8(const Instr *instr, byte i8);

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

#endif // __CODE_H__
