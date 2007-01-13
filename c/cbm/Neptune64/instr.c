/*
 * 	INSTR.C
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
 *
 */
#include <stdlib.h>
#include "common.h"
#include "instr.h"
/*
 * array of all supported operations
 */
const byte ops[] = {
	0x69, 0x65, 0x75, 0x6D, 0x7D, 0x79, 0x61, 0x71,
	0x29, 0x25, 0x35, 0x2D, 0x3D, 0x39, 0x21, 0x31,
	0x0A, 0x06, 0x16, 0x0E, 0x1E,
	0x90,
	0xB0,
	0xF0,
	0x24, 0x2C,
	0x30,
	0xD0,
	0x10,
	0x00,
	0x50,
	0x70,
	0x18,
	0xD8,
	0x58,
	0xB8,
	0xC9, 0xC5, 0xD5, 0xCD, 0xDD, 0xD9, 0xC1, 0xD1,
	0xE0, 0xE4, 0xEC, 
	0xC0, 0xC4, 0xCC,
	0xC6, 0xD6, 0xCE, 0xDE,
	0xCA,
	0x88,
	0x49, 0x45, 0x55, 0x4D, 0x5D, 0x59, 0x41, 0x51,
	0xE6, 0xF6, 0xEE, 0xFE,
	0xE8, 
	0xC8,
	0x4C, 0x6C,
	0x20,
	0xA9, 0xA5, 0xB5, 0xAD, 0xBD, 0xB9, 0xA1, 0xB1,
	0xA2, 0xA6, 0xB6, 0xAE, 0xBE,
	0xA0, 0xA4, 0xB4, 0xAC, 0xBC,
	0x4A, 0x46, 0x56, 0x4E, 0x5E,
	0xEA,
	0x09, 0x05, 0x15, 0x0D, 0x1D, 0x19, 0x01, 0x11,
	0x48, 
	0x08,
	0x68,
	0x28,
	0x2A, 0x26, 0x36, 0x2E, 0x3E,
	0x6A, 0x66, 0x76, 0x6E, 0x7E,
	0x40,
	0x60,
	0xE9, 0xE5, 0xF5, 0xED, 0xFD, 0xF9, 0xE1, 0xF1,
	0x38,
	0xF8,
	0x78,
	0x85, 0x95, 0x8D, 0x9D, 0x99, 0x81, 0x91,
	0x86, 0x96, 0x8E,
	0x84, 0x94, 0x8C,
	0xAA,
	0xA8,
	0xBA,
	0x8A,
	0x9A,
	0x98
};
const instr adc = {
	NULL, 		/* acc */
	&ops[0], 	/* imm */
	&ops[1],	/* zpg */
	&ops[2],	/* zpx */
	NULL,		/* zpy */
	&ops[3],	/* abs */
	&ops[4],	/* abx */
	&ops[5],	/* aby */
	NULL,		/* imp */
	NULL,		/* rel */
	&ops[6],	/* idx */
	&ops[7],	/* idy */
};
const instr and = {
	NULL,		/* acc */
	&ops[8],	/* imm */
	&ops[9],	/* zpg */
	&ops[10],	/* zpx */
	NULL,		/* zpy */
	&ops[11],	/* abs */
	&ops[12],	/* abx */
	&ops[13],	/* aby */
	NULL,		/* imp */
	NULL,		/* rel */
	&ops[14],	/* idx */
	&ops[15],	/* idy */
};
const instr asl = {
	&ops[16],	/* acc */
	NULL,		/* imm */
	&ops[17],	/* zpg */
	&ops[18],	/* zpx */
	NULL,		/* zpy */
	&ops[19],	/* abs */
	&ops[20]	/* abx */
};
const instr bcc = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	NULL,		/* imp */
	&ops[21]	/* rel */
};
const instr bcs = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	NULL,		/* imp */
	&ops[22]	/* rel */
};
const instr beq = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	NULL,		/* imp */
	&ops[23]	/* rel */
};
const instr bit = {
	NULL,		/* acc */
	NULL,		/* imm */
	&ops[24],	/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	&ops[25]	/* abs */
};
const instr bmi = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	NULL,		/* imp */
	&ops[26]	/* rel */
};
const instr bne = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	NULL,		/* imp */
	&ops[27]	/* rel */
};
const instr bpl = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	NULL,		/* imp */
	&ops[28]	/* rel */
};
const instr Brk = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	&ops[29]	/* imp */
};
const instr bvc = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	NULL,		/* imp */
	&ops[30]	/* rel */
};
const instr bvs = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	NULL,		/* imp */
	&ops[31]	/* rel */
};
const instr clc = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	&ops[32]	/* imp */
};
const instr cld = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	&ops[33]	/* imp */
};
const instr cli = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	&ops[34]	/* imp */
};
const instr clv = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	&ops[35]	/* imp */
};
const instr cmp = {
	NULL, 		/* acc */
	&ops[36], 	/* imm */
	&ops[37],	/* zpg */
	&ops[38],	/* zpx */
	NULL,		/* zpy */
	&ops[39],	/* abs */
	&ops[40],	/* abx */
	&ops[41],	/* aby */
	NULL,		/* imp */
	NULL,		/* rel */
	&ops[42],	/* idx */
	&ops[43],	/* idy */
};
const instr cpx = {
	NULL, 		/* acc */
	&ops[44], 	/* imm */
	&ops[45],	/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	&ops[46],	/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	NULL,		/* imp */
	NULL,		/* rel */
	NULL,		/* idx */
	NULL,		/* idy */
};
const instr cpy = {
	NULL, 		/* acc */
	&ops[47], 	/* imm */
	&ops[48],	/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	&ops[49],	/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	NULL,		/* imp */
	NULL,		/* rel */
	NULL,		/* idx */
	NULL,		/* idy */
};
const instr dec = {
	NULL,		/* acc */
	NULL,		/* imm */
	&ops[50],	/* zpg */
	&ops[51],	/* zpx */
	NULL,		/* zpy */
	&ops[52],	/* abs */
	&ops[53]	/* abx */		
};
const instr dex = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	&ops[54]	/* imp */
};
const instr dey = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	&ops[55]	/* imp */
};
const instr eor = {
	NULL, 		/* acc */
	&ops[56], 	/* imm */
	&ops[57],	/* zpg */
	&ops[58],	/* zpx */
	NULL,		/* zpy */
	&ops[59],	/* abs */
	&ops[60],	/* abx */
	&ops[61],	/* aby */
	NULL,		/* imp */
	NULL,		/* rel */
	&ops[62],	/* idx */
	&ops[63]	/* idy */
};
const instr inc = {
	NULL, 		/* acc */
	NULL,	 	/* imm */
	&ops[64],	/* zpg */
	&ops[65],	/* zpx */
	NULL,		/* zpy */
	&ops[66],	/* abs */
	&ops[67]	/* abx */
};
const instr inx = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	&ops[68]	/* imp */
};
const instr iny = {
	NULL,		/* acc */
	NULL,		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL, 		/* aby */
	&ops[69]	/* imp */
};
const instr jmp = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	&ops[70],	/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	NULL,		/* imp */
	NULL,		/* rel */
	NULL,		/* idx */
	NULL,		/* idy */
	&ops[71]	/* ind */
};
const instr jsr = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	&ops[72]	/* abs */
};
const instr lda = {
	NULL, 		/* acc */
	&ops[73], 	/* imm */
	&ops[74],	/* zpg */
	&ops[75],	/* zpx */
	NULL,		/* zpy */
	&ops[76],	/* abs */
	&ops[77],	/* abx */
	&ops[78],	/* aby */
	NULL,		/* imp */
	NULL,		/* rel */
	&ops[79],	/* idx */
	&ops[80]	/* idy */
};
const instr ldx = {
	NULL, 		/* acc */
	&ops[81], 	/* imm */
	&ops[82],	/* zpg */
	NULL,		/* zpx */
	&ops[83],	/* zpy */
	&ops[84],	/* abs */
	NULL,		/* abx */
	&ops[85]	/* aby */
};
const instr ldy = {
	NULL, 		/* acc */
	&ops[86], 	/* imm */
	&ops[87],	/* zpg */
	&ops[88],	/* zpx */
	NULL,		/* zpy */
	&ops[89],	/* abs */
	&ops[90]	/* abx */
};
const instr lsr = {
	&ops[91], 	/* acc */
	NULL, 		/* imm */
	&ops[92],	/* zpg */
	&ops[93],	/* zpx */
	NULL,		/* zpy */
	&ops[94],	/* abs */
	&ops[95]	/* abx */
};
const instr nop = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[96]	/* imp */
};
const instr ora = {
	NULL, 		/* acc */
	&ops[97], 	/* imm */
	&ops[98],	/* zpg */
	&ops[99],	/* zpx */
	NULL,		/* zpy */
	&ops[100],	/* abs */
	&ops[101],	/* abx */
	&ops[102],	/* aby */
	NULL,		/* imp */
	NULL,		/* rel */
	&ops[103],	/* idx */
	&ops[104]	/* idy */
};
const instr pha = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[105]	/* imp */
};
const instr php = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[106]	/* imp */
};
const instr pla = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[107]	/* imp */
};
const instr plp = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[108]	/* imp */
};
const instr rol = {
	&ops[109], 	/* acc */
	NULL, 		/* imm */
	&ops[110],	/* zpg */
	&ops[111],	/* zpx */
	NULL,		/* zpy */
	&ops[112],	/* abs */
	&ops[113]	/* abx */
};
const instr ror = {
	&ops[114], 	/* acc */
	NULL, 		/* imm */
	&ops[115],	/* zpg */
	&ops[116],	/* zpx */
	NULL,		/* zpy */
	&ops[117],	/* abs */
	&ops[118]	/* abx */
};
const instr rti = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[119]	/* imp */
};
const instr rts = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[120]	/* imp */
};
const instr sbc = {
	NULL, 		/* acc */
	&ops[121], 	/* imm */
	&ops[122],	/* zpg */
	&ops[123],	/* zpx */
	NULL,		/* zpy */
	&ops[124],	/* abs */
	&ops[125],	/* abx */
	&ops[126],	/* aby */
	NULL,		/* imp */
	NULL,		/* rel */
	&ops[127],	/* idx */
	&ops[128]	/* idy */
};
const instr sec = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[129]	/* imp */
};
const instr sed = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[130]	/* imp */
};
const instr sei = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[131]	/* imp */
};
const instr sta = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	&ops[132],	/* zpg */
	&ops[133],	/* zpx */
	NULL,		/* zpy */
	&ops[134],	/* abs */
	&ops[135],	/* abx */
	&ops[136],	/* aby */
	NULL,		/* imp */
	NULL,		/* rel */
	&ops[137],	/* idx */
	&ops[138]	/* idy */
};
const instr stx = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	&ops[139],	/* zpg */
	&ops[140],	/* zpx */
	NULL,		/* zpy */
	&ops[141]	/* abs */
};
const instr sty = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	&ops[142],	/* zpg */
	&ops[143],	/* zpx */
	NULL,		/* zpy */
	&ops[144]	/* abs */
};
const instr tax = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[145]	/* imp */
};
const instr tay = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[146]	/* imp */
};
const instr tsx = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[147]	/* imp */
};
const instr txa = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[148]	/* imp */
};
const instr txs = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[149]	/* imp */
};
const instr tya = {
	NULL, 		/* acc */
	NULL, 		/* imm */
	NULL,		/* zpg */
	NULL,		/* zpx */
	NULL,		/* zpy */
	NULL,		/* abs */
	NULL,		/* abx */
	NULL,		/* aby */
	&ops[150]	/* imp */
};

