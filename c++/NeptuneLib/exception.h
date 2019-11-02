/////////////////////////////////////////////////////////////////////////////
//
//	EXCEPTION.H : simple exception class
//
//	Copyright(c) 2006, Thomas A. Rieck, All Rights Reserved
//

#ifndef __EXCEPTION_INCLUDE_H__
#define __EXCEPTION_INCLUDE_H__

/////////////////////////////////////////////////////////////////////////////
class Exception
{
public:
    Exception(const tstring &msg)
    {
        description = msg;
    }
    Exception(const Exception & E)
    {
        *this = E;
    }
    Exception(LPCTSTR fmt, ...);
    Exception & operator = (const Exception & E)
    {
        if (this != &E)
            description = E.description;
        return *this;
    }
    tstring getDescription() const
    {
        return description;
    }
private:
    tstring description;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __EXCEPTION_INCLUDE_H__