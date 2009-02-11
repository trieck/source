/////////////////////////////////////////////////////////////////////////////
//
// ADFEXCEPT.H : ADF exception class
//
// LIBADF : A C++ Amiga Disk File Libary
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
// Adapted from ADF Library, Copyright(c) 1997-2002 Laurent Clevy.
//

#ifndef __ADFEXCEPT_H__
#define __ADFEXCEPT_H__

/////////////////////////////////////////////////////////////////////////////
class ADFException
{
public:
	ADFException();
	ADFException(const string &msg) { description = msg; }
	ADFException(const ADFException & E) { *this = E; }
	ADFException(const char *fmt, ...);
	ADFException & operator = (const ADFException & E) {
		if (this != & E)
			description = E.description;
		return *this;
	}
	string getDescription() const { return description; }
private:
	string description;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __ADFEXCEPT_H__