/////////////////////////////////////////////////////////////////////////////
//
// SHA1.H : Secure hash algorithm
//
// Derived from cryptoapi implementation, adapted for in-place
// scatterlist interface.  Originally based on the public domain
// implementation written by Steve Reid.
//
// Adapted for Win32
//
// Copyright (c) Alan Smithee.
// Copyright (c) Andrew McDonald <andrew@mcdonald.org.uk>
// Copyright (c) Jean-Francois Dive <jef@linuxbe.org>
//
// Copyright (C) 2006 Thomas A. Rieck, all rights reserved.
//

#ifndef __SHA1_H__
#define __SHA1_H__

#define SHA1_DIGEST_SIZE 20

/////////////////////////////////////////////////////////////////////////////
class SHA1 {
// Construction / Destruction
public:
	SHA1(const string &s);
	~SHA1();

// Interface
	string toHexString() const;
	operator LPCSTR() const {
		return digest;
	}

// Implementation
private:
	char digest[SHA1_DIGEST_SIZE];
};

/////////////////////////////////////////////////////////////////////////////

#endif // __SHA1_H__


