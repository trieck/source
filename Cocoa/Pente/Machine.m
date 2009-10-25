//
//  Machine.m
//  Pente
//
//  Created by Thomas Rieck on 9/30/09.
//  Copyright 2009 Rieck Enterprises. All rights reserved.
//

#import "Machine.h"
#import "Entry.h"
#import "Board.h"
#import "Vector.h"
#include "globals.h"

static const float MIN_WEIGHT = -FLT_MIN;
static const float MAX_WEIGHT = FLT_MAX;
static const float PIECE_WEIGHT = 1.0f;
static const float CONT_WEIGHT = 0.5f;
static const uint32_t CENTER = (BOARD_ENTRIES + 1) / 2 - 1;
static const uint32_t MEAN_POINT = VSIZE/2;

/* private methods */
@interface Machine(private)
	- (void) generate;
	- (float) weightVector:(Vector*)v;
	- (float) weightPoint:(Point)pt;
	- (BOOL)center:(Vector*)v;
	- (Point)bestMove:(Vector*)v;
	- (Point)mustBlock;
	- (Point)blockMove;
	- (Point)randomMove;
	- (Vector*)maxOpponentV;
	- (uint32_t)contiquity:(Vector*)v;
@end
	
@implementation Machine

- (id)init 
{
	if (self = [super init]) {
		vectors = [[NSMutableArray alloc] init];
		board = [Board sharedManager];
		[self generate];
	}
	return self;
}

- (void)dealloc
{
	[vectors release];
	[board release];
	[super dealloc];
}

- (Point)move
{
	float nweight, maxWeight = MIN_WEIGHT;
	NSEnumerator *enumerator;
	Vector *vector, *maxV = nil;
	Point block, pt = NIL_MOVE;
	
	enumerator = [vectors objectEnumerator];
	while (vector = [enumerator nextObject]) {
		nweight = [self weightVector:vector];
		if (nweight > maxWeight) {
			maxWeight = nweight;
			maxV = vector;
		}
	}
	
	block = [self mustBlock];
	if (maxWeight == MIN_WEIGHT && isNilMove(block)) { // no feasible strategy found
		pt = [self blockMove];	
		if (isNilMove(pt)) {
			pt = [self randomMove];	// try a random move
		}
	}
	
	// check if we must block
	if (!isNilMove(block) && maxWeight < MAX_WEIGHT) {
		pt = block;
	} else if (maxV != nil) {	
		pt = [self bestMove:maxV];
	}
	
	// mark the board
	if (!isNilMove(pt)) {
		[board setEntry:pt.h :pt.v :ET_PLAYER_TWO];
	}
	
	return pt;
}

- (Vector*)winner:(uint32_t *)ptype
{
	NSEnumerator *enumerator;
	Vector *vector;
	Point p;
	uint32_t type, i, onecount, twocount;
	
	*ptype = ET_EMPTY;
	enumerator = [vectors objectEnumerator];
	while (vector = [enumerator nextObject]) {
		for (i = 0, onecount = 0, twocount = 0; i < VSIZE; i++) {
			p = [vector entry:i];
			type = [board entry:p.h :p.v];
			if (type == ET_PLAYER_ONE) { onecount++; }
			if (type == ET_PLAYER_TWO) { twocount++; }
		}
		
		if (onecount == VSIZE) {
			*ptype = ET_PLAYER_ONE;
			return vector;
		}
		
		if (twocount == VSIZE) {
			*ptype = ET_PLAYER_TWO;
			return vector;
		}
	}
	
	return nil;
}

@end

@implementation Machine(private)

/* determine the weight of a vector */
- (float) weightVector:(Vector*)v
{
	float weight = 0, d;
	uint32_t type, i, m, n, x, y;
	
	Point pt;
	for (i = 0; i < VSIZE; i++) {
		pt = [v entry:i];
		type = [board entry:pt.h :pt.v];
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
		pt = [v entry:i];
		type = [board entry:pt.h :pt.v];
		if (type == ET_PLAYER_TWO) {
			weight += [self weightPoint:pt];
		}
	}
	
	// add weighted distance from center
	pt = [v entry:MEAN_POINT];
	m = pt.h; n = pt.v;
	x = CENTER / BOARD_SIZE; y = CENTER % BOARD_SIZE;
	d = abs(x - m) + abs(y - n) + 1;
	weight += 1/d;
	
	// add weighted contiguity
	weight += CONT_WEIGHT * [self contiquity:v];
	
	return weight;
}

 /* 
 * Determine weight of a square
 * By the number of maximally feasible vectors
 * it is contained in.
 */
- (float)weightPoint:(Point)pt 
{
	float weight = 0, vweight;
	NSEnumerator *enumerator;
	Vector *vector;
	Point p;
	uint32_t i;
	
	if ([board entry :pt.h :pt.v] != ET_EMPTY)
		return MIN_WEIGHT;
	
	enumerator = [vectors objectEnumerator];
	while (vector = [enumerator nextObject]) {
		for (i = 0; i < VSIZE; i++) {
			p = [vector entry:i];
			if (isEqualPoint(pt, p)) break;
		}
		
		if (i < VSIZE) {
			vweight = [self weightVector:vector];
			weight += MAX(0, vweight);
		}
	}
		
	return weight;
}

/* 
 * Determine square where we must block
 * where the vector contains VSIZE-1 ET_PLAYER_ONE and one ET_EMPTY
 */
-(Point)mustBlock
{
	Point p, q, b, maxP = NIL_MOVE;
	uint32_t i, type, onecount, ecount;
	float weight, maxWeight = MIN_WEIGHT;
	
	NSEnumerator *enumerator;
	Vector *vector;
	
	enumerator = [vectors objectEnumerator];
	while (vector = [enumerator nextObject]) {
		for (i = 0, onecount = 0, ecount = 0; i < VSIZE; i++) {
			p = [vector entry:i];
			type = [board entry:p.h :p.v];
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
			weight = [self weightPoint:b];
			if (weight > maxWeight) {
				maxP = b;
				maxWeight = weight;
			}
		}
		
		// block contiguous with open ends
		if (onecount == VSIZE-2 && ecount == 2) {
			p = [vector entry:0]; q = [vector entry:VSIZE-1];
			
			if ([board entry :p.h :p.v] == ET_EMPTY &&
				[board entry :q.h :q.v] == ET_EMPTY) {
				weight = [self weightPoint:b];
				if (weight > maxWeight) {
					maxP = b;
					maxWeight = weight;
				}
			}
		}
	}
		
	return maxP;
}

// does vector contain an empty center?
- (BOOL)center:(Vector*)vector
{
	uint32_t i, piece;
	Point p;
	
	for (i = 0; i < VSIZE; i++) {
		p = [vector entry:i];
		piece = p.h * BOARD_SIZE + p.v;
		if ((piece == CENTER) && [board entry:p.h :p.v] == ET_EMPTY)
			return YES;
	}
	
	return NO;
}

- (Point)bestMove:(Vector*)vector
{
	float weight, maxWeight = MIN_WEIGHT;
	Point p, maxP = NIL_MOVE;
	uint32_t i;
	
	if ([self center:vector]) {
		Point c = { CENTER / BOARD_SIZE, CENTER % BOARD_SIZE };
		return c;
	}

	// try to find an adjacent move
	for (i = 0; i < VSIZE; i++) {
		p = [vector entry:i];		
		if (i < VSIZE-1 && [board entry:p.h :p.v] == ET_PLAYER_TWO) {
			p = [vector entry:i+1];
			if ([board entry:p.h :p.v] == ET_EMPTY) {
				if ((weight = [self weightPoint:p]) > maxWeight) {
					maxWeight = weight;
					maxP = p;
				}
			}
		}
		
		if (i > 0 && [board entry:p.h :p.v] == ET_PLAYER_TWO) {
			p = [vector entry:i-1];
			if ([board entry:p.h :p.v] == ET_EMPTY) {
				if ((weight = [self weightPoint:p]) > maxWeight) {
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
		p = [vector entry:i];					
		if ([board entry:p.h :p.v] == ET_EMPTY) {
			if ((weight = [self weightPoint:p]) > maxWeight) {
				maxWeight = weight;
				maxP = p;
			}
		}
	}
	
	return maxP;
}

/* find an opponents maximally feasible vector */
- (Vector*)maxOpponentV
{
	NSEnumerator *enumerator;
	Vector *vector, *maxV = nil;
	Point p;
	float weight, maxWeight = MIN_WEIGHT;
	uint32_t type, i;
	
	enumerator = [vectors objectEnumerator];
	while (vector = [enumerator nextObject]) {
		for (i = 0, weight = 0; i < VSIZE; i++) {
			p = [vector entry:i];
			type = [board entry:p.h :p.v];
			if (type == ET_PLAYER_ONE) { weight += PIECE_WEIGHT; }
			if (type == ET_PLAYER_TWO) break;	// not feasible
		}
		
		if (weight > maxWeight) {
			maxWeight = weight;
			maxV = vector;
		}
	}
	
	return maxV;
}

/*
 * Attempt to block an opponent on a maximally feasible opponent vector
 */
- (Point)blockMove
{
	Vector *v;
	uint32_t i, type;
	Point p;
	
	if ((v = [self maxOpponentV]) == nil)
		return NIL_MOVE;
	
	for (i = 0; i < VSIZE; i++) {
		p = [v entry:i];
		type = [board entry:p.h :p.v];
		if (type == ET_EMPTY) return p;
	}
	
	return NIL_MOVE;
}

- (Point)randomMove
{
	NSArray *empty = [board empty];
	Entry *entry;
	uint32_t size, n;
	
	srandom(time(NULL));
	
	if ((size = [empty count]) != 0) {
		n = random() % size;
		entry = [empty objectAtIndex:n];
		return [entry where];
	}
	
	return NIL_MOVE;
}

/* determine the contiguity for a vector */
- (uint32_t)contiquity:(Vector*)v
{
	uint32_t i, type, cont = 0, maxCont = 0;
	Point pt;
	
	for (i = 0; i < VSIZE; i++) {
		pt = [v entry:i];
		type = [board entry:pt.h :pt.v];
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


/* generate all initially feasible vectors */
- (void)generate
{
	uint32_t i, j, m, n;
	
	Vector *v;
	
	for (i = 0; i < BOARD_ENTRIES; i++) {
		m = i / BOARD_SIZE;
		n = i % BOARD_SIZE;
		
		// check for horizontal vector
		if (VSIZE + n <= BOARD_SIZE) {
			v = [[Vector alloc] init];
			for (j = 0; j < VSIZE; j++) {
				[v setEntry:j :m :n+j];
			}
			[vectors addObject:v];
		}
		
		// check for vertical vector
		if (VSIZE + m <= BOARD_SIZE) {
			v = [[Vector alloc] init];
			for (j = 0; j < VSIZE; j++) {
				[v setEntry:j :m+j :n];
			}
			[vectors addObject:v];
		}
		
		// check for a "diagonal down" vector
		if (VSIZE + m <= BOARD_SIZE && VSIZE + n <= BOARD_SIZE) {
			v = [[Vector alloc] init];
			for (j = 0; j < VSIZE; j++) {
				[v setEntry:j :m+j :n+j];
			}
			[vectors addObject:v];
		}
		
		// check for a "diagonal up" vector
		if (m >= VSIZE - 1 && VSIZE + n <= BOARD_SIZE) {
			v = [[Vector alloc] init];
			for (j = 0; j < VSIZE; j++) {
				[v setEntry:j :m-j :n+j];
			}
			[vectors addObject:v];	
		}
	}
}

@end
