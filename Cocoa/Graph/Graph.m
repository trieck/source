//
//  Graph.m
//  Graph
//
//  Created by Thomas Rieck on Sun Mar 24 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import "Graph.h"
#import "CocoaQueue.h"

#define maxV 400

static int visited[maxV];

@implementation Graph

- (id)init 
{
	if (self = [super init]) {
		vertices = [[NSMutableArray alloc] init];
	}
	return self;
}

- (unsigned)vertices
{
	return [vertices count];
}

- (void)dealloc
{
	[vertices release];
	[super dealloc];
}

- (int)path:(Vertex*)v toVertex:(Vertex*)w
{
	int t, vi, wi;
	
	for (t = 0; t < [vertices count]; t++) visited[t] = 0;
	
	vi = [vertices indexOfObject:v];
	wi = [vertices indexOfObject:w];
	
	return [self pathR:vi toVertex:wi];
}

- (int)pathR:(int)v toVertex:(int)w
{
	int t;
	Vertex *v1, *v2;
	
	if (v == w) return 1;
	visited[v] = 1;
	
	v1 = [vertices objectAtIndex:v];
	
	for (t = 0; t < [vertices count]; t++) {
		v2 = [vertices objectAtIndex:t];
		if ([v1 isEdge:v2])
			if (visited[t] == 0)
				if ([self pathR:t toVertex:w]) return 1;
	}
	
	return 0;
}

/*
 * breadth-first search
 */
- (void)bfs:(Edge*)edge
{
	CocoaQueue *queue = [[CocoaQueue alloc] init];
	Edge *e;
	
	[queue addObject:edge];
	while (![queue isEmpty]) {
		e = [queue removeObject];
		
	}
	
	[queue release];
}

- (void)clear
{
	[vertices removeAllObjects];
}

- (NSEnumerator*)enumVertices
{
	return [vertices objectEnumerator];
}

- (void)removeVertex:(Vertex*)v
{
	NSEnumerator *enumerator = [vertices objectEnumerator];
	Vertex *vertex;
	
	while (vertex = [enumerator nextObject]) {
		if (![vertex isEqual:v]) {
			if ([vertex isEdge:v] ) {
				[vertex removeEdge:v];
			}
		}
	}
	
	[vertices removeObject:v];
}

- (Vertex*)vertex:(NSPoint)pt
{	
	Vertex *v = [[Vertex alloc] initWithCoords:pt.x andCoord:pt.y];
	
	unsigned idx = [vertices indexOfObject:v];
	
	[v release];
	
	if (idx == NSNotFound)
		return nil;
		
	return [vertices objectAtIndex:idx];
}

- (void)addVertex:(NSPoint)pt
{
	Vertex *v = [[Vertex alloc] initWithCoords:pt.x andCoord:pt.y];
	unsigned idx = [vertices indexOfObject:v];
	if (idx == NSNotFound)
		[vertices addObject:v];
		
	[v release];
}

@end
