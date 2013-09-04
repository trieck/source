/////////////////////////////////////////////////////////////////////////////
//
// CODE.CPP : Code generation
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Code.h"
#include "Program.h"
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
	// code0
	m_code0Map[AM_IMPLIED] = &Code::implied;

	// code1
	m_code1Map[AM_R8] = &Code::r8;
	m_code1Map[AM_R16] = &Code::r16;
	m_code1Map[AM_M8] = &Code::m8;
	m_code1Map[AM_M16] = &Code::m16;
	m_code1Map[AM_A8] = &Code::a8;
	m_code1Map[AM_A16] = &Code::a16;
	m_code1Map[AM_I16] = &Code::i16;
	m_code1Map[AM_I8] = &Code::i8;

	// code2
	m_code2Map[AM_RR8] = &Code::rr8;
	m_code2Map[AM_RI8] = &Code::ri8;
	m_code2Map[AM_RM8] = &Code::rm8;
	m_code2Map[AM_RA8] = &Code::ra8;
	m_code2Map[AM_RR16] = &Code::rr16;
	m_code2Map[AM_RI16] = &Code::ri16;
	m_code2Map[AM_RM16] = &Code::rm16;
	m_code2Map[AM_RA16] = &Code::ra16;
	m_code2Map[AM_MR8] = &Code::mr8;
	m_code2Map[AM_MR16] = &Code::mr16;
	m_code2Map[AM_M8I8] = &Code::m8i8;
	m_code2Map[AM_M16I8] = &Code::m16i8;
	m_code2Map[AM_MI16] = &Code::mi16;
	m_code2Map[AM_AR8] = &Code::ar8;
	m_code2Map[AM_AR16] = &Code::ar16;
	m_code2Map[AM_A8I8] = &Code::a8i8;
	m_code2Map[AM_A16I8] = &Code::a16i8;
	m_code2Map[AM_AI16] = &Code::ai16;
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
void Code::putList(LPSYMBOL s, uint32_t ctxt)
{
	SymbolVec::const_iterator it = s->vsyms.begin();

	for ( ; it != s->vsyms.end(); it++) {
		putSym(*it, ctxt);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Code::putSym(LPSYMBOL s, uint32_t ctxt)
{
	switch (s->type) {
	case ST_OP:		// operator
		putOp(s, ctxt);
		break;
	case ST_LIST:	// list
		putList(s, ctxt);
		break;
	case ST_UNDEF:	// forward reference
		putFixup(s, ctxt);
		break;
	case ST_ID:
	case ST_CONST:
		if (ctxt == IM8) {
			putByte(s->val8);
		} else {
			putWord(s->val16);
		}
		break;
	default:
		throw Exception("unexpected symbol type.");
	}
}

/////////////////////////////////////////////////////////////////////////////
void Code::putOp(LPSYMBOL s, uint32_t ctxt)
{
	// push program location, context
	// and memory store instruction
	program.push(&Machine::memstore);
	program.push(ctxt);
	program.push(location());

	// push symbol
	pushsym(s);

	if (ctxt == IM8) {
		putByte(0);
	} else {
		putWord(0);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Code::putFixup(LPSYMBOL s, uint32_t ctxt)
{
	// push args and fixup instruction
	program.push(&Machine::fixup);
	program.push(ctxt);
	program.push(location());

	// push symbol
	pushsym(s);

	if (ctxt == IM8) {
		putByte(0);
	} else {
		putWord(0);
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
void Code::putWordAt(word location, word w)
{
	putByteAt(location, HIBYTE(w));
	putByteAt(location+1, LOBYTE(w));
}

/////////////////////////////////////////////////////////////////////////////
void Code::putByteAt(word location, byte b)
{
	word offset = location - m_origin;

	ASSERT(m_memory[offset] == 0);

	m_memory[offset] = b;
}

/////////////////////////////////////////////////////////////////////////////
void Code::code0(uint32_t mode, LPSYMBOL s1)
{
	Code0FncMap::const_iterator it = m_code0Map.find(mode);
	if (it == m_code0Map.end()) {
		throw Exception("unexpected addressing mode %d.", mode);
	}

	Code0Ptr pfnc = (*it).second;

	(this->*(pfnc))(s1->instr);
}

/////////////////////////////////////////////////////////////////////////////
void Code::code1(uint32_t mode, LPSYMBOL s1, LPSYMBOL s2)
{
	Code1FncMap::const_iterator it = m_code1Map.find(mode);
	if (it == m_code1Map.end()) {
		throw Exception("unexpected addressing mode %d.", mode);
	}

	Code1Ptr pfnc = (*it).second;

	(this->*(pfnc))(s1->instr, s2);
}

/////////////////////////////////////////////////////////////////////////////
void Code::code2(uint32_t mode, LPSYMBOL s1, LPSYMBOL s2, LPSYMBOL s3)
{
	Code2FncMap::const_iterator it = m_code2Map.find(mode);
	if (it == m_code2Map.end()) {
		throw Exception("unexpected addressing mode %d.", mode);
	}

	Code2Ptr pfnc = (*it).second;

	(this->*(pfnc))(s1->instr, s2, s3);
}

/////////////////////////////////////////////////////////////////////////////
void Code::relcode(LPSYMBOL s1, LPSYMBOL s2)
{
	// relative branching
	putByte(OPCODE(s1->instr, AM_I8));
	putFixup(s2, IM8);
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
	putSym(s2, IM8);
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
	putSym(s2, IM16);
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
	putSym(s2, IM16);
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
	putSym(s2, IM16);
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
	putSym(s2, IM8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::m16i8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_M16I8));
	putByte(s1->val8);
	putSym(s2, IM8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::mi16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_MI16));
	putByte(s1->val8);
	putSym(s2, IM16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::ar8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_AR8));
	putByte(s2->val8);
	putSym(s1, IM16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::ar16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_AR16));
	putByte(s2->val8);
	putSym(s1, IM16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::a8i8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_A8I8));
	putSym(s2, IM8);
	putSym(s1, IM16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::a16i8(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_A16I8));
	putSym(s2, IM8);
	putSym(s1, IM16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::ai16(const Instr *instr, LPSYMBOL s1, LPSYMBOL s2)
{
	putByte(OPCODE(instr, AM_AI16));
	putSym(s2, IM16);
	putSym(s1, IM16);
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
	putSym(s, IM16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::a16(const Instr *instr, LPSYMBOL s)
{
	putByte(OPCODE(instr, AM_A16));
	putSym(s, IM16);
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
	putSym(s, IM16);
}

/////////////////////////////////////////////////////////////////////////////
void Code::i8(const Instr *instr, LPSYMBOL s)
{
	putByte(OPCODE(instr, AM_I8));
	putSym(s, IM8);
}

/////////////////////////////////////////////////////////////////////////////
void Code::pass2()
{
	// execute machine program
	Machine *machine = Machine::getInstance();
	machine->exec(program);
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

/////////////////////////////////////////////////////////////////////////////
void Code::pushsym(LPSYMBOL s)
{
	SymbolVec::const_iterator it;

	switch (s->type) {
	case ST_LIST: 	// list of arguments
		for (it = s->vsyms.begin(); it != s->vsyms.end(); it++) {
			pushsym(*it);
		}
		break;
	case ST_OP:	// operator
		program.pushop(s->opcode);
		pushsym(s->args);
		break;
	default:
		program.push(s);	// single argument
	};
}
