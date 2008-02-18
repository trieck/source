/////////////////////////////////////////////////////////////////////////////
// 
// ARRAY.H : Array message object class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#ifndef __ARRAY_H__
#define __ARRAY_H__

/////////////////////////////////////////////////////////////////////////////
class Array : public MessageObject
{
// Construction / Destruction
public:
	Array();
	Array(const Array &rhs);
	virtual ~Array();

// Interface
	Array &operator =(const Array &rhs);

	void add(int64_t i);
	void add(double d);
	void add(const string &s);
	void add(LPMOBJECT pObject);

	LPMOBJECT copy() const;
	string toString() const;
	ObjectType getType() const { return MO_ARRAY; }

// Implementation
private:
	void clear();
	typedef vector<LPMOBJECT> ObjectList;
	ObjectList list;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __ARRAY_H__
