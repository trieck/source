/////////////////////////////////////////////////////////////////////////////
//
//	6502.H : 6502 CPU Emulation
//
//	Copyright(c) 2003, Thomas A. Rieck
//

#ifndef __6502_H__
#define __6502_H__

/////////////////////////////////////////////////////////////////////////////
class CPU {

// Construction / Destruction
public:
	~CPU();
protected:
	CPU();

// Interface
public:
	static CPU* instance();	// singleton
	void SetA(BYTE b) {
		a = b;
	}
	void SetX(BYTE b) {
		x = b;
	}
	void SetY(BYTE b) {
		y = b;
	}
	void SetPCL(BYTE b) {
		pc |= b;
	}
	void SetPCH(BYTE b) {
		pc |= (b << 8);
	}
	void SetS(BYTE b) {
		s = b;
	}
	void SetP(BYTE b) {
		p = b;
	}

	// Registers
	BYTE GetA() {
		return a;
	}
	BYTE GetX() {
		return x;
	}
	BYTE GetY() {
		return y;
	}
	BYTE GetPCL() {
		return (BYTE)pc;
	}
	BYTE GetPCH() {
		return (BYTE)((pc & 0xFF00) >> 8);
	}
	BYTE GetS() {
		return s;
	}
	BYTE GetP() {
		return p;
	}

	// Flags
	int GetNeg() {
		return p & NFLAG;
	}
	int GetOverflow() {
		return p & VFLAG;
	}
	int GetUnused() {
		return p & UFLAG;
	}
	int GetBreak() {
		return p & BFLAG;
	}
	int GetDecimal() {
		return p & DFLAG;
	}
	int GetInterrupt() {
		return p & IFLAG;
	}
	int GetZero() {
		return p & ZFLAG;
	}
	int GetCarry() {
		return p & CFLAG;
	}

	void SetNeg() {
		p |= NFLAG;
	}
	void SetOverflow() {
		p |= VFLAG;
	}
	void SetUnused() {
		p |= UFLAG;
	}
	void SetBreak() {
		p |= BFLAG;
	}
	void SetDecimal() {
		p |= DFLAG;
	}
	void SetInterrupt() {
		p |= IFLAG;
	}
	void SetZero() {
		p |= ZFLAG;
	}
	void SetCarry() {
		p |= CFLAG;
	}

	void ClearNeg() {
		p &= ~NFLAG;
	}
	void ClearOverflow() {
		p &= ~VFLAG;
	}
	void ClearUnused() {
		p &= ~UFLAG;
	}
	void ClearBreak() {
		p &= ~BFLAG;
	}
	void ClearDecimal() {
		p &= ~DFLAG;
	}
	void ClearInterrupt() {
		p &= ~IFLAG;
	}
	void ClearZero() {
		p &= ~ZFLAG;
	}
	void ClearCarry() {
		p &= ~CFLAG;
	}

	void Reset();
	void Run();

// Implementation
private:
	enum Flags {
	    NFLAG = 1 << 7,
	    VFLAG = 1 << 6,
	    UFLAG = 1 << 5,
	    BFLAG = 1 << 4,
	    DFLAG = 1 << 3,
	    IFLAG = 1 << 2,
	    ZFLAG = 1 << 1,
	    CFLAG = 1 << 0
	};

	BYTE a, x, y, s, p;
	USHORT pc;
	ULONG clock;

	typedef std::auto_ptr<CPU> CPUPtr;
	static CPUPtr This;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __6502_H__
