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

extern int yyerror(const char *s);

/////////////////////////////////////////////////////////////////////////////
Code::Code() : m_origin(0), m_bOrigin(false), m_pmem(m_memory)
{
	memset(m_memory, 0, sizeof(byte) * MEMSIZE);
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
void Code::putByte(byte b)
{
	if ((m_pmem - m_memory) >= MEMSIZE)
		throw Exception("memory overflow.");

	*m_pmem++ = b;
}

/////////////////////////////////////////////////////////////////////////////
void Code::code1(uint32_t mode, LPSYMBOL s1)
{
	switch (mode) {
	case AM_IMPLIED:
		implied(s1->instr);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Code::code2(uint32_t mode, LPSYMBOL s1, LPSYMBOL s2)
{
	switch (mode) {
	case AM_R8:
		r8(s1->instr, s2);
		break;
	case AM_R16:
		r16(s1->instr, s2);
		break;
	case AM_M8:
		m8(s1->instr, s2);
		break;
	case AM_M16:
		m16(s1->instr, s2);
		break;
	case AM_A8:
		a8(s1->instr, s2);
		break;
	case AM_A16:
		a16(s1->instr, s2);
		break;
	case AM_I16:
		i16(s1->instr, s2);
		break;
	case AM_I8:
		i8(s1->instr, s2);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Code::code3(uint32_t mode, LPSYMBOL s1, LPSYMBOL s2, LPSYMBOL s3)
{
	switch (mode) {
	case AM_RR8:
		rr8(s1->instr, s2, s3);
		break;
	case AM_RI8:
		ri8(s1->instr, s2, s3);
		break;
	case AM_RM8:
		rm8(s1->instr, s2, s3);
		break;
	case AM_RA8:
		ra8(s1->instr, s2, s3);
		break;
	case AM_RR16:
		rr16(s1->instr, s2, s3);
		break;
	case AM_RI16:
		ri16(s1->instr, s2, s3);
		break;
	case AM_RM16:
		rm16(s1->instr, s2, s3);
		break;
	case AM_RA16:
		ra16(s1->instr, s2, s3);
		break;
	case AM_MR8:
		mr8(s1->instr, s2, s3);
		break;
	case AM_MR16:
		mr16(s1->instr, s2, s3);
		break;
	case AM_M8I8:
		m8i8(s1->instr, s2, s3);
		break;
	case AM_M16I8:
		m16i8(s1->instr, s2, s3);
		break;
	case AM_MI16:
		mi16(s1->instr, s2, s3);
		break;
	case AM_AR8:
		ar8(s1->instr, s2, s3);
		break;
	case AM_AR16:
		ar16(s1->instr, s2, s3);
		break;
	case AM_A8I8:
		a8i8(s1->instr, s2, s3);
		break;
	case AM_A16I8:
		a16i8(s1->instr, s2, s3);
		break;
	case AM_AI16:
		ai16(s1->instr, s2, s3);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Code::relcode(LPSYMBOL s1, LPSYMBOL s2)
{
	// calculate and encode relative branches

	// check whether target is in range for relative branch
	word diff = abs(s2->val16 - (location() + 2));
	if (diff >= 0x100) {
		yyerror("address out of range");
		return;
	}

	int8_t offset = (s2->val16 - (location() + 2));
	
	putByte(OPCODE(s1->instr, AM_I8));
	putByte(offset);
}

/////////////////////////////////////////////////////////////////////////////
void Code::rr8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_RR8));
	putByte(MAKEREG(s1->val8, s2->val8));
}

/////////////////////////////////////////////////////////////////////////////
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
	putWord(s2->val16);
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
	putWord(s2->val16);
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
	putWord(s2->val16);
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
	putWord(s2->val16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::ar8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_AR8));
	putByte(s2->val8);
	putWord(s1->val16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::ar16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_AR16));
	putByte(s2->val8);
	putWord(s1->val16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::a8i8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_A8I8));
	putByte(s2->val8);
	putWord(s1->val16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::a16i8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_A16I8));
	putByte(s2->val8);
	putWord(s1->val16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::ai16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_AI16));
	putWord(s2->val16);
	putWord(s1->val16);
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
	putWord(s->val16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::a16(const Instr *instr, LPSYMBOL s)
{
	putByte(OPCODE(instr, AM_A16));
	putWord(s->val16);
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
	putWord(s->val16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::i8(const Instr *instr, LPSYMBOL s)
{
	putByte(OPCODE(instr, AM_I8));
	putByte(s->val8);
}

