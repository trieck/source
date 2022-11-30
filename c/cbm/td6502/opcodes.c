/*
 * opcodes.c
 *
 * opcode definitions
 *
 */
#include "common.h"
#include "opcodes.h"

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

static const Instr adcAbsl = { ADC, absl };
static const Instr adcAbx = { ADC, abx };
static const Instr adcAby = { ADC, aby };
static const Instr adcIdx = { ADC, idx };
static const Instr adcIdy = { ADC, idy };
static const Instr adcImm = { ADC, imm };
static const Instr adcZp = { ADC, zpg };
static const Instr adcZpx = { ADC, zpx };
static const Instr andAbsl = { AND, absl };
static const Instr andAbx = { AND, abx };
static const Instr andAby = { AND, aby };
static const Instr andIdx = { AND, idx };
static const Instr andIdy = { AND, idy };
static const Instr andImm = { AND, imm };
static const Instr andZp = { AND, zpg };
static const Instr andZpx = { AND, zpx };
static const Instr aslAbsl = { ASL, absl };
static const Instr aslAbx = { ASL, abx };
static const Instr aslAcc = { ASL, acc };
static const Instr aslZp = { ASL, zpg };
static const Instr aslZpx = { ASL, zpx };
static const Instr bcc = { BCC, rel };
static const Instr bcs = { BCS, rel };
static const Instr beq = { BEQ, rel };
static const Instr bitAbsl = { BIT, absl };
static const Instr bitZp = { BIT, zpg };
static const Instr bmi = { BMI, rel };
static const Instr bne = { BNE, rel };
static const Instr bpl = { BPL, rel };
static const Instr Brk = { BRK, imp };
static const Instr bvc = { BVC, rel };
static const Instr bvs = { BVS, rel };
static const Instr clc = { CLC, imp };
static const Instr cld = { CLD, imp };
static const Instr cli = { CLI, imp };
static const Instr clv = { CLV, imp };
static const Instr cmpAbsl = { CMP, absl };
static const Instr cmpAbx = { CMP, abx };
static const Instr cmpAby = { CMP, aby };
static const Instr cmpIdx = { CMP, idx };
static const Instr cmpIdy = { CMP, idy };
static const Instr cmpImm = { CMP, imm };
static const Instr cmpZp = { CMP, zpg };
static const Instr cmpZpx = { CMP, zpx };
static const Instr cpxAbsl = { CPX, absl };
static const Instr cpxImm = { CPX, imm };
static const Instr cpxZp = { CPX, zpg };
static const Instr cpyAbsl = { CPY, absl };
static const Instr cpyImm = { CPY, imm };
static const Instr cpyZp = { CPY, zpg };
static const Instr decAbsl = { DEC, absl };
static const Instr decAbx = { DEC, abx };
static const Instr decZp = { DEC, zpg };
static const Instr decZpx = { DEC, zpx };
static const Instr dex = { DEX, imp };
static const Instr dey = { DEY, imp };
static const Instr eorAbsl = { EOR, absl };
static const Instr eorAbx = { EOR, abx };
static const Instr eorAby = { EOR, aby };
static const Instr eorIdx = { EOR, idx };
static const Instr eorIdy = { EOR, idy };
static const Instr eorImm = { EOR, imm };
static const Instr eorZp = { EOR, zpg };
static const Instr eorZpx = { EOR, zpx };
static const Instr incAbsl = { INC, absl };
static const Instr incAbx = { INC, abx };
static const Instr incZp = { INC, zpg };
static const Instr incZpx = { INC, zpx };
static const Instr inx = { INX, imp };
static const Instr iny = { INY, imp };
static const Instr jmpAbsl = { JMP, absl };
static const Instr jmpInd = { JMP, ind };
static const Instr jsr = { JSR, absl };
static const Instr ldaAbsl = { LDA, absl };
static const Instr ldaAbx = { LDA, abx };
static const Instr ldaAby = { LDA, aby };
static const Instr ldaIdx = { LDA, idx };
static const Instr ldaIdy = { LDA, idy };
static const Instr ldaImm = { LDA, imm };
static const Instr ldaZp = { LDA, zpg };
static const Instr ldaZpx = { LDA, zpx };
static const Instr ldxAbsl = { LDX, absl };
static const Instr ldxAby = { LDX, aby };
static const Instr ldxImm = { LDX, imm };
static const Instr ldxZp = { LDX, zpg };
static const Instr ldxZpy = { LDX, zpy };
static const Instr ldyAbsl = { LDY, absl };
static const Instr ldyAbx = { LDY, abx };
static const Instr ldyImm = { LDY, imm };
static const Instr ldyZp = { LDY, zpg };
static const Instr ldyZpx = { LDY, zpx };
static const Instr lsrAbsl = { LSR, absl };
static const Instr lsrAbx = { LSR, abx };
static const Instr lsrAcc = { LSR, acc };
static const Instr lsrZp = { LSR, zpg };
static const Instr lsrZpx = { LSR, zpx };
static const Instr nop = { NOP, imp };
static const Instr oraAbsl = { ORA, absl };
static const Instr oraAbx = { ORA, abx };
static const Instr oraAby = { ORA, aby };
static const Instr oraIdx = { ORA, idx };
static const Instr oraIdy = { ORA, idy };
static const Instr oraImm = { ORA, imm };
static const Instr oraZp = { ORA, zpg };
static const Instr oraZpx = { ORA, zpx };
static const Instr pha = { PHA, imp };
static const Instr php = { PHP, imp };
static const Instr pla = { PLA, imp };
static const Instr plp = { PLP, imp };
static const Instr rolAbsl = { ROL, absl };
static const Instr rolAbx = { ROL, abx };
static const Instr rolAcc = { ROL, acc };
static const Instr rolZp = { ROL, zpg };
static const Instr rolZpx = { ROL, zpx };
static const Instr rorAbsl = { ROR, absl };
static const Instr rorAbx = { ROR, abx };
static const Instr rorAcc = { ROR, acc };
static const Instr rorZp = { ROR, zpg };
static const Instr rorZpx = { ROR, zpx };
static const Instr rti = { RTI, imp };
static const Instr rts = { RTS, imp };
static const Instr sbcAbsl = { SBC, absl };
static const Instr sbcAbx = { SBC, abx };
static const Instr sbcAby = { SBC, aby };
static const Instr sbcIdx = { SBC, idx };
static const Instr sbcIdy = { SBC, idy };
static const Instr sbcImm = { SBC, imm };
static const Instr sbcZp = { SBC, zpg };
static const Instr sbcZpx = { SBC, zpx };
static const Instr sec = { SEC, imp };
static const Instr sed = { SED, imp };
static const Instr sei = { SEI, imp };
static const Instr staAbsl = { STA, absl };
static const Instr staAbx = { STA, abx };
static const Instr staAby = { STA, aby };
static const Instr staIdx = { STA, idx };
static const Instr staIdy = { STA, idy };
static const Instr staZp = { STA, zpg };
static const Instr staZpx = { STA, zpg };
static const Instr stxAbsl = { STX, absl };
static const Instr stxZp = { STX, zpg };
static const Instr stxZpy = { STX, zpy };
static const Instr styAbsl = { STY, absl };
static const Instr styZp = { STY, zpg };
static const Instr styZpx = { STY, zpg };
static const Instr tax = { TAX, imp };
static const Instr tay = { TAY, imp };
static const Instr tsx = { TSX, imp };
static const Instr txa = { TXA, imp };
static const Instr txs = { TXS, imp };
static const Instr tya = { TYA, imp };

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
