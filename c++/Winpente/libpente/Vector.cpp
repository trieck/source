/////////////////////////////////////////////////////////////////////////////
//
// VECTOR.CPP : Pente vector
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "vector.h"
#include "entry.h"

/////////////////////////////////////////////////////////////////////////////
Vector::Vector()
{
	clear();
}

/////////////////////////////////////////////////////////////////////////////
Vector::Vector(const Vector &rhs)
{
	*this = rhs;
}

/////////////////////////////////////////////////////////////////////////////
Vector & Vector::operator =(const Vector &rhs)
{
	if (this != &rhs) {
		memcpy(v, rhs.v, sizeof(POINT) * VSIZE);
	};

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
void Vector::clear()
{
	memset(v, ET_EMPTY, sizeof(POINT) * VSIZE);
}

/////////////////////////////////////////////////////////////////////////////
POINT Vector::entry(uint32_t index)
{
	return v[index % VSIZE];
}

/////////////////////////////////////////////////////////////////////////////
void Vector::setEntry(uint32_t index, uint32_t x, uint32_t y)
{
	POINT pt;
	pt.x = x; pt.y = y;
	v[index % VSIZE] = pt;
}