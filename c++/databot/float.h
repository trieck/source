/////////////////////////////////////////////////////////////////////////////
// 
// FLOAT.H : Float message object class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#ifndef __FLOAT_H__
#define __FLOAT_H__

/////////////////////////////////////////////////////////////////////////////
class Float : public MessageObject
{
// Construction / Destruction
public:
	Float(double d);
	Float(const Float &rhs);
	virtual ~Float();

// Interface
	Float &operator =(const Float &rhs);
	LPMOBJECT copy() const;
	string toString() const;

// Implementation
private:	
	double val;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __FLOAT_H__
