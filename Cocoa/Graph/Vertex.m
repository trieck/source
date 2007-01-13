//
//  Vertex.m
//  Graph
//
//  Created by Thomas Rieck on Sat Mar 16 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import "Vertex.h"

static const int VERTEX_CX = 20;
static const int VERTEX_CY = 20;

@implementation Vertex

- (id)init
{
	return [self initWithCoords:0 andCoord:0];
}

- (id)initWithCoords:(int)cx andCoord:(int)cy
{
	if (self = [super init]) {
		x = cx, y = cy;
		selected = NO;
		edges = [[NSMutableArray alloc] init];
		[self setColor:[NSColor orangeColor]];
		[self makeVertex];
	}
	return self;
}

- (int)x
{
	return x;
}

- (int)y
{
	return y;
}

+ (int)cx
{
	return VERTEX_CX;
}

+ (int)cy 
{
	return VERTEX_CY;
}

- (unsigned)hash
{
	return x * VERTEX_CY + y;
}

- (BOOL)isEqual:(id)object
{
	if ([object x] == x && [object y] == y)
		return YES;
		
	return NO;
}

- (void) makeVertex
{
	int cx = x * VERTEX_CX;
	int cy = y * VERTEX_CY;
			
	NSRect rect = NSMakeRect(cx, cy, VERTEX_CX, VERTEX_CY);
	rect = [Vertex inflateRect:rect  dx:-2 dy:-2];
	
	[path release];
	path = [[NSBezierPath alloc] init];
	[path appendBezierPathWithOvalInRect:rect];
}

- (void)draw
{
	[color set];
	[path fill];
}

- (NSEnumerator*)enumEdges
{
	return [edges objectEnumerator];
}

- (void)dealloc
{
	[edges release];
	[color release];
	[path release];
	[super dealloc];
}

- (void)setColor:(NSColor*)c
{
	[color release];
	color = [c copy];
}

- (void)select
{
	NSColor *c;
	
	selected = selected == YES ? NO : YES;
	c = selected ? [NSColor redColor] : [NSColor orangeColor];
	
	[self setColor:c];
}

- (BOOL)selected
{
	return selected;
}

- (void)setEdge:(Vertex*)v
{
	// check whether the edge exists
	unsigned index = [edges indexOfObject:v];
	if (index == NSNotFound) {
		[edges addObject:v];
	}
}

- (BOOL)removeEdge:(Vertex*)v
{
	unsigned index = [edges indexOfObject:v];
	if (index == NSNotFound)
		return NO;
		
	[edges removeObjectAtIndex:index];
	
	return YES;
}

- (BOOL)isEdge:(Vertex*)v
{
	return [edges indexOfObject:v] != NSNotFound;
}

/*
 * inflate rectangle based on dx and dy
 */
+ (NSRect) inflateRect:(NSRect) rect dx:(float)dx dy:(float)dy
{
	float cx = NSMinX(rect) + -dx;
	float cy = NSMinY(rect) + -dy;
	float ddx = NSWidth(rect) + dx + dx;
	float ddy = NSHeight(rect) + dy + dy;
	
	return NSMakeRect(cx, cy, ddx, ddy);
}

@end

