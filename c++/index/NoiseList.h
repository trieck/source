/////////////////////////////////////////////////////////////////////////////
//
//	NOISELIST.H : Noise word list
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __NOISELIST_H__
#define __NOISELIST_H__

/////////////////////////////////////////////////////////////////////////////
class NoiseList {
// Construction / Destruction
public:
	NoiseList();
	virtual ~NoiseList();

// Interface
	bool isnoise(const string &term) const;

// Implementation
private:
	void load();
	void close();
	IPeekableStreamPtr stream;	// input stream
	set<string> noise;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __NOISELIST_H__