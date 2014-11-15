/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.CPP : Pente machine
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Machine.h"

/////////////////////////////////////////////////////////////////////////////
Machine::Machine()
{
    board = Board::instance();
    generate();
}

/////////////////////////////////////////////////////////////////////////////
Machine::~Machine()
{
}

void Machine::generate()
{
    uint32_t i, j, m, n;
    Vector v;

    // generate all initially feasible vectors

    for (i = 0; i < BOARD_ENTRIES; i++) {
        m = i / BOARD_SIZE;
        n = i % BOARD_SIZE;

        // check for horizontal vector
        if (VSIZE + n <= BOARD_SIZE) {
            v.clear();
            for (j = 0; j < VSIZE; j++) {
                v.setEntry(j, m, n+j);
            }
            vectors.push_back(v);
        }

        // check for vertical vector
        if (VSIZE + m <= BOARD_SIZE) {
            v.clear();
            for (j = 0; j < VSIZE; j++) {
                v.setEntry(j, m+j, n);
            }
            vectors.push_back(v);
        }

        // check for a "diagonal down" vector
        if (VSIZE + m <= BOARD_SIZE && VSIZE + n <= BOARD_SIZE) {
            v.clear();
            for (j = 0; j < VSIZE; j++) {
                v.setEntry(j, m+j, n+j);
            }
            vectors.push_back(v);
        }

        // check for a "diagonal up" vector
        if (m >= VSIZE - 1 && VSIZE + n <= BOARD_SIZE) {
            v.clear();
            for (j = 0; j < VSIZE; j++) {
                v.setEntry(j, m-j, n+j);
            }
            vectors.push_back(v);
        }
    }

}