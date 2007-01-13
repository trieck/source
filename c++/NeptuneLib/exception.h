/////////////////////////////////////////////////////////////////////////////
//
//	EXCEPTION.H : simple exception class
//
//	Copyright(c) 2006, Thomas A. Rieck, All Rights Reserved
//

#ifndef __EXCEPTION_INCLUDE_H__
#define __EXCEPTION_INCLUDE_H__

/////////////////////////////////////////////////////////////////////////////
class Exception
{
public:
	Exception(const string &msg) { description = msg; }
	Exception(const Exception & E) { *this = E; }
	Exception(const char *fmt, ...);
	Exception & operator = (const Exception & E) {
		if (this != & E)
			description = E.description;
		return *this;
	}
	string getDescription() const { return description; }
private:
	string description;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __EXCEPTION_INCLUDE_H__