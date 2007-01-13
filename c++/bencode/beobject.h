/////////////////////////////////////////////////////////////////////////////
//
// BEOBJECT.H : Bencoded object abstract class
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __BEOBJECT_H__
#define __BEOBJECT_H__

/////////////////////////////////////////////////////////////////////////////
class BEObject
{
protected:
	// Construction / Destruction
	BEObject();
public:
	virtual ~BEObject();

// Interface

	// Object types
	enum ObjectType {
		BET_UNDEF = 0,
		BET_INTEGER = 1,
		BET_STRING = 2,
		BET_LIST = 3,
		BET_DICT = 4
	};

	virtual ObjectType GetType() const = 0;
	virtual BEObject *Copy() const = 0;

// Implementation
private:
};
/////////////////////////////////////////////////////////////////////////////

typedef BEObject *LPBEOBJECT;
typedef BEObject::ObjectType BEType;
typedef auto_ptr<BEObject> BEObjectPtr;

#endif // __BEOBJECT_H__