/////////////////////////////////////////////////////////////////////////////
//
// CODE.CPP : Code generation
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Code.h"
#include "Parser.hpp"
#include "Exception.h"

#define MAKEREG(hi, lo)	((hi << 4) | lo)
#define OPCODE(i, m)	(*(*i)[m])

CodePtr Code::instance(Code::getInstance());
extern SymbolTable *table;

extern int yyerror(const char *s);

/////////////////////////////////////////////////////////////////////////////
Code::Code() : m_origin(0), m_bOrigin(false), m_pmem(m_memory)
{
	memset(m_memory, 0, sizeof(byte) * MEMSIZE);
	initialize();
}

/////////////////////////////////////////////////////////////////////////////
Code::~Code()
{
}

/////////////////////////////////////////////////////////////////////////////
Code *Code::getInstance()
{
	if (instance.get() == NULL) {
		instance = CodePtr(new Code);
	}
	return instance.get();
}

/////////////////////////////////////////////////////////////////////////////
void Code::initialize()
{
	// code1
	m_code1Map[AM_IMPLIED] = &Code::implied;

	// code2
	m_code2Map[AM_R8] = &Code::r8;
	m_code2Map[AM_R16] = &Code::r16;
	m_code2Map[AM_M8] = &Code::m8;
	m_code2Map[AM_M16] = &Code::m16;
	m_code2Map[AM_A8] = &Code::a8;
	m_code2Map[AM_A16] = &Code::a16;
	m_code2Map[AM_I16] = &Code::i16;
	m_code2Map[AM_I8] = &Code::i8;

	// code3
	m_code3Map[AM_RR8] = &Code::rr8;
	m_code3Map[AM_RI8] = &Code::ri8;
	m_code3Map[AM_RM8] = &Code::rm8;
	m_code3Map[AM_RA8] = &Code::ra8;
	m_code3Map[AM_RR16] = &Code::rr16;
	m_code3Map[AM_RI16] = &Code::ri16;
	m_code3Map[AM_RM16] = &Code::rm16;
	m_code3Map[AM_RA16] = &Code::ra16;
	m_code3Map[AM_MR8] = &Code::mr8;
	m_code3Map[AM_MR16] = &Code::mr16;
	m_code3Map[AM_M8I8] = &Code::m8i8;
	m_code3Map[AM_M16I8] = &Code::m16i8;
	m_code3Map[AM_MI16] = &Code::mi16;
	m_code3Map[AM_AR8] = &Code::ar8;
	m_code3Map[AM_AR16] = &Code::ar16;
	m_code3Map[AM_A8I8] = &Code::a8i8;
	m_code3Map[AM_A16I8] = &Code::a16i8;
	m_code3Map[AM_AI16] = &Code::ai16;
}

/////////////////////////////////////////////////////////////////////////////
void Code::putString(const string &str)
{
	for (uint32_t i = 0; i < str.length(); i++) {
		putByte(str[i]);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Code::putWord(word w)
{
	putByte(HIBYTE(w));
	putByte(LOBYTE(w));
}

/////////////////////////////////////////////////////////////////////////////
void Code::putSym(LPSYMBOL s)
{
	if (s == ST_UNDEF) {	// forward reference
		makeFixup(s);
	}

	switch (s->sub) {
	case IM8:
		putByte(s->val8);
		break;
	case IM16:
		putWord(s->val16);
		break;
	default:
		throw Exception("unsupported symbol.");
	}
}

/////////////////////////////////////////////////////////////////////////////
void Code::putByte(byte b)
{
	if ((m_pmem - m_memory) >= MEMSIZE)
		throw Exception("memory overflow.");

	*m_pmem++ = b;
}

/////////////////////////////////////////////////////////////////////////////
void Code::code1(uint32_t mode, LPSYMBOL s1)
{
	Code1FncMap::const_iterator it = m_code1Map.find(mode);
	if (it == m_code1Map.end()) {
		throw Exception("unexpected addressing mode %d.", mode);
	}

	Code1Ptr pfnc = (*it).second;

	(this->*(pfnc))(s1->instr);
}

/////////////////////////////////////////////////////////////////////////////
void Code::code2(uint32_t mode, LPSYMBOL s1, LPSYMBOL s2)
{
	Code2FncMap::const_iterator it = m_code2Map.find(mode);
	if (it == m_code2Map.end()) {
		throw Exception("unexpected addressing mode %d.", mode);
	}

	Code2Ptr pfnc = (*it).second;

	(this->*(pfnc))(s1->instr, s2);
}

/////////////////////////////////////////////////////////////////////////////
void Code::code3(uint32_t mode, LPSYMBOL s1, LPSYMBOL s2, LPSYMBOL s3)
{
	Code3FncMap::const_iterator it = m_code3Map.find(mode);
	if (it == m_code3Map.end()) {
		throw Exception("unexpected addressing mode %d.", mode);
	}

	Code3Ptr pfnc = (*it).second;

	(this->*(pfnc))(s1->instr, s2, s3);
}

/////////////////////////////////////////////////////////////////////////////
void Code::relcode(LPSYMBOL s1, LPSYMBOL s2)
{
	// calculate and encode relative branches

	putByte(OPCODE(s1->instr, AM_I8));

	int8_t offset = 0;
	if (s2->type == ST_UNDEF) {	// forward reference branch
		makeFixup(s2, true);
	} else {
		// check whether target is in range for relative branch
		word diff = abs(s2->val16 - (location() + sizeof(byte)));
		if (diff >= 0x100) {
			yyerror("address out of range");
			return;
		}
		offset = (s2->val16 - (location() + sizeof(byte)));
	}

	putByte(offset);
}

/////////////////////////////////////////////////////////////////////////////
void Code::rr8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_RR8));
	putByte(MAKEREG(s1->val8, s2->val8));
}

////////////////////////////////////////////////////////////////////////////
void Code::ri8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_RI8));
	putByte(s1->val8);
	putByte(s2->val8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::rm8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_RM8));
	putByte(MAKEREG(s1->val8, s2->val8));
}

/////////////////////////////////////////////////////////////////////////////
void Code::ra8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_RA8));
	putByte(s1->val8);
	putSym(s2);
}

/////////////////////////////////////////////////////////////////////////////
void Code::rr16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_RR16));
	putByte(MAKEREG(s1->val8, s2->val8));
}

/////////////////////////////////////////////////////////////////////////////
void Code::ri16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_RI16));
	putByte(s1->val8);
	putSym(s2);
}

/////////////////////////////////////////////////////////////////////////////
void Code::rm16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_RM16));
	putByte(MAKEREG(s1->val8, s2->val8));
}

/////////////////////////////////////////////////////////////////////////////
void Code::ra16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_RA16));
	putByte(s1->val8);
	putSym(s2);
}

/////////////////////////////////////////////////////////////////////////////
void Code::mr8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_MR8));
	putByte(MAKEREG(s1->val8, s2->val8));
}

/////////////////////////////////////////////////////////////////////////////
void Code::mr16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_MR16));
	putByte(MAKEREG(s1->val8, s2->val8));
}

/////////////////////////////////////////////////////////////////////////////
void Code::m8i8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_M8I8));
	putByte(s1->val8);
	putByte(s2->val8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::m16i8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_M16I8));
	putByte(s1->val8);
	putByte(s2->val8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::mi16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_MI16));
	putByte(s1->val8);
	putSym(s2);
}

/////////////////////////////////////////////////////////////////////////////
void Code::ar8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_AR8));
	putByte(s2->val8);
	putSym(s1);
}

/////////////////////////////////////////////////////////////////////////////
void Code::ar16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_AR16));
	putByte(s2->val8);
	putSym(s1);
}

/////////////////////////////////////////////////////////////////////////////
void Code::a8i8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_A8I8));
	putByte(s2->val8);
	putSym(s1);
}

/////////////////////////////////////////////////////////////////////////////
void Code::a16i8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_A16I8));
	putByte(s2->val8);
	putSym(s1);
}

/////////////////////////////////////////////////////////////////////////////
void Code::ai16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_AI16));
	putSym(s2);
	putSym(s1);
}

/////////////////////////////////////////////////////////////////////////////
void Code::r8(const Instr *instr, LPSYMBOL s)
{
	putByte(OPCODE(instr, AM_R8));
	putByte(s->val8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::r16(const Instr *instr, LPSYMBOL s)
{
	putByte(OPCODE(instr, AM_R16));
	putByte(s->val8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::m8(const Instr *instr, LPSYMBOL s)
{
	putByte(OPCODE(instr, AM_M8));
	putByte(s->val8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::m16(const Instr *instr, LPSYMBOL s)
{
	putByte(OPCODE(instr, AM_M16));
	putByte(s->val8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::a8(const Instr *instr, LPSYMBOL s)
{
	putByte(OPCODE(instr, AM_A8));
	putSym(s);
}

/////////////////////////////////////////////////////////////////////////////
void Code::a16(const Instr *instr, LPSYMBOL s)
{
	putByte(OPCODE(instr, AM_A16));
	putSym(s);
}

/////////////////////////////////////////////////////////////////////////////
void Code::implied(const Instr *instr)
{
	putByte(OPCODE(instr, AM_IMPLIED));
}

/////////////////////////////////////////////////////////////////////////////
void Code::i16(const Instr *instr, LPSYMBOL s)
{
	putByte(OPCODE(instr, AM_I16));
	putSym(s);
}

/////////////////////////////////////////////////////////////////////////////
void Code::i8(const Instr *instr, LPSYMBOL s)
{
	putByte(OPCODE(instr, AM_I8));
	putByte(s->val8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::makeFixup(LPSYMBOL s, bool bRel)
{
	// if s is of type ST_UNDEF, we may be forward referencing a label.
	// In this case, generate a fixup that will be resolved during
	// the second pass of the assembler
	if (s->type != ST_UNDEF)
		return;

	// bRel is true if this is a relative branch fix-up, otherwise,
	// it's false.
	m_fixups.add(s->name.c_str(), location(), bRel);
}

/////////////////////////////////////////////////////////////////////////////
void Code::resolve()
{
	// resolve any fix-up locations

	uint32_t nfixups = m_fixups.size();

	for (uint32_t i = 0; i < nfixups; i++) {
		resolve(m_fixups[i]);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Code::resolve(const FixUp &fixup)
{
	LPSYMBOL sym;
	if (((sym = table->lookup(fixup.name)) == NULL) ||
	        (sym->type == ST_UNDEF)) {
		throw Exception("%s never defined.", fixup.name);
	}

	ASSERT(sym->type == ST_ID);
	ASSERT(sym->sub = IM16);

	word symloc = sym->val16;
	word fixloc = fixup.location;
	word diff = symloc - fixloc;

	if (fixup.isrel) {	// relative branch fix-up
		if (diff > 0x7F) {
			throw Exception("branch out of range for label \"%s\".",
			                fixup.name);
		}

		word offset = fixloc - m_origin;
		ASSERT(m_memory[offset] == 0);
		m_memory[offset] = (byte)diff;
	} else {
		/* TODO: */
	}
}

/////////////////////////////////////////////////////////////////////////////
void Code::write(FILE *fp) const
{
	const byte *pmem = &m_memory[0];
	
	if (fwrite(&m_origin, sizeof(word), 1, fp) != 1) {
		throw Exception("can't write to file: %s.",
				strerror(errno));
	}

	for ( ; pmem < m_pmem; pmem++) {
		if (fputc(*pmem, fp) == EOF) {
			throw Exception("can't write to file: %s.",
				strerror(errno));
		}
	}

	fflush(fp);
}
