/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.H : Pente machine
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#ifndef __MACHINE_H__
#define __MACHINE_H__

#include "Board.h"
#include "Vector.h"

/////////////////////////////////////////////////////////////////////////////
class Machine
{
// Construction / Destruction
public:
    Machine();
    ~Machine();

// Interface
    POINT move();

// Implementation
private:
    float weightVector(const Vector &v) const;
    float weightPoint(const POINT &pt) const;
    bool center(const Vector &v) const;
    POINT bestMove(const Vector &v) const;
    POINT mustBlock() const;
    bool matchBlock(uint8_t player, uint8_t empty, POINT& pt) const;
    POINT blockMove() const;
    POINT randomMove() const;
    const Vector *maxOpponentV() const;
    uint32_t contiguity(const Vector &v) const;
    const VecVec &vectors;
    Board *board;
};

#endif // __MACHINE_H__