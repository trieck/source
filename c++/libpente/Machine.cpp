/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.CPP : Pente machine
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Machine.h"
#include "Board.h"
#include <float.h>

ANON_BEGIN
const float MIN_WEIGHT = -FLT_MIN;
const float MAX_WEIGHT = FLT_MAX;
const float PIECE_WEIGHT = 1.0f;
const float CONT_WEIGHT = 0.5f;
const uint32_t CENTER = (BOARD_ENTRIES + 1) / 2 - 1;
const uint32_t MEAN_POINT = VSIZE/2;
ANON_END

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

/////////////////////////////////////////////////////////////////////////////
POINT Machine::move()
{
	float nweight, maxWeight = MIN_WEIGHT;
	const Vector *vector, *maxV = NULL;
	POINT block, pt = NIL_MOVE;

	VecVec::const_iterator it = vectors.begin();
	for ( ; it != vectors.end(); it++) {
		nweight = weightVector(*it);
		if (nweight > maxWeight) {
			maxWeight = nweight;
			maxV = &*it;
		}
	}

	return pt;
}

/////////////////////////////////////////////////////////////////////////////
float Machine::weightVector(const Vector &v) const
{
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
float Machine::weightPoint(const POINT &pt) const
{
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
bool Machine::center(const Vector &v) const
{
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
POINT Machine::bestMove(const Vector &v) const
{
	POINT pt;

	return pt;
}

/////////////////////////////////////////////////////////////////////////////
POINT Machine::mustBlock() const
{
	POINT pt;

	return pt;
}

/////////////////////////////////////////////////////////////////////////////
POINT Machine::blockMove() const
{
	POINT pt;

	return pt;
}

/////////////////////////////////////////////////////////////////////////////
POINT Machine::randomMove() const
{
	POINT pt;

	return pt;
}

/////////////////////////////////////////////////////////////////////////////
Vector Machine::maxOpponentV() const
{
	Vector v;

	return v;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t Machine::contiguity(const Vector &v) const
{
	return 0;
}
