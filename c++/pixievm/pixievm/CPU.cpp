/////////////////////////////////////////////////////////////////////////////
//
// CPU.CPP : Pixie VM CPU
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "PixieVM.h"
#include "Memory.h"
#include "Interrupt.h"
#include "CPU.h"
#include "Opcodes.h"

#define IREG_A              (0)
#define IREG_B              (IREG_A + 1)
#define IREG_C              (IREG_B + 1)
#define IREG_D              (IREG_C + 1)
#define IREG_X				(IREG_D + 1)
#define IREG_SP             (IREG_X + 1)
#define IREG_IP             (IREG_SP + 1)
#define IREG_FL             (IREG_IP + 1)

#define REG_A               (regs[IREG_A])
#define REG_B               (regs[IREG_B])
#define REG_C               (regs[IREG_C])
#define REG_D               (regs[IREG_D])
#define REG_X               (regs[IREG_X])
#define REG_SP              (regs[IREG_SP])
#define REG_IP              (regs[IREG_IP])
#define REG_FL              (regs[IREG_FL])

#define RESET_VECTOR        0xFFFC
#define IRQ_VECTOR          0xFFFE

#define NEG_FLAG            (0x80)
#define OVERFLOW_FLAG       (0x40)
#define BRK_FLAG            (0x08)
#define INT_DISABLE_FLAG    (0x04)
#define ZERO_FLAG           (0x02)
#define CARRY_FLAG          (0x01)

#define GET_CARRY()         (REG_FL & CARRY_FLAG)
#define SET_CARRY(f)                    \
    do {                                \
        if (f) REG_FL |= CARRY_FLAG;    \
        else REG_FL &= ~CARRY_FLAG;     \
    } while (0)

#define GET_ZERO()          (REG_FL & ZERO_FLAG)
#define SET_ZERO(f)                     \
    do {                                \
        if (f) REG_FL |= ZERO_FLAG;     \
        else REG_FL &= ~ZERO_FLAG;      \
    } while (0)

#define GET_INT_DISABLE()   (REG_FL & INT_DISABLE_FLAG)
#define SET_INT_DISABLE(f)                  \
    do {                                    \
        if (f) REG_FL |= INT_DISABLE_FLAG;  \
        else REG_FL &= ~INT_DISABLE_FLAG;   \
    } while (0)

#define GET_BRK()           (REG_FL & BRK_FLAG)
#define SET_BRK(f)                      \
    do {                                \
        if (f) REG_FL |= BRK_FLAG;      \
        else REG_FL &= ~BRK_FLAG;       \
    } while (0)

#define GET_OVERFLOW()      (REG_FL & OVERFLOW_FLAG)
#define SET_OVERFLOW(f)                     \
    do {                                    \
        if (f) REG_FL |= OVERFLOW_FLAG;     \
        else REG_FL &= ~OVERFLOW_FLAG;      \
    } while (0)

#define GET_NEG()           (REG_FL & NEG_FLAG)
#define SET_NEG(f)                          \
    do {                                    \
        if (f) REG_FL |= NEG_FLAG;          \
        else REG_FL &= ~NEG_FLAG;           \
    } while (0)

#define SET_NZ8(val)                        \
    do {                                    \
        SET_NEG(val & NEG_FLAG);            \
        SET_ZERO(!(val & 0xFF));            \
    } while (0)

#define SET_NZ16(val)                       \
    do {                                    \
        SET_NEG(val & (NEG_FLAG << 8));     \
        SET_ZERO(!(val & 0xFFFF));          \
    } while (0)

#define FETCH(a)            (memory->fetch(a))
#define FETCH_WORD(a)       ((FETCH(a) << 8) | FETCH(a+1))

#define STORE(a, b)         (memory->store(a, b))
#define STORE_WORD(a, w)        \
    do {                        \
        STORE(a, HIBYTE(w));    \
        STORE(a+1, LOBYTE(w));  \
    } while (0)

#define R8PTR(n)            (((byte*)&regs[n])+(n&1))
#define R8VAL(n)            (*(R8PTR(n)))
#define R16PTR(n)           (&regs[n])
#define R16VAL(n)           (regs[n])

#define EFFADDRESS(n)       \
    (R16VAL(LOREG16(n)) + (REG_X >> ((~n&8) << 1)))

#define DO_ADC_RR8()                                    \
    do {                                                \
        byte rp = FETCH(REG_IP+1);                      \
        byte hi = HIREG8(rp);                           \
        byte lo = LOREG8(rp);                           \
        word w = R8VAL(hi) + R8VAL(lo) + GET_CARRY();   \
        SET_CARRY(w > 0xFF);                            \
        SET_NZ8(w);                                     \
		SET_OVERFLOW(((w ^ R8VAL(hi)) & NEG_FLAG) &&	\
			!((R8VAL(hi) ^ R8VAL(lo)) & NEG_FLAG));		\
        R8VAL(hi) = (byte)w;                            \
        REG_IP += 2;                                    \
    } while (0)

#define DO_ADC_RI8()                                    \
    do {                                                \
        byte r = LOREG8(FETCH(REG_IP + 1));             \
        byte imm8 = FETCH(REG_IP + 2);                  \
        word w = R8VAL(r) + imm8 + GET_CARRY();         \
        SET_CARRY(w > 0xFF);                            \
        SET_NZ8(w);                                     \
		SET_OVERFLOW(((w ^ R8VAL(r)) & NEG_FLAG) &&		\
			!((R8VAL(r) ^ imm8) & NEG_FLAG));			\
        R8VAL(r) = (byte)w;                             \
        REG_IP += 3;                                    \
    } while (0)

#define DO_ADC_RR16()											\
    do {														\
        byte rp = FETCH(REG_IP+1);								\
        byte hi = HIREG16(rp);									\
        byte lo = LOREG16(rp);									\
        dword dw = R16VAL(hi) + R16VAL(lo) + GET_CARRY();		\
        SET_CARRY(dw > 0xFFFF);									\
        SET_NZ16(dw);											\
		SET_OVERFLOW(((dw ^ R16VAL(hi)) & (NEG_FLAG << 8)) &&	\
			!((R16VAL(hi) ^ R16VAL(lo)) & (NEG_FLAG << 8)));	\
        R16VAL(hi) = (word)dw;									\
        REG_IP += 2;											\
    } while (0)

#define DO_ADC_MR8()									\
    do {												\
        byte rp = FETCH(REG_IP+1);						\
        byte hi = HINYBBLE(rp);							\
        byte lo = LOREG8(rp);							\
        word ad = EFFADDRESS(hi);						\
        byte m = FETCH(ad);								\
        word w = m + R8VAL(lo) + GET_CARRY();			\
        SET_CARRY(w > 0xFF);							\
        SET_NZ8(w);										\
		SET_OVERFLOW(((w ^ m) & NEG_FLAG) &&			\
			!((m ^ R8VAL(lo)) & NEG_FLAG));				\
        STORE(ad, (byte)w);								\
        REG_IP += 2;									\
    } while (0)

#define DO_ADC_MR16()									\
    do {												\
        byte rp = FETCH(REG_IP+1);						\
        byte hi = HINYBBLE(rp);							\
        byte lo = LOREG16(rp);							\
        word ad = EFFADDRESS(hi);						\
        word m = FETCH_WORD(ad);						\
        dword dw = m + R16VAL(lo) + GET_CARRY();		\
        SET_CARRY(dw > 0xFFFF);							\
        SET_NZ16(dw);									\
		SET_OVERFLOW(((dw ^ m) & (NEG_FLAG << 8)) &&	\
			!((m ^ R16VAL(lo)) & (NEG_FLAG << 8)));		\
        STORE_WORD(ad, (word)dw);						\
        REG_IP += 2;									\
    } while (0)

#define DO_ADC_M8I8()                           \
    do {                                        \
        byte r = LONYBBLE(FETCH(REG_IP + 1));   \
        byte imm8 = FETCH(REG_IP + 2);          \
        word ad = EFFADDRESS(r);                \
        byte m = FETCH(ad);                     \
        word w = m + imm8 + GET_CARRY();        \
        SET_CARRY(w > 0xFF);                    \
        SET_NZ8(w);                             \
		SET_OVERFLOW(((w ^ m) & NEG_FLAG) &&	\
			!((m ^ imm8) & NEG_FLAG));			\
        STORE(ad, (byte)w);                     \
        REG_IP += 3;                            \
    } while (0)

#define DO_ADC_M16I8()									\
    do {												\
        byte r = LONYBBLE(FETCH(REG_IP + 1));			\
        byte imm8 = FETCH(REG_IP + 2);					\
        word ad = EFFADDRESS(r);						\
        word m = FETCH_WORD(ad);						\
        dword dw = m + imm8 + GET_CARRY();				\
        SET_CARRY(dw > 0xFFFF);							\
        SET_NZ16(dw);									\
		SET_OVERFLOW(((dw ^ m) & (NEG_FLAG << 8)) &&	\
			!((m ^ imm8) & (NEG_FLAG << 8)));			\
        STORE_WORD(ad, (word)dw);						\
        REG_IP += 3;									\
    } while (0)

#define DO_ADC_MI16()									\
    do {												\
        byte r = LONYBBLE(FETCH(REG_IP + 1));			\
        word imm16 = FETCH_WORD(REG_IP + 2);			\
        word ad = EFFADDRESS(r);						\
        word m = FETCH_WORD(ad);						\
        dword dw = m + imm16 + GET_CARRY();				\
        SET_CARRY(dw > 0xFFFF);							\
        SET_NZ16(dw);									\
		SET_OVERFLOW(((dw ^ m) & (NEG_FLAG << 8)) &&	\
			!((m ^ imm16) & (NEG_FLAG << 8)));			\
        STORE_WORD(ad, (word)dw);						\
        REG_IP += 4;									\
    } while (0)

#define DO_ADC_AR8()                            \
    do {                                        \
        byte r = LOREG8(FETCH(REG_IP + 1));     \
        word ad = FETCH_WORD(REG_IP + 2);       \
        byte m = FETCH(ad);                     \
        word w = m + R8VAL(r) + GET_CARRY();    \
        SET_CARRY(w > 0xFF);                    \
        SET_NZ8(w);                             \
		SET_OVERFLOW(((w ^ m) & NEG_FLAG) &&	\
			!((m ^ R8VAL(r)) & NEG_FLAG));		\
        STORE(ad, (byte)w);                     \
        REG_IP += 4;                            \
    } while (0)

#define DO_ADC_AR16()									\
    do {												\
        byte r = LOREG16(FETCH(REG_IP + 1));			\
        word ad = FETCH_WORD(REG_IP + 2);				\
        word m = FETCH_WORD(ad);						\
        dword dw = m + R16VAL(r) + GET_CARRY();			\
        SET_CARRY(dw > 0xFFFF);							\
        SET_NZ16(dw);									\
		SET_OVERFLOW(((dw ^ m) & (NEG_FLAG << 8)) &&	\
			!((m ^ R16VAL(r)) & (NEG_FLAG << 8)));		\
        STORE_WORD(ad, (word)dw);						\
        REG_IP += 4;									\
    } while (0)

#define DO_ADC_A8I8()                           \
    do {                                        \
        byte imm8 = FETCH(REG_IP + 1);          \
        word ad = FETCH_WORD(REG_IP + 2);       \
        byte m = FETCH(ad);                     \
        word w = m + imm8 + GET_CARRY();        \
        SET_CARRY(w > 0xFF);                    \
        SET_NZ8(w);                             \
		SET_OVERFLOW(((w ^ m) & NEG_FLAG) &&	\
			!((m ^ imm8) & NEG_FLAG));			\
        STORE(ad, (byte)w);                     \
        REG_IP += 4;                            \
    } while (0)

#define DO_ADC_A16I8()									\
    do {												\
        byte imm8 = FETCH(REG_IP + 1);					\
        word ad = FETCH_WORD(REG_IP + 2);				\
        word m = FETCH_WORD(ad);						\
        dword dw = m + imm8 + GET_CARRY();				\
        SET_CARRY(dw > 0xFFFF);							\
        SET_NZ16(dw);									\
		SET_OVERFLOW(((dw ^ m) & (NEG_FLAG << 8)) &&	\
			!((m ^ imm8) & (NEG_FLAG << 8)));			\
        STORE_WORD(ad, (word)dw);						\
        REG_IP += 4;									\
    } while (0)

#define DO_ADC_AI16()									\
    do {												\
        word imm16 = FETCH_WORD(REG_IP + 1);			\
        word ad = FETCH_WORD(REG_IP + 3);				\
        word m = FETCH_WORD(ad);						\
        dword dw = m + imm16 + GET_CARRY();				\
        SET_CARRY(dw > 0xFFFF);							\
        SET_NZ16(dw);									\
		SET_OVERFLOW(((dw ^ m) & (NEG_FLAG << 8)) &&	\
			!((m ^ imm16) & (NEG_FLAG << 8)));			\
        STORE_WORD(ad, (word)dw);						\
        REG_IP += 5;									\
    } while (0)

#define DO_ADC_RM8()                            \
    do {                                        \
        byte rp = FETCH(REG_IP+1);              \
        byte hi = HIREG8(rp);                   \
        byte lo = LONYBBLE(rp);                 \
        word ad = EFFADDRESS(lo);               \
        byte m = FETCH(ad);                     \
        word w = m + R8VAL(hi) + GET_CARRY();   \
		SET_CARRY(w > 0xFF);                    \
        SET_NZ8(w);                             \
		SET_OVERFLOW(((w ^ m) & NEG_FLAG) &&	\
			!((m ^ R8VAL(hi)) & NEG_FLAG));		\
        R8VAL(hi) = (byte)w;                    \
        REG_IP += 2;                            \
    } while (0)

#define DO_ADC_RM16()									\
    do {												\
        byte rp = FETCH(REG_IP+1);						\
        byte hi = HIREG16(rp);							\
        byte lo = LONYBBLE(rp);							\
        word ad = EFFADDRESS(lo);						\
        word m = FETCH_WORD(ad);						\
        dword dw = m + R16VAL(hi) + GET_CARRY();		\
        SET_CARRY(dw > 0xFFFF);							\
        SET_NZ16(dw);									\
		SET_OVERFLOW(((dw ^ m) & (NEG_FLAG << 8)) &&	\
			!((m ^ R16VAL(hi)) & (NEG_FLAG << 8)));		\
        R16VAL(hi) = (word)dw;							\
        REG_IP += 2;									\
    } while (0)

#define DO_ADC_RA8()                            \
    do {                                        \
        byte r = LOREG8(FETCH(REG_IP + 1));     \
        word ad = FETCH_WORD(REG_IP + 2);       \
        byte m = FETCH(ad);                     \
        word w = m + R8VAL(r) + GET_CARRY();    \
        SET_CARRY(w > 0xFF);                    \
        SET_NZ8(w);                             \
		SET_OVERFLOW(((w ^ m) & NEG_FLAG) &&	\
			!((m ^ R8VAL(r)) & NEG_FLAG));		\
        R8VAL(r) = (byte)w;                     \
        REG_IP += 4;                            \
    } while (0)

#define DO_ADC_RA16()									\
    do {												\
        byte r = LOREG16(FETCH(REG_IP + 1));			\
        word ad = FETCH_WORD(REG_IP + 2);				\
        word m = FETCH_WORD(ad);						\
        dword dw = m + R16VAL(r) + GET_CARRY();			\
        SET_CARRY(dw > 0xFFFF);							\
        SET_NZ16(dw);									\
		SET_OVERFLOW(((dw ^ m) & (NEG_FLAG << 8)) &&	\
			!((m ^ R16VAL(r)) & (NEG_FLAG << 8)));		\
        R16VAL(r) = (word)dw;							\
        REG_IP += 4;									\
    } while (0)

#define DO_ADC_RI16()										\
    do {													\
        byte r = FETCH(REG_IP + 1);							\
        word imm16 = FETCH_WORD(REG_IP + 2);				\
        dword dw = R16VAL(r) + imm16 + GET_CARRY();			\
        SET_CARRY(dw > 0xFFFF);								\
        SET_NZ16(dw);										\
		SET_OVERFLOW(((dw ^ R16VAL(r)) & (NEG_FLAG << 8)) &&\
			!((R16VAL(r) ^ imm16) & (NEG_FLAG << 8)));		\
        R16VAL(r) = (word)dw;								\
        REG_IP += 4;										\
    } while (0)

#define DO_AND_RR8()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG8(rp);               \
        byte lo = LOREG8(rp);               \
        byte res = R8VAL(hi) & R8VAL(lo);   \
        SET_NZ8(res);                       \
        R8VAL(hi) = res;                    \
		SET_OVERFLOW(0);					\
        REG_IP += 2;                        \
    } while (0)

#define DO_AND_RI8()                        \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP + 1)); \
        byte imm8 = FETCH(REG_IP + 2);      \
        byte res = R8VAL(r) & imm8;         \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        R8VAL(r) = res;                     \
        REG_IP += 3;                        \
    } while (0)

#define DO_AND_RR16()                       \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG16(rp);              \
        byte lo = LOREG16(rp);              \
        word res = R16VAL(hi) & R16VAL(lo); \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        R16VAL(hi) = res;                   \
        REG_IP += 2;                        \
    } while (0)

#define DO_AND_MR8()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HINYBBLE(rp);             \
        byte lo = LOREG8(rp);               \
        word ad = EFFADDRESS(hi);           \
        byte m = FETCH(ad);                 \
        byte res = m & R8VAL(lo);           \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        STORE(ad, res);                     \
        REG_IP += 2;                        \
    } while (0)

#define DO_AND_MR16()                       \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HINYBBLE(rp);             \
        byte lo = LOREG16(rp);              \
        word ad = EFFADDRESS(hi);           \
        word m = FETCH_WORD(ad);            \
        word res = m & R16VAL(lo);          \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        STORE_WORD(ad, res);                \
        REG_IP += 2;                        \
    } while (0)

#define DO_AND_M8I8()                           \
    do {                                        \
        byte r = LONYBBLE(FETCH(REG_IP + 1));   \
        byte imm8 = FETCH(REG_IP + 2);          \
        word ad = EFFADDRESS(r);                \
        byte m = FETCH(ad);                     \
        byte res = m & imm8;                    \
        SET_NZ8(res);                           \
		SET_OVERFLOW(0);						\
        STORE(ad, res);                         \
        REG_IP += 3;                            \
    } while (0)

#define DO_AND_M16I8()                          \
    do {                                        \
        byte r = LONYBBLE(FETCH(REG_IP + 1));   \
        byte imm8 = FETCH(REG_IP + 2);          \
        word ad = EFFADDRESS(r);                \
        word m = FETCH(ad);                     \
        word res = m & imm8;                    \
        SET_NZ16(res);                          \
		SET_OVERFLOW(0);						\
        STORE_WORD(ad, res);                    \
        REG_IP += 3;                            \
    } while (0)

#define DO_AND_MI16()                           \
    do {                                        \
        byte r = LONYBBLE(FETCH(REG_IP + 1));   \
        word imm16 = FETCH(REG_IP + 2);         \
        word ad = EFFADDRESS(r);                \
        word m = FETCH(ad);                     \
        word res = m & imm16;                   \
        SET_NZ16(res);                          \
		SET_OVERFLOW(0);						\
        STORE_WORD(ad, res);                    \
        REG_IP += 4;                            \
    } while (0)

#define DO_AND_AR8()                            \
    do {                                        \
        byte r = LOREG8(FETCH(REG_IP + 1));     \
        word ad = FETCH_WORD(REG_IP + 2);       \
        byte m = FETCH(ad);                     \
        byte res = m & R8VAL(r);                \
        SET_NZ8(res);                           \
		SET_OVERFLOW(0);						\
        STORE(ad, res);                         \
        REG_IP += 4;                            \
    } while (0)

#define DO_AND_AR16()                           \
    do {                                        \
        byte r = LOREG16(FETCH(REG_IP + 1));    \
        word ad = FETCH_WORD(REG_IP + 2);       \
        word m = FETCH_WORD(ad);                \
        word res = m & R16VAL(r);               \
        SET_NZ16(res);                          \
		SET_OVERFLOW(0);						\
        STORE_WORD(ad, res);                    \
        REG_IP += 4;                            \
    } while (0)

#define DO_AND_A8I8()                           \
    do {                                        \
        byte imm8 = FETCH(REG_IP + 1);          \
        word ad = FETCH_WORD(REG_IP + 2);       \
        byte m = FETCH(ad);                     \
        byte res = m & imm8;                    \
        SET_NZ8(res);                           \
		SET_OVERFLOW(0);						\
        STORE(ad, res);                         \
        REG_IP += 4;                            \
    } while (0)

#define DO_AND_A16I8()                          \
    do {                                        \
        byte imm8 = FETCH(REG_IP + 1);          \
        word ad = FETCH_WORD(REG_IP + 2);       \
        word m = FETCH_WORD(ad);                \
        word res = m & imm8;                    \
        SET_NZ16(res);                          \
		SET_OVERFLOW(0);						\
        STORE_WORD(ad, res);                    \
        REG_IP += 4;                            \
    } while (0)

#define DO_AND_AI16()                           \
    do {                                        \
        byte imm16 = FETCH_WORD(REG_IP + 1);    \
        word ad = FETCH_WORD(REG_IP + 3);       \
        word m = FETCH_WORD(ad);                \
        word res = m & imm16;                   \
        SET_NZ16(res);                          \
		SET_OVERFLOW(0);						\
        STORE_WORD(ad, res);                    \
        REG_IP += 5;                            \
    } while (0)

#define DO_AND_RM8()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG8(rp);               \
        byte lo = LONYBBLE(rp);             \
        word ad = EFFADDRESS(lo);           \
        byte m = FETCH(ad);                 \
        byte res = m & R8VAL(hi);           \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        R8VAL(hi) = res;                    \
        REG_IP += 2;                        \
    } while (0)

#define DO_AND_RM16()                       \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG16(rp);              \
        byte lo = LONYBBLE(rp);             \
        word ad = EFFADDRESS(lo);           \
        word m = FETCH_WORD(ad);            \
        word res = m & R16VAL(hi);          \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        R16VAL(hi) = res;                   \
        REG_IP += 2;                        \
    } while (0)

#define DO_AND_RA8()                            \
    do {                                        \
        byte r = LOREG8(FETCH(REG_IP + 1));     \
        word ad = FETCH_WORD(REG_IP + 2);       \
        byte m = FETCH(ad);                     \
        byte res = m & R8VAL(r);                \
        SET_NZ8(res);                           \
		SET_OVERFLOW(0);						\
        R8VAL(r) = res;                         \
        REG_IP += 4;                            \
    } while (0)

#define DO_AND_RA16()                           \
    do {                                        \
        byte r = LOREG16(FETCH(REG_IP + 1));    \
        word ad = FETCH_WORD(REG_IP + 2);       \
        word m = FETCH_WORD(ad);                \
        word res = m & R16VAL(r);               \
        SET_NZ16(res);                          \
		SET_OVERFLOW(0);						\
        R16VAL(r) = res;                        \
        REG_IP += 4;                            \
    } while (0)

#define DO_AND_RI16()                           \
    do {                                        \
        byte r = LOREG16(FETCH(REG_IP + 1));    \
        word I16 = FETCH_WORD(REG_IP+2);        \
        word res = R16VAL(r) & I16;             \
        SET_NZ16(res);                          \
		SET_OVERFLOW(0);						\
        R16VAL(r) = res;                        \
        REG_IP += 4;                            \
    } while (0)

#define DO_BIT_RR8()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG8(rp);               \
        byte lo = LOREG8(rp);               \
        byte res = R8VAL(hi) & R8VAL(lo);   \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        REG_IP += 2;                        \
    } while (0)

#define DO_BIT_RI8()                        \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP + 1)); \
        byte imm8 = FETCH(REG_IP + 2);      \
        byte res = R8VAL(r) & imm8;         \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        REG_IP += 3;                        \
    } while (0)

#define DO_BIT_RR16()                       \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG16(rp);              \
        byte lo = LOREG16(rp);              \
        word res = R16VAL(hi) & R16VAL(lo); \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        REG_IP += 2;                        \
    } while (0)

#define DO_BIT_MR8()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HINYBBLE(rp);             \
        byte lo = LOREG8(rp);               \
        word ad = EFFADDRESS(hi);           \
        byte m = FETCH(ad);                 \
        byte res = m & R8VAL(lo);           \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        REG_IP += 2;                        \
    } while (0)

#define DO_BIT_MR16()                       \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HINYBBLE(rp);             \
        byte lo = LOREG16(rp);              \
        word ad = EFFADDRESS(hi);           \
        word m = FETCH_WORD(ad);            \
        word res = m & R16VAL(lo);          \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        REG_IP += 2;                        \
    } while (0)

#define DO_BIT_M8I8()                       \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        byte imm8 = FETCH(REG_IP + 2);      \
        word ad = EFFADDRESS(r);            \
        byte m = FETCH(ad);                 \
        byte res = m & imm8;                \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        REG_IP += 3;                        \
    } while (0)

#define DO_BIT_M16I8()                      \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        byte imm8 = FETCH(REG_IP + 2);      \
        word ad = EFFADDRESS(r);            \
        word m = FETCH_WORD(ad);            \
        word res = m & imm8;                \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        REG_IP += 3;                        \
    } while (0)

#define DO_BIT_MI16()                       \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        word imm16 = FETCH_WORD(REG_IP+2);  \
        word ad = EFFADDRESS(r);            \
        word m = FETCH_WORD(ad);            \
        word res = m & imm16;               \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        REG_IP += 4;                        \
    } while (0)

#define DO_BIT_AR8()                        \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP+1));   \
        word ad = FETCH_WORD(REG_IP + 2);   \
        byte m = FETCH(ad);                 \
        byte res = m & R8VAL(r);            \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        REG_IP += 4;                        \
    } while (0)

#define DO_BIT_AR16()                       \
    do {                                    \
        byte r = LOREG16(FETCH(REG_IP+1));  \
        word ad = FETCH_WORD(REG_IP + 2);   \
        word m = FETCH_WORD(ad);            \
        word res = m & R16VAL(r);           \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        REG_IP += 4;                        \
    } while (0)

#define DO_BIT_A8I8()                       \
    do {                                    \
        byte imm8 = FETCH(REG_IP + 1);      \
        word ad = FETCH_WORD(REG_IP + 2);   \
        byte m = FETCH(ad);                 \
        byte res = m & imm8;                \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        REG_IP += 4;                        \
    } while (0)

#define DO_BIT_A16I8()                      \
    do {                                    \
        byte imm8 = FETCH(REG_IP + 1);      \
        word ad = FETCH_WORD(REG_IP + 2);   \
        word m = FETCH_WORD(ad);            \
        word res = m & imm8;                \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        REG_IP += 4;                        \
    } while (0)

#define DO_BIT_AI16()                       \
    do {                                    \
        byte imm16 = FETCH_WORD(REG_IP+1);  \
        word ad = FETCH_WORD(REG_IP + 3);   \
        word m = FETCH_WORD(ad);            \
        word res = m & imm16;               \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        REG_IP += 5;                        \
    } while (0)

#define DO_BIT_RM8()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG8(rp);               \
        byte lo = LONYBBLE(rp);             \
        word ad = EFFADDRESS(lo);           \
        byte m = FETCH(ad);                 \
        byte res = m & R8VAL(hi);           \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        REG_IP += 2;                        \
    } while (0)

#define DO_BIT_RM16()                       \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG16(rp);              \
        byte lo = LONYBBLE(rp);             \
        word ad = EFFADDRESS(lo);           \
        word m = FETCH_WORD(ad);            \
        word res = m & R16VAL(hi);          \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        REG_IP += 2;                        \
    } while (0)

#define DO_BIT_RA8()                        \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP+1));   \
        word ad = FETCH_WORD(REG_IP+2);     \
        byte m = FETCH(ad);                 \
        byte res = m & R8VAL(r);            \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        REG_IP += 4;                        \
    } while (0)

#define DO_BIT_RA16()                       \
    do {                                    \
        byte r = LOREG16(FETCH(REG_IP+1));  \
        word ad = FETCH_WORD(REG_IP+2);     \
        word m = FETCH_WORD(ad);            \
        word res = m & R16VAL(r);           \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        REG_IP += 4;                        \
    } while (0)

#define DO_BIT_RI16()                           \
    do {                                        \
        byte r = LOREG16(FETCH(REG_IP + 1));    \
        word I16 = FETCH_WORD(REG_IP+2);        \
        word res = R16VAL(r) & I16;             \
        SET_NZ16(res);                          \
		SET_OVERFLOW(0);						\
        REG_IP += 4;                            \
    } while (0)

#define PUSH8(b)                            \
    do {                                    \
        STORE(REG_SP, b);                   \
        REG_SP--;                           \
    } while (0)

#define POP8()   (FETCH(++REG_SP))

#define PUSH16(w)                            \
    do {                                    \
        STORE_WORD(REG_SP, w);              \
        REG_SP -= 2;                        \
    } while (0)

#define POP16()   (FETCH_WORD(++(++REG_SP)))

#define DO_BRK()                            \
    do {                                    \
        PUSH16(REG_IP+2);                   \
        PUSH16(REG_FL);                     \
        SET_BRK(1);                         \
        SET_INT_DISABLE(1);                 \
        REG_IP = FETCH_WORD(IRQ_VECTOR);    \
    } while (0)

#define DO_CALL_R16()                       \
    do {                                    \
        byte r = LOREG16(FETCH(REG_IP+1));  \
        word ad = R16VAL(r);                \
        PUSH16(REG_IP + 2);                 \
        REG_IP = ad;                        \
    } while (0)                             \
 
#define DO_CALL_M16()                       \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        word ad = EFFADDRESS(r);            \
        PUSH16(REG_IP + 2);                 \
        REG_IP = ad;                        \
    } while (0)                             \
 
#define DO_CALL_A16()                       \
    do {                                    \
        word ad = FETCH_WORD(REG_IP + 1);   \
        word m = FETCH_WORD(ad);            \
        PUSH16(REG_IP + 2);                 \
        REG_IP = m;                         \
    } while (0)                             \
 
#define DO_CALL_I16()                       \
    do {                                    \
        word I16 = FETCH_WORD(REG_IP+1);    \
        PUSH16(REG_IP + 3);                 \
        REG_IP = I16;                       \
    } while (0)                             \
 
#define DO_CLC()                            \
    do {                                    \
        SET_CARRY(0);                       \
        REG_IP++;                           \
    } while (0)

#define DO_CLI()            \
    do {                    \
        SET_INT_DISABLE(0); \
        REG_IP++;           \
    } while (0)

#define DO_CMP_RR8()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG8(rp);               \
        byte lo = LOREG8(rp);               \
        word w = R8VAL(hi) - R8VAL(lo);     \
        SET_CARRY(w < 0x100);               \
        SET_NZ8(w);                         \
        REG_IP += 2;                        \
    } while (0)

#define DO_CMP_RI8()                        \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP + 1)); \
        byte imm8 = FETCH(REG_IP + 2);      \
        word w = R8VAL(r) - imm8;           \
        SET_CARRY(w < 0x100);               \
        SET_NZ8(w);                         \
        REG_IP += 3;                        \
    } while (0)

#define DO_CMP_RR16()                           \
    do {                                        \
        byte rp = FETCH(REG_IP+1);              \
        byte hi = HIREG16(rp);                  \
        byte lo = LOREG16(rp);                  \
        dword dw = R16VAL(hi) - R16VAL(lo);     \
        SET_CARRY(dw < 0x10000);                \
        SET_NZ16(dw);                           \
        REG_IP += 2;                            \
    } while (0)

#define DO_CMP_MR8()                            \
    do {                                        \
        byte rp = FETCH(REG_IP+1);              \
        byte hi = HINYBBLE(rp);                 \
        byte lo = LOREG8(rp);                   \
        word ad = EFFADDRESS(hi);               \
        byte m = FETCH(ad);                     \
        word w = m - R8VAL(lo);                 \
        SET_CARRY(w < 0x100);                   \
        SET_NZ8(w);                             \
        REG_IP += 2;                            \
    } while (0)

#define DO_CMP_MR16()                           \
    do {                                        \
        byte rp = FETCH(REG_IP+1);              \
        byte hi = HINYBBLE(rp);                 \
        byte lo = LOREG16(rp);                  \
        word ad = EFFADDRESS(hi);               \
        word m = FETCH_WORD(ad);                \
        dword dw = m - R16VAL(lo);              \
        SET_CARRY(dw < 0x10000);                \
        SET_NZ16(dw);                           \
        REG_IP += 2;                            \
    } while (0)

#define DO_CMP_M8I8()                           \
    do {                                        \
        byte r = LONYBBLE(FETCH(REG_IP+1));     \
        byte imm8 = FETCH(REG_IP + 2);          \
        word ad = EFFADDRESS(r);                \
        byte m = FETCH(ad);                     \
        word w = m - imm8;                      \
        SET_CARRY(w < 0x100);                   \
        SET_NZ8(w);                             \
        REG_IP += 3;                            \
    } while (0)

#define DO_CMP_M16I8()                          \
    do {                                        \
        byte r = LONYBBLE(FETCH(REG_IP+1));     \
        byte imm8 = FETCH(REG_IP + 2);          \
        word ad = EFFADDRESS(r);                \
        word m = FETCH_WORD(ad);                \
        dword dw = m - imm8;                    \
        SET_CARRY(dw < 0x10000);                \
        SET_NZ8(dw);                            \
        REG_IP += 3;                            \
    } while (0)

#define DO_CMP_MI16()                           \
    do {                                        \
        byte r = LONYBBLE(FETCH(REG_IP+1));     \
        word imm16 = FETCH_WORD(REG_IP + 2);    \
        word ad = EFFADDRESS(r);                \
        word m = FETCH_WORD(ad);                \
        dword dw = m - imm16;                   \
        SET_CARRY(dw < 0x10000);                \
        SET_NZ8(dw);                            \
        REG_IP += 4;                            \
    } while (0)

#define DO_CMP_AR8()                            \
    do {                                        \
        byte r = LOREG8(FETCH(REG_IP + 1));     \
        word ad = FETCH_WORD(REG_IP + 2);       \
        byte m = FETCH(ad);                     \
        word w = m - R8VAL(r);                  \
        SET_CARRY(w < 0x100);                   \
        SET_NZ8(w);                             \
        REG_IP += 4;                            \
    } while (0)

#define DO_CMP_AR16()                           \
    do {                                        \
        byte r = LOREG16(FETCH(REG_IP + 1));    \
        word ad = FETCH_WORD(REG_IP + 2);       \
        word m = FETCH_WORD(ad);                \
        dword dw = m - R16VAL(r);               \
        SET_CARRY(dw < 0x10000);                \
        SET_NZ16(dw);                           \
        REG_IP += 4;                            \
    } while (0)

#define DO_CMP_A8I8()                           \
    do {                                        \
        byte imm8 = FETCH(REG_IP + 1);          \
        word ad = FETCH_WORD(REG_IP + 2);       \
        byte m = FETCH(ad);                     \
        word w = m - imm8;                      \
        SET_CARRY(w < 0x100);                   \
        SET_NZ8(w);                             \
        REG_IP += 4;                            \
    } while (0)

#define DO_CMP_A16I8()                          \
    do {                                        \
        byte imm8 = FETCH(REG_IP + 1);          \
        word ad = FETCH_WORD(REG_IP + 2);       \
        word m = FETCH_WORD(ad);                \
        dword dw = m - imm8;                    \
        SET_CARRY(dw < 0x10000);                \
        SET_NZ16(dw);                           \
        REG_IP += 4;                            \
    } while (0)

#define DO_CMP_AI16()                           \
    do {                                        \
        word imm16 = FETCH_WORD(REG_IP + 1);    \
        word ad = FETCH_WORD(REG_IP + 3);       \
        word m = FETCH_WORD(ad);                \
        dword dw = m - imm16;                   \
        SET_CARRY(dw < 0x10000);                \
        SET_NZ16(dw);                           \
        REG_IP += 5;                            \
    } while (0)

#define DO_CMP_RM8()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG8(rp);               \
        byte lo = LONYBBLE(rp);             \
        word ad = EFFADDRESS(lo);           \
        byte m = FETCH(ad);                 \
        word w = m - R8VAL(hi);             \
        SET_CARRY(w < 0x100);               \
        SET_NZ8(w);                         \
        REG_IP += 2;                        \
    } while (0)

#define DO_CMP_RM16()                       \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG16(rp);              \
        byte lo = LONYBBLE(rp);             \
        word ad = EFFADDRESS(lo);           \
        word m = FETCH_WORD(ad);            \
        dword dw = m - R16VAL(hi);          \
        SET_CARRY(dw < 0x10000);            \
        SET_NZ16(dw);                       \
        REG_IP += 2;                        \
    } while (0)

#define DO_CMP_RA8()                        \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP+1));   \
        word ad = FETCH_WORD(REG_IP + 2);   \
        byte m = FETCH(ad);                 \
        word w = m - R8VAL(r);              \
        SET_CARRY(w < 0x100);               \
        SET_NZ8(w);                         \
        REG_IP += 4;                        \
    } while (0)

#define DO_CMP_RA16()                       \
    do {                                    \
        byte r = LOREG16(FETCH(REG_IP+1));  \
        word ad = FETCH_WORD(REG_IP + 2);   \
        word m = FETCH_WORD(ad);            \
        dword dw = m - R16VAL(r);           \
        SET_CARRY(dw < 0x10000);            \
        SET_NZ16(dw);                       \
        REG_IP += 4;                        \
    } while (0)

#define DO_CMP_RI16()                           \
    do {                                        \
        byte r = LOREG16(FETCH(REG_IP + 1));    \
        word I16 = FETCH_WORD(REG_IP+2);        \
        dword dw = R16VAL(r) - I16;             \
        SET_CARRY(dw < 0x10000);                \
        SET_NZ16(dw);                           \
        REG_IP += 4;                            \
    } while (0)

#define DO_DEC_R8()                         \
    do {                                    \
        byte r = FETCH(REG_IP+1);           \
        byte lo = LOREG8(r);                \
        R8VAL(lo)--;                        \
        SET_NZ8(R8VAL(lo));                 \
        REG_IP += 2;                        \
    } while (0)

#define DO_DEC_R16()                        \
    do {                                    \
        byte r = FETCH(REG_IP+1);           \
        byte lo = LOREG16(r);               \
        R16VAL(lo)--;                       \
        SET_NZ16(R16VAL(lo));               \
        REG_IP += 2;                        \
    } while (0)

#define DO_DEC_M8()                         \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        word ad = EFFADDRESS(r);            \
        byte m = FETCH(ad) - 1;             \
        SET_NZ8(m);                         \
        STORE(ad, m);                       \
        REG_IP += 2;                        \
    } while (0)

#define DO_DEC_M16()                        \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        word ad = EFFADDRESS(r);            \
        word m = FETCH_WORD(ad) - 1;        \
        SET_NZ16(m);                        \
        STORE_WORD(ad, m);                  \
        REG_IP += 2;                        \
    } while (0)

#define DO_DEC_A8()                         \
    do {                                    \
        word ad = FETCH_WORD(REG_IP + 2);   \
        byte m = FETCH(ad) - 1;             \
        SET_NZ8(m);                         \
        STORE(ad, m);                       \
        REG_IP += 3;                        \
    } while (0)

#define DO_DEC_A16()                        \
    do {                                    \
        word ad = FETCH_WORD(REG_IP + 2);   \
        word m = FETCH_WORD(ad) - 1;        \
        SET_NZ16(m);                        \
        STORE_WORD(ad, m);                  \
        REG_IP += 3;                        \
    } while (0)

#define DO_DEX()							\
	do {									\
		REG_X--;							\
        SET_NZ16(REG_X);					\
        REG_IP++;							\
	} while (0)

#define DO_INC_R8()                         \
    do {                                    \
        byte r = FETCH(REG_IP+1);           \
        byte lo = LOREG8(r);                \
        R8VAL(lo)++;                        \
        SET_NZ8(R8VAL(lo));                 \
        REG_IP += 2;                        \
    } while (0)

#define DO_INC_R16()                        \
    do {                                    \
        byte r = FETCH(REG_IP+1);           \
        byte lo = LOREG16(r);               \
        R16VAL(lo)++;                       \
        SET_NZ16(R16VAL(lo));               \
        REG_IP += 2;                        \
    } while (0)

#define DO_INC_M8()                         \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        word ad = EFFADDRESS(r);            \
        byte m = FETCH(ad) + 1;             \
        SET_NZ8(m);                         \
        STORE(ad, m);                       \
        REG_IP += 2;                        \
    } while (0)

#define DO_INC_M16()                        \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        word ad = EFFADDRESS(r);            \
        word m = FETCH_WORD(ad) + 1;        \
        SET_NZ16(m);                        \
        STORE_WORD(ad, m);                  \
        REG_IP += 2;                        \
    } while (0)

#define DO_INC_A8()                         \
    do {                                    \
        word ad = FETCH_WORD(REG_IP + 2);   \
        byte m = FETCH(ad) + 1;             \
        SET_NZ8(m);                         \
        STORE(ad, m);                       \
        REG_IP += 3;                        \
    } while (0)

#define DO_INC_A16()                        \
    do {                                    \
        word ad = FETCH_WORD(REG_IP + 2);   \
        word m = FETCH_WORD(ad) + 1;        \
        SET_NZ16(m);                        \
        STORE_WORD(ad, m);                  \
        REG_IP += 3;                        \
    } while (0)

#define DO_INX()							\
	do {									\
		REG_X++;							\
        SET_NZ16(REG_X);					\
        REG_IP++;							\
	} while (0)

#define DO_IRET()                           \
    do {                                    \
        REG_FL = POP16();                   \
        REG_IP = POP16();                   \
    } while (0)

#define BRANCH(cond, val)               \
    do {                                \
        if (cond) {                     \
            REG_IP += (signed char)val; \
        }                               \
    } while(0)

#define DO_JCC()                            \
    do {                                    \
        byte b = FETCH(REG_IP + 1);         \
        REG_IP += 2;                        \
        BRANCH(!GET_CARRY(), b);            \
    } while (0)

#define DO_JCS()                            \
    do {                                    \
        byte b = FETCH(REG_IP + 1);         \
        REG_IP += 2;                        \
        BRANCH(GET_CARRY(), b);             \
    } while (0)

#define DO_JMI()                            \
    do {                                    \
        byte b = FETCH(REG_IP + 1);         \
        REG_IP += 2;                        \
        BRANCH(GET_NEG(), b);               \
    } while (0)

#define DO_JPL()                            \
    do {                                    \
        byte b = FETCH(REG_IP + 1);         \
        REG_IP += 2;                        \
        BRANCH(!GET_NEG(), b);              \
    } while (0)

#define DO_JVC()                            \
    do {                                    \
        byte b = FETCH(REG_IP + 1);         \
        REG_IP += 2;                        \
        BRANCH(!GET_OVERFLOW(), b);         \
    } while (0)

#define DO_JVS()                            \
    do {                                    \
        byte b = FETCH(REG_IP + 1);         \
        REG_IP += 2;                        \
        BRANCH(GET_OVERFLOW(), b);          \
    } while (0)

#define DO_JMP_R16()                            \
    do {                                        \
        byte r = LOREG16(FETCH(REG_IP + 1));    \
        REG_IP = R16VAL(r);                     \
    } while (0)

#define DO_JMP_M16()                            \
    do {                                        \
        byte r = LONYBBLE(FETCH(REG_IP + 1));   \
        word m = FETCH_WORD(EFFADDRESS(r));     \
        REG_IP = m;                             \
    } while (0)

#define DO_JMP_A16()                            \
    do {                                        \
        word w = FETCH_WORD(REG_IP + 1);        \
        word ad = FETCH_WORD(w);                \
        REG_IP = ad;                            \
    } while (0)

#define DO_JMP_I16()                            \
    do {                                        \
        REG_IP = FETCH_WORD(REG_IP + 1);        \
    } while (0)

#define DO_JNZ()                            \
    do {                                    \
        byte b = FETCH(REG_IP + 1);         \
        REG_IP += 2;                        \
        BRANCH(!GET_ZERO(), b);             \
    } while (0)

#define DO_JZ()                             \
    do {                                    \
        byte b = FETCH(REG_IP + 1);         \
        REG_IP += 2;                        \
        BRANCH(GET_ZERO(), b);              \
    } while (0)

#define DO_MOV_RR8()                        \
    do {                                    \
        byte rp = FETCH(REG_IP + 1);        \
        byte hi = HIREG8(rp);               \
        byte lo = LOREG8(rp);               \
        R8VAL(hi) = R8VAL(lo);              \
        REG_IP += 2;                        \
    } while (0)

#define DO_MOV_RI8()                        \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP + 1)); \
        byte imm8 = FETCH(REG_IP + 2);      \
        R8VAL(r) = imm8;                    \
        REG_IP += 3;                        \
    } while (0)

#define DO_MOV_RR16()                       \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG16(rp);              \
        byte lo = LOREG16(rp);              \
        R16VAL(hi) = R16VAL(lo);            \
        REG_IP += 2;                        \
    } while (0)

#define DO_MOV_MR8()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HINYBBLE(rp);             \
        byte lo = LOREG8(rp);               \
        STORE(EFFADDRESS(hi), R8VAL(lo));   \
        REG_IP += 2;                        \
    } while (0)

#define DO_MOV_MR16()                           \
    do {                                        \
        byte rp = FETCH(REG_IP+1);              \
        byte hi = HINYBBLE(rp);                 \
        byte lo = LOREG16(rp);                  \
        STORE_WORD(EFFADDRESS(hi), R16VAL(lo)); \
        REG_IP += 2;                            \
    } while (0)

#define DO_MOV_M8I8()                       \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        byte imm8 = FETCH(REG_IP + 2);      \
        STORE(EFFADDRESS(r), imm8);         \
        REG_IP += 3;                        \
    } while (0)

#define DO_MOV_M16I8()                      \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        byte imm8 = FETCH(REG_IP + 2);      \
        STORE_WORD(EFFADDRESS(r), imm8);    \
        REG_IP += 3;                        \
    } while (0)

#define DO_MOV_MI16()                       \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        word imm16 = FETCH_WORD(REG_IP+2);  \
        STORE_WORD(EFFADDRESS(r), imm16);   \
        REG_IP += 4;                        \
    } while (0)

#define DO_MOV_AR8()                        \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP+1));   \
        word ad = FETCH_WORD(REG_IP+2);     \
        STORE(ad, R8VAL(r));                \
        REG_IP += 4;                        \
    } while(0)

#define DO_MOV_AR16()                       \
    do {                                    \
        byte r = LOREG16(FETCH(REG_IP+1));  \
        word ad = FETCH_WORD(REG_IP+2);     \
        STORE_WORD(ad, R16VAL(r));          \
        REG_IP += 4;                        \
    } while(0)

#define DO_MOV_A8I8()                       \
    do {                                    \
        byte imm8 = FETCH(REG_IP+1);        \
        word ad = FETCH_WORD(REG_IP+2);     \
        STORE(ad, imm8);                    \
        REG_IP += 4;                        \
    } while(0)

#define DO_MOV_A16I8()                      \
    do {                                    \
        byte imm8 = FETCH(REG_IP+1);        \
        word ad = FETCH_WORD(REG_IP+2);     \
        STORE_WORD(ad, imm8);               \
        REG_IP += 4;                        \
    } while (0)

#define DO_MOV_AI16()                       \
    do {                                    \
        word imm16 = FETCH_WORD(REG_IP+1);  \
        word ad = FETCH_WORD(REG_IP+3);     \
        STORE_WORD(ad, imm16);              \
        REG_IP += 5;                        \
    } while (0)

#define DO_MOV_RM8()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG8(rp);               \
        byte lo = LONYBBLE(rp);             \
        word ad = EFFADDRESS(lo);           \
        R8VAL(hi) = FETCH(ad);              \
        REG_IP += 2;                        \
    } while (0)

#define DO_MOV_RM16()                       \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG16(rp);              \
        byte lo = LONYBBLE(rp);             \
        word ad = EFFADDRESS(lo);           \
        R16VAL(hi) = FETCH_WORD(ad);        \
        REG_IP += 2;                        \
    } while (0)

#define DO_MOV_RA8()                        \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP+1));   \
        word ad = FETCH_WORD(REG_IP + 2);   \
        R8VAL(r) = FETCH(ad);               \
        REG_IP += 4;                        \
    } while (0)

#define DO_MOV_RA16()                       \
    do {                                    \
        byte r = LOREG16(FETCH(REG_IP+1));  \
        word ad = FETCH_WORD(REG_IP + 2);   \
        R16VAL(r) = FETCH_WORD(ad);         \
        REG_IP += 4;                        \
    } while (0)

#define DO_MOV_RI16()                           \
    do {                                        \
        byte r = LOREG16(FETCH(REG_IP + 1));    \
        word I16 = FETCH_WORD(REG_IP+2);        \
        R16VAL(r) = I16;                        \
        REG_IP += 4;                            \
    } while (0)

#define DO_NOP()    (REG_IP++)

#define DO_OR_RR8()                         \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG8(rp);               \
        byte lo = LOREG8(rp);               \
        byte res = R8VAL(hi) | R8VAL(lo);   \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        R8VAL(hi) = res;                    \
        REG_IP += 2;                        \
    } while (0)

#define DO_OR_RI8()                         \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP + 1)); \
        byte imm8 = FETCH(REG_IP + 2);      \
        byte res = R8VAL(r) | imm8;         \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        R8VAL(r) = res;                     \
        REG_IP += 3;                        \
    } while (0)

#define DO_OR_RR16()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG16(rp);              \
        byte lo = LOREG16(rp);              \
        word res = R16VAL(hi) | R16VAL(lo); \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        R16VAL(hi) = res;                   \
        REG_IP += 2;                        \
    } while (0)

#define DO_OR_MR8()                         \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HINYBBLE(rp);             \
        byte lo = LOREG8(rp);               \
        word ad = EFFADDRESS(hi);           \
        byte m = FETCH(ad);                 \
        byte res = m | R8VAL(lo);           \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        STORE(ad, res);                     \
        REG_IP += 2;                        \
    } while (0)

#define DO_OR_MR16()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HINYBBLE(rp);             \
        byte lo = LOREG16(rp);              \
        word ad = EFFADDRESS(hi);           \
        word m = FETCH_WORD(ad);            \
        word res = m | R16VAL(lo);          \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        STORE_WORD(ad, res);                \
        REG_IP += 2;                        \
    } while (0)

#define DO_OR_M8I8()                        \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        byte imm8 = FETCH(REG_IP + 2);      \
        word ad = EFFADDRESS(r);            \
        byte m = FETCH(ad);                 \
        byte res = m | imm8;                \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        STORE(ad, res);                     \
        REG_IP += 3;                        \
    } while (0)

#define DO_OR_M16I8()                       \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        byte imm8 = FETCH(REG_IP + 2);      \
        word ad = EFFADDRESS(r);            \
        word m = FETCH_WORD(ad);            \
        word res = m | imm8;                \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        STORE_WORD(ad, res);                \
        REG_IP += 3;                        \
    } while (0)

#define DO_OR_MI16()                        \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        word imm16 = FETCH_WORD(REG_IP+2);  \
        word ad = EFFADDRESS(r);            \
        word m = FETCH_WORD(ad);            \
        word res = m | imm16;               \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        STORE_WORD(ad, res);                \
        REG_IP += 4;                        \
    } while (0)

#define DO_OR_AR8()                             \
    do {                                        \
        byte r = LOREG8(FETCH(REG_IP + 1));     \
        word ad = FETCH(REG_IP + 2);            \
        byte m = FETCH(ad);                     \
        byte res = m | R8VAL(r);                \
        SET_NZ8(res);                           \
		SET_OVERFLOW(0);						\
        STORE(ad, res);                         \
        REG_IP += 4;                            \
    } while (0)

#define DO_OR_AR16()                            \
    do {                                        \
        byte r = LOREG16(FETCH(REG_IP + 1));    \
        word ad = FETCH(REG_IP + 2);            \
        word m = FETCH_WORD(ad);                \
        word res = m | R16VAL(r);               \
        SET_NZ16(res);                          \
		SET_OVERFLOW(0);						\
        STORE_WORD(ad, res);                    \
        REG_IP += 4;                            \
    } while (0)

#define DO_OR_A8I8()                            \
    do {                                        \
        byte imm8 = FETCH(REG_IP + 1);          \
        word ad = FETCH_WORD(REG_IP + 2);       \
        byte m = FETCH(ad);                     \
        byte res = m | imm8;                    \
        SET_NZ8(res);                           \
		SET_OVERFLOW(0);						\
        STORE(ad, res);                         \
        REG_IP += 4;                            \
    } while (0)

#define DO_OR_A16I8()                           \
    do {                                        \
        byte imm8 = FETCH(REG_IP + 1);          \
        word ad = FETCH_WORD(REG_IP + 2);       \
        word m = FETCH_WORD(ad);                \
        word res = m | imm8;                    \
        SET_NZ16(res);                          \
        STORE_WORD(ad, res);                    \
		SET_OVERFLOW(0);						\
        REG_IP += 4;                            \
    } while (0)

#define DO_OR_AI16()                            \
    do {                                        \
        word imm16 = FETCH_WORD(REG_IP + 1);    \
        word ad = FETCH_WORD(REG_IP + 3);       \
        word m = FETCH_WORD(ad);                \
        word res = m | imm16;                   \
        SET_NZ16(res);                          \
		SET_OVERFLOW(0);						\
        STORE_WORD(ad, res);                    \
        REG_IP += 5;                            \
    } while (0)

#define DO_OR_RM8()                         \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG8(rp);               \
        byte lo = LONYBBLE(rp);             \
        word ad = EFFADDRESS(lo);           \
        byte m = FETCH(ad);                 \
        byte res = m | R8VAL(hi);           \
        SET_NZ8(res);                       \
		SET_OVERFLOW(0);					\
        R8VAL(hi) = res;                    \
        REG_IP += 2;                        \
    } while (0)

#define DO_OR_RM16()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG16(rp);              \
        byte lo = LONYBBLE(rp);             \
        word ad = EFFADDRESS(lo);           \
        word m = FETCH_WORD(ad);            \
        word res = m | R16VAL(hi);          \
        SET_NZ16(res);                      \
		SET_OVERFLOW(0);					\
        R16VAL(hi) = res;                   \
        REG_IP += 2;                        \
    } while (0)

#define DO_OR_RA8()                             \
    do {                                        \
        byte r = LOREG8(FETCH(REG_IP + 1));     \
        word ad = FETCH_WORD(REG_IP + 2);       \
        byte m = FETCH(ad);                     \
        byte res = m | R8VAL(r);                \
        SET_NZ8(res);                           \
		SET_OVERFLOW(0);						\
        R8VAL(r) = res;                         \
        REG_IP += 4;                            \
    } while (0)

#define DO_OR_RA16()                            \
    do {                                        \
        byte r = LOREG16(FETCH(REG_IP + 1));    \
        word ad = FETCH_WORD(REG_IP + 2);       \
        word m = FETCH_WORD(ad);                \
        word res = m | R16VAL(r);               \
        SET_NZ16(res);                          \
		SET_OVERFLOW(0);						\
        R16VAL(r) = res;                        \
        REG_IP += 4;                            \
    } while (0)

#define DO_OR_RI16()                            \
    do {                                        \
        byte r = LOREG16(FETCH(REG_IP + 1));    \
        word I16 = FETCH_WORD(REG_IP+2);        \
        word res = R16VAL(r) | I16;             \
        SET_NZ16(res);                          \
		SET_OVERFLOW(0);						\
        R16VAL(r) = res;                        \
        REG_IP += 4;                            \
    } while (0)

#define DO_POP_R8()                             \
    do {                                        \
        byte r = LOREG16(FETCH(REG_IP + 1));    \
        R8VAL(r) = POP8();                      \
        REG_IP += 2;                            \
    } while (0)

#define DO_POP_R16()                            \
    do {                                        \
        byte r = LOREG16(FETCH(REG_IP + 1));    \
        R16VAL(r) = POP16();                    \
        REG_IP += 2;                            \
    } while (0)

#define DO_POP_M8()                             \
    do {                                        \
        byte r = LONYBBLE(FETCH(REG_IP + 1));   \
        word ad = EFFADDRESS(r);                \
        STORE(ad, POP8());                      \
        REG_IP += 2;                            \
    } while (0)

#define DO_POP_M16()                            \
    do {                                        \
        byte r = LONYBBLE(FETCH(REG_IP + 1));   \
        word ad = EFFADDRESS(r);                \
        STORE_WORD(ad, POP16());                \
        REG_IP += 2;                            \
    } while (0)

#define DO_POP_A8()                             \
    do {                                        \
        word ad = FETCH_WORD(REG_IP + 1);       \
        STORE(ad, POP8());                      \
        REG_IP += 3;                            \
    } while (0)

#define DO_POP_A16()                            \
    do {                                        \
        word ad = FETCH_WORD(REG_IP + 1);       \
        STORE_WORD(ad, POP16());                \
        REG_IP += 3;                            \
    } while (0)

#define DO_POPA()                               \
    do {                                        \
        REG_SP = POP16();                       \
		REG_X = POP16();						\
        REG_D = POP16();                        \
        REG_C = POP16();                        \
        REG_B = POP16();                        \
        REG_A = POP16();                        \
        REG_IP++;                               \
    } while (0)

#define DO_POPF()                               \
    do {                                        \
        REG_FL = POP16();                       \
        REG_IP++;                               \
    } while (0)

#define DO_PUSH_R8()                            \
    do {                                        \
        byte r = LOREG8(FETCH(REG_IP + 1));     \
        PUSH8(R8VAL(r));                        \
        REG_IP += 2;                            \
    } while (0)

#define DO_PUSH_R16()                           \
    do {                                        \
        byte r = LOREG16(FETCH(REG_IP + 1));    \
        PUSH16(R16VAL(r));                      \
        REG_IP += 2;                            \
    } while (0)

#define DO_PUSH_M8()                            \
    do {                                        \
        byte r = LONYBBLE(FETCH(REG_IP + 1));   \
        word ad = EFFADDRESS(r);                \
        PUSH8(FETCH(ad));                       \
        REG_IP += 2;                            \
    } while (0)

#define DO_PUSH_M16()                           \
    do {                                        \
        byte r = LONYBBLE(FETCH(REG_IP + 1));   \
        word ad = EFFADDRESS(r);                \
        PUSH16(FETCH_WORD(ad));                 \
        REG_IP += 2;                            \
    } while (0)

#define DO_PUSH_A8()                            \
    do {                                        \
        word ad = FETCH_WORD(REG_IP + 1);       \
        PUSH8(FETCH(ad));                       \
        REG_IP += 3;                            \
    } while (0)

#define DO_PUSH_A16()                           \
    do {                                        \
        word ad = FETCH_WORD(REG_IP + 1);       \
        PUSH16(FETCH_WORD(ad));                 \
        REG_IP += 3;                            \
    } while (0)

#define DO_PUSH_I8()                            \
    do {                                        \
        byte I8 = FETCH(REG_IP + 1);            \
        PUSH8(I8);                              \
        REG_IP += 2;                            \
    } while (0)

#define DO_PUSH_I16()                           \
    do {                                        \
        word I16 = FETCH_WORD(REG_IP + 1);      \
        PUSH16(I16);                            \
        REG_IP += 3;                            \
    } while (0)

#define DO_PUSHA()                              \
    do {                                        \
        PUSH16(REG_A);                          \
        PUSH16(REG_B);                          \
        PUSH16(REG_C);                          \
        PUSH16(REG_D);                          \
		PUSH16(REG_X);                          \
        PUSH16(REG_SP);                         \
        REG_IP++;                               \
    } while (0)

#define DO_PUSHF()                              \
    do {                                        \
        PUSH16(REG_FL);                         \
        REG_IP++;                               \
    } while (0)

#define DO_RET()                                \
    do {                                        \
        REG_IP = POP16();                       \
    } while (0)

#define DO_ROL_R8()                                 \
    do {                                            \
        byte r = LOREG8(FETCH(REG_IP+1));           \
        word res = (R8VAL(r) << 1) | GET_CARRY();   \
        R8VAL(r) = (byte)res;                       \
        SET_CARRY(res & 0x100);                     \
        SET_NZ8(res);                               \
        REG_IP += 2;                                \
    } while (0)

#define DO_ROL_R16()                                \
    do {                                            \
        byte r = LOREG16(FETCH(REG_IP+1));          \
        dword res = (R16VAL(r) << 1) | GET_CARRY(); \
        R16VAL(r) = (word)res;                      \
        SET_CARRY(res & 0x10000);                   \
        SET_NZ16(res);                              \
        REG_IP += 2;                                \
    } while (0)

#define DO_ROL_M8()                                 \
    do {                                            \
        byte r = LONYBBLE(FETCH(REG_IP+1));         \
        word ad = EFFADDRESS(r);                    \
        byte m = FETCH(ad);                         \
        word res = (m << 1) | GET_CARRY();          \
        STORE(ad, (byte)res);                       \
        SET_CARRY(res & 0x100);                     \
        SET_NZ8(res);                               \
        REG_IP += 2;                                \
    } while (0)

#define DO_ROL_M16()                                \
    do {                                            \
        byte r = LONYBBLE(FETCH(REG_IP+1));         \
        word ad = EFFADDRESS(r);                    \
        word m = FETCH_WORD(ad);                    \
        dword res = (m << 1) | GET_CARRY();         \
        STORE_WORD(ad, (word)res);                  \
        SET_CARRY(res & 0x10000);                   \
        SET_NZ16(res);                              \
        REG_IP += 2;                                \
    } while (0)

#define DO_ROL_A8()                                 \
    do {                                            \
        word ad = FETCH_WORD(REG_IP + 1);           \
        byte m = FETCH(ad);                         \
        word res = (m << 1) | GET_CARRY();          \
        STORE(ad, (byte)res);                       \
        SET_CARRY(res & 0x100);                     \
        SET_NZ8(res);                               \
        REG_IP += 3;                                \
    } while (0)

#define DO_ROL_A16()                                \
    do {                                            \
        word ad = FETCH_WORD(REG_IP + 1);           \
        word m = FETCH_WORD(ad);                    \
        dword res = (m << 1) | GET_CARRY();         \
        STORE_WORD(ad, (word)res);                  \
        SET_CARRY(res & 0x10000);                   \
        SET_NZ16(res);                              \
        REG_IP += 3;                                \
    } while (0)

#define DO_ROR_R8()                                 \
    do {                                            \
        byte r = LOREG8(FETCH(REG_IP+1));           \
        word res = (R8VAL(r) >> 1) | (REG_FL << 7); \
        SET_CARRY(R8VAL(r) & 0x01);                 \
        R8VAL(r) = (byte)res;                       \
        SET_NZ8(res);                               \
        REG_IP += 2;                                \
    } while (0)

#define DO_ROR_R16()                                    \
    do {                                                \
        byte r = LOREG16(FETCH(REG_IP+1));              \
        dword res = (R16VAL(r) >> 1) | (REG_FL << 15);  \
        SET_CARRY(R16VAL(r) & 0x01);                    \
        R16VAL(r) = (word)res;                          \
        SET_NZ16(res);                                  \
        REG_IP += 2;                                    \
    } while (0)

#define DO_ROR_M8()                                 \
    do {                                            \
        byte r = LONYBBLE(FETCH(REG_IP+1));         \
        word ad = EFFADDRESS(r);                    \
        byte m = FETCH(ad);                         \
        word res = (m >> 1) | (REG_FL << 7);        \
        SET_CARRY(m & 0x01);                        \
        STORE(ad, (byte)res);                       \
        SET_NZ8(res);                               \
        REG_IP += 2;                                \
    } while (0)

#define DO_ROR_M16()                                \
    do {                                            \
        byte r = LONYBBLE(FETCH(REG_IP+1));         \
        word ad = EFFADDRESS(r);                    \
        word m = FETCH_WORD(ad);                    \
        dword res = (m >> 1) | (REG_FL << 15);      \
        SET_CARRY(m & 0x01);                        \
        STORE_WORD(ad, (word)res);                  \
        SET_NZ16(res);                              \
        REG_IP += 2;                                \
    } while (0)

#define DO_ROR_A8()                                 \
    do {                                            \
        word ad = FETCH_WORD(REG_IP + 1);           \
        byte m = FETCH(ad);                         \
        word res = (m >> 1) | (REG_FL << 7);        \
        SET_CARRY(m & 0x01);                        \
        STORE(ad, (byte)res);                       \
        SET_NZ8(res);                               \
        REG_IP += 3;                                \
    } while (0)

#define DO_ROR_A16()                                \
    do {                                            \
        word ad = FETCH_WORD(REG_IP + 1);           \
        word m = FETCH_WORD(ad);                    \
        dword res = (m >> 1) | (REG_FL << 15);      \
        SET_CARRY(m & 0x01);                        \
        STORE_WORD(ad, (word)res);                  \
        SET_NZ16(res);                              \
        REG_IP += 3;                                \
    } while (0)

#define DO_SBB_RR8()                                            \
    do {                                                        \
        byte rp = FETCH(REG_IP+1);                              \
        byte hi = HIREG8(rp);                                   \
        byte lo = LOREG8(rp);                                   \
        word w = R8VAL(hi) - R8VAL(lo) - (GET_CARRY() ? 0 : 1); \
        SET_CARRY(w < 0x100);                                   \
        SET_NZ8(w);                                             \
		SET_OVERFLOW(((w ^ R8VAL(hi)) & NEG_FLAG) &&			\
			((R8VAL(hi) ^ R8VAL(lo)) & NEG_FLAG));				\
        R8VAL(hi) = (byte)w;                                    \
        REG_IP += 2;                                            \
    } while (0)

#define DO_SBB_RI8()                                            \
    do {                                                        \
        byte r = LOREG8(FETCH(REG_IP+1));                       \
        byte imm8 = FETCH(REG_IP+2);                            \
        word w = R8VAL(r) - imm8 - (GET_CARRY() ? 0 : 1);       \
        SET_CARRY(w < 0x100);                                   \
        SET_NZ8(w);                                             \
		SET_OVERFLOW(((w ^ R8VAL(r)) & NEG_FLAG) &&				\
			((R8VAL(r) ^ imm8) & NEG_FLAG));					\
        R8VAL(r) = (byte)w;                                     \
        REG_IP += 3;                                            \
    } while (0)

#define DO_SBB_RR16()                                               \
    do {                                                            \
        byte rp = FETCH(REG_IP+1);                                  \
        byte hi = HIREG16(rp);                                      \
        byte lo = LOREG16(rp);                                      \
        dword dw = R16VAL(hi) - R16VAL(lo) - (GET_CARRY() ? 0 : 1); \
        SET_CARRY(dw < 0x10000);                                    \
        SET_NZ16(dw);                                               \
		SET_OVERFLOW(((dw ^ R16VAL(hi)) & (NEG_FLAG << 8)) &&		\
			((R16VAL(hi) ^ R16VAL(lo)) & (NEG_FLAG << 8)));			\
        R16VAL(hi) = (word)dw;                                      \
        REG_IP += 2;                                                \
    } while (0)

#define DO_SBB_MR8()                                        \
    do {                                                    \
        byte rp = FETCH(REG_IP+1);                          \
        byte hi = HINYBBLE(rp);                             \
        byte lo = LOREG8(rp);                               \
        word ad = EFFADDRESS(hi);                           \
        byte m = FETCH(ad);                                 \
        word w = m - R8VAL(lo) - (GET_CARRY() ? 0 : 1);     \
        SET_CARRY(w < 0x100);                               \
        SET_NZ8(w);                                         \
		SET_OVERFLOW(((w ^ m) & NEG_FLAG) &&				\
			((m ^ R8VAL(lo)) & NEG_FLAG));					\
        STORE(ad, (byte)w);                                 \
        REG_IP += 2;                                        \
    } while (0)

#define DO_SBB_MR16()                                       \
    do {                                                    \
        byte rp = FETCH(REG_IP+1);                          \
        byte hi = HINYBBLE(rp);                             \
        byte lo = LOREG16(rp);                              \
        word ad = EFFADDRESS(hi);                           \
        word m = FETCH_WORD(ad);                            \
        dword dw = m - R16VAL(lo) - (GET_CARRY() ? 0 : 1);  \
        SET_CARRY(dw < 0x10000);                            \
        SET_NZ16(dw);                                       \
		SET_OVERFLOW(((dw ^ m) & (NEG_FLAG << 8)) &&		\
			((m ^ R16VAL(lo)) & (NEG_FLAG << 8)));			\
        STORE_WORD(ad, (word)dw);                           \
        REG_IP += 2;                                        \
    } while (0)

#define DO_SBB_M8I8()                                       \
    do {                                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1));                 \
        byte imm8 = FETCH(REG_IP+1);                        \
        word ad = EFFADDRESS(r);                            \
        byte m = FETCH(ad);                                 \
        word w = m - imm8 - (GET_CARRY() ? 0 : 1);          \
        SET_CARRY(w < 0x100);                               \
        SET_NZ8(w);                                         \
		SET_OVERFLOW(((w ^ m) & NEG_FLAG) &&				\
			((m ^ imm8) & NEG_FLAG));						\
        STORE(ad, (byte)w);                                 \
        REG_IP += 3;                                        \
    } while (0)

#define DO_SBB_M16I8()                                      \
    do {                                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1));                 \
        byte imm8 = FETCH(REG_IP+1);                        \
        word ad = EFFADDRESS(r);                            \
        word m = FETCH_WORD(ad);                            \
        dword dw = m - imm8 - (GET_CARRY() ? 0 : 1);        \
        SET_CARRY(dw < 0x10000);                            \
        SET_NZ16(dw);                                       \
		SET_OVERFLOW(((dw ^ m) & (NEG_FLAG << 8)) &&		\
			((m ^ imm8) & (NEG_FLAG << 8)));				\
        STORE_WORD(ad, (word)dw);                           \
        REG_IP += 3;                                        \
    } while (0)

#define DO_SBB_MI16()                                       \
    do {                                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1));                 \
        word imm16 = FETCH_WORD(REG_IP+1);                  \
        word ad = EFFADDRESS(r);                            \
        word m = FETCH_WORD(ad);                            \
        dword dw = m - imm16 - (GET_CARRY() ? 0 : 1);       \
        SET_CARRY(dw < 0x10000);                            \
        SET_NZ16(dw);                                       \
		SET_OVERFLOW(((dw ^ m) & (NEG_FLAG << 8)) &&		\
			((m ^ imm16) & (NEG_FLAG << 8)));				\
        STORE_WORD(ad, (word)dw);                           \
        REG_IP += 4;                                        \
    } while (0)

#define DO_SBB_AR8()                                        \
    do {                                                    \
        byte r = LOREG8(FETCH(REG_IP+1));                   \
        word ad = FETCH_WORD(REG_IP+2);                     \
        byte m = FETCH(ad);                                 \
        word w = m - R8VAL(r) - (GET_CARRY() ? 0 : 1);      \
        SET_CARRY(w < 0x100);                               \
        SET_NZ8(w);                                         \
		SET_OVERFLOW(((w ^ m) & NEG_FLAG) &&				\
			((m ^ R8VAL(r)) & NEG_FLAG));					\
        STORE(ad, (byte)w);                                 \
        REG_IP += 4;                                        \
    } while (0)

#define DO_SBB_AR16()                                       \
    do {                                                    \
        byte r = LOREG16(FETCH(REG_IP+1));                  \
        word ad = FETCH_WORD(REG_IP+2);                     \
        word m = FETCH_WORD(ad);                            \
        dword dw = m - R16VAL(r) - (GET_CARRY() ? 0 : 1);   \
        SET_CARRY(dw < 0x10000);                            \
        SET_NZ16(dw);                                       \
		SET_OVERFLOW(((dw ^ m) & (NEG_FLAG << 8)) &&		\
			((m ^ R16VAL(r)) & (NEG_FLAG << 8)));			\
        STORE_WORD(ad, (word)dw);                           \
        REG_IP += 4;                                        \
    } while (0)

#define DO_SBB_A8I8()                                       \
    do {                                                    \
        byte imm8 = FETCH(REG_IP+1);                        \
        word ad = FETCH_WORD(REG_IP+2);                     \
        byte m = FETCH(ad);                                 \
        word w = m - imm8 - (GET_CARRY() ? 0 : 1);          \
        SET_CARRY(w < 0x100);                               \
        SET_NZ8(w);                                         \
		SET_OVERFLOW(((w ^ m) & NEG_FLAG) &&				\
			((m ^ imm8) & NEG_FLAG));						\
        STORE(ad, (byte)w);                                 \
        REG_IP += 4;                                        \
    } while (0)

#define DO_SBB_A16I8()                                      \
    do {                                                    \
        byte imm8 = FETCH(REG_IP+1);                        \
        word ad = FETCH_WORD(REG_IP+2);                     \
        word m = FETCH_WORD(ad);                            \
        dword dw = m - imm8 - (GET_CARRY() ? 0 : 1);        \
        SET_CARRY(dw < 0x10000);                            \
        SET_NZ16(dw);                                       \
		SET_OVERFLOW(((dw ^ m) & (NEG_FLAG << 8)) &&		\
			((m ^ imm8) & (NEG_FLAG << 8)));				\
        STORE_WORD(ad, (word)dw);                           \
        REG_IP += 4;                                        \
    } while (0)

#define DO_SBB_AI16()                                       \
    do {                                                    \
        word imm16 = FETCH_WORD(REG_IP+1);                  \
        word ad = FETCH_WORD(REG_IP+3);                     \
        word m = FETCH_WORD(ad);                            \
        dword dw = m - imm16 - (GET_CARRY() ? 0 : 1);       \
        SET_CARRY(dw < 0x10000);                            \
        SET_NZ16(dw);                                       \
		SET_OVERFLOW(((dw ^ m) & (NEG_FLAG << 8)) &&		\
			((m ^ imm16) & (NEG_FLAG << 8)));				\
        STORE_WORD(ad, (word)dw);                           \
        REG_IP += 5;                                        \
    } while (0)

#define DO_SBB_RM8()                                        \
    do {                                                    \
        byte rp = FETCH(REG_IP+1);                          \
        byte hi = HIREG8(rp);                               \
        byte lo = LONYBBLE(rp);                             \
        word ad = EFFADDRESS(lo);                           \
        byte m = FETCH(ad);                                 \
        word w = R8VAL(hi) - m - (GET_CARRY() ? 0 : 1);     \
        SET_CARRY(w < 0x100);                               \
        SET_NZ8(w);                                         \
		SET_OVERFLOW(((w ^ R8VAL(hi)) & NEG_FLAG) &&		\
			((R8VAL(hi) ^ m) & NEG_FLAG));					\
        R8VAL(hi) = (byte)w;                                \
        REG_IP += 2;                                        \
    } while (0)

#define DO_SBB_RM16()											\
    do {														\
        byte rp = FETCH(REG_IP+1);								\
        byte hi = HIREG16(rp);									\
        byte lo = LONYBBLE(rp);									\
        word ad = EFFADDRESS(lo);								\
        word m = FETCH_WORD(ad);								\
        dword dw = R16VAL(hi) - m - (GET_CARRY() ? 0 : 1);		\
        SET_CARRY(dw < 0x10000);								\
        SET_NZ16(dw);											\
		SET_OVERFLOW(((dw ^ R16VAL(hi)) & (NEG_FLAG << 8)) &&	\
			((R16VAL(hi) ^ m) & (NEG_FLAG << 8)));				\
        R16VAL(hi) = (word)dw;									\
        REG_IP += 2;											\
    } while (0)

#define DO_SBB_RA8()                                        \
    do {                                                    \
        byte r = LOREG8(FETCH(REG_IP+1));                   \
        word ad = FETCH(REG_IP+2);                          \
        byte m = FETCH(ad);                                 \
        word w = R8VAL(r) - m - (GET_CARRY() ? 0 : 1);      \
        SET_CARRY(w < 0x100);                               \
        SET_NZ8(w);                                         \
		SET_OVERFLOW(((w ^ R8VAL(r)) & NEG_FLAG) &&			\
			((R8VAL(r) ^ m) & NEG_FLAG));					\
        R8VAL(r) = (byte)w;                                 \
        REG_IP += 4;                                        \
    } while (0)

#define DO_SBB_RA16()                                       \
    do {                                                    \
        byte r = LOREG16(FETCH(REG_IP+1));                  \
        word ad = FETCH(REG_IP+2);                          \
        word m = FETCH_WORD(ad);                            \
        dword dw = R16VAL(r) - m - (GET_CARRY() ? 0 : 1);   \
        SET_CARRY(dw < 0x10000);                            \
        SET_NZ16(dw);                                       \
		SET_OVERFLOW(((dw ^ R16VAL(r)) & (NEG_FLAG << 8)) &&\
			((R8VAL(r) ^ m) & (NEG_FLAG << 8)));			\
        R16VAL(r) = (word)dw;                               \
        REG_IP += 4;                                        \
    } while (0)

#define DO_SBB_RI16()                                           \
    do {                                                        \
        byte r = LOREG16(FETCH(REG_IP+1));                      \
        word imm16 = FETCH(REG_IP+2);                           \
        dword dw = R16VAL(r) - imm16 - (GET_CARRY() ? 0 : 1);   \
        SET_CARRY(dw < 0x10000);                                \
        SET_NZ16(dw);                                           \
		SET_OVERFLOW(((dw ^ R16VAL(r)) & (NEG_FLAG << 8)) &&	\
			((R16VAL(r) ^ imm16) & (NEG_FLAG << 8)));			\
        R16VAL(r) = (word)dw;                                   \
        REG_IP += 4;                                            \
    } while (0)

#define DO_SEC()                                                \
    do {                                                        \
        SET_CARRY(1);                                           \
        REG_IP++;                                               \
    } while (0)

#define DO_SEI()                                                \
    do {                                                        \
        SET_INT_DISABLE(1);                                     \
        REG_IP++;                                               \
    } while (0)

#define DO_SHL_R8()                         \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP+1));   \
        SET_CARRY(R8VAL(r) & 0x80);         \
        R8VAL(r) <<= 1;                     \
        SET_NZ8(R8VAL(r));                  \
        REG_IP += 2;                        \
    } while (0)

#define DO_SHL_R16()                        \
    do {                                    \
        byte r = LOREG16(FETCH(REG_IP+1));  \
        SET_CARRY(R16VAL(r) & 0x8000);      \
        R16VAL(r) <<= 1;                    \
        SET_NZ16(R16VAL(r));                \
        REG_IP += 2;                        \
    } while (0)

#define DO_SHL_M8()                         \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        word ad = EFFADDRESS(r);            \
        byte m = FETCH(ad);                 \
        SET_CARRY(m & 0x80);                \
        m <<= 1;                            \
        STORE(ad, m);                       \
        SET_NZ8(m);                         \
        REG_IP += 2;                        \
    } while (0)

#define DO_SHL_M16()                        \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        word ad = EFFADDRESS(r);            \
        word m = FETCH_WORD(ad);            \
        SET_CARRY(m & 0x8000);              \
        m <<= 1;                            \
        STORE_WORD(ad, m);                  \
        SET_NZ16(m);                        \
        REG_IP += 2;                        \
    } while (0)

#define DO_SHL_A8()                         \
    do {                                    \
        word ad = FETCH_WORD(REG_IP+1);     \
        byte m = FETCH(ad);                 \
        SET_CARRY(m & 0x80);                \
        m <<= 1;                            \
        STORE(ad, m);                       \
        SET_NZ8(m);                         \
        REG_IP += 4;                        \
    } while (0)

#define DO_SHL_A16()                        \
    do {                                    \
        word ad = FETCH_WORD(REG_IP+1);     \
        word m = FETCH_WORD(ad);            \
        SET_CARRY(m & 0x8000);              \
        m <<= 1;                            \
        STORE_WORD(ad, m);                  \
        SET_NZ16(m);                        \
        REG_IP += 4;                        \
    } while (0)

#define DO_SHR_R8()                         \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP+1));   \
        SET_CARRY(R8VAL(r) & 0x01);         \
        R8VAL(r) >>= 1;                     \
        SET_NZ8(R8VAL(r));                  \
        REG_IP += 2;                        \
    } while (0)

#define DO_SHR_R16()                        \
    do {                                    \
        byte r = LOREG16(FETCH(REG_IP+1));  \
        SET_CARRY(R16VAL(r) & 0x01);        \
        R16VAL(r) >>= 1;                    \
        SET_NZ16(R16VAL(r));                \
        REG_IP += 2;                        \
    } while (0)

#define DO_SHR_M8()                         \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        word ad = EFFADDRESS(r);            \
        byte m = FETCH(ad);                 \
        SET_CARRY(m & 0x01);                \
        m >>= 1;                            \
        STORE(ad, m);                       \
        SET_NZ8(m);                         \
        REG_IP += 2;                        \
    } while (0)

#define DO_SHR_M16()                        \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        word ad = EFFADDRESS(r);            \
        word m = FETCH_WORD(ad);            \
        SET_CARRY(m & 0x01);                \
        m >>= 1;                            \
        STORE_WORD(ad, m);                  \
        SET_NZ16(m);                        \
        REG_IP += 2;                        \
    } while (0)

#define DO_SHR_A8()                         \
    do {                                    \
        word ad = FETCH_WORD(REG_IP+1);     \
        byte m = FETCH(ad);                 \
        SET_CARRY(m & 0x01);                \
        m >>= 1;                            \
        STORE(ad, m);                       \
        SET_NZ8(m);                         \
        REG_IP += 4;                        \
    } while (0)

#define DO_SHR_A16()                        \
    do {                                    \
        word ad = FETCH_WORD(REG_IP+1);     \
        word m = FETCH_WORD(ad);            \
        SET_CARRY(m & 0x01);                \
        m >>= 1;                            \
        STORE_WORD(ad, m);                  \
        SET_NZ16(m);                        \
        REG_IP += 4;                        \
    } while (0)

#define DO_XOR_RR8()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG8(rp);               \
        byte lo = LOREG8(rp);               \
        R8VAL(hi) ^= R8VAL(lo);             \
        SET_NZ8(R8VAL(hi));                 \
        REG_IP += 2;                        \
    } while (0)

#define DO_XOR_RI8()                        \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP+1));   \
        byte imm8 = FETCH(REG_IP+2);        \
        R8VAL(r) ^= imm8;                   \
        SET_NZ8(R8VAL(r));                  \
        REG_IP += 3;                        \
    } while (0)

#define DO_XOR_RR16()                       \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG16(rp);              \
        byte lo = LOREG16(rp);              \
        R16VAL(hi) ^= R16VAL(lo);           \
        SET_NZ16(R16VAL(hi));               \
        REG_IP += 2;                        \
    } while (0)

#define DO_XOR_MR8()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HINYBBLE(rp);             \
        byte lo = LOREG8(rp);               \
        word ad = EFFADDRESS(hi);           \
        byte m = FETCH(ad);                 \
        m ^= R8VAL(lo);                     \
        SET_NZ8(m);                         \
        STORE(ad, m);                       \
        REG_IP += 2;                        \
    } while (0)

#define DO_XOR_MR16()                       \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HINYBBLE(rp);             \
        byte lo = LOREG16(rp);              \
        word ad = EFFADDRESS(hi);           \
        word m = FETCH_WORD(ad);            \
        m ^= R16VAL(lo);                    \
        SET_NZ16(m);                        \
        STORE_WORD(ad, m);                  \
        REG_IP += 2;                        \
    } while (0)

#define DO_XOR_M8I8()                       \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        byte imm8 = FETCH(REG_IP + 2);      \
        word ad = EFFADDRESS(r);            \
        byte m = FETCH(ad);                 \
        m ^= imm8;                          \
        SET_NZ8(m);                         \
        STORE(ad, m);                       \
        REG_IP += 3;                        \
    } while (0)

#define DO_XOR_M16I8()                      \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        byte imm8 = FETCH(REG_IP + 2);      \
        word ad = EFFADDRESS(r);            \
        word m = FETCH_WORD(ad);            \
        m ^= imm8;                          \
        SET_NZ16(m);                        \
        STORE_WORD(ad, m);                  \
        REG_IP += 3;                        \
    } while (0)

#define DO_XOR_MI16()                       \
    do {                                    \
        byte r = LONYBBLE(FETCH(REG_IP+1)); \
        word imm16 = FETCH_WORD(REG_IP+2);  \
        word ad = EFFADDRESS(r);            \
        word m = FETCH_WORD(ad);            \
        m ^= imm16;                         \
        SET_NZ16(m);                        \
        STORE_WORD(ad, m);                  \
        REG_IP += 4;                        \
    } while (0)

#define DO_XOR_AR8()                        \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP+1));   \
        word ad = FETCH_WORD(REG_IP+2);     \
        byte m = FETCH(ad);                 \
        m ^= R8VAL(r);                      \
        SET_NZ8(m);                         \
        STORE(ad, m);                       \
        REG_IP += 4;                        \
    } while (0)

#define DO_XOR_AR16()                       \
    do {                                    \
        byte r = LOREG16(FETCH(REG_IP+1));  \
        word ad = FETCH_WORD(REG_IP+2);     \
        word m = FETCH_WORD(ad);            \
        m ^= R16VAL(r);                     \
        SET_NZ16(m);                        \
        STORE_WORD(ad, m);                  \
        REG_IP += 4;                        \
    } while (0)

#define DO_XOR_A8I8()                       \
    do {                                    \
        byte imm8 = FETCH(REG_IP+1);        \
        word ad = FETCH_WORD(REG_IP+2);     \
        byte m = FETCH(ad);                 \
        m ^= imm8;                          \
        SET_NZ8(m);                         \
        STORE(ad, m);                       \
        REG_IP += 4;                        \
    } while (0)

#define DO_XOR_A16I8()                      \
    do {                                    \
        byte imm8 = FETCH(REG_IP+1);        \
        word ad = FETCH_WORD(REG_IP+2);     \
        word m = FETCH_WORD(ad);            \
        m ^= imm8;                          \
        SET_NZ16(m);                        \
        STORE_WORD(ad, m);                  \
        REG_IP += 4;                        \
    } while (0)

#define DO_XOR_AI16()                       \
    do {                                    \
        word imm16 = FETCH_WORD(REG_IP+1);  \
        word ad = FETCH_WORD(REG_IP+3);     \
        word m = FETCH_WORD(ad);            \
        m ^= imm16;                         \
        SET_NZ16(m);                        \
        STORE_WORD(ad, m);                  \
        REG_IP += 5;                        \
    } while (0)

#define DO_XOR_RM8()                        \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG8(rp);               \
        byte lo = LONYBBLE(rp);             \
        word ad = EFFADDRESS(lo);           \
        byte m = FETCH(ad);                 \
        R8VAL(hi) ^= m;                     \
        SET_NZ8(R8VAL(hi));                 \
        REG_IP += 2;                        \
    } while (0)

#define DO_XOR_RM16()                       \
    do {                                    \
        byte rp = FETCH(REG_IP+1);          \
        byte hi = HIREG16(rp);              \
        byte lo = LONYBBLE(rp);             \
        word ad = EFFADDRESS(lo);           \
        word m = FETCH_WORD(ad);            \
        R16VAL(hi) ^= m;                    \
        SET_NZ16(R16VAL(hi));               \
        REG_IP += 2;                        \
    } while (0)

#define DO_XOR_RA8()                        \
    do {                                    \
        byte r = LOREG8(FETCH(REG_IP+1));   \
        word ad = FETCH_WORD(REG_IP+2);     \
        byte m = FETCH(ad);                 \
        R8VAL(r) ^= m;                      \
        SET_NZ8(R8VAL(r));                  \
        REG_IP += 4;                        \
    } while (0)

#define DO_XOR_RA16()                       \
    do {                                    \
        byte r = LOREG16(FETCH(REG_IP+1));  \
        word ad = FETCH_WORD(REG_IP+2);     \
        word m = FETCH_WORD(ad);            \
        R16VAL(r) ^= m;                     \
        SET_NZ16(R16VAL(r));                \
        REG_IP += 4;                        \
    } while (0)

#define DO_XOR_RI16()                       \
    do {                                    \
        byte r = LOREG16(FETCH(REG_IP+1));  \
        word I16 = FETCH_WORD(REG_IP+2);    \
        R16VAL(r) ^= I16;                   \
        SET_NZ16(R16VAL(r));                \
        REG_IP += 4;                        \
    } while (0)

/////////////////////////////////////////////////////////////////////////////
CPUPtr CPU::instance(CPU::getInstance());

/////////////////////////////////////////////////////////////////////////////
CPU::CPU() : m_shutdown(false)
{
	memory = Memory::getInstance();
	REG_A = REG_B = REG_C = REG_D = REG_X = REG_SP = REG_IP = REG_FL = 0;
}

/////////////////////////////////////////////////////////////////////////////
CPU::~CPU()
{
}

/////////////////////////////////////////////////////////////////////////////
CPU *CPU::getInstance()
{
	if (instance.get() == NULL) {
		instance = CPUPtr(new CPU());
	}
	return instance.get();
}

/////////////////////////////////////////////////////////////////////////////
word CPU::getA() const
{
	return REG_A;
}

/////////////////////////////////////////////////////////////////////////////
word CPU::getB() const
{
	return REG_B;
}

/////////////////////////////////////////////////////////////////////////////
word CPU::getC() const
{
	return REG_C;
}

/////////////////////////////////////////////////////////////////////////////
word CPU::getD() const
{
	return REG_D;
}

/////////////////////////////////////////////////////////////////////////////
word CPU::getX() const
{
	return REG_X;
}

/////////////////////////////////////////////////////////////////////////////
word CPU::getSP() const
{
	return REG_SP;
}

/////////////////////////////////////////////////////////////////////////////
word CPU::getIP() const
{
	return REG_IP;
}

/////////////////////////////////////////////////////////////////////////////
word CPU::getFL() const
{
	return REG_FL;
}

/////////////////////////////////////////////////////////////////////////////
void CPU::setIP(word address)
{
	REG_IP = address;
}

void CPU::setShutdown(bool fShutdown)
{
	m_shutdown = fShutdown;
}

#define DO_INTERRUPT()										\
	do {													\
		int pending_interrupt = g_interrupt.getPending();	\
															\
		/* reset */											\
		if (pending_interrupt & IK_RESET) {					\
			g_interrupt.clearPending(IK_RESET);				\
			REG_IP = FETCH_WORD(RESET_VECTOR);				\
		}													\
															\
		/* trap */											\
		if (pending_interrupt & IK_TRAP) {					\
			g_interrupt.clearPending(IK_TRAP);				\
			g_interrupt.handleTrap();						\
		}													\
															\
		/* monitor */										\
		if (pending_interrupt & IK_MONITOR) {				\
			g_interrupt.clearPending(IK_MONITOR);			\
			g_interrupt.handleMonitor();					\
		}													\
	} while (0)

/////////////////////////////////////////////////////////////////////////////
void CPU::run()
{
	byte b;
	int pending_interrupt;

	reset();

	while (!m_shutdown) {

		pending_interrupt = g_interrupt.getPending();
		if (pending_interrupt != IK_NONE) {
			DO_INTERRUPT();
		}

		if (m_shutdown)
			break;

		b = FETCH(REG_IP);
		switch (b) {
#include "FetchEx.cpp"
		};
	}
}

/////////////////////////////////////////////////////////////////////////////
void CPU::reset()
{
	g_interrupt.setPending(IK_RESET);
}
