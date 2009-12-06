/////////////////////////////////////////////////////////////////////////////
//
// MINIDISASSEMBLER.H : Mini Disassembler
//
// Copyright (c) 2006, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MINIDISASSEMBLER_H__
#define __MINIDISASSEMBLER_H__

/////////////////////////////////////////////////////////////////////////////
class MiniDisassembler {
// Construction / Destruction
public:
	MiniDisassembler();

// Interface
	void disassemble(word *start, word *end);

// Implementation
private:
	void disassemble(byte b);
	void DB(byte b);

	void RR8(LPOPINFO m);
	void RR16(LPOPINFO m);
	void RM8(LPOPINFO m);
	void RM16(LPOPINFO m);
	void RA8(LPOPINFO m);
	void RA16(LPOPINFO m);
	void RI8(LPOPINFO m);
	void RI16(LPOPINFO m);
	void MR8(LPOPINFO m);
	void MR16(LPOPINFO m);
	void M8I8(LPOPINFO m);
	void M16I8(LPOPINFO m);
	void MI16(LPOPINFO m);
	void AR8(LPOPINFO m);
	void AR16(LPOPINFO m);
	void A8I8(LPOPINFO m);
	void A16I8(LPOPINFO m);
	void AI16(LPOPINFO m);
	void R8(LPOPINFO m);
	void R16(LPOPINFO m);
	void M8(LPOPINFO m);
	void M16(LPOPINFO m);
	void A8(LPOPINFO m);
	void A16(LPOPINFO m);
	void IMPLIED(LPOPINFO m);
	void I8(LPOPINFO m);
	void I16(LPOPINFO m);

	enum { NLINES = 16 };

	void printip();
	byte fetch();
	word fetchWord();

	word ip;		/* instruction pointer used during disassembly */
	bool init;		/* have we been entered ? */
	Memory *mem;	/* pointer to memory */
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MINIDISASSEMBLER_H__
