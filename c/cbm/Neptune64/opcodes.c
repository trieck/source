/*
 * 	OPCODES.C
 *
 * 	opcode definitions
 * 	used during code disassembly and execution
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
#include "common.h"
#include "opcodes.h"
/* number of opcodes */
#define OPCODES 56
#define ADC &opnames[0]
#define AND &opnames[1]
#define ASL &opnames[2]
#define BCC &opnames[3]
#define BCS &opnames[4]
#define BEQ &opnames[5]
#define BIT &opnames[6]
#define BMI &opnames[7]
#define BNE &opnames[8]
#define BPL &opnames[9]
#define BRK &opnames[10]
#define BVC &opnames[11]
#define BVS &opnames[12]
#define CLC &opnames[13]
#define CLD &opnames[14]
#define CLI &opnames[15]
#define CLV &opnames[16]
#define CMP &opnames[17]
#define CPX &opnames[18]
#define CPY &opnames[19]
#define DEC &opnames[20]
#define DEX &opnames[21]
#define DEY &opnames[22]
#define EOR &opnames[23]
#define INC &opnames[24]
#define INX &opnames[25]
#define INY &opnames[26]
#define JMP &opnames[27]
#define JSR &opnames[28]
#define LDA &opnames[29]
#define LDX &opnames[30]
#define LDY &opnames[31]
#define LSR &opnames[32]
#define NOP &opnames[33]
#define ORA &opnames[34]
#define PHA &opnames[35]
#define PHP &opnames[36]
#define PLA &opnames[37]
#define PLP &opnames[38]
#define ROL &opnames[39]
#define ROR &opnames[40]
#define RTI &opnames[41]
#define RTS &opnames[42]
#define SBC &opnames[43]
#define SEC &opnames[44]
#define SED &opnames[45]
#define SEI &opnames[46]
#define STA &opnames[47]
#define STX &opnames[48]
#define STY &opnames[49]
#define TAX &opnames[50]
#define TAY &opnames[51]
#define TSX &opnames[52]
#define TXA &opnames[53]
#define TXS &opnames[54]
#define TYA &opnames[55]
/* opcode names */
static const char* opnames[OPCODES] = {
    "adc", "and", "asl", "bcc", "bcs", "beq", "bit", "bmi", "bne", "bpl",
    "brk", "bvc", "bvs", "clc", "cld", "cli", "clv", "cmp", "cpx", "cpy",
    "dec", "dex", "dey", "eor", "inc", "inx", "iny", "jmp", "jsr", "lda",
    "ldx", "ldy", "lsr", "nop", "ora", "pha", "php", "pla", "plp", "rol",
    "ror", "rti", "rts", "sbc", "sec", "sed", "sei", "sta", "stx", "sty",
    "tax", "tay", "tsx", "txa", "txs", "tya"
};
extern void _adcAbsl(void);
extern void _adcAbx(void);
extern void _adcAby(void);
extern void _adcIdx(void);
extern void _adcIdy(void);
extern void _adcImm(void);
extern void _adcZp(void);
extern void _adcZpx(void);
extern void _andAbsl(void);
extern void _andAbx(void);
extern void _andAby(void);
extern void _andIdx(void);
extern void _andIdy(void);
extern void _andImm(void);
extern void _andZp(void);
extern void _andZpx(void);
extern void _aslAbsl(void);
extern void _aslAbx(void);
extern void _aslAcc(void);
extern void _aslZp(void);
extern void _aslZpx(void);
extern void _bcc(void);
extern void _bcs(void);
extern void _beq(void);
extern void _bitAbsl(void);
extern void _bitZp(void);
extern void _bmi(void);
extern void _bne(void);
extern void _bpl(void);
extern void _brk(void);
extern void _bvc(void);
extern void _bvs(void);
extern void _clc(void);
extern void _cld(void);
extern void _cli(void);
extern void _clv(void);
extern void _cmpAbsl(void);
extern void _cmpAbx(void);
extern void _cmpAby(void);
extern void _cmpIdx(void);
extern void _cmpIdy(void);
extern void _cmpImm(void);
extern void _cmpZp(void);
extern void _cmpZpx(void);
extern void _cpxAbsl(void);
extern void _cpxImm(void);
extern void _cpxZp(void);
extern void _cpyAbsl(void);
extern void _cpyImm(void);
extern void _cpyZp(void);
extern void _decAbsl(void);
extern void _decAbx(void);
extern void _decZp(void);
extern void _decZpx(void);
extern void _dex(void);
extern void _dey(void);
extern void _eorAbsl(void);
extern void _eorAbx(void);
extern void _eorAby(void);
extern void _eorIdx(void);
extern void _eorIdy(void);
extern void _eorImm(void);
extern void _eorZp(void);
extern void _eorZpx(void);
extern void _incAbsl(void);
extern void _incAbx(void);
extern void _incZp(void);
extern void _incZpx(void);
extern void _inx(void);
extern void _iny(void);
extern void _jmpAbsl(void);
extern void _jmpInd(void);
extern void _jsr(void);
extern void _ldaAbsl(void);
extern void _ldaAbx(void);
extern void _ldaAby(void);
extern void _ldaIdx(void);
extern void _ldaIdy(void);
extern void _ldaImm(void);
extern void _ldaZp(void);
extern void _ldaZpx(void);
extern void _ldxAbsl(void);
extern void _ldxAby(void);
extern void _ldxImm(void);
extern void _ldxZp(void);
extern void _ldxZpy(void);
extern void _ldyAbsl(void);
extern void _ldyAbx(void);
extern void _ldyImm(void);
extern void _ldyZp(void);
extern void _ldyZpx(void);
extern void _lsrAbsl(void);
extern void _lsrAbx(void);
extern void _lsrAcc(void);
extern void _lsrZp(void);
extern void _lsrZpx(void);
extern void _nop(void);
extern void _oraAbsl(void);
extern void _oraAbx(void);
extern void _oraAby(void);
extern void _oraIdx(void);
extern void _oraIdy(void);
extern void _oraImm(void);
extern void _oraZp(void);
extern void _oraZpx(void);
extern void _pha(void);
extern void _php(void);
extern void _pla(void);
extern void _plp(void);
extern void _rolAbsl(void);
extern void _rolAbx(void);
extern void _rolAcc(void);
extern void _rolZp(void);
extern void _rolZpx(void);
extern void _rorAbsl(void);
extern void _rorAbx(void);
extern void _rorAcc(void);
extern void _rorZp(void);
extern void _rorZpx(void);
extern void _rti(void);
extern void _rts(void);
extern void _sbcAbsl(void);
extern void _sbcAbx(void);
extern void _sbcAby(void);
extern void _sbcIdx(void);
extern void _sbcIdy(void);
extern void _sbcImm(void);
extern void _sbcZp(void);
extern void _sbcZpx(void);
extern void _sec(void);
extern void _sed(void);
extern void _sei(void);
extern void _staAbsl(void);
extern void _staAbx(void);
extern void _staAby(void);
extern void _staIdx(void);
extern void _staIdy(void);
extern void _staZp(void);
extern void _staZpx(void);
extern void _stxAbsl(void);
extern void _stxZp(void);
extern void _stxZpy(void);
extern void _styAbsl(void);
extern void _styZp(void);
extern void _styZpx(void);
extern void _tax(void);
extern void _tay(void);
extern void _tsx(void);
extern void _txa(void);
extern void _txs(void);
extern void _tya(void);
static const Instr adcAbsl = { ADC, absl, _adcAbsl };
static const Instr adcAbx = { ADC, abx, _adcAbx };
static const Instr adcAby = { ADC, aby, _adcAby };
static const Instr adcIdx = { ADC, idx, _adcIdx };
static const Instr adcIdy = { ADC, idy, _adcIdy };
static const Instr adcImm = { ADC, imm, _adcImm };
static const Instr adcZp = { ADC, zpg, _adcZp };
static const Instr adcZpx = { ADC, zpx, _adcZpx };
static const Instr andAbsl = { AND, absl, _andAbsl };
static const Instr andAbx = { AND, abx, _andAbx };
static const Instr andAby = { AND, aby, _andAby };
static const Instr andIdx = { AND, idx, _andIdx };
static const Instr andIdy = { AND, idy, _andIdy };
static const Instr andImm = { AND, imm, _andImm };
static const Instr andZp = { AND, zpg, _andZp };
static const Instr andZpx = { AND, zpx, _andZpx };
static const Instr aslAbsl = { ASL, absl, _aslAbsl };
static const Instr aslAbx = { ASL, abx, _aslAbx };
static const Instr aslAcc = { ASL, acc, _aslAcc };
static const Instr aslZp = { ASL, zpg, _aslZp };
static const Instr aslZpx = { ASL, zpx, _aslZpx };
static const Instr bcc = { BCC, rel, _bcc };
static const Instr bcs = { BCS, rel, _bcs };
static const Instr beq = { BEQ, rel, _beq };
static const Instr bitAbsl = { BIT, absl, _bitAbsl };
static const Instr bitZp = { BIT, zpg, _bitZp };
static const Instr bmi = { BMI, rel, _bmi };
static const Instr bne = { BNE, rel, _bne };
static const Instr bpl = { BPL, rel, _bpl };
static const Instr Brk = { BRK, imp, _brk };
static const Instr bvc = { BVC, rel, _bvc };
static const Instr bvs = { BVS, rel, _bvs };
static const Instr clc = { CLC, imp, _clc };
static const Instr cld = { CLD, imp, _cld };
static const Instr cli = { CLI, imp, _cli };
static const Instr clv = { CLV, imp, _clv };
static const Instr cmpAbsl = { CMP, absl, _cmpAbsl };
static const Instr cmpAbx = { CMP, abx, _cmpAbx };
static const Instr cmpAby = { CMP, aby, _cmpAby };
static const Instr cmpIdx = { CMP, idx, _cmpIdx };
static const Instr cmpIdy = { CMP, idy, _cmpIdy };
static const Instr cmpImm = { CMP, imm, _cmpImm };
static const Instr cmpZp = { CMP, zpg, _cmpZp };
static const Instr cmpZpx = { CMP, zpx, _cmpZpx };
static const Instr cpxAbsl = { CPX, absl, _cpxAbsl };
static const Instr cpxImm = { CPX, imm, _cpxImm };
static const Instr cpxZp = { CPX, zpg, _cpxZp };
static const Instr cpyAbsl = { CPY, absl, _cpyAbsl };
static const Instr cpyImm = { CPY, imm, _cpyImm };
static const Instr cpyZp = { CPY, zpg, _cpyZp };
static const Instr decAbsl = { DEC, absl, _decAbsl };
static const Instr decAbx = { DEC, abx, _decAbx };
static const Instr decZp = { DEC, zpg, _decZp };
static const Instr decZpx = { DEC, zpx, _decZpx };
static const Instr dex = { DEX, imp, _dex };
static const Instr dey = { DEY, imp, _dey };
static const Instr eorAbsl = { EOR, absl, _eorAbsl };
static const Instr eorAbx = { EOR, abx, _eorAbx };
static const Instr eorAby = { EOR, aby, _eorAby };
static const Instr eorIdx = { EOR, idx, _eorIdx };
static const Instr eorIdy = { EOR, idy, _eorIdy };
static const Instr eorImm = { EOR, imm, _eorImm };
static const Instr eorZp = { EOR, zpg, _eorZp };
static const Instr eorZpx = { EOR, zpx, _eorZpx };
static const Instr incAbsl = { INC, absl, _incAbsl };
static const Instr incAbx = { INC, abx, _incAbx };
static const Instr incZp = { INC, zpg, _incZp };
static const Instr incZpx = { INC, zpx, _incZpx };
static const Instr inx = { INX, imp, _inx };
static const Instr iny = { INY, imp, _iny };
static const Instr jmpAbsl = { JMP, absl, _jmpAbsl };
static const Instr jmpInd = { JMP, ind, _jmpInd };
static const Instr jsr = { JSR, absl, _jsr };
static const Instr ldaAbsl = { LDA, absl, _ldaAbsl };
static const Instr ldaAbx = { LDA, abx, _ldaAbx };
static const Instr ldaAby = { LDA, aby, _ldaAby };
static const Instr ldaIdx = { LDA, idx, _ldaIdx };
static const Instr ldaIdy = { LDA, idy, _ldaIdy };
static const Instr ldaImm = { LDA, imm, _ldaImm };
static const Instr ldaZp = { LDA, zpg, _ldaZp };
static const Instr ldaZpx = { LDA, zpx, _ldaZpx };
static const Instr ldxAbsl = { LDX, absl, _ldxAbsl };
static const Instr ldxAby = { LDX, aby, _ldxAby };
static const Instr ldxImm = { LDX, imm, _ldxImm };
static const Instr ldxZp = { LDX, zpg, _ldxZp };
static const Instr ldxZpy = { LDX, zpy, _ldxZpy };
static const Instr ldyAbsl = { LDY, absl, _ldyAbsl };
static const Instr ldyAbx = { LDY, abx, _ldyAbx };
static const Instr ldyImm = { LDY, imm, _ldyImm };
static const Instr ldyZp = { LDY, zpg, _ldyZp };
static const Instr ldyZpx = { LDY, zpx, _ldyZpx };
static const Instr lsrAbsl = { LSR, absl, _lsrAbsl };
static const Instr lsrAbx = { LSR, abx, _lsrAbx };
static const Instr lsrAcc = { LSR, acc, _lsrAcc };
static const Instr lsrZp = { LSR, zpg, _lsrZp };
static const Instr lsrZpx = { LSR, zpx, _lsrZpx };
static const Instr nop = { NOP, imp, _nop };
static const Instr oraAbsl = { ORA, absl, _oraAbsl };
static const Instr oraAbx = { ORA, abx, _oraAbx };
static const Instr oraAby = { ORA, aby, _oraAby };
static const Instr oraIdx = { ORA, idx, _oraIdx };
static const Instr oraIdy = { ORA, idy, _oraIdy };
static const Instr oraImm = { ORA, imm, _oraImm };
static const Instr oraZp = { ORA, zpg, _oraZp };
static const Instr oraZpx = { ORA, zpx, _oraZpx };
static const Instr pha = { PHA, imp, _pha };
static const Instr php = { PHP, imp, _php };
static const Instr pla = { PLA, imp, _pla };
static const Instr plp = { PLP, imp, _plp };
static const Instr rolAbsl = { ROL, absl, _rolAbsl };
static const Instr rolAbx = { ROL, abx, _rolAbx };
static const Instr rolAcc = { ROL, acc, _rolAcc };
static const Instr rolZp = { ROL, zpg, _rolZp };
static const Instr rolZpx = { ROL, zpx, _rolZpx };
static const Instr rorAbsl = { ROR, absl, _rorAbsl };
static const Instr rorAbx = { ROR, abx, _rorAbx };
static const Instr rorAcc = { ROR, acc, _rorAcc };
static const Instr rorZp = { ROR, zpg, _rorZp };
static const Instr rorZpx = { ROR, zpx, _rorZpx };
static const Instr rti = { RTI, imp, _rti };
static const Instr rts = { RTS, imp, _rts };
static const Instr sbcAbsl = { SBC, absl, _sbcAbsl };
static const Instr sbcAbx = { SBC, abx, _sbcAbx };
static const Instr sbcAby = { SBC, aby, _sbcAby };
static const Instr sbcIdx = { SBC, idx, _sbcIdx };
static const Instr sbcIdy = { SBC, idy, _sbcIdy };
static const Instr sbcImm = { SBC, imm, _sbcImm };
static const Instr sbcZp = { SBC, zpg, _sbcZp };
static const Instr sbcZpx = { SBC, zpx, _sbcZpx };
static const Instr sec = { SEC, imp, _sec };
static const Instr sed = { SED, imp, _sed };
static const Instr sei = { SEI, imp, _sei };
static const Instr staAbsl = { STA, absl, _staAbsl };
static const Instr staAbx = { STA, abx, _staAbx };
static const Instr staAby = { STA, aby, _staAby };
static const Instr staIdx = { STA, idx, _staIdx };
static const Instr staIdy = { STA, idy, _staIdy };
static const Instr staZp = { STA, zpg, _staZp };
static const Instr staZpx = { STA, zpg, _staZpx };
static const Instr stxAbsl = { STX, absl, _stxAbsl };
static const Instr stxZp = { STX, zpg, _stxZp };
static const Instr stxZpy = { STX, zpy, _stxZpy };
static const Instr styAbsl = { STY, absl, _styAbsl };
static const Instr styZp = { STY, zpg, _styZp };
static const Instr styZpx = { STY, zpg, _styZpx };
static const Instr tax = { TAX, imp, _tax };
static const Instr tay = { TAY, imp, _tay };
static const Instr tsx = { TSX, imp, _tsx };
static const Instr txa = { TXA, imp, _txa };
static const Instr txs = { TXS, imp, _txs };
static const Instr tya = { TYA, imp, _tya };
/* instructions */
const Instr* instructions[INSTRUCTIONS] = {
    &Brk,     /* 0x00 */
    &oraIdx,  /* 0x01 */
    NULL,     /* 0x02 */
    NULL,     /* 0x03 */
    NULL,     /* 0x04 */
    &oraZp,   /* 0x05 */
    &aslZp,   /* 0x06 */
    NULL,     /* 0x07 */
    &php,     /* 0x08 */
    &oraImm,  /* 0x09 */
    &aslAcc,  /* 0x0A */
    NULL,     /* 0x0B */
    NULL,     /* 0x0C */
    &oraAbsl, /* 0x0D */
    &aslAbsl, /* 0x0E */
    NULL,     /* 0x0F */
    &bpl,     /* 0x10 */
    &oraIdy,  /* 0x11 */
    NULL,     /* 0x12 */
    NULL,     /* 0x13 */
    NULL,     /* 0x14 */
    &oraZpx,  /* 0x15 */
    &aslZpx,  /* 0x16 */
    NULL,     /* 0x17 */
    &clc,     /* 0x18 */
    &oraAby,  /* 0x19 */
    NULL,     /* 0x1A */
    NULL,     /* 0x1B */
    NULL,     /* 0x1C */
    &oraAbx,  /* 0x1D */
    &aslAbx,  /* 0x1E */
    NULL,     /* 0x1F */
    &jsr,     /* 0x20 */
    &andIdx,  /* 0x21 */
    NULL,     /* 0x22 */
    NULL,     /* 0x23 */
    &bitZp,   /* 0x24 */
    &andZp,   /* 0x25 */
    &rolZp,   /* 0x26 */
    NULL,     /* 0x27 */
    &plp,     /* 0x28 */
    &andImm,  /* 0x29 */
    &rolAcc,  /* 0x2A */
    NULL,     /* 0x2B */
    &bitAbsl, /* 0x2C */
    &andAbsl, /* 0x2D */
    &rolAbsl, /* 0x2E */
    NULL,     /* 0x2F */
    &bmi,     /* 0x30 */
    &andIdy,  /* 0x31 */
    NULL,     /* 0x32 */
    NULL,     /* 0x33 */
    NULL,     /* 0x34 */
    &andZpx,  /* 0x35 */
    &rolZpx,  /* 0x36 */
    NULL,     /* 0x37 */
    &sec,     /* 0x38 */
    &andAby,  /* 0x39 */
    NULL,     /* 0x3A */
    NULL,     /* 0x3B */
    NULL,     /* 0x3C */
    &andAbx,  /* 0x3D */
    &rolAbx,  /* 0x3E */
    NULL,     /* 0x3F */
    &rti,     /* 0x40 */
    &eorIdx,  /* 0x41 */
    NULL,     /* 0x42 */
    NULL,     /* 0x43 */
    NULL,     /* 0x44 */
    &eorZp,   /* 0x45 */
    &lsrZp,   /* 0x46 */
    NULL,     /* 0x47 */
    &pha,     /* 0x48 */
    &eorImm,  /* 0x49 */
    &lsrAcc,  /* 0x4A */
    NULL,     /* 0x4B */
    &jmpAbsl, /* 0x4C */
    &eorAbsl, /* 0x4D */
    &lsrAbsl, /* 0x4E */
    NULL,     /* 0x4F */
    &bvc,     /* 0x50 */
    &eorIdy,  /* 0x51 */
    NULL,     /* 0x52 */
    NULL,     /* 0x53 */
    NULL,     /* 0x54 */
    &eorZpx,  /* 0x55 */
    &lsrZpx,  /* 0x56 */
    NULL,     /* 0x57 */
    &cli,     /* 0x58 */
    &eorAby,  /* 0x59 */
    NULL,     /* 0x5A */
    NULL,     /* 0x5B */
    NULL,     /* 0x5C */
    &eorAbx,  /* 0x5D */
    &lsrAbx,  /* 0x5E */
    NULL,     /* 0x5F */
    &rts,     /* 0x60 */
    &adcIdx,  /* 0x61 */
    NULL,     /* 0x62 */
    NULL,     /* 0x63 */
    NULL,     /* 0x64 */
    &adcZp,   /* 0x65 */
    &rorZp,   /* 0x66 */
    NULL,     /* 0x67 */
    &pla,     /* 0x68 */
    &adcImm,  /* 0x69 */
    &rorAcc,  /* 0x6A */
    NULL,     /* 0x6B */
    &jmpInd,  /* 0x6C */
    &adcAbsl, /* 0x6D */
    &rorAbsl, /* 0x6E */
    NULL,     /* 0x6F */
    &bvs,     /* 0x70 */
    &adcIdy,  /* 0x71 */
    NULL,     /* 0x72 */
    NULL,     /* 0x73 */
    NULL,     /* 0x74 */
    &adcZpx,  /* 0x75 */
    &rorZpx,  /* 0x76 */
    NULL,     /* 0x77 */
    &sei,     /* 0x78 */
    &adcAby,  /* 0x79 */
    NULL,     /* 0x7A */
    NULL,     /* 0x7B */
    NULL,     /* 0x7C */
    &adcAbx,  /* 0x7D */
    &rorAbx,  /* 0x7E */
    NULL,     /* 0x7F */
    NULL,     /* 0x80 */
    &staIdx,  /* 0x81 */
    NULL,     /* 0x82 */
    NULL,     /* 0x83 */
    &styZp,   /* 0x84 */
    &staZp,   /* 0x85 */
    &stxZp,   /* 0x86 */
    NULL,     /* 0x87 */
    &dey,     /* 0x88 */
    NULL,     /* 0x89 */
    &txa,     /* 0x8A */
    NULL,     /* 0x8B */
    &styAbsl, /* 0x8C */
    &staAbsl, /* 0x8D */
    &stxAbsl, /* 0x8E */
    NULL,     /* 0x8F */
    &bcc,     /* 0x90 */
    &staIdy,  /* 0x91 */
    NULL,     /* 0x92 */
    NULL,     /* 0x93 */
    &styZpx,  /* 0x94 */
    &staZpx,  /* 0x95 */
    &stxZpy,  /* 0x96 */
    NULL,     /* 0x97 */
    &tya,     /* 0x98 */
    &staAby,  /* 0x99 */
    &txs,     /* 0x9A */
    NULL,     /* 0x9B */
    NULL,     /* 0x9C */
    &staAbx,  /* 0x9D */
    NULL,     /* 0x9E */
    NULL,     /* 0x9F */
    &ldyImm,  /* 0xA0 */
    &ldaIdx,  /* 0xA1 */
    &ldxImm,  /* 0xA2 */
    NULL,     /* 0xA3 */
    &ldyZp,   /* 0xA4 */
    &ldaZp,   /* 0xA5 */
    &ldxZp,   /* 0xA6 */
    NULL,     /* 0xA7 */
    &tay,     /* 0xA8 */
    &ldaImm,  /* 0xA9 */
    &tax,     /* 0xAA */
    NULL,     /* 0xAB */
    &ldyAbsl, /* 0xAC */
    &ldaAbsl, /* 0xAD */
    &ldxAbsl, /* 0xAE */
    NULL,     /* 0xAF */
    &bcs,     /* 0xB0 */
    &ldaIdy,  /* 0xB1 */
    NULL,     /* 0xB2 */
    NULL,     /* 0xB3 */
    &ldyZpx,  /* 0xB4 */
    &ldaZpx,  /* 0xB5 */
    &ldxZpy,  /* 0xB6 */
    NULL,     /* 0xB7 */
    &clv,     /* 0xB8 */
    &ldaAby,  /* 0xB9 */
    &tsx,     /* 0xBA */
    NULL,     /* 0xBB */
    &ldyAbx,  /* 0xBC */
    &ldaAbx,  /* 0xBD */
    &ldxAby,  /* 0xBE */
    NULL,     /* 0xBF */
    &cpyImm,  /* 0xC0 */
    &cmpIdx,  /* 0xC1 */
    NULL,     /* 0xC2 */
    NULL,     /* 0xC3 */
    &cpyZp,   /* 0xC4 */
    &cmpZp,   /* 0xC5 */
    &decZp,   /* 0xC6 */
    NULL,     /* 0xC7 */
    &iny,     /* 0xC8 */
    &cmpImm,  /* 0xC9 */
    &dex,     /* 0xCA */
    NULL,     /* 0xCB */
    &cpyAbsl, /* 0xCC */
    &cmpAbsl, /* 0xCD */
    &decAbsl, /* 0xCE */
    NULL,     /* 0xCF */
    &bne,     /* 0xD0 */
    &cmpIdy,  /* 0xD1 */
    NULL,     /* 0xD2 */
    NULL,     /* 0xD3 */
    NULL,     /* 0xD4 */
    &cmpZpx,  /* 0xD5 */
    &decZpx,  /* 0xD6 */
    NULL,     /* 0xD7 */
    &cld,     /* 0xD8 */
    &cmpAby,  /* 0xD9 */
    NULL,     /* 0xDA */
    NULL,     /* 0xDB */
    NULL,     /* 0xDC */
    &cmpAbx,  /* 0xDD */
    &decAbx,  /* 0xDE */
    NULL,     /* 0xDF */
    &cpxImm,  /* 0xE0 */
    &sbcIdx,  /* 0xE1 */
    NULL,     /* 0xE2 */
    NULL,     /* 0xE3 */
    &cpxZp,   /* 0xE4 */
    &sbcZp,   /* 0xE5 */
    &incZp,   /* 0xE6 */
    NULL,     /* 0xE7 */
    &inx,     /* 0xE8 */
    &sbcImm,  /* 0xE9 */
    &nop,     /* 0xEA */
    NULL,     /* 0xEB */
    &cpxAbsl, /* 0xEC */
    &sbcAbsl, /* 0xED */
    &incAbsl, /* 0xEE */
    NULL,     /* 0xEF */
    &beq,     /* 0xF0 */
    &sbcIdy,  /* 0xF1 */
    NULL,     /* 0xF2 */
    NULL,     /* 0xF3 */
    NULL,     /* 0xF4 */
    &sbcZpx,  /* 0xF5 */
    &incZpx,  /* 0xF6 */
    NULL,     /* 0xF7 */
    &sed,     /* 0xF8 */
    &sbcAby,  /* 0xF9 */
    NULL,     /* 0xFA */
    NULL,     /* 0xFB */
    NULL,     /* 0xFC */
    &sbcAbx,  /* 0xFD */
    &incAbx,  /* 0xFE */
    NULL      /* 0xFF */
};
