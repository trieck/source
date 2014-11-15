/////////////////////////////////////////////////////////////////////////////
//
//	MEMORY.CPP : Memory class
//
//	Copyright(c) 2003, Thomas A. Rieck
//

#include "stdafx.h"
#include "memory.h"

Memory::MemoryPtr Memory::This;

/////////////////////////////////////////////////////////////////////////////
Memory::Memory()
{
    memory = (LPBYTE)calloc(MEMSIZE, sizeof(BYTE));
}

/////////////////////////////////////////////////////////////////////////////
Memory::~Memory()
{
    free(memory);
}

/////////////////////////////////////////////////////////////////////////////
Memory* Memory::instance()
{
    if (This.get() == NULL) {
        This = MemoryPtr(new Memory());
    }
    return This.get();
}

/////////////////////////////////////////////////////////////////////////////
void Memory::Set(USHORT address, BYTE b)
{
    memory[address] = b;
}

/////////////////////////////////////////////////////////////////////////////
BYTE Memory::Get(USHORT address)
{
    return memory[address];
}