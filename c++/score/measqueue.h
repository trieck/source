/////////////////////////////////////////////////////////////////////////////
//
//	MEASQUEUE.H : queue of measure pointers
//
//	This class implements a queue of measures
//	and is used in implementing a double buffering
//	scheme for streamed ouput
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#ifndef __MEASQUEUE_H__
#define __MEASQUEUE_H__

#include <queue>

/////////////////////////////////////////////////////////////////////////////
class MeasureQueue : public std::queue<Measure *> {
public:
    // Construction / Destruction
    MeasureQueue();
    virtual ~MeasureQueue();

    // Interface
    void clear();

    // Implementation
protected:
};
/////////////////////////////////////////////////////////////////////////////


#endif // __MEASQUEUE_H__