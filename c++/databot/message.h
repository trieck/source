/////////////////////////////////////////////////////////////////////////////
// 
// MESSAGE.H : Message class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#import <msxml6.dll> no_namespace
#include "mobject.h"
#include "dict.h"

/////////////////////////////////////////////////////////////////////////////
class Message 
{
// Construction / Destruction
public:
	Message();
	Message(const Message &rhs);
	Message(const string &xml);
	virtual ~Message();

// Interface
	Message &operator =(const Message &rhs);

	void put(const string &key, const string &val);
	void put(const string &key, int64_t val);
	void put(const string &key, double val);
	void put(const string &key, const MessageObject &o);

	string toString() const;

// Implementation
private:
	void parse(const string &xml);
	MessageObjectPtr parseElement(IXMLDOMElementPtr element);
	MessageObjectPtr parseDictionary(IXMLDOMElementPtr element);
	MessageObjectPtr parseArray(IXMLDOMElementPtr element);
	MessageObjectPtr parseString(IXMLDOMElementPtr element);
	MessageObjectPtr parseInt(IXMLDOMElementPtr element);
	MessageObjectPtr parseReal(IXMLDOMElementPtr element);
	string parseKey(IXMLDOMElementPtr element);

	Dictionary dict;	// underlying dictionary
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MESSAGE_H__
