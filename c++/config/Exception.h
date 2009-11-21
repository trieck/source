/////////////////////////////////////////////////////////////////////////////
//
// EXCEPTION.H : Simple exception class
//
// Copyright (c) 2004, Thomas A. Rieck
// All Rights Reserved
//

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

/////////////////////////////////////////////////////////////////////////////
class Exception {
// Construction / Destruction
public:
	Exception(const char *pdesc) : desc(pdesc) {}
	Exception(const string &sdesc) : desc(sdesc) {}
	virtual ~Exception() {}

// Interface
	string GetDescription() const {
		return desc;
	}

// Implementation
private:
	string desc;
};

#endif // __EXCEPTION_H__