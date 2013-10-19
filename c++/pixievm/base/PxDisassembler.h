/////////////////////////////////////////////////////////////////////////////
//
// PXDISASSEMBLER.H : Abstract Pixie Disassembler
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __PXDISASSEMBLER_H__
#define __PXDISASSEMBLER_H__

#include "OpInfo.h"

/////////////////////////////////////////////////////////////////////////////
class PxDisassembler {
// Construction / Destruction
public:
	PxDisassembler();
	virtual ~PxDisassembler();

// Interface

// Implementation
protected:
	virtual byte fetch() = 0;
	word fetchWord();

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

	void printip();

	word ip;		// instruction pointer used during disassembly
};
/////////////////////////////////////////////////////////////////////////////

#endif // __PXDISASSEMBLER_H__
