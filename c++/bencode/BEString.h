/////////////////////////////////////////////////////////////////////////////
//
// BESTRING.H : Bencoded string class
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __BESTRING_H__
#define __BESTRING_H__

/////////////////////////////////////////////////////////////////////////////
class String : public BEObject
{
private:
	// Construction / Destruction
	String(LPBYTE data, INT len);
public:
	String(const String &str);
	~String();

// Interface
	String &operator = (const String &rhs);

	virtual ObjectType GetType() const { return BET_STRING; }
	virtual LPBEOBJECT Copy() const;

	INT GetLength() const { return nlen; }
	LPBYTE GetData() const { return data; }
	BYTE GetAt(int i) const;

	operator string() const;	

// Implementation
private:
	LPBYTE data;
	INT nlen;
	friend String *MakeString(LPBYTE data, INT nLen);
	friend String *MakeString(LPCSTR pstr);
};
/////////////////////////////////////////////////////////////////////////////

typedef String *LPSTRING;

/////////////////////////////////////////////////////////////////////////////
// Global helpers
LPSTRING MakeString(LPBYTE data, INT nlen);
LPSTRING MakeString(LPCSTR pstr);

#endif // __BESTRING_H__