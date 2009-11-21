/////////////////////////////////////////////////////////////////////////////
//
//	6502.CPP : 6502 CPU Emulation
//
//	Copyright(c) 2003, Thomas A. Rieck
//

#include "stdafx.h"
#include "6502.h"
#include "memory.h"

CPU::CPUPtr CPU::This;

#define FETCH_BYTE(addr) \
	(Memory::instance()->Get(addr))
#define	PUT_BYTE(addr, byte) \
	(Memory::instance()->Set(addr, byte))

#define FETCH_WORD(addr) \
	((FETCH_BYTE(addr+1) << 8) | FETCH_BYTE(addr))
#define FETCH()	(FETCH_BYTE(pc))

#define INITIAL_P_STATE 0x20
#define PAGE_ONE 0x100
#define STACK_BEGIN 0xff
#define RESET_VECTOR 0xfffc
#define IRQ_VECTOR 0xfffe

#define PUSH(val) PUT_BYTE(PAGE_ONE + s--, val)
#define PULL() FETCH_BYTE(PAGE_ONE + ++s)

#define FETCH_IND_X(addr)					\
	(FETCH_WORD(FETCH_BYTE(addr) + x))

#define FETCH_IND_Y(addr)					\
	(FETCH_WORD(FETCH_BYTE(addr)) + y)

#define FETCH_ZERO(addr)					\
	(FETCH_BYTE(addr))

#define FETCH_ZERO_X(addr)					\
	((FETCH_BYTE(addr)+x)&0xff)

#define FETCH_ZERO_Y(addr)					\
	((FETCH_BYTE(addr)+y)&0xff)

#define FETCH_ABS(addr)						\
	(FETCH_WORD(addr))

#define FETCH_ABS_X(addr)					\
	(FETCH_WORD((addr) + x))

#define FETCH_ABS_Y(addr)					\
	(FETCH_WORD((addr) + y))

#define SET_NEG(val)						\
	do {									\
		if (val) SetNeg();					\
		else ClearNeg();					\
	} while (0)

#define SET_V(val)							\
	do {									\
		if (val) SetOverflow();				\
		else ClearOverflow();				\
	} while (0)

#define SET_ZERO(val)						\
	do {									\
		if (val) SetZero();					\
		else ClearZero();					\
	} while (0)

#define SET_CARRY(val)						\
	do {									\
		if (val) SetCarry();				\
		else ClearCarry();					\
	} while (0)

#define SET_NZ(val)							\
	do {									\
		SET_NEG(val & NFLAG);				\
		SET_ZERO(!(val & 0xFF));			\
	} while (0)

#define GET_CARRY() (GetCarry() ? 1 : 0)

#define ORA(val, clk_inc, pc_inc)			\
  do {                                      \
      clock += (clk_inc);					\
      a |= val;								\
      SET_NZ(a);							\
      pc += (pc_inc);						\
  } while (0)

#define PHP()								\
	do {									\
		clock += 3;							\
		PUSH(p);							\
		pc++;								\
	} while (0)

#define BRK()								\
	do {									\
		clock += 7;							\
		if (!GetInterrupt()) {				\
			USHORT retaddr = pc + 1;		\
			PUSH(HIBYTE(retaddr));			\
			PUSH(LOBYTE(retaddr));			\
			SetBreak();						\
			PHP();							\
			SetInterrupt();					\
			pc = FETCH_WORD(IRQ_VECTOR);	\
		}									\
	} while (0)

#define ASL(addr, clk_inc, pc_inc)			\
	do {									\
		clock += clk_inc;					\
		BYTE val = FETCH_BYTE((addr));		\
		SET_CARRY(val & 0x80);				\
		val <<= 1;							\
		SET_NZ(val);						\
		PUT_BYTE((addr), val);				\
		pc += (pc_inc);						\
	} while (0)

#define ASL_A()								\
	do {									\
		clock += 2;							\
		SET_CARRY(a & 0x80);				\
		a <<= 1;							\
		SET_NZ(a);							\
		pc++;								\
	} while (0)

#define BPL()								\
	do {									\
		clock += 2;							\
		BYTE val = FETCH_BYTE(pc+1);		\
		pc += 2;							\
		if (!GetNeg())						\
			pc += (signed char)val;			\
	} while (0)

#define CLC()								\
	do {									\
		clock += 2;							\
		ClearCarry();						\
		pc++;								\
	} while (0)

#define JSR(addr, clk_inc, pc_inc)			\
	do {									\
		clock += clk_inc;					\
		PUSH(HIBYTE(pc + (clk_inc) - 1));	\
		PUSH(LOBYTE(pc + (clk_inc) - 1));	\
		pc = addr;							\
	} while (0)

#define AND(val, clk_inc, pc_inc)			\
	do {									\
		clock += clk_inc;					\
		SET_NZ(a &= val);					\
		pc += (pc_inc);						\
	} while (0)

#define BIT(addr, clk_inc, pc_inc)			\
	do {									\
		clock += clk_inc;					\
		BYTE val = FETCH_BYTE((addr));		\
		SET_ZERO(!(a & val));				\
		SET_NEG(val & 0x80);				\
		SET_V(val & 0x40);					\
		pc += (pc_inc);						\
	} while (0)

#define ROL(addr, clk_inc, pc_inc)			\
	do {									\
		clock += clk_inc;					\
		BYTE val = FETCH_BYTE((addr));		\
		SET_CARRY(val & 0x80);				\
		val = (val << 1) + GET_CARRY();		\
		SET_NZ(val);						\
		PUT_BYTE(addr, val);				\
		pc += (pc_inc);						\
	} while (0)

#define PLP()								\
	do {									\
		clock += 4;							\
		p = PULL();							\
		pc++;								\
	} while (0)

/////////////////////////////////////////////////////////////////////////////
CPU::CPU()
{
	Reset();
}

/////////////////////////////////////////////////////////////////////////////
CPU::~CPU()
{
}

/////////////////////////////////////////////////////////////////////////////
CPU* CPU::instance()
{
	if (This.get() == NULL) {
		This = CPUPtr(new CPU());
	}
	return This.get();
}

/////////////////////////////////////////////////////////////////////////////
void CPU::Reset()
{
	a = x = y = 0;
	clock = 0UL;
	p = INITIAL_P_STATE;
	s = STACK_BEGIN;
	pc = FETCH_WORD(RESET_VECTOR);
}

/////////////////////////////////////////////////////////////////////////////
void CPU::Run()
{
	BYTE opcode;

	for (;;) {
		opcode = FETCH();
		switch (opcode) {
		case 0x00:				// BRK
			BRK();
			break;
		case 0x01:				// ORA ($nn, X)
			ORA(FETCH_BYTE(FETCH_IND_X(pc+1)), 4, 2);
			break;
		case 0x05:				// ORA $nn
			ORA(FETCH_BYTE(FETCH_ZERO(pc+1)), 3, 2);
		case 0x06:				// ASL $nn
			ASL(FETCH_BYTE(pc+1), 5, 2);
			break;
		case 0x08:				// PHP
			PHP();
			break;
		case 0x09:				// ORA #$nn
			ORA(FETCH_BYTE(pc+1), 2, 2);
			break;
		case 0x0a:				// ASL A
			ASL_A();
			break;
		case 0x0d:				// ORA $nnnn
			ORA(FETCH_BYTE(FETCH_ABS(pc+1)), 4, 3);
			break;
		case 0x0e:				// ASL $nnnn
			ASL(FETCH_ABS(pc+1), 6, 3);
			break;
		case 0x10:
			BPL();				// BPL $nn
			break;
		case 0x11:				// ORA ($nn), Y
			ORA(FETCH_BYTE(FETCH_IND_Y(pc+1)), 5, 2);
			break;
		case 0x15:				// ORA $nn, X
			ORA(FETCH_BYTE(FETCH_ZERO_X(pc+1)), 4, 2);
			break;
		case 0x16:				// ASL $nn, X
			ASL(FETCH_ZERO_X(pc+1), 6, 2);
			break;
		case 0x18:				// CLC
			CLC();
			break;
		case 0x19:				// ORA $nnnn, Y
			ORA(FETCH_BYTE(FETCH_ABS_Y(pc+1)), 4, 3);
		case 0x20:				// JSR $nnnn
			JSR(FETCH_ABS(pc+1), 6, 3);
		case 0x21:				// AND ($nn, X)
			AND(FETCH_BYTE(FETCH_IND_X(pc+1)), 6, 2);
			break;
		case 0x24:				// BIT $nn
			BIT(FETCH_ZERO(pc+1), 3, 2);
			break;
		case 0x25:				// AND $nn
			AND(FETCH_BYTE(FETCH_ZERO(pc+1)), 3, 2);
			break;
		case 0x26:				// ROL $nn
			ROL(FETCH_ZERO(pc+1), 5, 2);
			break;
		case 0x28:				// PLP
			PLP();
			break;
		case 0x29:				// AND #$nn
			AND(FETCH_BYTE(pc+1), 2, 2);
		default:
			break;
		}
	}
}