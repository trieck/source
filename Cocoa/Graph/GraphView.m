//
//  GraphView.m
//  Graph
//
//  Created by Thomas Rieck on Fri Mar 15 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import "GraphView.h"
#import "Vertex.h"
#import "AppController.h"

@implementation GraphView

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
		grid = [[NSBezierPath alloc] init];
		[self makeGrid];
    }
    return self;
}

- (void)drawRect:(NSRect)rect {

	[[NSColor whiteColor] set];
	[NSBezierPath fillRect:[self bounds]];
	
	[[NSColor lightGrayColor] set];
	[grid stroke];
	[self drawVertices];
	[self drawEdges];
}

- (void)makeGrid
{
	int cx, dx, cy, dy;
	NSRect r = [self bounds];
	NSPoint pt;
	
	dx = round(NSWidth(r)) / [Vertex cx];
	dy = round(NSHeight(r)) / [Vertex cy];
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

- (void)drawVertices
{
	NSEnumerator *enumerator = [[appController graph] enumVertices];
	Vertex *vertex;
	
	while ((vertex = [enumerator nextObject])) {
		[vertex draw];
	}
}

- (void)drawEdges
{
	NSEnumerator *V, *E;
	Vertex *vertex, *edge;
	NSPoint pt1, pt2;
	
	[[NSColor blueColor] set];
	
	V = [[appController graph] enumVertices];
	
	while (vertex = [V nextObject]) {
		E = [vertex enumEdges];
		while (edge = [E nextObject]) {
			if ([edge hash] < [vertex hash])
				continue;	// lower order vertex already drawn edge
				
			pt1 = [self vertexCenter:vertex];
			pt2 = [self vertexCenter:edge];
			
			[NSBezierPath strokeLineFromPoint:pt1 toPoint:pt2];
		}
	}
}

- (void)mouseDown:(NSEvent *)event
{
	NSPoint pt = [event locationInWindow];
	unsigned flags = [event modifierFlags];
	int x, y;
	
	pt = [self convertPoint:pt fromView:nil];		// convert point to view coordinates
	x = round(pt.x) / [Vertex cx];
	y = round(pt.y) / [Vertex cy];
	
	[appController selection:flags atPoint:NSMakePoint(x, y)];
	
	[self setNeedsDisplay:YES];
}

- (void)dealloc
{	
	// Something is not right, I should not have
	// to release the appController since it was
	// set up in Interface builder.  There is a general
	// circular reference problem that needs to be fixed,
	// but I don't understand the problem well enough yet.
	[appController release];
	
	[grid release];
	[super dealloc];
}

- (NSPoint)vertexCenter:(Vertex*)v
{
	int x, y, cx, cy;
	
	cx = [Vertex cx];
	cy = [Vertex cy];
	
	x = [v x] * cx + cx / 2;
	y = [v y] * cy + cy / 2;
	
	return NSMakePoint(x, y);
}

@end
