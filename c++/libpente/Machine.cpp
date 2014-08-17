/////////////////////////////////////////////////////////////////////////////
//
// MACHINE.CPP : Pente machine
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "Machine.h"
#include "Board.h"
#include <float.h>
#include <time.h>

ANON_BEGIN
const float MIN_WEIGHT = -FLT_MIN;
const float MAX_WEIGHT = FLT_MAX;
const float PIECE_WEIGHT = 1.0f;
const float CONT_WEIGHT = 0.5f;
const uint32_t CENTER = (BOARD_ENTRIES + 1) / 2 - 1;
const uint32_t MEAN_POINT = VSIZE/2;
typedef std::vector<POINT> PointVec;
ANON_END


/////////////////////////////////////////////////////////////////////////////
Machine::Machine() : vectors (Board::instance()->getVectors())
{
	board = Board::instance();
}

/////////////////////////////////////////////////////////////////////////////
Machine::~Machine()
{
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
	m = pt.x;
	n = pt.y;
	x = CENTER / BOARD_SIZE;
	y = CENTER % BOARD_SIZE;
	d = abs((int)(x - m)) + abs((int)(y - n)) + 1;
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
	POINT pt;

	if (matchBlock(4, 1, pt))
		return pt;

	if (matchBlock(3, 2, pt))
		return pt;

	return NIL_MOVE;
}

/////////////////////////////////////////////////////////////////////////////
bool Machine::matchBlock(uint8_t player, uint8_t empty, POINT& pt) const
{
	uint32_t i, type;
	uint8_t p1s, empties;
	POINT p, maxP;
	float weight, maxWeight = MIN_WEIGHT;
	bool matched = false;
	PointVec candidates;

	VecVec::const_iterator it = vectors.begin();
	for ( ; it != vectors.end(); it++) {
		candidates.clear();
		for (i = 0, p1s = 0, empties = 0; i < VSIZE; i++) {
			p = (*it).entry(i);
			type = board->getEntry(p.x, p.y);
			if (type == ET_PLAYER_ONE) p1s++;
			if (type == ET_EMPTY) {
				candidates.push_back(p);
				empties++;			
			}
		}
		if (p1s == player && empties == empty) {
			PointVec::const_iterator it2 = candidates.begin();
			for ( ; it2 != candidates.end(); ++it2) {
				weight = weightPoint(*it2);
				if (weight > maxWeight) {
					maxP = *it2;
					maxWeight = weight;
				}
			}
			matched = true;
		}
	}

	if (matched) {
		pt = maxP;
		return true;
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////
POINT Machine::blockMove() const
{
	/*
	 * Attempt to block an opponent on a maximally feasible opponent vector
	 */
	const Vector *v;
	uint32_t i, type;
	POINT p;

	if ((v = maxOpponentV()) == NULL)
		return NIL_MOVE;

	for (i = 0; i < VSIZE; i++) {
		p = v->entry(i);
		type = board->getEntry(p.x, p.y);
		if (type == ET_EMPTY) return p;
	}

	return NIL_MOVE;
}

/////////////////////////////////////////////////////////////////////////////
POINT Machine::randomMove() const
{
	EntryVec empty = board->empty();
	size_t size, n;

	srand((uint32_t)time(NULL));

	if ((size = empty.size()) > 0) {
		n = (size_t)(double)rand() / (RAND_MAX + 1) * (size-1);
		const Entry &entry = empty.at(n);
		return entry.where();
	}

	return NIL_MOVE;
}

/////////////////////////////////////////////////////////////////////////////
const Vector *Machine::maxOpponentV() const
{
	/* find an opponents maximally feasible vector */
	uint32_t type, i;
	POINT p;
	const Vector *maxV = NULL;
	float weight, maxWeight = MIN_WEIGHT;

	VecVec::const_iterator it = vectors.begin();
	for ( ; it != vectors.end(); it++) {
		for (i = 0, weight = 0; i < VSIZE; i++) {
			p = (*it).entry(i);
			type = board->getEntry(p.x, p.y);
			if (type == ET_PLAYER_ONE) {
				weight += PIECE_WEIGHT;
			}
			if (type == ET_PLAYER_TWO) break;	// not feasible
		}

		if (weight > maxWeight) {
			maxWeight = weight;
			maxV = &*it;
		}
	}

	return maxV;
}

/////////////////////////////////////////////////////////////////////////////
uint32_t Machine::contiguity(const Vector &v) const
{
	uint32_t i, type, cont = 0, maxCont = 0;
	POINT pt;

	for (i = 0; i < VSIZE; i++) {
		pt = v.entry(i);
		type = board->getEntry(pt.x, pt.y);
		switch (type) {
		case ET_PLAYER_TWO:
			cont++;
			break;
		case ET_EMPTY:
			if (cont > maxCont) {
				maxCont = cont;
			}
			cont = 0;
			break;
		}
	}

	if (cont > maxCont) {
		maxCont = cont;
	}

	return maxCont;
}

