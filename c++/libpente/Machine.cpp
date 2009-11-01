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
	const Vector *maxV = NULL;
	POINT block, pt = NIL_MOVE;

	VecVec::const_iterator it = vectors.begin();
	for ( ; it != vectors.end(); it++) {
		nweight = weightVector(*it);
		if (nweight > maxWeight) {
			maxWeight = nweight;
			maxV = &*it;
		}
	}

	block = mustBlock();
	if (maxWeight == MIN_WEIGHT && isNilMove(block)) {	// no feasible strategy found
		pt = blockMove();
		if (isNilMove(pt)) {
			pt = randomMove();	// try random move
		}
	}

	// check if we must block
	if (!isNilMove(block) && maxWeight < MAX_WEIGHT) {
		pt = block;
	} else if (maxV != NULL) {	
		pt = bestMove(*maxV);
	}
	
	// mark the board
	if (!isNilMove(pt)) {
		board->setEntry(pt.x, pt.y, ET_PLAYER_TWO);
	}
	
	return pt;
}

/////////////////////////////////////////////////////////////////////////////
float Machine::weightVector(const Vector &v) const
{
	float weight = 0;
	uint32_t type, i, m, n, x, y, d;
	
	POINT pt;
	for (i = 0; i < VSIZE; i++) {
		pt = v.entry(i);
		type = board->getEntry(pt.x, pt.y);
		switch (type) {
			case ET_PLAYER_ONE:
				return MIN_WEIGHT;	// vector must not contain opponent pieces
			case ET_PLAYER_TWO:
				weight += PIECE_WEIGHT;
				break;
		}
	}
	
	if (weight == (VSIZE - 1) * PIECE_WEIGHT)
		return MAX_WEIGHT;   // winner
	
	// TODO: vector must contain a blocking strategy
	
	// add the individual piece weights
	for (i = 0; i < VSIZE; i++) {
		pt = v.entry(i);
		type = board->getEntry(pt.x, pt.y);
		if (type == ET_PLAYER_TWO) {
			weight += weightPoint(pt);
		}
	}
	
	// add weighted distance from center
	pt = v.entry(MEAN_POINT);
	m = pt.x; n = pt.y;
	x = CENTER / BOARD_SIZE; y = CENTER % BOARD_SIZE;
	d = abs(x - m) + abs(y - n) + 1;
	weight += 1/float(d);
	
	// add weighted contiguity
	weight += CONT_WEIGHT * contiguity(v);
	
	return weight;
}

/////////////////////////////////////////////////////////////////////////////
float Machine::weightPoint(const POINT &pt) const
{
	/* 
	 * Determine weight of a square
	 * By the number of maximally feasible vectors
	 * it is contained in.
	 */
	float weight = 0, vweight;
	POINT p;
	uint32_t i;
	
	if (board->getEntry(pt.x, pt.y) != ET_EMPTY)
		return MIN_WEIGHT;
	
	VecVec::const_iterator it = vectors.begin();
	for ( ; it != vectors.end(); it++) {
		for (i = 0; i < VSIZE; i++) {
			p = (*it).entry(i);
			if (isEqualPoint(pt, p)) break;
		}
		
		if (i < VSIZE) {
			vweight = weightVector(*it);
			weight += max(0, vweight);
		}
	}
		
	return weight;
}

/////////////////////////////////////////////////////////////////////////////
bool Machine::center(const Vector &v) const
{
	// does vector contain an empty center?
	uint32_t i, piece;
	POINT p;
	
	for (i = 0; i < VSIZE; i++) {
		p = v.entry(i);
		piece = p.x * BOARD_SIZE + p.y;
		if ((piece == CENTER) && board->getEntry(p.x, p.y) == ET_EMPTY)
			return true;
	}
	
	return false;
}

/////////////////////////////////////////////////////////////////////////////
POINT Machine::bestMove(const Vector &v) const
{
	float weight, maxWeight = MIN_WEIGHT;
	POINT p, maxP = NIL_MOVE;
	uint32_t i;
	
	if (center(v)) {
		POINT c = { CENTER / BOARD_SIZE, CENTER % BOARD_SIZE };
		return c;
	}

	// try to find an adjacent move
	for (i = 0; i < VSIZE; i++) {
		p = v.entry(i);		
		if (i < VSIZE-1 && board->getEntry(p.x, p.y) == ET_PLAYER_TWO) {
			p = v.entry(i+1);
			if (board->getEntry(p.x, p.y) == ET_EMPTY) {
				if ((weight = weightPoint(p)) > maxWeight) {
					maxWeight = weight;
					maxP = p;
				}
			}
		}
		
		if (i > 0 && board->getEntry(p.x, p.y) == ET_PLAYER_TWO) {
			p = v.entry(i-1);
			if (board->getEntry(p.x, p.y) == ET_EMPTY) {
				if ((weight = weightPoint(p)) > maxWeight) {
					maxWeight = weight;
					maxP = p;
				}
			}
		}
	}
	
	if (!isNilMove(maxP))
		return maxP;
	
	// try to find an empty piece
	for (i = 0; i < VSIZE; i++) {
		p = v.entry(i);					
		if (board->getEntry(p.x, p.y) == ET_EMPTY) {
			if ((weight = weightPoint(p)) > maxWeight) {
				maxWeight = weight;
				maxP = p;
			}
		}
	}
	
	return maxP;
}

/////////////////////////////////////////////////////////////////////////////
POINT Machine::mustBlock() const
{
	/* 
	 * Determine square where we must block
	 * where the vector contains VSIZE-1 ET_PLAYER_ONE and one ET_EMPTY
	 */
	POINT p, q, b, maxP = NIL_MOVE;
	uint32_t i, type, onecount, ecount;
	float weight, maxWeight = MIN_WEIGHT;
	
	VecVec::const_iterator it = vectors.begin();
	for ( ; it != vectors.end(); it++) {
		for (i = 0, onecount = 0, ecount = 0; i < VSIZE; i++) {
			p = (*it).entry(i);
			type = board->getEntry(p.x, p.y);
			switch (type) {
				case ET_PLAYER_ONE:
					onecount++;
					break;
				case ET_EMPTY:
					ecount++;
					b = p;
					break;
			}
		}
		
		if (onecount == VSIZE-1 && ecount == 1) { // must block, b contains the square to block
			weight = weightPoint(b);
			if (weight > maxWeight) {
				maxP = b;
				maxWeight = weight;
			}
		}
		
		// block contiguous with open ends
		if (onecount == VSIZE-2 && ecount == 2) {
			p = (*it).entry(0); q = (*it).entry(VSIZE-1);
			
			if (board->getEntry(p.x, p.y) == ET_EMPTY &&
				board->getEntry(q.x, q.y) == ET_EMPTY) {
				weight = weightPoint(b);
				if (weight > maxWeight) {
					maxP = b;
					maxWeight = weight;
				}
			}
		}
	}
		
	return maxP;
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
