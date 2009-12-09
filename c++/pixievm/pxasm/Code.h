/////////////////////////////////////////////////////////////////////////////
//
// CODE.H : Code generation
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __CODE_H__
#define __CODE_H__

class Code;
typedef auto_ptr<Code> CodePtr;

/////////////////////////////////////////////////////////////////////////////
class Code
{
private:
	Code();
public:
	~Code();

	static Code *getInstance();

	word getOrigin() const;
	void setOrigin(word origin);
	bool isOriginSet() const;

	void putWord(word w);
	void putByte(byte b);
	void putString(const string &str);

private:
	static CodePtr instance;	// singleton instance

	enum { MEMSIZE = 4096 };	// maximum code size
	
	word m_origin;				// assembly origin
	bool m_bOrigin;				// origin has been declared
	byte m_memory[MEMSIZE];		// memory
	byte *m_pmem;				// current memory pointer
};

/////////////////////////////////////////////////////////////////////////////
inline word Code::getOrigin() const { 
	return m_origin; 
}
	
/////////////////////////////////////////////////////////////////////////////
inline void Code::setOrigin(word origin) { 
	m_origin = origin; 
	m_bOrigin = true;
}

/////////////////////////////////////////////////////////////////////////////
inline bool Code::isOriginSet() const {
	return m_bOrigin;
}

#endif // __CODE_H__
