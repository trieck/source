/////////////////////////////////////////////////////////////////////////////
//
// FSTRING.H : fast string class
//

#ifndef __FSTRING_H__
#define __FSTRING_H__

#define BUFFSIZE 65535

/////////////////////////////////////////////////////////////////////////////
class String
{
public:
// Construction / Destruction
	String();
	String(const char * pstr);
	String(const String & str);
	virtual ~String();

// Interface
	String & operator =(const String & rhs);
	String & operator += (const String & rhs);
	bool operator == (const String & rhs);
	operator const char *() const;

	size_t length() const;

protected:
// Implementation
	void AllocBuffer(size_t len = BUFFSIZE);
	void Realloc(size_t nsize);
private:
	char *buffer;
	size_t size;
	size_t nlen;
};
/////////////////////////////////////////////////////////////////////////////

inline String::operator const char *() const
{
	return buffer;
}

inline size_t String::length() const
{
	return nlen;
}

// global operators
String operator +(const String & lhs, const String & rhs);

#endif // __FSTRING_H__