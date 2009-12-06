/////////////////////////////////////////////////////////////////////////////
//
// CPU.H : Pixie VM CPU
//
// Copyright (c) 2006, Thomas A. Rieck, All Rights Reserved
//

#ifndef __CPU_H__
#define __CPU_H__

#define HIREG8(n)           (LOREG8((n >> 4)))
#define LOREG8(n)           (n & 7)

#define HIREG16(n)          (LOREG16((n >> 4)))
#define LOREG16(n)          (n & ((n&5) | ((~n&4) >> 1)))

#define NEG_FLAG            (0x80)
#define OVERFLOW_FLAG       (0x40)
#define BRK_FLAG            (0x08)
#define INT_DISABLE_FLAG    (0x04)
#define ZERO_FLAG           (0x02)
#define CARRY_FLAG          (0x01)

class CPU;
typedef auto_ptr<CPU> CPUPtr;

/////////////////////////////////////////////////////////////////////////////
class CPU 
{
// Construction / Destruction
private:
	CPU();
public:
	~CPU();

// Interface
public:
	static CPU *getInstance();

	void run();
	void reset();

	word getA();
	word getB();
	word getC();
	word getD();
	word getX();
	word getSP();
	word getIP();
	word getFL();

// Implementation
private:
	enum { NREGS = 8 };		// number of registers
	static CPUPtr instance;	// singleton instance
    word regs[NREGS];		// registers
	Memory *memory;			// memory
};
/////////////////////////////////////////////////////////////////////////////

#endif // __CPU_H__
