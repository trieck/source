/*
 * 	OPCODES.H
 *
 * 	6502 instruction set
 *
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
 */
#ifndef __OPCODES_H__
#define __OPCODES_H__

#define MODES 13

typedef const byte* Instr[MODES];
extern const byte opcodes[];
extern const Instr adc;
extern const Instr and;
extern const Instr asl;
extern const Instr bcc;
extern const Instr bcs;
extern const Instr beq;
extern const Instr bit;
extern const Instr bmi;
extern const Instr bne;
extern const Instr bpl;
extern const Instr Brk;
extern const Instr bvc;
extern const Instr bvs;
extern const Instr clc;
extern const Instr cld;
extern const Instr cli;
extern const Instr clv;
extern const Instr cmp;
extern const Instr cpx;
extern const Instr cpy;
extern const Instr dec;
extern const Instr dex;
extern const Instr dey;
extern const Instr eor;
extern const Instr inc;
extern const Instr inx;
extern const Instr iny;
extern const Instr jmp;
extern const Instr jsr;
extern const Instr lda;
extern const Instr ldx;
extern const Instr ldy;
extern const Instr lsr;
extern const Instr nop;
extern const Instr ora;
extern const Instr pha;
extern const Instr php;
extern const Instr pla;
extern const Instr plp;
extern const Instr rol;
extern const Instr ror;
extern const Instr rti;
extern const Instr rts;
extern const Instr sbc;
extern const Instr sec;
extern const Instr sed;
extern const Instr sei;
extern const Instr sta;
extern const Instr stx;
extern const Instr sty;
extern const Instr tax;
extern const Instr tay;
extern const Instr tsx;
extern const Instr txa;
extern const Instr txs;
extern const Instr tya;

#endif							/*  __OPCODES_H__ */
