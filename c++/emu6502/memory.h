/////////////////////////////////////////////////////////////////////////////
//
//	MEMORY.H : Memory class
//
//	Copyright(c) 2003, Thomas A. Rieck
//

#ifndef __MEMORY_H__
#define __MEMORY_H__

/////////////////////////////////////////////////////////////////////////////
class Memory
{

// Construction / Destruction
public:
    ~Memory();
protected:
    Memory();

// Interface
public:
    static Memory* instance();	// singleton
    static UINT GetMemorySize()
    {
        return MEMSIZE;
    }

    void Set(USHORT address, BYTE b);
    BYTE Get(USHORT address);

// Implementation
private:
    enum { MEMSIZE = 1 << 16 };
    typedef std::auto_ptr<Memory> MemoryPtr;
    static MemoryPtr This;
    LPBYTE memory;
};

#endif // __MEMORY_H__