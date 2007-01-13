/////////////////////////////////////////////////////////////////////////////
//
// MINIDISASSEMBLER.CPP : Mini Disassembler
//
// Copyright (c) 2006, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Opinfo.h"
#include "Modes.h"
#include "Memory.h"
#include "MiniDisassembler.h"
#include "CPU.h"

namespace {	/* anonymous */

char *r8_tbl[] = {
	"al", "ah",
	"bl", "bh",
	"cl", "ch",
	"dl", "dh"
};

char *r16_tbl[] = {
	"a", "b", "c", "d", "x", "sp"
};

char *r16ex_tbl[] = {
	"a+x", "b+x", "c+x", "d+x", "x+x", "sp+x"
};

}	/* anonymous */

#define R16STR(n)	\
	((n & 8) ? r16ex_tbl[LOREG16(n)] : r16_tbl[LOREG16(n)])

/////////////////////////////////////////////////////////////////////////////
MiniDisassembler::MiniDisassembler() : init(false)
{
	mem = Memory::getInstance();	
}

/////////////////////////////////////////////////////////////////////////////
byte MiniDisassembler::fetch() 
{
	return mem->fetch(ip++);
}

/////////////////////////////////////////////////////////////////////////////
word MiniDisassembler::fetchWord() 
{
	return ((fetch() << 8) | fetch());
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::disassemble(word *start, word *end)
{	 
	word lastip = 0;
	if (start) {		/* start address supplied */
		ip = *start;
	} else if (!init) { /* not entered */
		ip = CPU::getInstance()->getIP(); 
		init = true; 
	}

	for (int i = 0; ip >= lastip && (end ? ip <= *end : i < 16); i++) {
		printip();
		lastip = ip;
		byte b = fetch();
		disassemble(b);
	}
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::printip()
{	
	printf("$%.4x ", ip);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::disassemble(byte b)
{
	LPOPINFO m = opinfo[b];
	printf("%.2x", b);

	if (m == NULL) {
		DB(b);
	} else {		
		switch (m->mode) {
		case AM_RR8:
			RR8(m);
			break;
		case AM_RR16:
			RR16(m);
			break;
		case AM_RM8:
			RM8(m);
			break;
		case AM_RM16:
			RM16(m);
			break;
		case AM_RA8:
			RA8(m);
			break;
		case AM_RA16:
			RA16(m);
			break;
		case AM_RI8:
			RI8(m);
			break;
		case AM_RI16:
			RI16(m);
			break;
		case AM_MR8:
			MR8(m);
			break;
		case AM_MR16:
			MR16(m);
			break;
		case AM_M8I8:
			M8I8(m);
			break;
		case AM_M16I8:
			M16I8(m);
			break;
		case AM_MI16:
			MI16(m);
			break;
		case AM_AR8:
			AR8(m);
			break;	
		case AM_AR16:
			AR16(m);
			break;
		case AM_A8I8:
			A8I8(m);
			break;
		case AM_A16I8:
			A16I8(m);
			break;
		case AM_AI16:
			AI16(m);
			break;
		case AM_R8:
			R8(m);
			break;
		case AM_R16:
			R16(m);
			break;
		case AM_M8:
			M8(m);
			break;
		case AM_M16:
			M16(m);
			break;
		case AM_A8:
			A8(m);
			break;
		case AM_A16:
			A16(m);
			break;
		case AM_IMPLIED:
			IMPLIED(m);
			break;
		case AM_I8:
			I8(m);
			break;
		case AM_I16:
			I16(m);
			break;		
		default:
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::DB(byte b)
{
	printf("             db $%.2x\n", b);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::RR8(LPOPINFO m)
{
	byte rp = fetch();
	char *hi = r8_tbl[HIREG8(rp)];
	char *lo = r8_tbl[LOREG8(rp)];
	printf(" %.2x          %s %s, %s\n", rp, *m->mnemonic, hi, lo);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::RR16(LPOPINFO m)
{
	byte rp = fetch();
	char *hi = r16_tbl[HIREG16(rp)];
	char *lo = r16_tbl[LOREG16(rp)];
	printf(" %.2x          %s %s, %s\n", rp, *m->mnemonic, hi, lo);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::RM8(LPOPINFO m)
{
	byte rp = fetch();
	char *hi = r8_tbl[HIREG8(rp)];
	char *lo = R16STR(LONIBBLE(rp));
	printf(" %.2x          %s %s, [%s]\n", rp, *m->mnemonic, hi, lo);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::RM16(LPOPINFO m)
{
	byte rp = fetch();
	char *hi = r16_tbl[HIREG16(rp)];
	char *lo = R16STR(LONIBBLE(rp));
	printf(" %.2x          %s %s, [%s]\n", rp, *m->mnemonic, hi, lo);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::RA8(LPOPINFO m)
{
	byte b = fetch();
	word a16 = fetchWord();
	char *r = r8_tbl[LOREG8(b)];		
	printf(" %.2x %.2x %.2x    %s %s, [$%.4x]\n", 
		b, HIBYTE(a16), LOBYTE(a16), *m->mnemonic, r, a16);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::RA16(LPOPINFO m)
{
	byte b = fetch();
	word a16 = fetchWord();
	char *r = r16_tbl[LOREG16(b)];		
	printf(" %.2x %.2x %.2x    %s %s, [$%.4x]\n", 
		b, HIBYTE(a16), LOBYTE(a16), *m->mnemonic, r, a16);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::RI8(LPOPINFO m)
{
	byte b = fetch();
	byte imm8 = fetch();
	char *r = r8_tbl[LOREG8(b)];		
	printf(" %.2x %.2x       %s %s, $%.2x\n", 
		b, imm8, *m->mnemonic, r, imm8);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::RI16(LPOPINFO m)
{
	byte b = fetch();
	word imm16 = fetchWord();
	char *r = r16_tbl[LOREG16(b)];		
	printf(" %.2x %.2x %.2x    %s %s, $%.4x\n", 
		b, HIBYTE(imm16), LOBYTE(imm16), *m->mnemonic, r, imm16);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::MR8(LPOPINFO m)
{
	byte rp = fetch();
	char *hi = R16STR(HINIBBLE(rp));
	char *lo = r8_tbl[LOREG8(rp)];
	printf(" %.2x          %s [%s], %s\n", rp, *m->mnemonic, hi, lo);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::MR16(LPOPINFO m)
{
	byte rp = fetch();
	char *hi = R16STR(HINIBBLE(rp));
	char *lo = r16_tbl[LOREG16(rp)];
	printf(" %.2x          %s [%s], %s\n", rp, *m->mnemonic, hi, lo);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::M8I8(LPOPINFO m)
{
	byte b = fetch();
	byte imm8 = fetch();
	char *r = R16STR(LONIBBLE(b));	
	printf(" %.2x %.2x       %s byte [%s], $%.2x\n", b, imm8, *m->mnemonic, r, imm8);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::M16I8(LPOPINFO m)
{
	byte b = fetch();
	byte imm8 = fetch();
	char *r = R16STR(LONIBBLE(b));
	printf(" %.2x %.2x       %s word [%s], $%.2x\n", b, imm8, *m->mnemonic, r, imm8);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::MI16(LPOPINFO m)
{
	byte b = fetch();
	word imm16 = fetchWord();
	char *r = R16STR(LONIBBLE(b));
	printf(" %.2x %.2x %.2x    %s [%s], $%.4x\n", b, HIBYTE(imm16), 
		LOBYTE(imm16), *m->mnemonic, r, imm16);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::AR8(LPOPINFO m)
{
	byte b = fetch();
	word a16 = fetchWord();
	char *r = r8_tbl[LOREG8(b)];	
	printf(" %.2x %.2x %.2x    %s [$%.4x], %s\n", b, HIBYTE(a16), 
		LOBYTE(a16), *m->mnemonic, a16, r);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::AR16(LPOPINFO m)
{
	byte b = fetch();
	word a16 = fetchWord();
	char *r = r16_tbl[LOREG16(b)];	
	printf(" %.2x %.2x %.2x    %s [$%.4x], %s\n", b, HIBYTE(a16), 
		LOBYTE(a16), *m->mnemonic, a16, r);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::A8I8(LPOPINFO m)
{
	byte imm8 = fetch();
	word a16 = fetchWord();
	printf(" %.2x %.2x %.2x    %s byte [$%.4x], $%.2x\n", imm8, HIBYTE(a16), 
		LOBYTE(a16), *m->mnemonic, a16, imm8);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::A16I8(LPOPINFO m)
{
	byte imm8 = fetch();
	word a16 = fetchWord();
	printf(" %.2x %.2x %.2x    %s word [$%.4x], $%.2x\n", imm8, HIBYTE(a16), 
		LOBYTE(a16), *m->mnemonic, a16, imm8);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::AI16(LPOPINFO m)
{
	word imm16 = fetchWord();
	word a16 = fetchWord();
	printf(" %.2x %.2x %.2x %.2x %s [$%.4x], $%.4x\n", 
		HIBYTE(imm16), LOBYTE(imm16), HIBYTE(a16), LOBYTE(a16), 
		*m->mnemonic, a16, imm16);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::R8(LPOPINFO m)
{
	byte b = fetch();
	char *r = r8_tbl[LOREG8(b)];
	printf(" %.2x          %s %s\n", b, *m->mnemonic, r);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::R16(LPOPINFO m)
{
	byte b = fetch();
	char *r = r16_tbl[LOREG16(b)];
	printf(" %.2x          %s %s\n", b, *m->mnemonic, r);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::M8(LPOPINFO m)
{
	byte b = fetch();
	char *r = R16STR(LONIBBLE(b));
	printf(" %.2x          %s byte [%s]\n", b, *m->mnemonic, r);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::M16(LPOPINFO m)
{
	byte b = fetch();
	char *r = R16STR(LONIBBLE(b));
	if (strcmp(*m->mnemonic, "call") == 0 || strcmp(*m->mnemonic, "jmp") == 0) {
		printf(" %.2x          %s [%s]\n", b, *m->mnemonic, r);
	} else {
		printf(" %.2x          %s word [%s]\n", b, *m->mnemonic, r);
	}
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::A8(LPOPINFO m)
{
	word a16 = fetchWord();
	printf(" %.2x %.2x       %s byte [$%.4x]\n", 
		HIBYTE(a16), LOBYTE(a16), *m->mnemonic, a16);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::A16(LPOPINFO m)
{
	word a16 = fetchWord();
	if (strcmp(*m->mnemonic, "call") == 0 || strcmp(*m->mnemonic, "jmp") == 0) {
		printf(" %.2x %.2x       %s [$%.4x]\n", 
			HIBYTE(a16), LOBYTE(a16), *m->mnemonic, a16);
	} else {
		printf(" %.2x %.2x       %s word [$%.4x]\n", 
			HIBYTE(a16), LOBYTE(a16), *m->mnemonic, a16);
	}
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::IMPLIED(LPOPINFO m)
{
	printf("             %s\n", *m->mnemonic);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::I8(LPOPINFO m)
{
	byte imm8 = fetch();
	printf(" %.2x          %s $%.2x\n", imm8, *m->mnemonic, imm8);
}

/////////////////////////////////////////////////////////////////////////////
void MiniDisassembler::I16(LPOPINFO m)
{
	word imm16 = fetchWord();
	printf(" %.2x %.2x       %s $%.4x\n", HIBYTE(imm16), 
		LOBYTE(imm16), *m->mnemonic, imm16);
}
