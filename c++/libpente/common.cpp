#include "common.h"
#include <limits.h>

const POINT NIL_MOVE = { INT_MIN, INT_MIN };

bool isNilMove(const POINT &pt)
{
    return memcmp(&pt, &NIL_MOVE, sizeof(POINT)) == 0;
}

bool isEqualPoint(const POINT &pt1, const POINT &pt2)
{
    return memcmp(&pt1, &pt2, sizeof(POINT)) == 0;
}
