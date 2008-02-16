/////////////////////////////////////////////////////////////////////////////
// 
// MESSAGE.CPP : Message class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "message.h"
#include "mstring.h"
#include "integer.h"
#include "float.h"

/////////////////////////////////////////////////////////////////////////////
Message::Message()
{
}

/////////////////////////////////////////////////////////////////////////////
Message::~Message()
{
}

/////////////////////////////////////////////////////////////////////////////
void Message::put(const string &key, const string &val)
{
	dict.put(key, new String(val));
}

/////////////////////////////////////////////////////////////////////////////
void Message::put(const string &key, int64_t val)
{
	dict.put(key, new Integer(val));
}

/////////////////////////////////////////////////////////////////////////////
void Message::put(const string &key, double val)
{
	dict.put(key, new Float(val));
}

/////////////////////////////////////////////////////////////////////////////
void Message::put(const string &key, const MessageObject &o)
{
	dict.put(key, o.copy());
}

/////////////////////////////////////////////////////////////////////////////
string Message::toString() const
{
	return dict.toString();
}
