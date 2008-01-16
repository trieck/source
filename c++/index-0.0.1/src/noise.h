/////////////////////////////////////////////////////////////////////////////
//
//	NOISE.H : Noise word list
//
//	Copyright (c) 2008 Thomas A. Rieck, All Rights Reserved
//

#ifndef __NOISELIST_H__
#define __NOISELIST_H__

/////////////////////////////////////////////////////////////////////////////
class NoiseList
{
// Construction / Destruction
public:
	NoiseList();
	virtual ~NoiseList();

// Interface
	bool isnoise(const string &term) const;

// Implementation
private:
	void load();
	set<string> noise;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __NOISELIST_H__
