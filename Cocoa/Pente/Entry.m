//
//  Entry.m
//  Pente
//
//  Created by Thomas Rieck on 10/4/09.
//  Copyright 2009 Rieck Enterprises. All rights reserved.
//

#import "Entry.h"
#import "Board.h"

@implementation Entry

- (id)init
{
	return [self initWithCoords:0 :0 :ET_EMPTY];
}

- (id)initWithCoords:(uint32_t)x :(uint32_t)y :(uint32_t)ntype
{
	if (self = [super init]) {
		pt.h = x % BOARD_SIZE; 
		pt.v = y % BOARD_SIZE;
		type = ntype % (ET_PLAYER_TWO+1);
	}
	
	return self;
}

- (Point) where 
{
	return pt;
}

- (uint32_t) type
{
	return type;
}

- (void) setType :(uint32_t)ntype
{
	type = ntype % (ET_PLAYER_TWO+1);
}

- (unsigned)hash
{
	return pt.h * BOARD_SIZE + pt.v;
}

- (BOOL)isEqual:(id)object
{
	Point objectPt = [object where];
	if (memcmp(&pt, &objectPt, sizeof(Point)) == 0)
		return YES;
	return NO;
}


@end
