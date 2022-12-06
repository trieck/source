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
#include "common.h"
#include "opcodes.h"

const byte opcodes[] = {
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

const Instr adc = {
    NULL,        /* acc */
    &opcodes[0], /* imm */
    &opcodes[1], /* zpg */
    &opcodes[2], /* zpx */
    NULL,        /* zpy */
    &opcodes[3], /* abs */
    &opcodes[4], /* abx */
    &opcodes[5], /* aby */
    NULL,        /* imp */
    NULL,        /* rel */
    &opcodes[6], /* idx */
    &opcodes[7], /* idy */
};

const Instr and = {
    NULL,         /* acc */
    &opcodes[8],  /* imm */
    &opcodes[9],  /* zpg */
    &opcodes[10], /* zpx */
    NULL,         /* zpy */
    &opcodes[11], /* abs */
    &opcodes[12], /* abx */
    &opcodes[13], /* aby */
    NULL,         /* imp */
    NULL,         /* rel */
    &opcodes[14], /* idx */
    &opcodes[15], /* idy */
};

const Instr asl = {
    &opcodes[16], /* acc */
    NULL,         /* imm */
    &opcodes[17], /* zpg */
    &opcodes[18], /* zpx */
    NULL,         /* zpy */
    &opcodes[19], /* abs */
    &opcodes[20]  /* abx */
};

const Instr bcc = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    NULL,        /* imp */
    &opcodes[21] /* rel */
};

const Instr bcs = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    NULL,        /* imp */
    &opcodes[22] /* rel */
};

const Instr beq = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    NULL,        /* imp */
    &opcodes[23] /* rel */
};

const Instr bit = {
    NULL,         /* acc */
    NULL,         /* imm */
    &opcodes[24], /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    &opcodes[25]  /* abs */
};

const Instr bmi = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    NULL,        /* imp */
    &opcodes[26] /* rel */
};

const Instr bne = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    NULL,        /* imp */
    &opcodes[27] /* rel */
};

const Instr bpl = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    NULL,        /* imp */
    &opcodes[28] /* rel */
};

const Instr Brk = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    &opcodes[29] /* imp */
};

const Instr bvc = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    NULL,        /* imp */
    &opcodes[30] /* rel */
};

const Instr bvs = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    NULL,        /* imp */
    &opcodes[31] /* rel */
};

const Instr clc = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    &opcodes[32] /* imp */
};

const Instr cld = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    &opcodes[33] /* imp */
};

const Instr cli = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    &opcodes[34] /* imp */
};

const Instr clv = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    &opcodes[35] /* imp */
};

const Instr cmp = {
    NULL,         /* acc */
    &opcodes[36], /* imm */
    &opcodes[37], /* zpg */
    &opcodes[38], /* zpx */
    NULL,         /* zpy */
    &opcodes[39], /* abs */
    &opcodes[40], /* abx */
    &opcodes[41], /* aby */
    NULL,         /* imp */
    NULL,         /* rel */
    &opcodes[42], /* idx */
    &opcodes[43], /* idy */
};

const Instr cpx = {
    NULL,         /* acc */
    &opcodes[44], /* imm */
    &opcodes[45], /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    &opcodes[46], /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    NULL,         /* imp */
    NULL,         /* rel */
    NULL,         /* idx */
    NULL,         /* idy */
};

const Instr cpy = {
    NULL,         /* acc */
    &opcodes[47], /* imm */
    &opcodes[48], /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    &opcodes[49], /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    NULL,         /* imp */
    NULL,         /* rel */
    NULL,         /* idx */
    NULL,         /* idy */
};

const Instr dec = {
    NULL,         /* acc */
    NULL,         /* imm */
    &opcodes[50], /* zpg */
    &opcodes[51], /* zpx */
    NULL,         /* zpy */
    &opcodes[52], /* abs */
    &opcodes[53]  /* abx */
};

const Instr dex = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    &opcodes[54] /* imp */
};

const Instr dey = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    &opcodes[55] /* imp */
};

const Instr eor = {
    NULL,         /* acc */
    &opcodes[56], /* imm */
    &opcodes[57], /* zpg */
    &opcodes[58], /* zpx */
    NULL,         /* zpy */
    &opcodes[59], /* abs */
    &opcodes[60], /* abx */
    &opcodes[61], /* aby */
    NULL,         /* imp */
    NULL,         /* rel */
    &opcodes[62], /* idx */
    &opcodes[63]  /* idy */
};

const Instr inc = {
    NULL,         /* acc */
    NULL,         /* imm */
    &opcodes[64], /* zpg */
    &opcodes[65], /* zpx */
    NULL,         /* zpy */
    &opcodes[66], /* abs */
    &opcodes[67]  /* abx */
};

const Instr inx = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    &opcodes[68] /* imp */
};

const Instr iny = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    &opcodes[69] /* imp */
};

const Instr jmp = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    &opcodes[70], /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    NULL,         /* imp */
    NULL,         /* rel */
    NULL,         /* idx */
    NULL,         /* idy */
    &opcodes[71]  /* ind */
};

const Instr jsr = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    &opcodes[72] /* abs */
};

const Instr lda = {
    NULL,         /* acc */
    &opcodes[73], /* imm */
    &opcodes[74], /* zpg */
    &opcodes[75], /* zpx */
    NULL,         /* zpy */
    &opcodes[76], /* abs */
    &opcodes[77], /* abx */
    &opcodes[78], /* aby */
    NULL,         /* imp */
    NULL,         /* rel */
    &opcodes[79], /* idx */
    &opcodes[80]  /* idy */
};

const Instr ldx = {
    NULL,         /* acc */
    &opcodes[81], /* imm */
    &opcodes[82], /* zpg */
    NULL,         /* zpx */
    &opcodes[83], /* zpy */
    &opcodes[84], /* abs */
    NULL,         /* abx */
    &opcodes[85]  /* aby */
};

const Instr ldy = {
    NULL,         /* acc */
    &opcodes[86], /* imm */
    &opcodes[87], /* zpg */
    &opcodes[88], /* zpx */
    NULL,         /* zpy */
    &opcodes[89], /* abs */
    &opcodes[90]  /* abx */
};

const Instr lsr = {
    &opcodes[91], /* acc */
    NULL,         /* imm */
    &opcodes[92], /* zpg */
    &opcodes[93], /* zpx */
    NULL,         /* zpy */
    &opcodes[94], /* abs */
    &opcodes[95]  /* abx */
};

const Instr nop = {
    NULL,        /* acc */
    NULL,        /* imm */
    NULL,        /* zpg */
    NULL,        /* zpx */
    NULL,        /* zpy */
    NULL,        /* abs */
    NULL,        /* abx */
    NULL,        /* aby */
    &opcodes[96] /* imp */
};

const Instr ora = {
    NULL,          /* acc */
    &opcodes[97],  /* imm */
    &opcodes[98],  /* zpg */
    &opcodes[99],  /* zpx */
    NULL,          /* zpy */
    &opcodes[100], /* abs */
    &opcodes[101], /* abx */
    &opcodes[102], /* aby */
    NULL,          /* imp */
    NULL,          /* rel */
    &opcodes[103], /* idx */
    &opcodes[104]  /* idy */
};

const Instr pha = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[105] /* imp */
};

const Instr php = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[106] /* imp */
};

const Instr pla = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[107] /* imp */
};

const Instr plp = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[108] /* imp */
};

const Instr rol = {
    &opcodes[109], /* acc */
    NULL,          /* imm */
    &opcodes[110], /* zpg */
    &opcodes[111], /* zpx */
    NULL,          /* zpy */
    &opcodes[112], /* abs */
    &opcodes[113]  /* abx */
};

const Instr ror = {
    &opcodes[114], /* acc */
    NULL,          /* imm */
    &opcodes[115], /* zpg */
    &opcodes[116], /* zpx */
    NULL,          /* zpy */
    &opcodes[117], /* abs */
    &opcodes[118]  /* abx */
};

const Instr rti = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[119] /* imp */
};

const Instr rts = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[120] /* imp */
};

const Instr sbc = {
    NULL,          /* acc */
    &opcodes[121], /* imm */
    &opcodes[122], /* zpg */
    &opcodes[123], /* zpx */
    NULL,          /* zpy */
    &opcodes[124], /* abs */
    &opcodes[125], /* abx */
    &opcodes[126], /* aby */
    NULL,          /* imp */
    NULL,          /* rel */
    &opcodes[127], /* idx */
    &opcodes[128]  /* idy */
};

const Instr sec = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[129] /* imp */
};

const Instr sed = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[130] /* imp */
};

const Instr sei = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[131] /* imp */
};

const Instr sta = {
    NULL,          /* acc */
    NULL,          /* imm */
    &opcodes[132], /* zpg */
    &opcodes[133], /* zpx */
    NULL,          /* zpy */
    &opcodes[134], /* abs */
    &opcodes[135], /* abx */
    &opcodes[136], /* aby */
    NULL,          /* imp */
    NULL,          /* rel */
    &opcodes[137], /* idx */
    &opcodes[138]  /* idy */
};

const Instr stx = {
    NULL,          /* acc */
    NULL,          /* imm */
    &opcodes[139], /* zpg */
    &opcodes[140], /* zpx */
    NULL,          /* zpy */
    &opcodes[141]  /* abs */
};

const Instr sty = {
    NULL,          /* acc */
    NULL,          /* imm */
    &opcodes[142], /* zpg */
    &opcodes[143], /* zpx */
    NULL,          /* zpy */
    &opcodes[144]  /* abs */
};

const Instr tax = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[145] /* imp */
};

const Instr tay = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[146] /* imp */
};

const Instr tsx = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[147] /* imp */
};

const Instr txa = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[148] /* imp */
};

const Instr txs = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[149] /* imp */
};

const Instr tya = {
    NULL,         /* acc */
    NULL,         /* imm */
    NULL,         /* zpg */
    NULL,         /* zpx */
    NULL,         /* zpy */
    NULL,         /* abs */
    NULL,         /* abx */
    NULL,         /* aby */
    &opcodes[150] /* imp */
};
