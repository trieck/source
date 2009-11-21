//
//  Edge.h
//  Graph
//
//  Created by Thomas Rieck on Fri Mar 29 2002.
//  Copyright (c) 2001 Rieck Enterprises. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Vertex.h"

@interface Edge :
NSObject {
	Vertex *v, *w;
}

- (id)initWithVertex:
(Vertex*)v toVertex:
(Vertex*)w;

@end
