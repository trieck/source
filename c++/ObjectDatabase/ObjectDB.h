/////////////////////////////////////////////////////////////////////////////
//
// OBJECTDB.H : Object Database
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __OBJECTDB_H__
#define __OBJECTDB_H__

/////////////////////////////////////////////////////////////////////////////
class ObjectDB
{
	// Construction / Destruction
private:
	ObjectDB();
public:
	virtual ~ObjectDB();

	typedef auto_ptr<ObjectDB> ObjectDBPtr;

// Interface
	static ObjectDB *instance();
	
	LPCSTR MakePool();
	LPCSTR CreateObject(const string &poolid, int ntype, 
		LPSTRING pObjectID = NULL,
		LPBEOBJECT pValue = NULL);	

	LPBEOBJECT GetObject(const string &poolid,
		const string &objectid) const;

	BOOL SetObject(const string &poolid,
		const string &objectid,
		LPBEOBJECT pObject);

	BOOL DestroyObject(const string &poolid, const string &objectid);
		
	unsigned GetPoolCount() const { return pools.size(); }

// Implementation
private:
	LPCSTR Insert(const string &poolid, LPBEOBJECT pObject,
		LPSTRING pKey = NULL);
	static string NewKey();
	static LPBEOBJECT MakeObject(int ntype);

	typedef map<string, LPBEOBJECT> PoolMap;

	typedef struct Pool {
		Pool();
		~Pool();
		void Lock(); 
		void Unlock();
		CRITICAL_SECTION cs;	// critical section
		PoolMap entries;		// pool entries
	} *LPPOOL;

	typedef map<string, LPPOOL> Pools;

	LPPOOL GetPool(const string &poolid) const;
	LPBEOBJECT GetObject(LPPOOL pPool, const string &Key) const;

	void Lock();
	void Unlock();

	Pools pools;
	CRITICAL_SECTION pools_cs;	// main critical section for pools
	static ObjectDBPtr This;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __OBJECTDB_H__