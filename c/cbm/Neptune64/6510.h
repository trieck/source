/*
 * 	6510.H
 *
 * 	6510 emulation
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
#ifndef __6510_H__
#define __6510_H__

#define NEG_FLAG			0x80
#define OVERFLOW_FLAG		0x40
#define BRK_FLAG			0x10
#define DECIMAL_FLAG		0x08
#define INT_DISABLE_FLAG	0x04
#define ZERO_FLAG			0x02
#define CARRY_FLAG			0x01

#define get_neg_flag() 					\
	((cpu.sr & NEG_FLAG) >> 7)
#define get_overflow_flag()				\
	((cpu.sr & OVERFLOW_FLAG) >> 6)
#define get_brk_flag()					\
	((cpu.sr & BRK_FLAG) >> 4)
#define get_dec_flag()					\
	((cpu.sr & DECIMAL_FLAG) >> 3)
#define get_int_disable_flag()			\
	((cpu.sr & INT_DISABLE_FLAG) >> 2)
#define get_zero_flag()					\
	((cpu.sr & ZERO_FLAG) >> 1)
#define get_carry_flag()				\
	(cpu.sr & CARRY_FLAG)

typedef struct
{
    word pc; /* program counter */
    byte sp; /* stack pointer */
    byte a;  /* accumulator */
    byte x;  /* x register */
    byte y;  /* y register */
    byte sr; /* status register */
} Cpu;

extern Cpu cpu;

/***************************************************************************/
void cpu_run(void);
byte pop(void);
void push(byte c);
/***************************************************************************/

#endif /* __6510_H__ */
