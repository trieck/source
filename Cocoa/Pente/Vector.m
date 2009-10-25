//
//  Vector.m
//  Pente
//
//  Created by Thomas Rieck on 9/30/09.
//  Copyright 2009 Rieck Enterprises. All rights reserved.
//

#import "Vector.h"

@implementation Vector

- (id)init 
{
	if (self = [super init]) {
		memset(v, 0, sizeof(Point) * VSIZE);
	}
	return self;
}

- (Point)entry:(uint32_t)index
{
	return v[index % VSIZE];
}

- (void)setEntry:(uint32_t)index :(uint32_t)m :(uint32_t)n
{
	Point pt;
	pt.v = m; pt.h = n;
	v[index % VSIZE] = pt;
}

@end
