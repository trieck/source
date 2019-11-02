/////////////////////////////////////////////////////////////////////////////
//
//	CSHOLDER.H : Critical section holder
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __CSHOLDER_H__
#define __CSHOLDER_H__

/////////////////////////////////////////////////////////////////////////////
class CSHolder
{
// Construction / Destruction
public:
    CSHolder(CComAutoCriticalSection &s) : cs(s)
    {
        cs.Lock();
    }
    ~CSHolder()
    {
        cs.Unlock();
    }

// Implementation
private:
    CComAutoCriticalSection &cs;
};

#endif // __CSHOLDER_H__