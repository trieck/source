/*
 *  globals.m
 *  Pente
 *
 *  Created by Thomas Rieck on 10/5/09.
 *  Copyright 2009 Rieck Enterprises. All rights reserved.
 *
 */

#import <Cocoa/Cocoa.h>
#import "globals.h"

const Point NIL_MOVE = { SHRT_MIN, SHRT_MIN };

BOOL isNilMove(Point pt)
{
	return isEqualPoint(pt, NIL_MOVE);
}

BOOL isEqualPoint(Point pt1, Point pt2)
{
	return memcmp(&pt1, &pt2, sizeof(Point)) == 0;
}
