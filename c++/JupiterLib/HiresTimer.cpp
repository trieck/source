/////////////////////////////////////////////////////////////////////////////
//
//	HIRESTIMER.CPP : High resolution timer
//
//	Copyright(c) 2006, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "HiresTimer.h"
#include <limits.h>

/////////////////////////////////////////////////////////////////////////////
HiresTimer::HiresTimer() : ticksPerSecond(0)
{
    QueryPerformanceCounter(&start);

    LARGE_INTEGER li;
    if (QueryPerformanceFrequency(&li)) {
        ticksPerSecond = LI2INT64(&li);
    }
}

/////////////////////////////////////////////////////////////////////////////
HiresTimer::~HiresTimer()
{
}

/////////////////////////////////////////////////////////////////////////////
INT64 HiresTimer::LI2INT64(PLARGE_INTEGER li) const
{
    return (((INT64)(*li).HighPart) << 32) + (*li).LowPart;
}

/////////////////////////////////////////////////////////////////////////////
HiresTimer::operator string() const
{
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);

    char buf[MAX_PATH] = { '\0' };

    if (ticksPerSecond) {
        INT64 tstart = LI2INT64((PLARGE_INTEGER)&start);
        INT64 tend = LI2INT64(&end);
        INT64 ntime = (tend - tstart) / (ticksPerSecond / 100);

        int hours = (ntime / 100) / 3600;
        int minutes = ((ntime / 100) % 3600) / 60;
        int seconds = (ntime / 100) % 60;
        int hundreths = ntime % 100;

        if (hours)
            sprintf(buf, "%2d:%02d:%02d hours", hours, minutes, seconds);

        else if (minutes)
            sprintf(buf, "%2d:%02d minutes", minutes, seconds);

        else
            sprintf(buf, "%2d.%02d seconds", seconds, hundreths);
    }

    return buf;
}

/////////////////////////////////////////////////////////////////////////////
ostream & operator << (ostream &os, const HiresTimer &t)
{
    return os << string(t);
}