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

// Implementation
private:
    void generate();

    Board::BoardPtr board;
    typedef std::vector<Vector> VecVec;
    VecVec vectors;
};

#endif // __MACHINE_H__