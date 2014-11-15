//
//  GraphView.h
//  Graph
//
//  Created by Thomas Rieck on Fri Mar 15 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import <AppKit/AppKit.h>
#import "Vertex.h"

@class AppController;

@interface GraphView :
NSView {
    NSBezierPath *grid;				// grid bezier path
    AppController *appController;	// controller
}

// Methods
- (void)makeGrid;
- (void)drawVertices;
- (void)drawEdges;
- (NSPoint)vertexCenter:
(Vertex*)v;

@end
