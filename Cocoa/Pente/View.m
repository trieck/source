//
//  View.m
//  Pente
//
//  Created by Thomas Rieck on 10/1/09.
//  Copyright 2009 Rieck Enterprises. All rights reserved.
//

#import "View.h"
#import "Board.h"
#import "Entry.h"
#import "AppController.h"
#import "globals.h"

#define SCALE_FACTOR (10)
#define POLYGON_SIDES (17)

@interface View (private) 
- (void)drawWinner;
- (void)drawPieces;
- (void)drawPiece:(Entry*)entry;
- (void)makeGrid;
- (void)makePolygon;
- (NSRect)rectFromEntry:(uint32_t)x :(uint32_t)y;
- (NSPoint)pointFromEntry:(uint32_t)x :(uint32_t)y;
@end

@implementation View (private) 

- (void)drawWinner
{
	NSBezierPath *path;
	NSPoint pt1, pt2;
	Point vpt1, vpt2;
	
	NSAssert(winner != nil, @"winner == nil");
	vpt1 = [winner entry:0];
	vpt2 = [winner entry:VSIZE-1];
	
	pt1 = [self pointFromEntry:vpt1.h :vpt1.v];
	pt2 = [self pointFromEntry:vpt2.h :vpt2.v];
	
	[winnerColor set];
	
	path = [NSBezierPath bezierPath];
	[path setLineWidth:5];
	[path moveToPoint:pt1];
	[path lineToPoint:pt2];
	[path stroke];
}

- (void)drawPieces
{
	NSEnumerator *enumerator = [board enumEntries];
	Entry *entry;
	
	while ((entry = [enumerator nextObject])) {
		[self drawPiece :entry];
	}
}

- (void)drawPiece:(Entry*)entry
{
	Point where = [entry where];
	NSPoint to = [self pointFromEntry:where.h :where.v];
	
	NSRect rect = NSMakeRect(to.x-(squareSize.width/2), 
			   to.y-(squareSize.height/2), squareSize.width, squareSize.height);
	if ([self needsToDrawRect:rect]) {
		NSPoint origin = [self bounds].origin;
		[self translateOriginToPoint:to];
	
		[[NSColor blackColor] setStroke];
		[polygon stroke];
	
		if ([entry type] == ET_PLAYER_ONE) {
			[playerOneColor setFill];
		} else {
			[playerTwoColor setFill];
		}
		[polygon fill];
		[self setBoundsOrigin:origin];
	}
}

- (void)makeGrid
{
	int cx, dx, cy, dy;
	NSRect r = [self bounds];
	NSPoint pt;
	
	dx = round(NSWidth(r)) / BOARD_SIZE;
	dy = round(NSHeight(r)) / BOARD_SIZE;
	cx = round(NSMinX(r));
	cy = round(NSMinY(r));
	
	while (cx <= NSWidth(r)) {
		pt = NSMakePoint(cx, NSMinY(r));
		[grid moveToPoint:pt];
		
		pt = NSMakePoint(cx, NSMaxY(r));
		[grid lineToPoint:pt];
		
		cx += dx;
	}
	
	while (cy <= NSHeight(r)) {
		pt = NSMakePoint(NSMinX(r), cy);
		[grid moveToPoint:pt];
		
		pt = NSMakePoint(NSMaxX(r), cy);
		[grid lineToPoint:pt];
		
		cy += dy;
	} 
}

- (void) makePolygon
{ 
	NSAffineTransform *transform = [NSAffineTransform transform];
	[transform scaleBy:SCALE_FACTOR];
	
	if (polygon)
		[polygon release];
    
	polygon = [transform transformBezierPath:[NSBezierPath polygonWithSides:POLYGON_SIDES]];
	[polygon retain];
	
	[transform release];
}

- (NSRect) rectFromEntry:(uint32_t)x :(uint32_t)y
{
	return NSMakeRect(x * squareSize.width,
					  ((BOARD_SIZE-1)-y) * squareSize.height, 
					  squareSize.width, 
					  squareSize.height
	);
}

- (NSPoint) pointFromEntry:(uint32_t)x :(uint32_t)y
{
	return NSMakePoint(squareSize.width*x+(squareSize.width/2),
					   squareSize.height*((BOARD_SIZE-1)-y)+(squareSize.width/2)
	);
}

@end
@implementation View

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
		bkgndColor = [[NSColor 
					   colorWithDeviceRed: 255.0/255.0 
					   green: 255.0/255.0 
					   blue: 220.0/255.0 alpha: 1.0] retain];
		
		playerOneColor = [[NSColor 
					   colorWithDeviceRed: 0.0/255.0 
					   green: 100.0/255.0 
					   blue: 0.0/255.0 alpha: 1.0] retain];
		playerTwoColor = [[NSColor 
						   colorWithDeviceRed: 100.0/255.0 
						   green: 0.0/255.0 
						   blue: 0.0/255.0 alpha: 1.0] retain];
		
		winnerColor = [[NSColor  
						colorWithDeviceRed: 1.0 
						green: 183.0/255.0
						blue: 213.0/255.0 alpha: 0.5] retain];
		
		NSRect rect = [self bounds];
		squareSize = NSMakeSize(NSWidth(rect) / BOARD_SIZE,
							   NSHeight(rect) / BOARD_SIZE);
		board = [Board sharedManager];
		grid = [[NSBezierPath bezierPath] retain];
		winner = nil;
		[self makeGrid];
		[self makePolygon];
	}
    return self;
}

- (void) dealloc
{
	[polygon release];
	[grid release];
	[board release];
	[bkgndColor release];
	[playerOneColor release];
	[playerTwoColor release];
	[super dealloc];
}

- (void)drawRect:(NSRect)rect 
{
	[bkgndColor set];
	[NSBezierPath fillRect:rect];
	
	[[NSColor gridColor] set];
	[grid stroke];
	
	[self drawPieces];
	
	if (winner != nil) {
		[self drawWinner];
	}
}

- (void)mouseDown:(NSEvent *)event
{
	NSPoint pt;
	Point p;
	uint32_t x, y;
	
	pt = [event locationInWindow];
	pt = [self convertPoint:pt fromView:nil];		// convert point to view coordinates
	x = pt.x / squareSize.width;
	y = (BOARD_SIZE-1) - (int)(pt.y / squareSize.height);		// translate coordinates
	
	if ([board entry:x :y] == ET_EMPTY) {
		[board setEntry:x :y :ET_PLAYER_ONE];
		[self redrawSquare:x :y];
		
		p = [appController move];
		if (!isNilMove(p)) {
			[self redrawSquare:p.h :p.v];
		}
	}
}

- (void) redrawSquare:(uint32_t)x :(uint32_t)y
{
	NSRect rect = rect = [self rectFromEntry:x :y];
	[self setNeedsDisplayInRect:rect];
}

- (void)setWinner:(Vector *)vector
{
	winner = vector;
	[self setNeedsDisplay:YES];
}

@end

