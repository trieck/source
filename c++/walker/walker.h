/////////////////////////////////////////////////////////////////////////////
// 
// WALKER.H : B-tree walker
//
// Copyright (c) 2006 Thomas. A. Rieck, All Rights Reserved
//

#ifndef __WALKER_H__
#define __WALKER_H__

/////////////////////////////////////////////////////////////////////////////
class Walker : public IItemWalker
{
// Construction / Destruction
public:
	Walker();
	virtual ~Walker();

	void walk(LPCSTR filename);

	// ITreeWalkerClient methods
	void Call(PITEM pItem);

// Implementation
private:
	BTree btree;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __WALKER_H__
