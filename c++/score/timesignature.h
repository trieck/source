///////////////////////////////////////////////////////////////////////
//
//	TIMESIGNATURE.H
//
//	Copyright © 1999 Rieck Enterprises
//

#ifndef __TIMESIGNATURE_H__
#define __TIMESIGNATURE_H__

///////////////////////////////////////////////////////////////////////
// BeatLength enumeration

typedef enum {
    EmptyLength = 0,
    Minim = 2,
    Crotchet = 4, 
    Quaver = 8
} BeatLength;
 
///////////////////////////////////////////////////////////////////////
// TimeSignature class
class TimeSignature
{
public:
    // Construction / Destruction
    TimeSignature();
    TimeSignature(int, BeatLength);
    virtual ~TimeSignature();

    // Interface
    void SetTimeSignature (int, BeatLength);
    void GetTimeSignature(int &, BeatLength &) const;
    
    inline void SetBeats(int beats) { m_beats = beats; }
    inline int GetBeats() const { return m_beats; }

    inline void SetLength(BeatLength length) { m_length = length; }
    inline BeatLength GetLength() const { return m_length; }

    float GetDuration() const;

    // Implementation
protected:
    int m_beats;
    BeatLength m_length;
};

///////////////////////////////////////////////////////////////////////

#endif // __TIMESIGNATURE_H__
