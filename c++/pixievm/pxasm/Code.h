/////////////////////////////////////////////////////////////////////////////
//
// CODE.H : Code generation
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __CODE_H__
#define __CODE_H__

#include "SymbolTable.h"
#include "Machine.h"

class Code;
typedef auto_ptr<Code> CodePtr;

/////////////////////////////////////////////////////////////////////////////
class Code {
private:
	Code();
public:
	~Code();

	static Code *getInstance();

	void code0(uint32_t mode, LPSYMBOL s1);
	void code1(uint32_t mode, LPSYMBOL s1, LPSYMBOL s2);
	void code2(uint32_t mode, LPSYMBOL s1, LPSYMBOL s2, LPSYMBOL s3);
	void relcode(LPSYMBOL s1, LPSYMBOL s2);

	bool isGenerating() const;

	word getOrigin() const;
	void setOrigin(word origin);
	bool isOriginSet() const;

	void putSym(LPSYMBOL s, uint32_t ctxt);
	void putWord(word w);
	void putByte(byte b);

	void putWordAt(word location, word w);
	void putByteAt(word location, byte b);

	void putString(const string &str);
	word location() const;

	void pass2();
	void write(FILE *fp) const;

private:
	void initialize();

	void rr8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void ri8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void rm8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void ra8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void rr16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void ri16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void rm16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void ra16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void mr8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void mr16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void m8i8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void m16i8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void mi16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void ar8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void ar16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void a8i8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void a16i8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void ai16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2);
	void r8(const Instr *instr, LPSYMBOL s);
	void r16(const Instr *instr, LPSYMBOL s);
	void m8(const Instr *instr, LPSYMBOL s);
	void m16(const Instr *instr, LPSYMBOL s);
	void a8(const Instr *instr, LPSYMBOL s);
	void a16(const Instr *instr, LPSYMBOL s);
	void implied(const Instr *instr);
	void i16(const Instr *instr, LPSYMBOL s);
	void i8(const Instr *instr, LPSYMBOL s);

	void putOp(LPSYMBOL s, uint32_t ctxt);
	void putList(LPSYMBOL s, uint32_t ctxt);
	void putFixup(LPSYMBOL s, uint32_t ctxt);

	void pushargs(LPSYMBOL s);

	typedef void (Code::*Code0Ptr)(const Instr *);
	typedef void (Code::*Code1Ptr)(const Instr *, LPSYMBOL);
	typedef void (Code::*Code2Ptr)(const Instr *, LPSYMBOL, LPSYMBOL);

	typedef map<uint32_t, Code0Ptr> Code0FncMap;
	typedef map<uint32_t, Code1Ptr> Code1FncMap;
	typedef map<uint32_t, Code2Ptr> Code2FncMap;

	static CodePtr instance;	// singleton instance

	enum { MEMSIZE = 4096 };	// maximum code size

	word m_origin;				// assembly origin
	bool m_bOrigin;				// origin has been declared
	byte m_memory[MEMSIZE];		// memory
	byte *m_pmem;				// current memory pointer
	Program program;			// program for runtime machine
	Code0FncMap	m_code0Map;		// code0 function map
	Code1FncMap m_code1Map;		// code1 function map
	Code2FncMap m_code2Map;		// code2 function map
};

/////////////////////////////////////////////////////////////////////////////
inline word Code::getOrigin() const
{
	return m_origin;
}

/////////////////////////////////////////////////////////////////////////////
inline void Code::setOrigin(word origin)
{
	m_origin = origin;
	m_bOrigin = true;
}

/////////////////////////////////////////////////////////////////////////////
inline bool Code::isOriginSet() const
{
	return m_bOrigin;
}

/////////////////////////////////////////////////////////////////////////////
inline bool Code::isGenerating() const  	// has code generation begun?
{
	return ((m_pmem - m_memory) > 0);
}

/////////////////////////////////////////////////////////////////////////////
inline word Code::location() const
{
	return m_origin + (m_pmem - m_memory);
}

#endif // __CODE_H__
