/////////////////////////////////////////////////////////////////////////////
//
// LIST.H : Bencoded list class
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __LIST_H__
#define __LIST_H__

/////////////////////////////////////////////////////////////////////////////
class List : public BEObject
{
private:
	// Construction / Destruction
	List();
public:
	List(const List &l);
	~List();

// Interface
	List &operator =(const List &rhs);

	virtual ObjectType GetType() const { return BET_LIST; }
	virtual LPBEOBJECT Copy() const;

	void AddObject(LPBEOBJECT o);
	LPBEOBJECT Get(unsigned index) const;
	unsigned size() const { return list.size(); }

// Implementation
private:
	vector<LPBEOBJECT> list;
	friend List *MakeList();
};
/////////////////////////////////////////////////////////////////////////////

typedef List *LPLIST;

/////////////////////////////////////////////////////////////////////////////
// Global helpers
LPLIST MakeList();

#endif // __LIST_H__