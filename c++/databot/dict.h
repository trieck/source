/////////////////////////////////////////////////////////////////////////////
// 
// DICT.H : Dictionary message object class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#ifndef __DICT_H__
#define __DICT_H__

/////////////////////////////////////////////////////////////////////////////
class Dictionary : public MessageObject
{
// Construction / Destruction
public:
	Dictionary();
	Dictionary(const Dictionary &rhs);
	virtual ~Dictionary();

// Interface
	Dictionary &operator =(const Dictionary &rhs);
	void put(const string &key, LPMOBJECT val);
	LPMOBJECT get(const string &key) const;

	LPMOBJECT copy() const;
	string toString() const;
	ObjectType getType() const { return MO_DICTIONARY; }

// Implementation
private:
	void clear();

	typedef map<string, LPMOBJECT> ObjectMap;
	typedef const std::pair<string, LPMOBJECT> ObjectEntry;
	ObjectMap map;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __DICT_H__
