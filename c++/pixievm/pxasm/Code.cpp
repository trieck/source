/////////////////////////////////////////////////////////////////////////////
//
// CODE.CPP : Code generation
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Code.h"
#include "Exception.h"

#define MAKEREG(hi, lo)	((hi << 4) | lo)
#define OPCODE(i, m)	(*(*i)[m])

CodePtr Code::instance(Code::getInstance());

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
		IMPLIED(s1->instr);
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
		R8(s1->instr, s2->val8);
		break;
	case AM_R16:
		R16(s1->instr, s2->val8);
		break;
	case AM_M8:
		M8(s1->instr, s2->val8);
		break;
	case AM_M16:
		M16(s1->instr, s2->val8);
		break;
	case AM_A8:
		A8(s1->instr, s2->val16);
		break;
	case AM_A16:
		A16(s1->instr, s2->val16);
		break;
	case AM_I16:
		I16(s1->instr, s2->val16);
		break;
	case AM_I8:
		I8(s1->instr, s2->val8);
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
		RR8(s1->instr, s2->val8, s3->val8);
		break;
	case AM_RI8:
		RI8(s1->instr, s2->val8, s3->val8);
		break;
	case AM_RM8:
		RM8(s1->instr, s2->val8, s3->val8);
		break;
	case AM_RA8:
		RA8(s1->instr, s2->val8, s3->val16);
		break;
	case AM_RR16:
		RR16(s1->instr, s2->val8, s3->val8);
		break;
	case AM_RI16:
		RI16(s1->instr, s2->val8, s3->val16);
		break;
	case AM_RM16:
		RM16(s1->instr, s2->val8, s3->val8);
		break;
	case AM_RA16:
		RA16(s1->instr, s2->val8, s3->val16);
		break;
	case AM_MR8:
		MR8(s1->instr, s2->val8, s3->val8);
		break;
	case AM_MR16:
		MR16(s1->instr, s2->val8, s3->val8);
		break;
	case AM_M8I8:
		M8I8(s1->instr, s2->val8, s3->val8);
		break;
	case AM_M16I8:
		M16I8(s1->instr, s2->val8, s3->val8);
		break;
	case AM_MI16:
		MI16(s1->instr, s2->val8, s3->val16);
		break;
	case AM_AR8:
		AR8(s1->instr, s2->val16, s3->val8);
		break;
	case AM_AR16:
		AR16(s1->instr, s2->val16, s3->val8);
		break;
	case AM_A8I8:
		A8I8(s1->instr, s2->val16, s3->val8);
		break;
	case AM_A16I8:
		A16I8(s1->instr, s2->val16, s3->val8);
		break;
	case AM_AI16:
		AI16(s1->instr, s2->val16, s3->val16);
		break;
	default:
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
void Code::RR8(const Instr *instr, byte dest, byte src)
{
	putByte(OPCODE(instr, AM_RR8));
	putByte(MAKEREG(dest, src));
}

/////////////////////////////////////////////////////////////////////////////
void Code::RI8(const Instr *instr, byte r8, byte i8)
{
	putByte(OPCODE(instr, AM_RI8));
	putByte(r8);
	putByte(i8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::RM8(const Instr *instr, byte r8, byte m16)
{
	putByte(OPCODE(instr, AM_RM8));
	putByte(MAKEREG(r8, m16));
}

/////////////////////////////////////////////////////////////////////////////
void Code::RA8(const Instr *instr, byte r8, word a16)
{
	putByte(OPCODE(instr, AM_RA8));
	putByte(r8);
	putByte(HIBYTE(a16));
	putByte(LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void Code::RR16(const Instr *instr, byte dest, byte src)
{
	putByte(OPCODE(instr, AM_RR16));
	putByte(MAKEREG(dest, src));
}

/////////////////////////////////////////////////////////////////////////////
void Code::RI16(const Instr *instr, byte r16, word i16)
{
	putByte(OPCODE(instr, AM_RI16));
	putByte(r16);
	putByte(HIBYTE(i16));
	putByte(LOBYTE(i16));
}

/////////////////////////////////////////////////////////////////////////////
void Code::RM16(const Instr *instr, byte r16, byte m16)
{
	putByte(OPCODE(instr, AM_RM16));
	putByte(MAKEREG(r16, m16));
}

/////////////////////////////////////////////////////////////////////////////
void Code::RA16(const Instr *instr, byte r16, word a16)
{
	putByte(OPCODE(instr, AM_RA16));
	putByte(r16);
	putByte(HIBYTE(a16));
	putByte(LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void Code::MR8(const Instr *instr, byte m16, byte r8)
{
	putByte(OPCODE(instr, AM_MR8));
	putByte(MAKEREG(m16, r8));
}

/////////////////////////////////////////////////////////////////////////////
void Code::MR16(const Instr *instr, byte m16, byte r16)
{
	putByte(OPCODE(instr, AM_MR16));
	putByte(MAKEREG(m16, r16));
}

/////////////////////////////////////////////////////////////////////////////
void Code::M8I8(const Instr *instr, byte m16, byte i8)
{
	putByte(OPCODE(instr, AM_M8I8));
	putByte(m16);
	putByte(i8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::M16I8(const Instr *instr, byte m16, byte i8)
{
	putByte(OPCODE(instr, AM_M16I8));
	putByte(m16);
	putByte(i8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::MI16(const Instr *instr, byte m16, word i16)
{
	putByte(OPCODE(instr, AM_MI16));
	putByte(m16);
	putByte(HIBYTE(i16));
	putByte(LOBYTE(i16));
}

/////////////////////////////////////////////////////////////////////////////
void Code::AR8(const Instr *instr, word a16, byte r8)
{
	putByte(OPCODE(instr, AM_AR8));
	putByte(r8);
	putByte(HIBYTE(a16));
	putByte(LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void Code::AR16(const Instr *instr, word a16, byte r16)
{
	putByte(OPCODE(instr, AM_AR16));
	putByte(r16);
	putByte(HIBYTE(a16));
	putByte(LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void Code::A8I8(const Instr *instr, word a16, byte i8)
{
	putByte(OPCODE(instr, AM_A8I8));
	putByte(i8);
	putByte(HIBYTE(a16));
	putByte(LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void Code::A16I8(const Instr *instr, word a16, byte i8)
{
	putByte(OPCODE(instr, AM_A16I8));
	putByte(i8);
	putByte(HIBYTE(a16));
	putByte(LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void Code::AI16(const Instr *instr, word a16, word i16)
{
	putByte(OPCODE(instr, AM_AI16));
	putByte(HIBYTE(i16));
	putByte(LOBYTE(i16));
	putByte(HIBYTE(a16));
	putByte(LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void Code::R8(const Instr *instr, byte r8)
{
	putByte(OPCODE(instr, AM_R8));
	putByte(r8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::R16(const Instr *instr, byte r16)
{
	putByte(OPCODE(instr, AM_R16));
	putByte(r16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::M8(const Instr *instr, byte m16)
{
	putByte(OPCODE(instr, AM_M8));
	putByte(m16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::M16(const Instr *instr, byte m16)
{
	putByte(OPCODE(instr, AM_M16));
	putByte(m16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::A8(const Instr *instr, word a16)
{
	putByte(OPCODE(instr, AM_A8));
	putByte(HIBYTE(a16));
	putByte(LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void Code::A16(const Instr *instr, word a16)
{
	putByte(OPCODE(instr, AM_A16));
	putByte(HIBYTE(a16));
	putByte(LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void Code::IMPLIED(const Instr *instr)
{
	putByte(OPCODE(instr, AM_IMPLIED));
}

/////////////////////////////////////////////////////////////////////////////
void Code::I16(const Instr *instr, word i16)
{
}

/////////////////////////////////////////////////////////////////////////////
void Code::I8(const Instr *instr, byte i8)
{
}

