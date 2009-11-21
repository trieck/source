/////////////////////////////////////////////////////////////////////////////
//
// CODE.CPP : Code generation
//
// Copyright (c) 2006, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Modes.h"
#include "Instructions.h"
#include "SymbolTable.h"
#include "Code.h"
#include "Memory.h"

#define MAKEREG(hi, lo)	((hi << 4) | lo)
#define OPCODE(i, m)	(*(*i)[m])
#define HIBYTE(w)		((w & 0xFF00) >> 8)
#define LOBYTE(w)		(w & 0xFF)

extern word address;
namespace {
void RR8(const Instr *instr, byte dest, byte src);
}
namespace {
void RI8(const Instr *instr, byte r8, byte i8);
}
namespace {
void RM8(const Instr *instr, byte r8, byte m16);
}
namespace {
void RA8(const Instr *instr, byte r8, word a16);
}
namespace {
void RR16(const Instr *instr, byte dest, byte src);
}
namespace {
void RI16(const Instr *instr, byte r16, word i16);
}
namespace {
void RM16(const Instr *instr, byte r16, byte m16);
}
namespace {
void RA16(const Instr *instr, byte r16, word a16);
}
namespace {
void MR8(const Instr *instr, byte m16, byte r8);
}
namespace {
void MR16(const Instr *instr, byte m16, byte r16);
}
namespace {
void M8I8(const Instr *instr, byte m16, byte i8);
}
namespace {
void M16I8(const Instr *instr, byte m16, byte i8);
}
namespace {
void MI16(const Instr *instr, byte m16, word i16);
}
namespace {
void AR8(const Instr *instr, word a16, byte r8);
}
namespace {
void AR16(const Instr *instr, word a16, byte r16);
}
namespace {
void A8I8(const Instr *instr, word a16, byte i8);
}
namespace {
void A16I8(const Instr *instr, word a16, byte i8);
}
namespace {
void AI16(const Instr *instr, word a16, word i16);
}
namespace {
void R8(const Instr *instr, byte r8);
}
namespace {
void R16(const Instr *instr, byte r16);
}
namespace {
void M8(const Instr *instr, byte m16);
}
namespace {
void M16(const Instr *instr, byte m16);
}
namespace {
void A8(const Instr *instr, word a16);
}
namespace {
void A16(const Instr *instr, word a16);
}
namespace {
void IMPLIED(const Instr *instr);
}
namespace {
void I16(const Instr *instr, word i16);
}
namespace {
void I8(const Instr *instr, byte i8);
}

namespace {
Memory *memory = Memory::getInstance();
}

/////////////////////////////////////////////////////////////////////////////
void code1(int mode, LPSYMBOL s1)
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
void code2(int mode, LPSYMBOL s1, LPSYMBOL s2)
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
void code3(int mode, LPSYMBOL s1, LPSYMBOL s2, LPSYMBOL s3)
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
namespace {	// anonymous

/////////////////////////////////////////////////////////////////////////////
void RR8(const Instr *instr, byte dest, byte src)
{
	memory->store(address++, OPCODE(instr, AM_RR8));
	memory->store(address++, MAKEREG(dest, src));
}

/////////////////////////////////////////////////////////////////////////////
void RI8(const Instr *instr, byte r8, byte i8)
{
	memory->store(address++, OPCODE(instr, AM_RI8));
	memory->store(address++, r8);
	memory->store(address++, i8);
}

/////////////////////////////////////////////////////////////////////////////
void RM8(const Instr *instr, byte r8, byte m16)
{
	memory->store(address++, OPCODE(instr, AM_RM8));
	memory->store(address++, MAKEREG(r8, m16));
}

/////////////////////////////////////////////////////////////////////////////
void RA8(const Instr *instr, byte r8, word a16)
{
	memory->store(address++, OPCODE(instr, AM_RA8));
	memory->store(address++, r8);
	memory->store(address++, HIBYTE(a16));
	memory->store(address++, LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void RR16(const Instr *instr, byte dest, byte src)
{
	memory->store(address++, OPCODE(instr, AM_RR16));
	memory->store(address++, MAKEREG(dest, src));
}

/////////////////////////////////////////////////////////////////////////////
void RI16(const Instr *instr, byte r16, word i16)
{
	memory->store(address++, OPCODE(instr, AM_RI16));
	memory->store(address++, r16);
	memory->store(address++, HIBYTE(i16));
	memory->store(address++, LOBYTE(i16));
}

/////////////////////////////////////////////////////////////////////////////
void RM16(const Instr *instr, byte r16, byte m16)
{
	memory->store(address++, OPCODE(instr, AM_RM16));
	memory->store(address++, MAKEREG(r16, m16));
}

/////////////////////////////////////////////////////////////////////////////
void RA16(const Instr *instr, byte r16, word a16)
{
	memory->store(address++, OPCODE(instr, AM_RA16));
	memory->store(address++, r16);
	memory->store(address++, HIBYTE(a16));
	memory->store(address++, LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void MR8(const Instr *instr, byte m16, byte r8)
{
	memory->store(address++, OPCODE(instr, AM_MR8));
	memory->store(address++, MAKEREG(m16, r8));
}

/////////////////////////////////////////////////////////////////////////////
void MR16(const Instr *instr, byte m16, byte r16)
{
	memory->store(address++, OPCODE(instr, AM_MR16));
	memory->store(address++, MAKEREG(m16, r16));
}

/////////////////////////////////////////////////////////////////////////////
void M8I8(const Instr *instr, byte m16, byte i8)
{
	memory->store(address++, OPCODE(instr, AM_M8I8));
	memory->store(address++, m16);
	memory->store(address++, i8);
}

/////////////////////////////////////////////////////////////////////////////
void M16I8(const Instr *instr, byte m16, byte i8)
{
	memory->store(address++, OPCODE(instr, AM_M16I8));
	memory->store(address++, m16);
	memory->store(address++, i8);
}

/////////////////////////////////////////////////////////////////////////////
void MI16(const Instr *instr, byte m16, word i16)
{
	memory->store(address++, OPCODE(instr, AM_MI16));
	memory->store(address++, m16);
	memory->store(address++, HIBYTE(i16));
	memory->store(address++, LOBYTE(i16));
}

/////////////////////////////////////////////////////////////////////////////
void AR8(const Instr *instr, word a16, byte r8)
{
	memory->store(address++, OPCODE(instr, AM_AR8));
	memory->store(address++, r8);
	memory->store(address++, HIBYTE(a16));
	memory->store(address++, LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void AR16(const Instr *instr, word a16, byte r16)
{
	memory->store(address++, OPCODE(instr, AM_AR16));
	memory->store(address++, r16);
	memory->store(address++, HIBYTE(a16));
	memory->store(address++, LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void A8I8(const Instr *instr, word a16, byte i8)
{
	memory->store(address++, OPCODE(instr, AM_A8I8));
	memory->store(address++, i8);
	memory->store(address++, HIBYTE(a16));
	memory->store(address++, LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void A16I8(const Instr *instr, word a16, byte i8)
{
	memory->store(address++, OPCODE(instr, AM_A16I8));
	memory->store(address++, i8);
	memory->store(address++, HIBYTE(a16));
	memory->store(address++, LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void AI16(const Instr *instr, word a16, word i16)
{
	memory->store(address++, OPCODE(instr, AM_AI16));
	memory->store(address++, HIBYTE(i16));
	memory->store(address++, LOBYTE(i16));
	memory->store(address++, HIBYTE(a16));
	memory->store(address++, LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void R8(const Instr *instr, byte r8)
{
	memory->store(address++, OPCODE(instr, AM_R8));
	memory->store(address++, r8);
}

/////////////////////////////////////////////////////////////////////////////
void R16(const Instr *instr, byte r16)
{
	memory->store(address++, OPCODE(instr, AM_R16));
	memory->store(address++, r16);
}

/////////////////////////////////////////////////////////////////////////////
void M8(const Instr *instr, byte m16)
{
	memory->store(address++, OPCODE(instr, AM_M8));
	memory->store(address++, m16);
}

/////////////////////////////////////////////////////////////////////////////
void M16(const Instr *instr, byte m16)
{
	memory->store(address++, OPCODE(instr, AM_M16));
	memory->store(address++, m16);
}

/////////////////////////////////////////////////////////////////////////////
void A8(const Instr *instr, word a16)
{
	memory->store(address++, OPCODE(instr, AM_A8));
	memory->store(address++, HIBYTE(a16));
	memory->store(address++, LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void A16(const Instr *instr, word a16)
{
	memory->store(address++, OPCODE(instr, AM_A16));
	memory->store(address++, HIBYTE(a16));
	memory->store(address++, LOBYTE(a16));
}

/////////////////////////////////////////////////////////////////////////////
void IMPLIED(const Instr *instr)
{
	memory->store(address++, OPCODE(instr, AM_IMPLIED));
}

/////////////////////////////////////////////////////////////////////////////
void I16(const Instr *instr, word i16)
{
	memory->store(address++, OPCODE(instr, AM_I16));
	memory->store(address++, HIBYTE(i16));
	memory->store(address++, LOBYTE(i16));
}

/////////////////////////////////////////////////////////////////////////////
void I8(const Instr *instr, byte i8)
{
	memory->store(address++, OPCODE(instr, AM_I8));
	memory->store(address++, i8);
}

/////////////////////////////////////////////////////////////////////////////
}	// anonymous
