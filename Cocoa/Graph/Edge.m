//
//  Edge.m
//  Graph
//
//  Created by Thomas Rieck on Fri Mar 29 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import "Edge.h"

@implementation Edge

- (id)init
{
	return [self initWithVertex:0 toVertex:0];
}

- (id)initWithVertex:(Vertex*)vertex1 toVertex:(Vertex*)vertex2
{
	if (self = [super init]) {
		v = vertex1;
		w = vertex2;
		[v retain];		// should the edge retain vertices?
		[w retain];
	}
	
	return self;
}

- (void)dealloc
{
	[v release];
	[w release];
	[super dealloc];
}

@end
