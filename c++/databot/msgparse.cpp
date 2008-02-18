/////////////////////////////////////////////////////////////////////////////
// 
// MSGPARSE.CPP : Message parser
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "msgparse.h"
#include "dict.h"
#include "array.h"
#include "mstring.h"
#include "integer.h"
#include "float.h"
#include <atlbase.h>

static string formatParseError(IXMLDOMParseErrorPtr error);

/////////////////////////////////////////////////////////////////////////////
MessageParser::MessageParser()
{
}

/////////////////////////////////////////////////////////////////////////////
MessageParser::~MessageParser()
{
}

/////////////////////////////////////////////////////////////////////////////
Message MessageParser::parse(const string &xml)
{
	// create an instance of the DOM parser
	IXMLDOMDocumentPtr document;
	HRESULT hr = document.CreateInstance(__uuidof(DOMDocument));

	// validate the document on parsing
	hr = document->put_validateOnParse(VARIANT_TRUE);
	_com_util::CheckError(hr);

	// load the XML document
	IXMLDOMParseErrorPtr error;
	VARIANT_BOOL ret = document->loadXML(xml.c_str());
	if (ret == VARIANT_FALSE) {	
		error = document->GetparseError();
		if (error != NULL)
			throw Exception(formatParseError(error));
	}	

	// parse the XML document
	MessageObjectPtr pObject = 
		parseElement(document->selectSingleNode("//plist/dict"));

	Message message = pObject.get();

	return message;
}

/////////////////////////////////////////////////////////////////////////////
MessageObjectPtr MessageParser::parseElement(IXMLDOMElementPtr element)
{
	string tag = (LPCSTR)element->GettagName();
	
	if (tag == "dict") {
		return parseDictionary(element);
	} else if (tag == "array") {
		return parseArray(element);
	} else if (tag == "string") {
		return parseString(element);
	} else if (tag == "integer") {
		return parseInt(element);
	} else if (tag == "real") {
		return parseReal(element);
	} else {
		throw new Exception("unexpected element \"%s\".", tag.c_str());
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
MessageObjectPtr MessageParser::parseDictionary(IXMLDOMElementPtr element)
{
	Dictionary *pDict = new Dictionary();

	string key, tag;
	MessageObjectPtr pVal;
	IXMLDOMNodeListPtr children = element->GetchildNodes();
	IXMLDOMNodePtr node;

	while ((node = children->nextNode()) != NULL) {
		if (node->GetnodeType() == NODE_ELEMENT) {
			element = node;
			tag = (LPCSTR)element->GettagName();
			if (tag == "key") {
				key = parseKey(node);
			} else {
				pVal = parseElement(node);
				pDict->put(key, pVal.release());
			}
		}
	}

	return pDict;
}

/////////////////////////////////////////////////////////////////////////////
MessageObjectPtr MessageParser::parseArray(IXMLDOMElementPtr element)
{
	Array *pArray = new Array();

	MessageObjectPtr pItem;

	IXMLDOMNodeListPtr children = element->GetchildNodes();
	IXMLDOMNodePtr node;
	while ((node = children->nextNode()) != NULL) {
		if (node->GetnodeType() == NODE_ELEMENT) {
			pItem = parseElement(node);
			pArray->add(pItem.release());
		}
	}

	return pArray;
}

/////////////////////////////////////////////////////////////////////////////
string MessageParser::parseKey(IXMLDOMElementPtr element)
{
	IXMLDOMNodeListPtr children = element->GetchildNodes();
	IXMLDOMNodePtr node;
	while ((node = children->nextNode()) != NULL) {
		if (node->GetnodeType() == NODE_TEXT) {
			return (LPCSTR)node->Gettext();
		}
	}
	
	return "";
}

/////////////////////////////////////////////////////////////////////////////
MessageObjectPtr MessageParser::parseString(IXMLDOMElementPtr element)
{
	IXMLDOMNodeListPtr children = element->GetchildNodes();
	IXMLDOMNodePtr node;
	while ((node = children->nextNode()) != NULL) {
		if (node->GetnodeType() == NODE_TEXT)
			return new String((LPCSTR)node->Gettext());
	}
	
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
MessageObjectPtr MessageParser::parseInt(IXMLDOMElementPtr element)
{
	IXMLDOMNodeListPtr children = element->GetchildNodes();
	IXMLDOMNodePtr node;
	while ((node = children->nextNode()) != NULL) {
		if (node->GetnodeType() == NODE_TEXT) {
			int64_t ival = _atoi64((LPCSTR)node->Gettext());
			return new Integer(ival);
		}
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
MessageObjectPtr MessageParser::parseReal(IXMLDOMElementPtr element)
{
	IXMLDOMNodeListPtr children = element->GetchildNodes();
	IXMLDOMNodePtr node;
	while ((node = children->nextNode()) != NULL) {
		if (node->GetnodeType() == NODE_TEXT) {
			double dval = atof((LPCSTR)node->Gettext());
			return new Float(dval);
		}
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
string formatParseError(IXMLDOMParseErrorPtr error)
{
	char buffer[1000];

	USES_CONVERSION;
	string reason = error->reason.length() == 0 ? "" : OLE2A(error->reason);
	string text = error->srcText.length() == 0 ? "" : OLE2A(error->srcText);
	string url = error->url.length() == 0 ? "" : OLE2A(error->url);

	int code = error->errorCode;
	int line = error->line;
	int pos = error->linepos;

	sprintf(buffer, "Parse Error:\nUrl : %s\nCode : 0x%x\nSource = "
		"Line : %ld; Char : %ld\nDescription : %s\nSource Text : %s", 
		url.c_str(), code, line, pos, reason.c_str(), text.c_str());
	
	return buffer;
}