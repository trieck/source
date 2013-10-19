/////////////////////////////////////////////////////////////////////////////
//
// REFOBJ.H : Reference counted object interface
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __REFOBJ_H__
#define __REFOBJ_H__

/////////////////////////////////////////////////////////////////////////////
class RefObj {
public:
	RefObj() {}
	virtual ~RefObj() {};

	virtual uint32_t IncRef() = 0;
	virtual uint32_t DecRef() = 0;
};

#endif // __REFOBJ_H__
