//
//  Vertex.h
//  Graph
//
//  Created by Thomas Rieck on Sat Mar 16 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface Vertex :
NSObject {
    BOOL selected;			// is selected?
    int x, y;				// coordinates
    NSBezierPath *path;		// path
    NSColor *color;			// color of vertex
    NSMutableArray *edges;	// array of edges
}

- (id)initWithCoords:
(int)cx andCoord:
(int)cy;
- (int)x;
- (int)y;
- (void)makeVertex;
- (void)draw;
- (void)setColor:
(NSColor*)c;
- (void)select;
- (BOOL)selected;
- (void)setEdge:
(Vertex*)v;
- (BOOL)isEdge:
(Vertex*)v;
- (BOOL)removeEdge:
(Vertex*)v;
- (NSEnumerator*)enumEdges;

+ (int)cx;
+ (int)cy;
+ (NSRect)inflateRect:
(NSRect) rect dx:
(float)dx dy:
(float)dy;

@end

