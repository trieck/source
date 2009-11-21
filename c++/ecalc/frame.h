/////////////////////////////////////////////////////////////////////////////
//
// FRAME.H		procedure / function call frame stack
//
// Copyright (c) 1999 Thomas A. Rieck
//

#ifndef __FRAME_H__
#define __FRAME_H__

typedef struct {
	const Symbol *sp;	// symbol table entry
	const Instr *retpc;	// where to resume after return
	Datum * argn;		// n-th argument on the stack
	int nargs;			// number of arguments
} Frame;

#define NFRAME 1024

/////////////////////////////////////////////////////////////////////////////
class FrameStack {
public:
// Construction / Destruction
	FrameStack();
	~FrameStack();

// Interface
	Frame pop();
	void push(const Frame &);
	void reset();

	Frame * framep;
protected:
// Implementation
	Frame frame[NFRAME];
};

/////////////////////////////////////////////////////////////////////////////

#endif // __FRAME_H__

