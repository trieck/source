/////////////////////////////////////////////////////////////////////////////
//
// PIXIEVM.H : Pixie virtual machine definitions
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __PIXIEVM_H__
#define __PIXIEVM_H__

// 8-bit registers
#define REG8_AL				(0x00)
#define REG8_AH				(0x01)
#define REG8_BL				(0x02)
#define REG8_BH				(0x03)
#define REG8_CL				(0x04)
#define REG8_CH				(0x05)
#define REG8_DL				(0x06)
#define REG8_DH				(0x07)

// 16-bit registers
#define REG16_A				(0x00)
#define REG16_B				(0x01)
#define REG16_C				(0x02)
#define REG16_D				(0x03)
#define REG16_X				(0x04)
#define REG16_SP			(0x05)

// CPU flags
#define NEG_FLAG            (0x80)
#define OVERFLOW_FLAG       (0x40)
#define BRK_FLAG            (0x08)
#define INT_DISABLE_FLAG    (0x04)
#define ZERO_FLAG           (0x02)
#define CARRY_FLAG          (0x01)

// register encoding
#define MAKEREG(hi, lo)		((hi << 4) | lo)

// 8-bit register decoding
#define HIREG8(n)           (LOREG8((n >> 4)))
#define LOREG8(n)           (n & 7)

// 16-bit register decoding
#define HIREG16(n)          (LOREG16((n >> 4)))
#define LOREG16(n)          (n & ((n&5) | ((~n&4) >> 1)))

// instruction opcode lookup by addressing mode
#define OPCODE(i, m)		(*(*i)[m])

#endif // __PIXIEVM_H__
