/////////////////////////////////////////////////////////////////////////////
//
// INTEGER.H : Bencoded integer class
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __INTEGER_H__
#define __INTEGER_H__

/////////////////////////////////////////////////////////////////////////////
class Integer : public BEObject {
private:
	// Construction / Destruction
	Integer(INT64 v);
public:
	Integer(const Integer &i);
	~Integer();

// Interface
	Integer &operator =(const Integer &i);

	virtual ObjectType GetType() const {
		return BET_INTEGER;
	}
	virtual LPBEOBJECT Copy() const;

	operator INT64() const {
		return val;
	}

// Implementation
private:
	INT64 val;
	friend Integer *MakeInteger(INT64 v);
};
/////////////////////////////////////////////////////////////////////////////

typedef Integer *LPINTEGER;

/////////////////////////////////////////////////////////////////////////////
// Global helpers
LPINTEGER MakeInteger(INT64 v);

#endif // __INTEGER_H__