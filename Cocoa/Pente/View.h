//
//  View.h
//  Pente
//
//  Created by Thomas Rieck on 10/1/09.
//  Copyright 2009 Rieck Enterprises. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Board.h"
#import "RegularPolygon.h"
#import "Vector.h"

@class AppController;

@interface View :
NSView {
	NSBezierPath *grid;				// grid bezier path
	NSBezierPath *polygon;
	Board *board;					// board
	AppController *appController;	// controller
	NSSize squareSize;
	NSColor *bkgndColor, *playerOneColor, *playerTwoColor, *winnerColor;
	Vector *winner;
}

- (void) redrawSquare:
(uint32_t)x :
(uint32_t)y;
- (void) setWinner:
(Vector*)winner;

@end
