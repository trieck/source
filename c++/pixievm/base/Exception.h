/////////////////////////////////////////////////////////////////////////////
//
// EXCEPTION.H : Simple exception class
//
// Copyright (c) 2006, Thomas A. Rieck
// All Rights Reserved
//

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

/////////////////////////////////////////////////////////////////////////////
class Exception {
// Construction / Destruction
public:
	Exception(const char *fmt, ...) {
		char buffer[BUFF_SIZE];
		va_list arglist;
		va_start(arglist, fmt);
		vsprintf(buffer, fmt, arglist);
		va_end(arglist);
		desc = buffer;
	}

	Exception(const string &sdesc) : desc(sdesc) {}
	Exception::Exception(const Exception &rhs) {
		*this = rhs;
	}
	virtual ~Exception() {}

// Interface
	Exception &operator =(const Exception &rhs) {
		if (this != &rhs) {
			desc = rhs.desc;
		}
		return *this;
	}
	string getDescription() const {
		return desc;
	}

// Implementation
private:
	string desc;
	enum { BUFF_SIZE = 1024 };
};

#endif // __EXCEPTION_H__
