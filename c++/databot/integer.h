/////////////////////////////////////////////////////////////////////////////
// 
// INTEGER.H : Integer message object class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#ifndef __INTEGER_H__
#define __INTEGER_H__

/////////////////////////////////////////////////////////////////////////////
class Integer : public MessageObject
{
// Construction / Destruction
public:
	Integer(int64_t i);
	Integer(const Integer &rhs);
	virtual ~Integer();

// Interface
	Integer &operator =(const Integer &rhs);
	LPMOBJECT copy() const;
	string toString() const;

// Implementation
private:	
	int64_t val;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __INTEGER_H__
