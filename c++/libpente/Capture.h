/////////////////////////////////////////////////////////////////////////////
//
// CAPTURE.H : Pente capture
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#ifndef __CAPTURE_H__
#define __CAPTURE_H__

/////////////////////////////////////////////////////////////////////////////
class Capture
{
// Construction / Destruction
public:
    Capture(const POINT &pt1, const POINT &pt2);
    Capture(const Capture &rhs);
    ~Capture();

// Interface
    Capture &operator = (const Capture &rhs);

    const POINT &getPoint1() const
    {
        return pts[0];
    }
    const POINT &getPoint2() const
    {
        return pts[1];
    }

// Implementation
private:
    POINT pts[2];
};

typedef std::vector<Capture> CaptureVec;

#endif // __CAPTURE_H__