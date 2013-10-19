/////////////////////////////////////////////////////////////////////////////
//
// ASSEMBLER.H : Assembler interface
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

/////////////////////////////////////////////////////////////////////////////
class Assembler {
public:
	Assembler();
	~Assembler();

	int assemble(const char *filename);
private:
	void open(const char *filename);
	void close();

	FILE *m_pOut;	// output file pointer
};

#endif // __ASSEMBLER_H__
