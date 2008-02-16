/////////////////////////////////////////////////////////////////////////////
// 
// STRING.H : String message object class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#ifndef __STRING_H__
#define __STRING_H__

/////////////////////////////////////////////////////////////////////////////
class String : public MessageObject
{
// Construction / Destruction
public:
	String(const string &s);
	String(const String &rhs);
	virtual ~String();

// Interface
	String &operator=(const String &rhs);
	LPMOBJECT copy() const;
	string toString() const;

// Implementation
private:	
	string val;
};

/////////////////////////////////////////////////////////////////////////////

typedef String *LPSTRING;

#endif // __STRING_H__
