//
//  AdjacencyMatrix.m
//  Graph
//
//  Created by Thomas Rieck on Tue Mar 19 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import "AdjacencyMatrix.h"

static int** MATRIXint(int r, int c, int val);
static void MATRIXfree(int **M, int r);

@implementation AdjacencyMatrix

- (id)init
{
	return [self initWithCount:0];
}

- (id)initWithCount:(int)c
{
	if (self = [super init]) {
		count = c;
		adj = MATRIXint(count, count, 0);
	}
	
	return self;
}

- (BOOL)isEdge:(Vertex*)v andVertex:(Vertex*)w
{
	 unsigned i, j;
	 i = [v hash], j = [w hash];
	 
	 if (adj[i][j] == 1 && adj[j][i] == 1)
		return YES;

	return NO;
}

- (void)setEdge:(Vertex*)v toVertex:(Vertex*)w
{
	/* 
	 * The Vertex hash method has to be quaranteed to
	 * return a valid index into the adjacency matrix.
	 *
	 * This is assured by constructing the matrix
	 * so that there is space enough for all vertices
	 * ahead of time and assuring that each vertex
	 * hashes to a unique table location not exceeding
	 * a maximum vertex count.
	 *
	 */
	 unsigned i, j;
	 i = [v hash], j = [w hash];
	 adj[i][j] = adj[j][i] = 1;
}

- (void)removeEdge:(Vertex*)v toVertex:(Vertex*)w
{
	 unsigned i, j;
	 i = [v hash], j = [w hash];
	 adj[i][j] = adj[j][i] = 0;
}

- (void)dealloc
{
	MATRIXfree(adj, count);
	[super dealloc];
}

@end

/* 
 * matrix allocation and initialization
 */
int **MATRIXint(int r, int c, int val)
{
	int i, j;
	int **t = malloc(r * sizeof(int *));
	for (i = 0; i < r; i++) 
		t[i] = malloc(c * sizeof(int));
	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			t[i][j] = val;
	return t;
}

/* 
 * matrix reclaimation
 */
void MATRIXfree(int **M, int r)
{
	int i;
	for (i = 0; i < r; i++) 
		free(M[i]);
	
	free(M);
}
