/////////////////////////////////////////////////////////////////////////////
//
// INVERTER.H
//
// Inverted list of term locations in memory
// Copyright (c) 2008 Thomas A. Rieck
//

#ifndef __INVERTER_H__
#define __INVERTER_H__

/////////////////////////////////////////////////////////////////////////////
class Inverter
{
// Construction / Destruction
public:
	Inverter();
	~Inverter();

	void insert(const char *term, uint32_t docid);
	uint32_t write(FILE *fp);
    bool isfull() const;	// check if full
    uint32_t getcount() const;
    
// Implementation
private:	
	uint32_t lookup(const char *term);
	void alloc(uint32_t i, const char *term);
	void realloc(uint32_t i);
	void clear();
	void compact();
		
	uint32_t count;			// number of entries
	uint32_t maxcount;		// maximum number of records
	uint32_t size;			// total records in table
	uint32_t maxpool;		// maximum ammount of pool memory allowed
	
	char **record;			// array of pointers to document lists
	char *pool;				// inverter allocation pool
	char *ppool;			// current allocation pointer	
};

/////////////////////////////////////////////////////////////////////////////
inline bool Inverter::isfull() const {
    return (count > maxcount || (uint32_t)(ppool-pool) > maxpool);
}

/////////////////////////////////////////////////////////////////////////////
inline uint32_t Inverter::getcount() const {
	return count;
}

#endif // __INVERTER_H__
