#include "Common.h"
#include "Opcodes.h"
#include "Modes.h"
#include "Instructions.h"

const byte opcodes[] = {
	ADC_RR8, ADC_RR16, ADC_RM8, ADC_RM16, ADC_RA8, ADC_RA16, 
	ADC_RI8, ADC_RI16, ADC_MR8, ADC_MR16, ADC_M8I8, ADC_M16I8, 
	ADC_MI16, ADC_AR8, ADC_AR16, ADC_A8I8, ADC_A16I8, ADC_AI16, 
	AND_RR8, AND_RR16, AND_RM8, AND_RM16, AND_RA8, AND_RA16, 
	AND_RI8, AND_RI16, AND_MR8, AND_MR16, AND_M8I8, AND_M16I8, 
	AND_MI16, AND_AR8, AND_AR16, AND_A8I8, AND_A16I8, AND_AI16, 
	BIT_RR8, BIT_RR16, BIT_RM8, BIT_RM16, BIT_RA8, BIT_RA16, 
	BIT_RI8, BIT_RI16, BIT_MR8, BIT_MR16, BIT_M8I8, BIT_M16I8, 
	BIT_MI16, BIT_AR8, BIT_AR16, BIT_A8I8, BIT_A16I8, BIT_AI16, 
	BRK, CALL_R16, CALL_M16, CALL_A16, CALL_I16, CLC, 
	CLI, CMP_RR8, CMP_RR16, CMP_RM8, CMP_RM16, CMP_RA8, 
	CMP_RA16, CMP_RI8, CMP_RI16, CMP_MR8, CMP_MR16, CMP_M8I8, 
	CMP_M16I8, CMP_MI16, CMP_AR8, CMP_AR16, CMP_A8I8, CMP_A16I8, 
	CMP_AI16, DEC_R8, DEC_R16, DEC_M8, DEC_M16, DEC_A8, 
	DEC_A16, DEX, INC_R8, INC_R16, INC_M8, INC_M16, 
	INC_A8, INC_A16, INX, IRET, JCC, JCS, 
	JMI, JMP_R16, JMP_M16, JMP_A16, JMP_I16, JNZ, 
	JPL, JVC, JVS, JZ, MOV_RR8, MOV_RR16, 
	MOV_RM8, MOV_RM16, MOV_RA8, MOV_RA16, MOV_RI8, MOV_RI16, 
	MOV_MR8, MOV_MR16, MOV_M8I8, MOV_M16I8, MOV_MI16, MOV_AR8, 
	MOV_AR16, MOV_A8I8, MOV_A16I8, MOV_AI16, NOP, OR_RR8, 
	OR_RR16, OR_RM8, OR_RM16, OR_RA8, OR_RA16, OR_RI8, 
	OR_RI16, OR_MR8, OR_MR16, OR_M8I8, OR_M16I8, OR_MI16, 
	OR_AR8, OR_AR16, OR_A8I8, OR_A16I8, OR_AI16, POP_R8, 
	POP_R16, POP_M8, POP_M16, POP_A8, POP_A16, POPA, 
	POPF, PUSH_R8, PUSH_R16, PUSH_M8, PUSH_M16, PUSH_A8, 
	PUSH_A16, PUSH_I8, PUSH_I16, PUSHA, PUSHF, RET, 
	ROL_R8, ROL_R16, ROL_M8, ROL_M16, ROL_A8, ROL_A16, 
	ROR_R8, ROR_R16, ROR_M8, ROR_M16, ROR_A8, ROR_A16, 
	SBB_RR8, SBB_RR16, SBB_RM8, SBB_RM16, SBB_RA8, SBB_RA16, 
	SBB_RI8, SBB_RI16, SBB_MR8, SBB_MR16, SBB_M8I8, SBB_M16I8, 
	SBB_MI16, SBB_AR8, SBB_AR16, SBB_A8I8, SBB_A16I8, SBB_AI16, 
	SEC, SEI, SHL_R8, SHL_R16, SHL_M8, SHL_M16, 
	SHL_A8, SHL_A16, SHR_R8, SHR_R16, SHR_M8, SHR_M16, 
	SHR_A8, SHR_A16, XOR_RR8, XOR_RR16, XOR_RM8, XOR_RM16, 
	XOR_RA8, XOR_RA16, XOR_RI8, XOR_RI16, XOR_MR8, XOR_MR16, 
	XOR_M8I8, XOR_M16I8, XOR_MI16, XOR_AR8, XOR_AR16, XOR_A8I8, 
	XOR_A16I8, XOR_AI16, 
};

const Instr INS_ADC = {
	&opcodes[0x00],	/* RR8 */
	&opcodes[0x01],	/* RR16 */
	&opcodes[0x02],	/* RM8 */
	&opcodes[0x03],	/* RM16 */
	&opcodes[0x04],	/* RA8 */
	&opcodes[0x05],	/* RA16 */
	&opcodes[0x06],	/* RI8 */
	&opcodes[0x07],	/* RI16 */
	&opcodes[0x08],	/* MR8 */
	&opcodes[0x09],	/* MR16 */
	&opcodes[0x0A],	/* M8I8 */
	&opcodes[0x0B],	/* M16I8 */
	&opcodes[0x0C],	/* MI16 */
	&opcodes[0x0D],	/* AR8 */
	&opcodes[0x0E],	/* AR16 */
	&opcodes[0x0F],	/* A8I8 */
	&opcodes[0x10],	/* A16I8 */
	&opcodes[0x11],	/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_AND = {
	&opcodes[0x12],	/* RR8 */
	&opcodes[0x13],	/* RR16 */
	&opcodes[0x14],	/* RM8 */
	&opcodes[0x15],	/* RM16 */
	&opcodes[0x16],	/* RA8 */
	&opcodes[0x17],	/* RA16 */
	&opcodes[0x18],	/* RI8 */
	&opcodes[0x19],	/* RI16 */
	&opcodes[0x1A],	/* MR8 */
	&opcodes[0x1B],	/* MR16 */
	&opcodes[0x1C],	/* M8I8 */
	&opcodes[0x1D],	/* M16I8 */
	&opcodes[0x1E],	/* MI16 */
	&opcodes[0x1F],	/* AR8 */
	&opcodes[0x20],	/* AR16 */
	&opcodes[0x21],	/* A8I8 */
	&opcodes[0x22],	/* A16I8 */
	&opcodes[0x23],	/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_BIT = {
	&opcodes[0x24],	/* RR8 */
	&opcodes[0x25],	/* RR16 */
	&opcodes[0x26],	/* RM8 */
	&opcodes[0x27],	/* RM16 */
	&opcodes[0x28],	/* RA8 */
	&opcodes[0x29],	/* RA16 */
	&opcodes[0x2A],	/* RI8 */
	&opcodes[0x2B],	/* RI16 */
	&opcodes[0x2C],	/* MR8 */
	&opcodes[0x2D],	/* MR16 */
	&opcodes[0x2E],	/* M8I8 */
	&opcodes[0x2F],	/* M16I8 */
	&opcodes[0x30],	/* MI16 */
	&opcodes[0x31],	/* AR8 */
	&opcodes[0x32],	/* AR16 */
	&opcodes[0x33],	/* A8I8 */
	&opcodes[0x34],	/* A16I8 */
	&opcodes[0x35],	/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_BRK = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	&opcodes[0x36],	/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_CALL = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	&opcodes[0x37],	/* R16 */
	NULL,			/* M8 */
	&opcodes[0x38],	/* M16 */
	NULL,			/* A8 */
	&opcodes[0x39],	/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	&opcodes[0x3A],	/* I16 */
};

const Instr INS_CLC = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	&opcodes[0x3B],	/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_CLI = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	&opcodes[0x3C],	/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_CMP = {
	&opcodes[0x3D],	/* RR8 */
	&opcodes[0x3E],	/* RR16 */
	&opcodes[0x3F],	/* RM8 */
	&opcodes[0x40],	/* RM16 */
	&opcodes[0x41],	/* RA8 */
	&opcodes[0x42],	/* RA16 */
	&opcodes[0x43],	/* RI8 */
	&opcodes[0x44],	/* RI16 */
	&opcodes[0x45],	/* MR8 */
	&opcodes[0x46],	/* MR16 */
	&opcodes[0x47],	/* M8I8 */
	&opcodes[0x48],	/* M16I8 */
	&opcodes[0x49],	/* MI16 */
	&opcodes[0x4A],	/* AR8 */
	&opcodes[0x4B],	/* AR16 */
	&opcodes[0x4C],	/* A8I8 */
	&opcodes[0x4D],	/* A16I8 */
	&opcodes[0x4E],	/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_DEC = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	&opcodes[0x4F],	/* R8 */
	&opcodes[0x50],	/* R16 */
	&opcodes[0x51],	/* M8 */
	&opcodes[0x52],	/* M16 */
	&opcodes[0x53],	/* A8 */
	&opcodes[0x54],	/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_DEX = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	&opcodes[0x55],	/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_INC = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	&opcodes[0x56],	/* R8 */
	&opcodes[0x57],	/* R16 */
	&opcodes[0x58],	/* M8 */
	&opcodes[0x59],	/* M16 */
	&opcodes[0x5A],	/* A8 */
	&opcodes[0x5B],	/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_INX = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	&opcodes[0x5C],	/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_IRET = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	&opcodes[0x5D],	/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_JCC = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	&opcodes[0x5E],	/* I8 */
	NULL,			/* I16 */
};

const Instr INS_JCS = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	&opcodes[0x5F],	/* I8 */
	NULL,			/* I16 */
};

const Instr INS_JMI = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	&opcodes[0x60],	/* I8 */
	NULL,			/* I16 */
};

const Instr INS_JMP = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	&opcodes[0x61],	/* R16 */
	NULL,			/* M8 */
	&opcodes[0x62],	/* M16 */
	NULL,			/* A8 */
	&opcodes[0x63],	/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	&opcodes[0x64],	/* I16 */
};

const Instr INS_JNZ = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	&opcodes[0x65],	/* I8 */
	NULL,			/* I16 */
};

const Instr INS_JPL = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	&opcodes[0x66],	/* I8 */
	NULL,			/* I16 */
};

const Instr INS_JVC = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	&opcodes[0x67],	/* I8 */
	NULL,			/* I16 */
};

const Instr INS_JVS = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	&opcodes[0x68],	/* I8 */
	NULL,			/* I16 */
};

const Instr INS_JZ = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	&opcodes[0x69],	/* I8 */
	NULL,			/* I16 */
};

const Instr INS_MOV = {
	&opcodes[0x6A],	/* RR8 */
	&opcodes[0x6B],	/* RR16 */
	&opcodes[0x6C],	/* RM8 */
	&opcodes[0x6D],	/* RM16 */
	&opcodes[0x6E],	/* RA8 */
	&opcodes[0x6F],	/* RA16 */
	&opcodes[0x70],	/* RI8 */
	&opcodes[0x71],	/* RI16 */
	&opcodes[0x72],	/* MR8 */
	&opcodes[0x73],	/* MR16 */
	&opcodes[0x74],	/* M8I8 */
	&opcodes[0x75],	/* M16I8 */
	&opcodes[0x76],	/* MI16 */
	&opcodes[0x77],	/* AR8 */
	&opcodes[0x78],	/* AR16 */
	&opcodes[0x79],	/* A8I8 */
	&opcodes[0x7A],	/* A16I8 */
	&opcodes[0x7B],	/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_NOP = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	&opcodes[0x7C],	/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_OR = {
	&opcodes[0x7D],	/* RR8 */
	&opcodes[0x7E],	/* RR16 */
	&opcodes[0x7F],	/* RM8 */
	&opcodes[0x80],	/* RM16 */
	&opcodes[0x81],	/* RA8 */
	&opcodes[0x82],	/* RA16 */
	&opcodes[0x83],	/* RI8 */
	&opcodes[0x84],	/* RI16 */
	&opcodes[0x85],	/* MR8 */
	&opcodes[0x86],	/* MR16 */
	&opcodes[0x87],	/* M8I8 */
	&opcodes[0x88],	/* M16I8 */
	&opcodes[0x89],	/* MI16 */
	&opcodes[0x8A],	/* AR8 */
	&opcodes[0x8B],	/* AR16 */
	&opcodes[0x8C],	/* A8I8 */
	&opcodes[0x8D],	/* A16I8 */
	&opcodes[0x8E],	/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_POP = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	&opcodes[0x8F],	/* R8 */
	&opcodes[0x90],	/* R16 */
	&opcodes[0x91],	/* M8 */
	&opcodes[0x92],	/* M16 */
	&opcodes[0x93],	/* A8 */
	&opcodes[0x94],	/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_POPA = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	&opcodes[0x95],	/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_POPF = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	&opcodes[0x96],	/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_PUSH = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	&opcodes[0x97],	/* R8 */
	&opcodes[0x98],	/* R16 */
	&opcodes[0x99],	/* M8 */
	&opcodes[0x9A],	/* M16 */
	&opcodes[0x9B],	/* A8 */
	&opcodes[0x9C],	/* A16 */
	NULL,			/* IMPLIED */
	&opcodes[0x9D],	/* I8 */
	&opcodes[0x9E],	/* I16 */
};

const Instr INS_PUSHA = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	&opcodes[0x9F],	/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_PUSHF = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	&opcodes[0xA0],	/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_RET = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	&opcodes[0xA1],	/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_ROL = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	&opcodes[0xA2],	/* R8 */
	&opcodes[0xA3],	/* R16 */
	&opcodes[0xA4],	/* M8 */
	&opcodes[0xA5],	/* M16 */
	&opcodes[0xA6],	/* A8 */
	&opcodes[0xA7],	/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_ROR = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	&opcodes[0xA8],	/* R8 */
	&opcodes[0xA9],	/* R16 */
	&opcodes[0xAA],	/* M8 */
	&opcodes[0xAB],	/* M16 */
	&opcodes[0xAC],	/* A8 */
	&opcodes[0xAD],	/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_SBB = {
	&opcodes[0xAE],	/* RR8 */
	&opcodes[0xAF],	/* RR16 */
	&opcodes[0xB0],	/* RM8 */
	&opcodes[0xB1],	/* RM16 */
	&opcodes[0xB2],	/* RA8 */
	&opcodes[0xB3],	/* RA16 */
	&opcodes[0xB4],	/* RI8 */
	&opcodes[0xB5],	/* RI16 */
	&opcodes[0xB6],	/* MR8 */
	&opcodes[0xB7],	/* MR16 */
	&opcodes[0xB8],	/* M8I8 */
	&opcodes[0xB9],	/* M16I8 */
	&opcodes[0xBA],	/* MI16 */
	&opcodes[0xBB],	/* AR8 */
	&opcodes[0xBC],	/* AR16 */
	&opcodes[0xBD],	/* A8I8 */
	&opcodes[0xBE],	/* A16I8 */
	&opcodes[0xBF],	/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_SEC = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	&opcodes[0xC0],	/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_SEI = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	&opcodes[0xC1],	/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_SHL = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	&opcodes[0xC2],	/* R8 */
	&opcodes[0xC3],	/* R16 */
	&opcodes[0xC4],	/* M8 */
	&opcodes[0xC5],	/* M16 */
	&opcodes[0xC6],	/* A8 */
	&opcodes[0xC7],	/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_SHR = {
	NULL,			/* RR8 */
	NULL,			/* RR16 */
	NULL,			/* RM8 */
	NULL,			/* RM16 */
	NULL,			/* RA8 */
	NULL,			/* RA16 */
	NULL,			/* RI8 */
	NULL,			/* RI16 */
	NULL,			/* MR8 */
	NULL,			/* MR16 */
	NULL,			/* M8I8 */
	NULL,			/* M16I8 */
	NULL,			/* MI16 */
	NULL,			/* AR8 */
	NULL,			/* AR16 */
	NULL,			/* A8I8 */
	NULL,			/* A16I8 */
	NULL,			/* AI16 */
	&opcodes[0xC8],	/* R8 */
	&opcodes[0xC9],	/* R16 */
	&opcodes[0xCA],	/* M8 */
	&opcodes[0xCB],	/* M16 */
	&opcodes[0xCC],	/* A8 */
	&opcodes[0xCD],	/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};

const Instr INS_XOR = {
	&opcodes[0xCE],	/* RR8 */
	&opcodes[0xCF],	/* RR16 */
	&opcodes[0xD0],	/* RM8 */
	&opcodes[0xD1],	/* RM16 */
	&opcodes[0xD2],	/* RA8 */
	&opcodes[0xD3],	/* RA16 */
	&opcodes[0xD4],	/* RI8 */
	&opcodes[0xD5],	/* RI16 */
	&opcodes[0xD6],	/* MR8 */
	&opcodes[0xD7],	/* MR16 */
	&opcodes[0xD8],	/* M8I8 */
	&opcodes[0xD9],	/* M16I8 */
	&opcodes[0xDA],	/* MI16 */
	&opcodes[0xDB],	/* AR8 */
	&opcodes[0xDC],	/* AR16 */
	&opcodes[0xDD],	/* A8I8 */
	&opcodes[0xDE],	/* A16I8 */
	&opcodes[0xDF],	/* AI16 */
	NULL,			/* R8 */
	NULL,			/* R16 */
	NULL,			/* M8 */
	NULL,			/* M16 */
	NULL,			/* A8 */
	NULL,			/* A16 */
	NULL,			/* IMPLIED */
	NULL,			/* I8 */
	NULL,			/* I16 */
};
