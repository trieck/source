/////////////////////////////////////////////////////////////////////////////
// 
// MOBJECT.H : Message Object base class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MOBJECT_H__
#define __MOBJECT_H__

/////////////////////////////////////////////////////////////////////////////
class MessageObject
{
// Construction / Destruction
public:
	MessageObject();
	virtual ~MessageObject();

// Interface
	virtual MessageObject *copy() const = 0;
	virtual string toString() const = 0;

// Implementation
private:
};
/////////////////////////////////////////////////////////////////////////////

typedef MessageObject *LPMOBJECT;
typedef auto_ptr<MessageObject> MessageObjectPtr;

#endif // __MOBJECT_H__
