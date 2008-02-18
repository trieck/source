/////////////////////////////////////////////////////////////////////////////
// 
// MSGPARSE.H : Message parser
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MSGPARSE_H__
#define __MSGPARSE_H__

#import <msxml6.dll> no_namespace
#include "mobject.h"
#include "message.h"

/////////////////////////////////////////////////////////////////////////////
class MessageParser 
{
// Construction / Destruction
public:
	MessageParser();
	virtual ~MessageParser();

// Interface
	Message parse(const string &xml);

// Implementation
private:	
	MessageObjectPtr parseElement(IXMLDOMElementPtr element);
	MessageObjectPtr parseDictionary(IXMLDOMElementPtr element);
	MessageObjectPtr parseArray(IXMLDOMElementPtr element);
	MessageObjectPtr parseString(IXMLDOMElementPtr element);
	MessageObjectPtr parseInt(IXMLDOMElementPtr element);
	MessageObjectPtr parseReal(IXMLDOMElementPtr element);
	string parseKey(IXMLDOMElementPtr element);
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MSGPARSE_H__
