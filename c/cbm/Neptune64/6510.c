/*
 *	6510.C
 *
 *	6510 emulation
 *
 *	Neptune64 Commodore 64 Emulator
 * 	Copyright (C) 2001 Thomas A. Rieck <trieck@bellsouth.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */
#include "common.h"
#include "6510.h"
#include "mem.h"
#include "opcodes.h"
#include "interrupt.h"

#define PAGEONE				0x100
#define STACKBEGIN			0xFF
#define STACKEND			0x00
#define NMI_VECTOR			0xFFFA
#define IRQ_VECTOR			0xFFFE

#define set_neg_flag()				\
	(cpu.sr |= NEG_FLAG)

#define clear_neg_flag()			\
	(cpu.sr &= ~NEG_FLAG)

#define set_overflow_flag()			\
	(cpu.sr |= OVERFLOW_FLAG)

#define clear_overflow_flag()		\
	(cpu.sr &= ~OVERFLOW_FLAG)

#define set_brk_flag()				\
	(cpu.sr |= BRK_FLAG)

#define clear_brk_flag()			\
	(cpu.sr &= ~BRK_FLAG)

#define set_dec_flag()				\
	(cpu.sr |= DECIMAL_FLAG)

#define clear_dec_flag()			\
	(cpu.sr &= ~DECIMAL_FLAG)

#define set_int_disable_flag()		\
	(cpu.sr |= INT_DISABLE_FLAG)

#define clear_int_disable_flag()	\
	(cpu.sr &= ~INT_DISABLE_FLAG)

#define set_zero_flag()				\
	(cpu.sr |= ZERO_FLAG)

#define clear_zero_flag()			\
	(cpu.sr &= ~ZERO_FLAG)

#define set_carry_flag()			\
	(cpu.sr |= CARRY_FLAG)

#define clear_carry_flag()			\
	(cpu.sr &= ~CARRY_FLAG)

/* set carry flag based on condition */
#define set_carry(flag)				\
	do {							\
		if (flag) set_carry_flag();	\
		else clear_carry_flag();	\
	} while(0)

/* set neg flag based on condition */
#define set_neg(flag)				\
	do {							\
		if (flag) set_neg_flag();	\
		else clear_neg_flag();		\
	} while (0)

/* set zero flag based on condition */
#define set_zero(flag)				\
	do {							\
		if (flag) set_zero_flag();	\
		else clear_zero_flag();		\
	} while (0)

/* set negative and zero flag on result */
#define set_nz(res)					\
	do {							\
		set_neg((res) & NEG_FLAG);	\
		set_zero(!((res) & 0xFF));	\
	} while (0)

/* set overflow based on condition */
#define set_overflow(flag)				\
	do {								\
		if (flag) set_overflow_flag();	\
		else clear_overflow_flag();		\
	} while (0)

/* fetch word from memory */
#define fetch_word(a)				\
	(fetch_byte((word)(a)) + fetch_byte((word)((a) + 1)) * 256)

/* perform a branch instruction */
#define branch(b)					\
	do {							\
		if ((b) < 0x80)				\
			cpu.pc += (b);			\
		else cpu.pc -= (0x100 - (b));	\
	} while(0)

#define ADC(value)											\
	do {													\
		word tmp_value;										\
		word tmp;											\
															\
		tmp_value = (value);								\
		if (get_dec_flag()) {								\
			tmp = (cpu.a & 0xF) + (tmp_value & 0xF) 		\
				+ get_carry_flag();							\
			if (tmp > 0x9)									\
				tmp += 0x6;									\
			if (tmp <= 0x0F)								\
				tmp = (tmp & 0xF) + (cpu.a & 0xF0) + 		\
					(tmp_value & 0xF0);						\
			else											\
				tmp = (tmp & 0xF) + (cpu.a & 0xF0) + 		\
					(tmp_value & 0xF0) + 0x10;				\
			set_zero(!((cpu.a + tmp_value + 				\
				get_carry_flag()) & 0xFF));					\
			set_neg(tmp & NEG_FLAG);						\
			set_overflow(!((cpu.a ^ tmp_value) & NEG_FLAG)	\
				&& ((cpu.a ^ tmp) & NEG_FLAG));				\
			if ((tmp & 0x1F0) > 0x90)						\
				tmp += 0x60;								\
			set_carry((tmp & 0xFF0) > 0xF0);				\
		} else {											\
			tmp = tmp_value + cpu.a + get_carry_flag();		\
															\
			set_nz(tmp);									\
			set_overflow(!((cpu.a ^ tmp_value) & NEG_FLAG)	\
				&& ((cpu.a ^ tmp) & NEG_FLAG));				\
			set_carry(tmp > 0xFF);							\
		}													\
		cpu.a = (byte)tmp;									\
	} while (0)

#define ASL(addr)											\
	do {													\
		word val;											\
															\
		val = fetch_byte((addr));							\
		set_carry(val & 0x80);								\
															\
		val <<= 1;											\
		set_nz(val);										\
															\
		store_byte((addr), (byte)val);						\
	} while (0)

#define ASL_A()												\
	do {													\
		set_carry(cpu.a & 0x80);							\
		cpu.a <<= 1;										\
		set_nz(cpu.a);										\
	} while (0)

#define BIT(addr)											\
	do {													\
		word val;											\
															\
		val = fetch_byte(addr);								\
															\
		set_zero(!(cpu.a & val));							\
		set_neg(val & NEG_FLAG);							\
		set_overflow(val & OVERFLOW_FLAG);					\
	} while (0)

#define LSR(addr)											\
	do {													\
		word val;											\
															\
		val = fetch_byte(addr);								\
		set_carry(val & 0x01);								\
															\
		val >>= 1;											\
		set_nz(val);										\
															\
		store_byte(addr, (byte)val);						\
	} while (0)

#define LSR_A()												\
	do {													\
		set_carry(cpu.a & 0x01);							\
		cpu.a >>= 1;										\
		set_nz(cpu.a);										\
	} while (0)

#define ROL(addr)											\
	do {													\
		word res;											\
															\
		res = (fetch_byte(addr) << 1) + get_carry_flag();	\
		set_carry(res & 0x100);								\
															\
		store_byte(addr, (byte)res);						\
		set_nz(res);										\
	} while (0)

#define ROL_A()												\
	do {													\
		word res;											\
															\
		res = (cpu.a << 1) + get_carry_flag();				\
		set_carry(res & 0x100);								\
															\
		cpu.a = (byte)res;									\
		set_nz(res);										\
	} while (0)

#define ROR(addr)											\
	do {													\
		word res;											\
															\
		res = fetch_byte(addr);								\
		if (get_carry_flag())								\
			res |= 0x100;									\
		set_carry(res & CARRY_FLAG);						\
		res >>= 1;											\
		store_byte(addr, (byte)res);						\
		set_nz(res);										\
	} while (0)

#define ROR_A()												\
	do {													\
		word res;											\
															\
		res = (cpu.a);										\
		if (get_carry_flag())								\
			res |= 0x100;									\
		set_carry(res & CARRY_FLAG);						\
		res >>= 1;											\
		cpu.a = (byte)res;									\
		set_nz(res);										\
	} while (0)

#define SBC(value)														\
	do {																\
		word src, tmp;													\
																		\
		src = (value);													\
		tmp = cpu.a - src - get_carry_flag();							\
																		\
		if (get_dec_flag()) {											\
			word tmp_a;													\
																		\
			tmp_a = (cpu.a & 0xF) - (src & 0xF) - get_carry_flag();		\
			if (tmp_a & 0x10)											\
				tmp_a = ((tmp_a - 6) & 0xF)								\
					| ((cpu.a & 0xF0) - (src & 0xF0) - 0x10);			\
			else														\
				tmp_a = (tmp_a & 0xF) | ((cpu.a & 0xF0) - (src & 0xF0));\
			if (tmp_a & 0x100)											\
				tmp_a -= 0x60;											\
																		\
			set_carry(tmp < 0x100);										\
			set_nz(tmp & 0xFF);											\
			set_overflow(((cpu.a ^ tmp) & 0x80)							\
				&& ((cpu.a ^ src) & 0x80));								\
			cpu.a = (byte)tmp_a;										\
		}else {															\
			set_nz(tmp & 0xFF);											\
			set_carry(tmp < 0x100);										\
			set_overflow(((cpu.a ^ tmp) & 0x80)							\
				&& ((cpu.a ^ src) & 0x80));								\
			cpu.a = (byte)tmp;											\
		}																\
	} while (0)

#define DO_INTERRUPT()							\
	do {										\
		push(hibyte(cpu.pc + sizeof(word)));	\
		push(lobyte(cpu.pc + sizeof(word)));	\
												\
		push(cpu.sr);							\
												\
		set_int_disable_flag();					\
												\
		cpu.pc = fetch_word(IRQ_VECTOR);		\
	} while (0)

#define DO_NMI()								\
	do {										\
		push(hibyte(cpu.pc + sizeof(word)));	\
		push(lobyte(cpu.pc + sizeof(word)));	\
												\
		push(cpu.sr);							\
												\
		cpu.pc = fetch_word(NMI_VECTOR);		\
	} while (0)

Cpu cpu;

extern int err, pending_interrupt;

/*
 * reset the cpu
 */
void cpu_reset(void)
{
    cpu.pc = fetch_word(0xfffc);
    err = 0;
}

/*
 * run the cpu
 */
void cpu_run(void)
{
    cpu_reset();

    do {
        /* check for pending interrupts */
        if (!get_int_disable_flag() && pending_interrupt & HANDLE_IRQ)
            DO_INTERRUPT();

        if (pending_interrupt & HANDLE_NMI) {
            pending_interrupt &= ~HANDLE_NMI;
            DO_NMI();
        }

        /* fetch the next instruction */
        byte i = fetch_byte(cpu.pc);

        const Instr* pi = instructions[i];
        if (NULL == pi) {
            warning("unrecognized instruction \"$%.2x\" at $%.4hx.\n",
                    i, cpu.pc);
            break;
        }

        /* execute the instruction */
        (*pi->fnc)();
    } while (!err);
}

/*
 * push a value onto the stack
 */
void push(byte c)
{
    if (cpu.sp == STACKEND) {
        warning("stack overflow error.\n");
        err = 1;
        return;
    }
    store_byte((word)(PAGEONE + cpu.sp--), c);
}

/*
 * pop a value from the stack
 */
byte pop(void)
{
    if (cpu.sp == STACKBEGIN) {
        warning("stack underflow error.\n");
        err = 1;
        return 0;
    }
    return fetch_byte((word)(PAGEONE + ++cpu.sp));
}

/*
 * add with carry, absolute mode
 */
void _adcAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    byte value = fetch_byte(addr);

    ADC(value);

    cpu.pc += 3;
}

/*
 * add with carry absolute, x mode
 */
void _adcAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.x;

    byte value = fetch_byte(addr);
    ADC(value);

    cpu.pc += 3;
}

/*
 * add with carry absolute, y mode
 */
void _adcAby(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.y;

    fetch_byte(addr);
    ADC(addr);

    cpu.pc += 3;
}

/*
 * add with carry indirect, x mode
 */
void _adcIdx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;

    word addr = fetch_word(zaddr);
    byte value = fetch_byte(addr);
    ADC(value);

    cpu.pc += 2;
}

/*
 * add with carry indirect, y mode
 */
void _adcIdy(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    word addr = fetch_word(zaddr) + cpu.y;
    byte value = fetch_byte(addr);
    ADC(value);

    cpu.pc += 2;
}

/*
 * add with carry immediate mode
 */
void _adcImm(void)
{
    byte value = fetch_byte((word)(cpu.pc + 1));

    ADC(value);

    cpu.pc += 2;
}

/*
 * add with carry zero page mode
 */
void _adcZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    byte value = fetch_byte(zaddr);
    ADC(value);

    cpu.pc += 2;
}

/*
 * add with carry zero page, x mode
 */
void _adcZpx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;

    byte value = fetch_byte(zaddr);
    ADC(value);

    cpu.pc += 2;
}

void _andAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    word res = cpu.a &= fetch_byte(addr);

    set_nz(res);

    cpu.pc += 3;
}

void _andAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.x;

    word res = cpu.a &= fetch_byte(addr);

    set_nz(res);

    cpu.pc += 3;
}

void _andAby(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.y;

    word res = cpu.a &= fetch_byte(addr);

    set_nz(res);

    cpu.pc += 3;
}

void _andIdx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;

    word addr = fetch_word(zaddr);

    word res = cpu.a &= fetch_byte(addr);

    set_nz(res);

    cpu.pc += 2;
}

void _andIdy(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    word addr = fetch_word(zaddr) + cpu.y;

    word res = cpu.a &= fetch_byte(addr);

    set_nz(res);

    cpu.pc += 2;
}

void _andImm(void)
{
    byte val = fetch_byte((word)(cpu.pc + 1));

    word res = cpu.a &= val;

    set_nz(res);

    cpu.pc += 2;
}

void _andZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    word res = cpu.a &= fetch_byte(zaddr);

    set_nz(res);

    cpu.pc += 2;
}

void _andZpx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;

    word res = cpu.a &= fetch_byte(zaddr);

    set_nz(res);

    cpu.pc += 2;
}

void _aslAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    ASL(addr);

    cpu.pc += 3;
}

void _aslAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    ASL((word)(addr + cpu.x));

    cpu.pc += 3;
}

void _aslAcc(void)
{
    ASL_A();
    cpu.pc++;
}

void _aslZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    ASL(zaddr);

    cpu.pc += 2;
}

void _aslZpx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    ASL((word)(zaddr + cpu.x));

    cpu.pc += 2;
}

void _bcc(void)
{
    byte b = fetch_byte((word)(cpu.pc + 1));

    cpu.pc += 2;
    if (!get_carry_flag())
        branch(b);
}

void _bcs(void)
{
    byte b = fetch_byte((word)(cpu.pc + 1));
    cpu.pc += 2;
    if (get_carry_flag())
        branch(b);
}

void _beq(void)
{
    byte b = fetch_byte((word)(cpu.pc + 1));
    cpu.pc += 2;
    if (get_zero_flag())
        branch(b);
}

void _bitAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    BIT(addr);

    cpu.pc += 3;
}

void _bitZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    BIT(zaddr);

    cpu.pc += 2;
}

void _bmi(void)
{
    byte b = fetch_byte((word)(cpu.pc + 1));
    cpu.pc += 2;
    if (get_neg_flag())
        branch(b);
}

void _bne(void)
{
    byte b = fetch_byte((word)(cpu.pc + 1));
    cpu.pc += 2;
    if (!get_zero_flag())
        branch(b);
}

void _bpl(void)
{
    byte b = fetch_byte((word)(cpu.pc + 1));
    cpu.pc += 2;
    if (!get_neg_flag())
        branch(b);
}

void _brk(void)
{
    push(hibyte(cpu.pc + sizeof(word)));
    push(lobyte(cpu.pc + sizeof(word)));
    push(cpu.sr);
    set_brk_flag();

    set_int_disable_flag();
    cpu.pc = fetch_word(IRQ_VECTOR);
}

void _bvc(void)
{
    byte b = fetch_byte((word)(cpu.pc + 1));
    cpu.pc += 2;
    if (!get_overflow_flag())
        branch(b);
}

void _bvs(void)
{
    byte b = fetch_byte((word)(cpu.pc + 1));
    cpu.pc += 2;
    if (get_overflow_flag())
        branch(b);
}

void _clc(void)
{
    clear_carry_flag();
    cpu.pc++;
}

void _cld(void)
{
    clear_dec_flag();
    cpu.pc++;
}

void _cli(void)
{
    clear_int_disable_flag();
    cpu.pc++;
}

void _clv(void)
{
    clear_overflow_flag();
    cpu.pc++;
}

void _cmpAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    word res = cpu.a - fetch_byte(addr);

    set_carry(res < 0x100);
    set_nz(res);

    cpu.pc += 3;
}

void _cmpAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    addr += cpu.x;

    word res = cpu.a - fetch_byte(addr);

    set_carry(res < 0x100);
    set_nz(res);

    cpu.pc += 3;
}

void _cmpAby(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    addr += cpu.y;

    word res = cpu.a - fetch_byte(addr);

    set_carry(res < 0x100);
    set_nz(res);

    cpu.pc += 3;
}

void _cmpIdx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;

    word addr = fetch_word(zaddr);

    word res = cpu.a - fetch_byte(addr);

    set_carry(res < 0x100);
    set_nz(res);

    cpu.pc += 2;
}

void _cmpIdy(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    word addr = fetch_word(zaddr) + cpu.y;

    word res = cpu.a - fetch_byte(addr);

    set_carry(res < 0x100);
    set_nz(res);

    cpu.pc += 2;
}

void _cmpImm(void)
{
    byte value = fetch_byte((word)(cpu.pc + 1));

    word res = cpu.a - value;

    set_carry(res < 0x100);
    set_nz(res);

    cpu.pc += 2;
}

void _cmpZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    word res = cpu.a - fetch_byte(zaddr);

    set_carry(res < 0x100);
    set_nz(res);

    cpu.pc += 2;
}

void _cmpZpx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;

    word res = cpu.a - fetch_byte(zaddr);

    set_carry(res < 0x100);
    set_nz(res);

    cpu.pc += 2;
}

void _cpxAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    word res = cpu.x - fetch_byte(addr);

    set_carry(res < 0x100);
    set_nz(res);

    cpu.pc += 3;
}

void _cpxImm(void)
{
    byte value = fetch_byte((word)(cpu.pc + 1));

    word res = cpu.x - value;

    set_carry(res < 0x100);
    set_nz(res);

    cpu.pc += 2;
}

void _cpxZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    word res = cpu.x - fetch_byte(zaddr);

    set_carry(res < 0x100);
    set_nz(res);

    cpu.pc += 2;
}

void _cpyAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    word res = cpu.y - fetch_byte(addr);

    set_carry(res < 0x100);
    set_nz(res);

    cpu.pc += 3;
}

void _cpyImm(void)
{
    byte value = fetch_byte((word)(cpu.pc + 1));

    word res = cpu.y - value;

    set_carry(res < 0x100);
    set_nz(res);

    cpu.pc += 2;
}

void _cpyZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    word res = cpu.y - fetch_byte(zaddr);

    set_carry(res < 0x100);
    set_nz(res);

    cpu.pc += 2;
}

void _decAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    word res = fetch_byte(addr);
    res = res - 1 & 0xFF;

    store_byte(addr, (byte)res);

    set_nz(res);

    cpu.pc += 3;
}

void _decAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.x;

    word res = fetch_byte(addr);
    res = res - 1 & 0xFF;

    store_byte(addr, (byte)res);

    set_nz(res);

    cpu.pc += 3;
}

void _decZp(void)
{
    byte addr = fetch_byte((word)(cpu.pc + 1));

    word res = fetch_byte(addr);
    res = res - 1 & 0xFF;

    store_byte(addr, (byte)res);

    set_nz(res);

    cpu.pc += 2;
}

void _decZpx(void)
{
    byte addr = fetch_byte((word)(cpu.pc + 1));
    addr += cpu.x;

    word res = fetch_byte(addr);
    res = res - 1 & 0xFF;

    store_byte(addr, (byte)res);

    set_nz(res);

    cpu.pc += 2;
}

void _dex(void)
{
    word res = cpu.x - 1 & 0xFF;

    cpu.x = (byte)res;

    set_nz(res);

    cpu.pc++;
}

void _dey(void)
{
    word res = cpu.y - 1 & 0xFF;

    cpu.y = (byte)res;

    set_nz(res);

    cpu.pc++;
}

void _eorAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    word res = cpu.a ^= fetch_byte(addr);
    set_nz(res);

    cpu.pc += 3;
}

void _eorAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.x;

    word res = cpu.a ^= fetch_byte(addr);
    set_nz(res);

    cpu.pc += 3;
}

void _eorAby(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.y;

    word res = cpu.a ^= fetch_byte(addr);
    set_nz(res);

    cpu.pc += 3;
}

void _eorIdx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    zaddr += cpu.x;

    word addr = fetch_word(zaddr);

    word res = cpu.a ^= fetch_byte(addr);

    set_nz(res);

    cpu.pc += 2;
}

void _eorIdy(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    word addr = fetch_word(zaddr) + cpu.y;

    word res = cpu.a ^= fetch_byte(addr);

    set_nz(res);

    cpu.pc += 2;
}

void _eorImm(void)
{
    byte val = fetch_byte((word)(cpu.pc + 1));

    word res = cpu.a ^= val;
    set_nz(res);

    cpu.pc += 2;
}

void _eorZp(void)
{
    byte addr = fetch_byte((word)(cpu.pc + 1));

    word res = cpu.a ^= fetch_byte(addr);
    set_nz(res);

    cpu.pc += 2;
}

void _eorZpx(void)
{
    byte addr = fetch_byte((word)(cpu.pc + 1));
    addr += cpu.x;

    word res = cpu.a ^= fetch_byte(addr);
    set_nz(res);

    cpu.pc += 2;
}

void _incAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    word res = fetch_byte(addr);
    res = res + 1 & 0xFF;

    store_byte(addr, (byte)res);

    set_nz(res);

    cpu.pc += 3;
}

void _incAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.x;

    word res = fetch_byte(addr);
    res = res + 1 & 0xFF;

    store_byte(addr, (byte)res);

    set_nz(res);

    cpu.pc += 3;
}

void _incZp(void)
{
    byte addr = fetch_byte((word)(cpu.pc + 1));

    word res = fetch_byte(addr);
    res = res + 1 & 0xFF;

    store_byte(addr, (byte)res);

    set_nz(res);

    cpu.pc += 2;
}

void _incZpx(void)
{
    byte addr = fetch_byte((word)(cpu.pc + 1));
    addr += cpu.x;

    word res = fetch_byte(addr);
    res = res + 1 & 0xFF;

    store_byte(addr, (byte)res);

    set_nz(res);

    cpu.pc += 2;
}

void _inx(void)
{
    word res = cpu.x + 1;
    cpu.x = (byte)res;

    set_nz(res);

    cpu.pc++;
}

void _iny(void)
{
    word res = cpu.y + 1;
    cpu.y = (byte)res;

    set_nz(res);

    cpu.pc++;
}

void _jmpAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    cpu.pc = addr;
}

void _jmpInd(void)
{
    word iaddr = fetch_word((word)(cpu.pc + 1));
    word eaddr = fetch_word(iaddr);
    cpu.pc = eaddr;
}

void _jsr(void)
{
    push(hibyte(cpu.pc + 3));
    push(lobyte(cpu.pc + 3));
    word addr = fetch_word((word)(cpu.pc + 1));
    cpu.pc = addr;
}

void _ldaAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    word res = cpu.a = fetch_byte(addr);
    set_nz(res);

    cpu.pc += 3;
}

void _ldaAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.x;
    word res = cpu.a = fetch_byte(addr);
    set_nz(res);

    cpu.pc += 3;
}

void _ldaAby(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.y;
    word res = cpu.a = fetch_byte(addr);
    set_nz(res);

    cpu.pc += 3;
}

void _ldaIdx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;
    word addr = fetch_word(zaddr);
    word res = cpu.a = fetch_byte(addr);
    set_nz(res);

    cpu.pc += 2;
}

void _ldaIdy(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    word addr = fetch_word(zaddr) + cpu.y;
    word res = cpu.a = fetch_byte(addr);
    set_nz(res);

    cpu.pc += 2;
}

void _ldaImm(void)
{
    byte val = fetch_byte((word)(cpu.pc + 1));
    word res = cpu.a = val;
    set_nz(res);

    cpu.pc += 2;
}

void _ldaZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    word res = cpu.a = fetch_byte(zaddr);
    set_nz(res);

    cpu.pc += 2;
}

void _ldaZpx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;
    word res = cpu.a = fetch_byte(zaddr);
    set_nz(res);

    cpu.pc += 2;
}

void _ldxAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    word res = cpu.x = fetch_byte(addr);
    set_nz(res);

    cpu.pc += 3;
}

void _ldxAby(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.y;
    word res = cpu.x = fetch_byte(addr);
    set_nz(res);

    cpu.pc += 3;
}

void _ldxImm(void)
{
    byte val = fetch_byte((word)(cpu.pc + 1));
    word res = cpu.x = val;
    set_nz(res);

    cpu.pc += 2;
}

void _ldxZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    word res = cpu.x = fetch_byte(zaddr);
    set_nz(res);

    cpu.pc += 2;
}

void _ldxZpy(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.y;
    word res = cpu.x = fetch_byte(zaddr);
    set_nz(res);

    cpu.pc += 2;
}

void _ldyAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    word res = cpu.y = fetch_byte(addr);
    set_nz(res);

    cpu.pc += 3;
}

void _ldyAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.x;
    word res = cpu.y = fetch_byte(addr);
    set_nz(res);

    cpu.pc += 3;
}

void _ldyImm(void)
{
    byte val = fetch_byte((word)(cpu.pc + 1));
    word res = cpu.y = val;
    set_nz(res);

    cpu.pc += 2;
}

void _ldyZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    word res = cpu.y = fetch_byte(zaddr);
    set_nz(res);

    cpu.pc += 2;
}

void _ldyZpx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;
    word res = cpu.y = fetch_byte(zaddr);
    set_nz(res);

    cpu.pc += 2;
}

void _lsrAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    LSR(addr);

    cpu.pc += 3;
}

void _lsrAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    LSR((word)(addr + cpu.x));

    cpu.pc += 3;
}

void _lsrAcc(void)
{
    LSR_A();
    cpu.pc++;
}

void _lsrZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    LSR(zaddr);

    cpu.pc += 2;
}

void _lsrZpx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    LSR((word)(zaddr + cpu.x));

    cpu.pc += 2;
}

void _nop(void)
{
    cpu.pc++;
}

void _oraAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    word res = cpu.a |= fetch_byte(addr);
    set_nz(res);

    cpu.pc += 3;
}

void _oraAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.x;
    word res = cpu.a |= fetch_byte(addr);
    set_nz(res);

    cpu.pc += 3;
}

void _oraAby(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.y;
    word res = cpu.a |= fetch_byte(addr);
    set_nz(res);

    cpu.pc += 3;
}

void _oraIdx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;
    word addr = fetch_word(zaddr);
    word res = cpu.a |= fetch_byte(addr);
    set_nz(res);

    cpu.pc += 2;
}

void _oraIdy(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    word addr = fetch_word(zaddr) + cpu.y;
    word res = cpu.a |= fetch_byte(addr);
    set_nz(res);

    cpu.pc += 2;
}

void _oraImm(void)
{
    byte val = fetch_byte((word)(cpu.pc + 1));
    word res = cpu.a |= val;
    set_nz(res);

    cpu.pc += 2;
}

void _oraZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    word res = cpu.a |= fetch_byte(zaddr);
    set_nz(res);

    cpu.pc += 2;
}

void _oraZpx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;
    word res = cpu.a |= fetch_byte(zaddr);
    set_nz(res);

    cpu.pc += 2;
}

void _pha(void)
{
    push(cpu.a);
    cpu.pc++;
}

void _php(void)
{
    push(cpu.sr);
    cpu.pc++;
}

void _pla(void)
{
    word res = cpu.a = pop();
    set_nz(res);
    cpu.pc++;
}

void _plp(void)
{
    cpu.sr = pop();
    cpu.pc++;
}

void _rolAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    ROL(addr);

    cpu.pc += 3;
}

void _rolAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    ROL((word)(addr + cpu.x));

    cpu.pc += 3;
}

void _rolAcc(void)
{
    ROL_A();
    cpu.pc++;
}

void _rolZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    ROL(zaddr);

    cpu.pc += 2;
}

void _rolZpx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    ROL((word)(zaddr + cpu.x));

    cpu.pc += 2;
}

void _rorAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    ROR(addr);

    cpu.pc += 3;
}

void _rorAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));

    ROR((word)(addr + cpu.x));

    cpu.pc += 3;
}

void _rorAcc(void)
{
    ROR_A();
    cpu.pc++;
}

void _rorZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    ROR(zaddr);

    cpu.pc += 2;
}

void _rorZpx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    ROR((word)(zaddr + cpu.x));

    cpu.pc += 2;
}

void _rti(void)
{
    cpu.sr = pop();
    byte pcl = pop();
    byte pch = pop();
    cpu.pc = pch * 0x100 + pcl;
}

void _rts(void)
{
    byte pcl = pop();
    byte pch = pop();
    cpu.pc = pch * 0x100 + pcl;
}

void _sbcAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    byte value = fetch_byte(addr);

    SBC(value);

    cpu.pc += 3;
}

void _sbcAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    byte value = fetch_byte((word)(addr + cpu.x));

    SBC(value);

    cpu.pc += 3;
}

void _sbcAby(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    byte value = fetch_byte((word)(addr + cpu.y));

    SBC(value);

    cpu.pc += 3;
}

void _sbcIdx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;

    word addr = fetch_word(zaddr);
    byte value = fetch_byte(addr);
    SBC(value);

    cpu.pc += 2;
}

void _sbcIdy(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    word addr = fetch_word(zaddr) + cpu.y;
    byte value = fetch_byte(addr);
    SBC(value);

    cpu.pc += 2;
}

void _sbcImm(void)
{
    byte value = fetch_byte((word)(cpu.pc + 1));

    SBC(value);

    cpu.pc += 2;
}

void _sbcZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    byte value = fetch_byte(zaddr);
    SBC(value);

    cpu.pc += 2;
}

void _sbcZpx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;

    byte value = fetch_byte(zaddr);
    SBC(value);

    cpu.pc += 2;
}

void _sec(void)
{
    set_carry_flag();
    cpu.pc++;
}

void _sed(void)
{
    set_dec_flag();
    cpu.pc++;
}

void _sei(void)
{
    set_int_disable_flag();
    cpu.pc++;
}

void _staAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    store_byte(addr, cpu.a);

    cpu.pc += 3;
}

void _staAbx(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.x;
    store_byte(addr, cpu.a);

    cpu.pc += 3;
}

void _staAby(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    addr += cpu.y;
    store_byte(addr, cpu.a);

    cpu.pc += 3;
}

void _staIdx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;
    word addr = fetch_word(zaddr);
    store_byte(addr, cpu.a);

    cpu.pc += 2;
}

void _staIdy(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    word addr = fetch_word(zaddr) + cpu.y;
    store_byte(addr, cpu.a);

    cpu.pc += 2;
}

void _staZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    store_byte(zaddr, cpu.a);

    cpu.pc += 2;
}

void _staZpx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;
    store_byte(zaddr, cpu.a);

    cpu.pc += 2;
}

void _stxAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    store_byte(addr, cpu.x);

    cpu.pc += 3;
}

void _stxZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    store_byte(zaddr, cpu.x);

    cpu.pc += 2;
}

void _stxZpy(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.y;
    store_byte(zaddr, cpu.x);

    cpu.pc += 2;
}

void _styAbsl(void)
{
    word addr = fetch_word((word)(cpu.pc + 1));
    store_byte(addr, cpu.y);

    cpu.pc += 3;
}

void _styZp(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));

    store_byte(zaddr, cpu.y);

    cpu.pc += 2;
}

void _styZpx(void)
{
    byte zaddr = fetch_byte((word)(cpu.pc + 1));
    zaddr += cpu.x;
    store_byte(zaddr, cpu.y);

    cpu.pc += 2;
}

void _tax(void)
{
    word res = cpu.x = cpu.a;
    set_nz(res);

    cpu.pc++;
}

void _tay(void)
{
    word res = cpu.y = cpu.a;
    set_nz(res);

    cpu.pc++;
}

void _tsx(void)
{
    word res = cpu.x = cpu.sp;
    set_nz(res);

    cpu.pc++;
}

void _txa(void)
{
    word res = cpu.a = cpu.x;
    set_nz(res);

    cpu.pc++;
}

void _txs(void)
{
    cpu.sp = cpu.x;
    cpu.pc++;
}

void _tya(void)
{
    word res = cpu.a = cpu.y;
    set_nz(res);

    cpu.pc++;
}
