//
//  Graph.h
//  Graph
//
//  Created by Thomas Rieck on Sun Mar 24 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Vertex.h"
#import "Edge.h"

@interface Graph :
NSObject {
    NSMutableArray *vertices;
}

- (int)path:
(Vertex*)v toVertex:
(Vertex*)w;
- (int)pathR:
(int)v toVertex:
(int)w;
- (void)bfs:
(Edge*)edge;
- (unsigned)vertices;
- (void)clear;
- (NSEnumerator*)enumVertices;
- (Vertex*)vertex:
(NSPoint)pt;
- (void)addVertex:
(NSPoint)pt;
- (void)removeVertex:
(Vertex*)v;

@end
