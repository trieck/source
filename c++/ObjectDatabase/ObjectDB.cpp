/////////////////////////////////////////////////////////////////////////////
//
// OBJECTDB.CPP : Object Database
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "BEObject.h"
#include "Integer.h"
#include "String.h"
#include "List.h"
#include "Dictionary.h"
#include "ObjectDB.h"
#include "proto.h"

ObjectDB::ObjectDBPtr ObjectDB::This;

/////////////////////////////////////////////////////////////////////////////
ObjectDB::ObjectDB()
{
	// initialize pools critical section
	InitializeCriticalSection(&pools_cs);
}

/////////////////////////////////////////////////////////////////////////////
ObjectDB::~ObjectDB()
{
	// destroy pools critical section
	DeleteCriticalSection(&pools_cs);

	Pools::const_iterator it = pools.begin();
	for ( ; it != pools.end(); it++) {
		delete (*it).second;
	}
}

/////////////////////////////////////////////////////////////////////////////
ObjectDB *ObjectDB::instance()
{
	if (This.get() == NULL) {
		This = ObjectDBPtr(new ObjectDB());
	}

	return This.get();
}

/////////////////////////////////////////////////////////////////////////////
void ObjectDB::Lock()
{
	EnterCriticalSection(&pools_cs);
}

/////////////////////////////////////////////////////////////////////////////
void ObjectDB::Unlock()
{
	LeaveCriticalSection(&pools_cs);
}

/////////////////////////////////////////////////////////////////////////////
LPCSTR ObjectDB::MakePool()
{
	Lock();		// lock the pools map

	// insert the pool into the map
	std::pair <Pools::const_iterator, bool> pr = 
		pools.insert (Pools::value_type(NewKey(), new Pool()));

	Unlock();	// unlock the pools map

	return (pr.first)->first.c_str();
}

/////////////////////////////////////////////////////////////////////////////
ObjectDB::Pool::Pool() 
{
	InitializeCriticalSection(&cs);
}

/////////////////////////////////////////////////////////////////////////////
ObjectDB::Pool::~Pool() 
{
	DeleteCriticalSection(&cs);
}

/////////////////////////////////////////////////////////////////////////////
void ObjectDB::Pool::Lock() 
{
	EnterCriticalSection(&cs);
}

/////////////////////////////////////////////////////////////////////////////
void ObjectDB::Pool::Unlock() 
{
	LeaveCriticalSection(&cs);
}

/////////////////////////////////////////////////////////////////////////////
LPCSTR ObjectDB::CreateObject(const string &poolid, int ntype, 
 LPSTRING pObjectID, LPBEOBJECT pValue)
{
	if (pValue == NULL) {	// create a new empty object
		if ((pValue = MakeObject(ntype)) == NULL) {
			SetLastError(ERROR_INVALID_PARAMETER);
			return NULL;	// invalid type
		}
		return Insert(poolid, pValue, pObjectID);
	} else {	// store a copy in the pool
		return Insert(poolid, pValue->Copy(), pObjectID);
	}
}

/////////////////////////////////////////////////////////////////////////////
LPBEOBJECT ObjectDB::GetObject(const string &poolid, 
 const string &objectid) const
{
	LPPOOL pPool = GetPool(poolid);
	if (pPool == NULL) {
		SetLastError(ERROR_INVALID_HANDLE);
		return FALSE;	// pool not found
	}

	PoolMap::iterator it = pPool->entries.find(objectid);
	if (it == pPool->entries.end()) {
		SetLastError(ERROR_INVALID_HANDLE);
		return FALSE;	// object not found in pool
	}

	return (*it).second;
}

/////////////////////////////////////////////////////////////////////////////
BOOL ObjectDB::SetObject(const string &poolid, const string &objectid, 
 LPBEOBJECT pObject)
{
	LPPOOL pPool = GetPool(poolid);
	if (pPool == NULL) {
		SetLastError(ERROR_INVALID_HANDLE);
		return FALSE;	// pool not found
	}

	PoolMap::iterator it = pPool->entries.find(objectid);
	if (it == pPool->entries.end()) {
		SetLastError(ERROR_INVALID_HANDLE);
		return FALSE;	// object not found in pool
	}

	pPool->Lock();		// lock the pool

	// destroy current object 
	delete (*it).second;

	// store a copy
	(*it).second = pObject->Copy();

	pPool->Unlock();	// unlock the pool

	return TRUE;


	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
BOOL ObjectDB::DestroyObject(const string &poolid, const string &objectid)
{
	LPPOOL pPool = GetPool(poolid);
	if (pPool == NULL) {
		SetLastError(ERROR_INVALID_HANDLE);
		return FALSE;	// pool not found
	}

	PoolMap::iterator it = pPool->entries.find(objectid);
	if (it == pPool->entries.end()) {
		SetLastError(ERROR_INVALID_HANDLE);
		return FALSE;	// object not found in pool
	}

	pPool->Lock();		// lock the pool

	delete (*it).second;
	pPool->entries.erase(it);

	pPool->Unlock();	// unlock the pool

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
LPCSTR ObjectDB::Insert(const string &poolid, LPBEOBJECT pObject, LPSTRING pKey)
{
	LPPOOL pPool = GetPool(poolid);
	if (pPool == NULL) {
		SetLastError(ERROR_INVALID_HANDLE);
		return NULL;	// pool not found
	}

	string ObjectKey = pKey == NULL ? NewKey() : *pKey;

	// key must not exist
	if (GetObject(pPool, ObjectKey) != NULL) {
		SetLastError(ERROR_OBJECT_ALREADY_EXISTS);
		return NULL;
	}

	pPool->Lock();		// lock the pool

	// insert the object into the pool
	std::pair <PoolMap::const_iterator, bool> pr = 
		pPool->entries.insert (PoolMap::value_type(ObjectKey, pObject));

	pPool->Unlock();	// unlock the pool

	return (pr.first)->first.c_str();
}

/////////////////////////////////////////////////////////////////////////////
LPBEOBJECT ObjectDB::GetObject(LPPOOL pPool, const string &Key) const
{
	PoolMap::const_iterator it = pPool->entries.find(Key);
	if (it == pPool->entries.end())
		return NULL;

	return (*it).second;
}

/////////////////////////////////////////////////////////////////////////////
ObjectDB::LPPOOL ObjectDB::GetPool(const string &poolid) const
{
	Pools::const_iterator it = pools.find(poolid);
	if (it == pools.end())
		return NULL;

	return (*it).second;
}

/////////////////////////////////////////////////////////////////////////////
string ObjectDB::NewKey()
{
	GUID guid;
	CoCreateGuid(&guid);

	char key[sizeof(GUID) * 2 + 1];
	sprintf(key, "%.8x%.4x%.4x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x",
		guid.Data1, guid.Data2,
		guid.Data3, 
		guid.Data4[0],
		guid.Data4[1],
		guid.Data4[2],
		guid.Data4[3],
		guid.Data4[4],
		guid.Data4[5],
		guid.Data4[6],
		guid.Data4[7]
		);

	return key;
}

/////////////////////////////////////////////////////////////////////////////
LPBEOBJECT ObjectDB::MakeObject(int ntype)
{
	LPBEOBJECT pObject = NULL;

	switch (ntype) {
	case OT_INTEGER:
		pObject = MakeInteger(0);
		break;
	case OT_STRING:			
		pObject = MakeString("");
		break;
	case OT_LIST:
		pObject = MakeList();
		break;
	case OT_DICT:
		pObject = MakeDictionary();
		break;
	}

	return pObject;
}