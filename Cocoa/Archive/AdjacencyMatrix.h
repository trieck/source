//
//  AdjacencyMatrix.h
//  Graph
//
//  Created by Thomas Rieck on Tue Mar 19 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Vertex.h"

@interface AdjacencyMatrix : NSObject {
	int **adj;	// representation
	int count;	// entries
}

- (id)initWithCount:(int)c;
- (BOOL)isEdge:(Vertex*)v andVertex:(Vertex*)w;
- (void)setEdge:(Vertex*)v toVertex:(Vertex*)w;
- (void)removeEdge:(Vertex*)v toVertex:(Vertex*)w;

@end
