/////////////////////////////////////////////////////////////////////////////
//
// VOLUME.H : ADF volume definition
//
// Copyright(c) 2009 Thomas A. Rieck
// All Rights Reserved
//

#ifndef __VOLUME_H__
#define __VOLUME_H__

/////////////////////////////////////////////////////////////////////////////
class Volume
{
// Construction / destruction
public:
	Volume();
	~Volume();

// Interface

// Implementation
private:
	int8_t type;	// FFS/OFS, DIRCACHE, INTERNATIONAL
	string name;	// volume name
};

#endif // __VOLUME_H__
