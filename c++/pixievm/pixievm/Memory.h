/////////////////////////////////////////////////////////////////////////////
//
// MEMORY.H : Pixie Virtual Machine Memory
//
// Copyright (c) 2006, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MEMORY_H__
#define __MEMORY_H__

class Memory;
typedef auto_ptr<Memory> MemoryPtr;

/////////////////////////////////////////////////////////////////////////////
class Memory {
// Construction / Destruction
private:
	Memory();
public:
	~Memory();

// Interface
	static Memory *getInstance();

	byte fetch(word address);
	void store(word address, byte b);
	bool load(istream &is, word base, int size);
	bool save(ostream &os, word base, int size);
private:
	enum { MEM_SIZE = 0x10000 };
	static MemoryPtr instance;		// singleton instance
	byte *memory;
};

#endif // __MEMORY_H__
