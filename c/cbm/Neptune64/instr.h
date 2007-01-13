/*
 *	INSTR.H
 *
 * 	6502 instruction set
 * 	used during code assembly
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
 */
#ifndef __INSTR_H__
#define __INSTR_H__
/* number of addressing modes */
#define MODES 13
/*
 * an instruction is an array of pointers
 * to 6502 machine operations (byte), 
 * one for each supported mode.
 * a NULL pointer slot represents an unsupported
 * addressing mode.
 */
typedef const byte * instr[MODES];
extern const instr adc;
extern const instr and;
extern const instr asl; 
extern const instr bcc; 
extern const instr bcs; 
extern const instr beq; 
extern const instr bit; 
extern const instr bmi; 
extern const instr bne; 
extern const instr bpl; 
extern const instr Brk;
extern const instr bvc; 
extern const instr bvs; 
extern const instr clc; 
extern const instr cld; 
extern const instr cli; 
extern const instr clv; 
extern const instr cmp; 
extern const instr cpx; 
extern const instr cpy; 
extern const instr dec; 
extern const instr dex; 
extern const instr dey; 
extern const instr eor; 
extern const instr inc; 
extern const instr inx; 
extern const instr iny; 
extern const instr jmp; 
extern const instr jsr; 
extern const instr lda; 
extern const instr ldx; 
extern const instr ldy; 
extern const instr lsr; 
extern const instr nop; 
extern const instr ora; 
extern const instr pha; 
extern const instr php; 
extern const instr pla; 
extern const instr plp; 
extern const instr rol; 
extern const instr ror; 
extern const instr rti; 
extern const instr rts; 
extern const instr sbc; 
extern const instr sec; 
extern const instr sed; 
extern const instr sei; 
extern const instr sta; 
extern const instr stx; 
extern const instr sty; 
extern const instr tax; 
extern const instr tay; 
extern const instr tsx; 
extern const instr txa; 
extern const instr txs; 
extern const instr tya; 
#endif /*  __INSTR_H__ */

