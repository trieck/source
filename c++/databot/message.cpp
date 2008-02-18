/////////////////////////////////////////////////////////////////////////////
// 
// MESSAGE.CPP : Message class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "message.h"
#include "array.h"
#include "mstring.h"
#include "integer.h"
#include "float.h"

/////////////////////////////////////////////////////////////////////////////
Message::Message()
{
}

/////////////////////////////////////////////////////////////////////////////
Message::Message(const Message &rhs)
{
	*this = rhs;
}

/////////////////////////////////////////////////////////////////////////////
Message::Message(LPMOBJECT pObj)
{
	*this = pObj;
}

/////////////////////////////////////////////////////////////////////////////
Message::~Message()
{
}

/////////////////////////////////////////////////////////////////////////////
Message &Message::operator =(const Message &rhs)
{
	if (this != &rhs) {
		dict = rhs.dict;
	}
	return *this;
}

/////////////////////////////////////////////////////////////////////////////
Message &Message::operator =(LPMOBJECT pObj)
{
	if (pObj->getType() == MessageObject::MO_DICTIONARY) {
		dict = *(Dictionary*)pObj;
	}
	return *this;
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
	ostringstream oss;
	oss << "<?xml version=\"1.0\" ?>\n";
	oss << "<!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST "
		"1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n";
	oss << "<plist version=\"1.0\">\n";
	oss << dict.toString();
	oss << "</plist>";
	return oss.str();
}

