/////////////////////////////////////////////////////////////////////////////
//
// VECTOR.H : Pente vector
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//


#ifndef __VECTOR_H__
#define __VECTOR_H__

#define VSIZE	(5)

/////////////////////////////////////////////////////////////////////////////
class Vector
{
// Construction / Destruction
public:
    Vector();
    Vector(const Vector &rhs);
    ~Vector();

// Interface
    Vector & operator = (const Vector &rhs);

    void clear();
    POINT entry(uint32_t index) const;
    void setEntry(uint32_t index, uint32_t m, uint32_t n);

// Implementation
private:
    POINT v[VSIZE];
};

#endif // __VECTOR_H__