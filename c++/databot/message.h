/////////////////////////////////////////////////////////////////////////////
// 
// MESSAGE.H : Message class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "mobject.h"
#include "dict.h"

/////////////////////////////////////////////////////////////////////////////
class Message 
{
// Construction / Destruction
public:
	Message();
	Message(const Message &rhs);
	Message(LPMOBJECT pObj);
	virtual ~Message();

// Interface
	Message &operator =(const Message &rhs);
	Message &operator =(LPMOBJECT pObj);

	void put(const string &key, const string &val);
	void put(const string &key, int64_t val);
	void put(const string &key, double val);
	void put(const string &key, const MessageObject &o);

	string toString() const;

// Implementation
private:
	Dictionary dict;	// underlying dictionary
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MESSAGE_H__
