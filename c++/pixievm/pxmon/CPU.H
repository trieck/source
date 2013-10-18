/////////////////////////////////////////////////////////////////////////////
//
// CPU.H : Pixie VM CPU
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __CPU_H__
#define __CPU_H__

#include "Memory.h"

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

	word getA() const;
	word getB() const;
	word getC() const;
	word getD() const;
	word getX() const;
	word getSP() const;
	word getIP() const;
	word getFL() const;

	byte getAL() const;
	byte getAH() const;
	byte getBL() const;
	byte getBH() const;
	byte getCL() const;
	byte getCH() const;
	byte getDL() const;
	byte getDH() const;

	void setA(word w);
	void setB(word w);
	void setC(word w);
	void setD(word w);
	void setX(word w);
	void setSP(word w);
	void setIP(word w);
	void setFL(word w);

	void setAL(byte b);
	void setAH(byte b);
	void setBL(byte b);
	void setBH(byte b);
	void setCL(byte b);
	void setCH(byte b);
	void setDL(byte b);
	void setDH(byte b);

	void push16(word w);
	word pop16();

	void setShutdown(bool f);

// Implementation
private:
	enum { NREGS = 8 };		// number of registers
	static CPUPtr instance;	// singleton instance
    word regs[NREGS];		// registers
	Memory *memory;			// memory
	bool m_shutdown;		// shut down flag
};
/////////////////////////////////////////////////////////////////////////////

#endif // __CPU_H__
